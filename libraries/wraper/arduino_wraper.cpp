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
#include "arduino_wraper.h"
#include "HardwareSerial.h"




bool arduino_serial_new(serial_struct** serial){
    HardwareSerial *Serial = new  HardwareSerial();
    if(Serial == NULL)
        return false;
    *serial = (serial_struct*)Serial;
    return true;
}

static bool arduino_serial_delete(serial_struct* serial){
    HardwareSerial *Serial = (HardwareSerial *)serial;
    if(Serial != NULL){
        delete Serial;
        return true;
    }
    return false;
}

#define Serial ((HardwareSerial *)serial)
void arduino_serial_begin(serial_struct* serial,unsigned long baudrate , int uart_num_ , int rx_pin_, int tx_pin_){
     Serial->begin(baudrate, (uart_device_number_t)uart_num_, rx_pin_, tx_pin_);
}

void arduino_serial_end(serial_struct* serial){
    Serial->end();
    arduino_serial_delete(serial);
}

int arduino_serial_available(serial_struct* serial){
    return Serial->available();    
}

int arduino_serial_peek(serial_struct* serial){
    return Serial->peek();        
}

int arduino_serial_read(serial_struct* serial,void *buf_in, uint32_t size){
    return Serial->readBytes((char*)buf_in,size);    
}

size_t arduino_serial_write(serial_struct* serial, const void *buf_in, uint32_t size){
    return Serial->write(( const uint8_t *)buf_in,size);     
}

void arduino_serial_flush(serial_struct* serial){
    Serial->flush();      
}
#undef Serial 