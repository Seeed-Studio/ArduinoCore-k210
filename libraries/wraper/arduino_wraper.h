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


#ifndef __ARDUINO_WRAPPER_H
#define __ARDUINO_WRAPPER_H
#include <stddef.h>
#include <stdint.h>
#define NO_GLOBAL_INSTANCES 1

#ifdef __cplusplus
extern "C"{
#endif
typedef struct serial_struct_builder  serial_struct;

bool arduino_serial_new(serial_struct** serial);
void arduino_serial_begin(serial_struct* serial, unsigned long baudrate , int uart_num_ , int rx_pin_, int tx_pin_);
void arduino_serial_end(serial_struct* serial);
int arduino_serial_available(serial_struct* serial);
int arduino_serial_peek(serial_struct* serial);
int arduino_serial_read(serial_struct* serial,void *buf_in, uint32_t size);
size_t arduino_serial_write(serial_struct* serial,const void *buf_in, uint32_t size);
void arduino_serial_flush(serial_struct* serial);

#ifdef __cplusplus
};
#endif

#endif //__ARDUINO_WRAPPER_H