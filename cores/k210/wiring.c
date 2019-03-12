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
#include "devices.h"
#include <FreeRTOS.h>
#include <task.h>
volatile unsigned long timer0_overflow_count = 0;
volatile unsigned long timer0_millis = 0;


handle_t gio;

// the whole number of milliseconds per timer0 overflow
#define MILLIS_INC 1000

/**
 * Description: Returns the number of milliseconds passed since the Arduino 
 * board began running the current program. This number will overflow (go 
 * back to zero), after approximately 50 days.
*/
unsigned long millis(){
    return timer0_millis;
}

/**
 * Description: Returns the number of microseconds since the Arduino board 
 * began running the current program. This number will overflow (go back to
 *  zero), after approximately 70 minutes. On 16 MHz Arduino boards (e.g. 
 * Duemilanove and Nano), this function has a resolution of four microseconds 
 * (i.e. the value returned is always a multiple of four). On 8 MHz Arduino 
 * boards (e.g. the LilyPad), this function has a resolution of eight microseconds.
*/
unsigned long micros() {
    return timer0_overflow_count;
}

/**
 * Description:Pauses the program for the amount of time (in milliseconds) 
 * specified as parameter. (There are 1000 milliseconds in a second.)
*/
void delay(unsigned long ms){
    vTaskDelay(ms / portTICK_RATE_MS);
}

/**
 * Description: Pauses the program for the amount of time (in microseconds) s
 * pecified as parameter. There are a thousand microseconds in a millisecond, 
 * and a million microseconds in a second.
 * 
 * 
*/
void delayMicroseconds(unsigned int us){
    uint32_t m = micros();
    if(us){
        uint32_t e = (m + us);
        if(m > e){ //overflow
            while(micros() > e){
                portNOP();
            }
        }
        while(micros() < e){
            portNOP();
        }
    }
}



static void on_tick ( void *unused )
{
    timer0_overflow_count++;
    if (timer0_overflow_count % MILLIS_INC == 0){
        timer0_millis++;
    }
}

void init(){
    handle_t timer = io_open("/dev/timer0" );
    timer_set_interval(timer, 1000 );
    timer_set_on_tick(timer, on_tick, NULL );
    timer_set_enable(timer, true );    

    gio = io_open("/dev/gpio0");
    configASSERT(gio);
}