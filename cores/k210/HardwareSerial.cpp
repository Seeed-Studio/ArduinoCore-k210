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
HardwareSerial Serial(UART_DEVICE_1,4,5);
HardwareSerial Serial1(UART_DEVICE_2,6,7);
#endif

#define UART_BRATE_CONST 16
#define RINGBUFF_LEN 64
/**
 * @description:
 * @param {type}
 * @return:
 */
HardwareSerial::HardwareSerial(uart_device_number_t uart_num_ , int rx_pin_, int tx_pin_) {
    _uart_num = uart_num_;
    _rx_pin = rx_pin_;
    _tx_pin = tx_pin_;
}

int HardwareSerial::on_irq_recv_callback_(void *userdata) {
    char data;
    auto &driver = *reinterpret_cast<HardwareSerial *>(userdata);
    uart_receive_data(driver.uart, &data, 1);
    driver.rb_->store_char(data);

    #ifdef FREERTOS
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(driver.receive_event_, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) {
        vTaskSwitchContext();                                       
        // vPortYieldFromISR();
    }
    #endif
    return 0;
}

void HardwareSerial::init_(unsigned long baudrate, uint16_t config, uart_device_number_t uart_num, int rx_pin, int tx_pin) {
    fpioa_set_function(rx_pin, pin_map[rx_pin].PinType[PIO_UART]);
    fpioa_set_function(tx_pin, pin_map[tx_pin].PinType[PIO_UART]);

    uart_init(uart_num);
    uart_configure(uart_num, baudrate, UART_BITWIDTH_8BIT, uart_stopbit_t((config & SERIAL_STOP_BIT_MASK) >> 4),
                   uart_parity_t(config & SERIAL_PARITY_MASK));

    uart_set_receive_trigger(uart_num, UART_RECEIVE_FIFO_8);
    uart_irq_register(uart_num, UART_RECEIVE, on_irq_recv_callback_, this, 2);

    #ifdef FREERTOS
    receive_event_ = xSemaphoreCreateBinary();
    #endif

    rb_ = new RingBuffer();
    rb_->clear();

    uart = uart_num;
}

/**
 * @description:
 * @param {type}
 * @return:
 */
void HardwareSerial::begin(unsigned long baudrate) {
    init_(baudrate, SERIAL_8N1, _uart_num, _rx_pin, _tx_pin);
}

/**
 * @description:
 * @param {type}
 * @return:
 */
void HardwareSerial::begin(unsigned long baudrate, uint16_t config) {
    init_(baudrate, config, _uart_num, _rx_pin, _tx_pin);
}

/**
 * @description:
 * @param {type}
 * @return:
 */
void HardwareSerial::end() { delete rb_; }

/**
 * @description:
 * @param {type}
 * @return:
 */
int HardwareSerial::available(void) { return rb_->available(); }

/**
 * @description:
 * @param {type}
 * @return:
 */
int HardwareSerial::peek(void) { return rb_->peek(); }

/**
 * @description:
 * @param {type}
 * @return:
 */
int HardwareSerial::read(void) {
    while (true) {
        if (0 != rb_->available()) {
            return rb_->read_char();
        } else {
            #ifdef FREERTOS
            if (xSemaphoreTake(receive_event_, read_timeout_) == pdTRUE) {
                continue;
            } else {
                return -1;
            }
            #else
            return -1;
            #endif

        }
    }
}

/**
 * @description:
 * @param {type}
 * @return:
 */
void HardwareSerial::flush(void) { rb_->clear(); }

/**
 * @description:
 * @param {type}
 * @return:
 */
size_t HardwareSerial::write(uint8_t c) { return uart_send_data(uart, (char *)&c, 1); }

/**
 * @description:
 * @param {type}
 * @return:
 */
HardwareSerial::operator bool() const { return true; }
