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
#include "gpiohs.h"

int gpiohs_irq_callback_t(void *ctx){
    voidFuncPtr func = ctx;
    func();
    return 0;
}

 /*
 * \brief Specifies a named Interrupt Service Routine (ISR) to call when an interrupt occurs.
 *        Replaces any previous function that was attached to the interrupt.
 */
void attachInterrupt(pin_size_t pin, voidFuncPtr callback, PinStatus mode){
    fpioa_set_function(pin, pin_map[pin]);
    gpiohs_set_drive_mode(pin, GPIO_DM_INPUT_PULL_UP);
    gpiohs_set_pin_edge(pin, GPIO_PE_BOTH);

    gpiohs_irq_register(pin, 1, gpiohs_irq_callback_t, callback);
}

void attachInterruptParam(pin_size_t pin, voidFuncPtrParam callback, PinStatus mode, void* param){
    fpioa_set_function(pin, pin_map[pin]);
    gpiohs_set_drive_mode(pin, GPIO_DM_INPUT_PULL_UP);
    gpiohs_set_pin_edge(pin, GPIO_PE_BOTH);

    gpiohs_irq_register(pin, 1, callback, param);
}
/*
 * \brief Turns off the given interrupt.
 */
void detachInterrupt(pin_size_t pin){
    gpiohs_irq_unregister(pin);
}