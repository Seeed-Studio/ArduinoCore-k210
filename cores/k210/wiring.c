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
#include <sleep.h>
#include <FreeRTOS.h>
#include <task.h>
#include "bsp.h"
#include "sysctl.h"
#include "plic.h"
#include "pins_arduino.h"
// the whole number of milliseconds per timer0 overflow
#define MILLIS_INC 1000
#ifdef MICROPYTHON
extern  void mp_hal_delay_ms(uint64_t ms);
extern  void mp_hal_delay_us(uint64_t us);
#endif
/**
 * Description: Returns the number of milliseconds passed since the Arduino 
 * board began running the current program. This number will overflow (go 
 * back to zero), after approximately 50 days.
*/
unsigned long millis(){
    uint64_t v_cycle = read_cycle();
    return v_cycle * 1000 / sysctl_clock_get_freq(SYSCTL_CLOCK_CPU);

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
    uint64_t v_cycle = read_cycle();
    return v_cycle * 1000000 / sysctl_clock_get_freq(SYSCTL_CLOCK_CPU);
}

/**
 * Description:Pauses the program for the amount of time (in milliseconds) 
 * specified as parameter. (There are 1000 milliseconds in a second.)
*/
void delay(unsigned long ms){
#ifdef FREERTOS
    vTaskDelay(ms / portTICK_RATE_MS);
#elif MICROPYTHON
    mp_hal_delay_ms(ms);
#elif NOFREERTOS
    msleep(ms);
#endif
}

/**
 * Description: Pauses the program for the amount of time (in microseconds) s
 * pecified as parameter. There are a thousand microseconds in a millisecond, 
 * and a million microseconds in a second.
 * 
 * 
*/
void delayMicroseconds(unsigned int us){
#ifndef MICROPYTHON
    usleep(us);
#else
    mp_hal_delay_ms(us);
#endif
}


void __attribute__((weak))  init(){
    plic_init();
    sysctl_enable_irq();
}