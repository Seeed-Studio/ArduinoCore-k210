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
#include "Arduino.h"
#include <timer.h>
#include <pwm.h>
#include <plic.h>
#include <sysctl.h>
#include <fpioa.h>

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
    uint32_t cpu_freq = sysctl_clock_get_freq(SYSCTL_CLOCK_CPU);
    uint32_t loops = 0;
    uint32_t max_timeout = timeout * (cpu_freq / 1000000L) / 16;
    uint32_t start, end;

    // wait for any previous pulse to end
    while (digitalRead(pin) == state)
        if (loops++ == max_timeout)
            return 0;

    // wait for the pulse to start
    while (digitalRead(pin) != state)
        if (loops++ == max_timeout)
            return 0;

    // wait for the pulse to stop
    start = micros();
    while (digitalRead(pin) == state)
        if (loops++ == max_timeout)
            return 0;
    end = micros();

    return (end - start);
}

unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
    return pulseIn(pin, state, timeout);
}

int __attribute__((weak)) pwm_callback(void *ctx)
{
#if 0
    static double cnt = 0.01;
    static int flag = 0;

    pwm_set_frequency(TIMER_PWM, TIMER_PWM_CHN, 200000, cnt);

    flag ? (cnt -= 0.01) : (cnt += 0.01);
    if (cnt > 1.0)
    {
        cnt = 1.0;
        flag = 1;
    }
    else if (cnt < 0.0)
    {
        cnt = 0.0;
        flag = 0;
    }
#endif
    return 0;
}

#ifndef TIMER_NOR
#define TIMER_NOR 0
#endif

#ifndef TIMER_CHN
#define TIMER_CHN 0
#endif

#ifndef TIMER_PWM
#define TIMER_PWM 1
#endif

#ifndef TIMER_PWM_CHN
#define TIMER_PWM_CHN 0
#endif

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
{
    /* Init FPIOA pin mapping for PWM*/
    fpioa_set_function(_pin, pin_map[_pin]);
    /* Init timer */
    timer_init(TIMER_NOR);
    /* Set timer interval to 10ms (1e7ns) */
    timer_set_interval(TIMER_NOR, TIMER_CHN, 1e7);
    /* Set timer callback function with repeat method */
    timer_irq_register(TIMER_NOR, TIMER_CHN, 0, 1, pwm_callback, NULL);
    /* Enable timer */
    timer_set_enable(TIMER_NOR, TIMER_CHN, 1);
    /* Init PWM */
    pwm_init(TIMER_PWM);
    /* Set PWM to 200000Hz */
    pwm_set_frequency(TIMER_PWM, TIMER_PWM_CHN, frequency, duration);
    /* Enable PWM */
    pwm_set_enable(TIMER_PWM, TIMER_PWM_CHN, 1);
}
void noTone(uint8_t _pin)
{
    /* Disable PWM */
    pwm_set_enable(TIMER_PWM, TIMER_PWM_CHN, 0);
}