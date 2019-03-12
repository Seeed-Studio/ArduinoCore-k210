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
HardwareSerial Serial(0);
#endif

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
HardwareSerial::HardwareSerial(int uart_nr): _uart_nr(uart_nr) {

}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void HardwareSerial::begin(unsigned long baudrate){
    char uart_str[14];
    sprintf(uart_str,"/dev/uart%d", _uart_nr);
    file = io_open(uart_str);


}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void HardwareSerial::begin(unsigned long baudrate, uint16_t config){
    char uart_str[14];
    sprintf(uart_str,"/dev/uart%d", _uart_nr);
    file = io_open(uart_str);
   // COMMON_ENTRY(uart);
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void HardwareSerial::end(){

}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int HardwareSerial::available(void){
    return 0;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int HardwareSerial::peek(void){
    return 0;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int HardwareSerial::read(void){
    return 0;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void HardwareSerial::flush(void){

}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
size_t HardwareSerial::write(uint8_t){
    return 0;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
HardwareSerial::operator bool() const{
    return true;
}