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
#ifdef FREERTOS
#include <sleep.h>
#include <FreeRTOS.h>
#include <task.h>
#endif
#include "bsp.h"
#include "sysctl.h"
#include "plic.h"
#include <timer.h>
#include <pwm.h>
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
#else
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


extern void timer_set_clock_div(timer_device_number_t timer_number, uint32_t div);

int  __attribute__((weak)) timer_callback(void *ctx)
{
    return 0;
}

void __attribute__((weak))  init(){
    plic_init();
    sysctl_enable_irq();

    timer_set_clock_div((timer_device_number_t)TIMER_PWM, 0);
    timer_init((timer_device_number_t)TIMER_PWM);

    /* Set timer interval to 10ms (1e7ns) */
    timer_set_interval((timer_device_number_t)TIMER_PWM, (timer_channel_number_t)TIMER_PWM_CHN1, 1e7);
        /* Set timer interval to 10ms (1e7ns) */
    timer_set_interval((timer_device_number_t)TIMER_PWM, (timer_channel_number_t)TIMER_PWM_CHN2, 1e7);

    /* Set timer callback function with repeat method */
    timer_irq_register((timer_device_number_t)TIMER_PWM, (timer_channel_number_t)TIMER_PWM_CHN1, 0, 1, timer_callback, NULL);
        /* Set timer callback function with repeat method */
    timer_irq_register((timer_device_number_t)TIMER_PWM, (timer_channel_number_t)TIMER_PWM_CHN2, 0, 1, timer_callback, NULL);

    timer_set_enable((timer_device_number_t)TIMER_PWM,(timer_channel_number_t)TIMER_PWM_CHN1, 1);
    timer_set_enable((timer_device_number_t)TIMER_PWM,(timer_channel_number_t)TIMER_PWM_CHN2, 1);

    pwm_init((pwm_device_number_t)TIMER_PWM);
    /* Enable PWM */
    pwm_set_enable((pwm_device_number_t)TIMER_PWM, (pwm_channel_number_t)TIMER_PWM_CHN1, 1);
    pwm_set_enable((pwm_device_number_t)TIMER_PWM, (pwm_channel_number_t)TIMER_PWM_CHN2, 1);

}