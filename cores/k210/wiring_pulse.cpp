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





void tone(uint8_t _pin, unsigned int frequency, double duration)
{
    if(_pin != 11 && _pin != 12) return;
    fpioa_set_function(_pin, pin_map[_pin].PinType[PIO_TIMER]);
    pwm_set_frequency((pwm_device_number_t)TIMER_PWM, (pwm_channel_number_t)(_pin == 11 ? 1 : 0), frequency, duration);
}

void noTone(uint8_t _pin)
{
    if(_pin != 11 && _pin != 12) return;
    /* Disable PWM */
    pwm_set_enable((pwm_device_number_t)TIMER_PWM, (pwm_channel_number_t)(_pin == 11 ? 1 : 0), 0);
}