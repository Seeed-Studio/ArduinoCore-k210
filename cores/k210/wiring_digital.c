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
#include <devices.h>
#include <FreeRTOS.h>
#include <task.h>

#ifdef __cplusplus
 extern "C" {
#endif
extern handle_t gio;

/**
 * @description: Configures the specified pin to behave either as an input or an 
 * output. See the description of (digital pins) for details on the functionality
 *  of the pins.
 * @param: the number of the pin whose mode you wish to set
 * @param: INPUT, OUTPUT, or INPUT_PULLUP. (see the (digital pins) page for a more
 *   complete description of the functionality.)
 * @return: Nothing
 */
void pinMode( pin_size_t ulPin, PinMode ulMode ){
    gpio_set_drive_mode(ulPin, 2, ulMode);
}

/**
 * @description: Write a HIGH or a LOW value to a digital pin.
 * If the pin has been configured as an OUTPUT with pinMode(), its voltage will be
 *  set to the corresponding value: 5V (or 3.3V on 3.3V boards) for HIGH, 0V 
 *  (ground) for LOW.
 * If the pin is configured as an INPUT, digitalWrite() will enable (HIGH) or disable 
 * (LOW) the internal pullup on the input pin. It is recommended to set the pinMode()
 *  to INPUT_PULLUP to enable the internal pull-up resistor. See the digital pins 
 *  tutorial for more information.
 * If you do not set the pinMode() to OUTPUT, and connect an LED to a pin, when calling 
 * digitalWrite(HIGH), the LED may appear dim. Without explicitly setting pinMode(), 
 * digitalWrite() will have enabled the internal pull-up resistor, which acts like a 
 * large current-limiting resistor.
 * @param: The pin number
 * @param: HIGH or LOW
 * @return: Nothing
 */
void digitalWrite( pin_size_t ulPin, PinStatus ulVal ){
    gpio_set_pin_value(gio, ulPin, ulVal);
}

/**
 * @description: Reads the value from a specified digital pin, either HIGH or LOW.
 * @param: The number of the digital pin you want to read
 * @return: HIGH or LOW
 */
PinStatus digitalRead( pin_size_t ulPin ){
    return gpio_get_pin_value(gio, ulPin);
}

#ifdef __cplusplus
}
#endif
