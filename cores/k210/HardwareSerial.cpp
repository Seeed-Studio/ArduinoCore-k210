/**
 * The MIT License (MIT)
 * 
 * Author: Baozhu Zuo (baozhu.zuo@gmail.com)
 * 
 * Copyright (C) 2019  Seeed Technology Co.,Ltd. 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "HardwareSerial.h"

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL)
HardwareSerial Serial(UART1_BASE_ADDR, SYSCTL_CLOCK_UART1, IRQN_UART1_INTERRUPT);
#endif


#define UART_BRATE_CONST 16
#define RINGBUFF_LEN 64
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
HardwareSerial::HardwareSerial(uintptr_t base_addr, sysctl_clock_t clock, plic_irq_t irq):
                            uart_(*reinterpret_cast<volatile uart_t *>(base_addr)), clock_(clock), irq_(irq) {

}


void HardwareSerial::on_irq_recv_callback_(void *userdata)
{
    auto &driver = *reinterpret_cast<HardwareSerial *>(userdata);
    auto &uart = driver.uart_;

    while (uart.LSR & 1)
    {
        driver.rb_->store_char(((uint8_t)(uart.RBR & 0xff)));
    }
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(driver.receive_event_, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken)
    {
        portYIELD_FROM_ISR();
    }
}


void HardwareSerial::init_(){
    receive_event_ = xSemaphoreCreateBinary();

    sysctl_clock_enable(clock_);
    pic_set_irq_handler(irq_, on_irq_recv_callback_, this);
    rb_ = new RingBuffer();
    rb_->clear();
    pic_set_irq_priority(irq_, 1);
    pic_set_irq_enable(irq_, 1);    
}


void HardwareSerial::ParameterConfig_(uint32_t baud_rate, uint32_t databits, uart_stopbits_t stopbits, uart_parity_t parity) {
    configASSERT(databits >= 5 && databits <= 8);
    if (databits == 5)
    {
        configASSERT(stopbits != UART_STOP_2);
    }
    else
    {
        configASSERT(stopbits != UART_STOP_1_5);
    }

    uint32_t stopbit_val = stopbits == UART_STOP_1 ? 0 : 1;
    uint32_t parity_val = 0;
    switch (parity)
    {
    case UART_PARITY_NONE:
        parity_val = 0;
        break;
    case UART_PARITY_ODD:
        parity_val = 1;
        break;
    case UART_PARITY_EVEN:
        parity_val = 3;
        break;
    default:
        configASSERT(!"Invalid parity");
        break;
    }

    uint32_t freq = sysctl_clock_get_freq(clock_);
    uint32_t u16Divider = (freq + UART_BRATE_CONST * baud_rate / 2) / (UART_BRATE_CONST * baud_rate);

    /* Set UART registers */
    uart_.TCR &= ~(1u);
    uart_.TCR &= ~(1u << 3);
    uart_.TCR &= ~(1u << 4);
    uart_.TCR |= (1u << 2);
    uart_.TCR &= ~(1u << 1);
    uart_.DE_EN &= ~(1u);

    uart_.LCR |= 1u << 7;
    uart_.DLL = u16Divider & 0xFF;
    uart_.DLH = u16Divider >> 8;
    uart_.LCR = 0;
    uart_.LCR = (databits - 5) | (stopbit_val << 2) | (parity_val << 3);
    uart_.LCR &= ~(1u << 7);
    uart_.MCR &= ~3;
    uart_.IER = 1;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void HardwareSerial::begin(unsigned long baudrate){
    init_();
    ParameterConfig_(baudrate,8,UART_STOP_1, UART_PARITY_NONE);
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void HardwareSerial::begin(unsigned long baudrate, uint16_t config){
    init_();
    ParameterConfig_(baudrate,8,UART_STOP_1, UART_PARITY_NONE);
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void HardwareSerial::end(){
    sysctl_clock_disable(clock_);
    delete rb_;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int HardwareSerial::available(void){
    return rb_->available();
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int HardwareSerial::peek(void){
    return rb_->peek();
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int HardwareSerial::read(void){
    while(true){
        if(0 != rb_->available()){
            return rb_->read_char();
        }
        else{
            if(xSemaphoreTake(receive_event_, read_timeout_) == pdTRUE){
                continue;
            }
            else{
                return -1;
            }
        }
    }
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void HardwareSerial::flush(void){
    rb_->clear();
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
size_t HardwareSerial::write(uint8_t c){
    while (!(uart_.LSR & (1u << 6)))
        ;
    uart_.THR = c;
    return 1;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
HardwareSerial::operator bool() const{
    return true;
}