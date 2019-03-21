/*
  Copyright (c) 2016 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/**
 * 为什么不用官方的uart.cpp
 * 1, 不支持peek，flush
 * 2, 需要支持Stream
 * 
 * TODO: settimeout需要优化
*/

#pragma once

#include "Arduino.h"
#include "RingBuffer.h"
#include "fpioa.h"
#include <string.h>
#include "uart.h"
#include "gpiohs.h"
#include "sysctl.h"
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>



// XXX: Those constants should be defined as const int / enums?
// XXX: shall we use namespaces too?

#define SERIAL_PARITY_EVEN   (0x2ul)
#define SERIAL_PARITY_ODD    (0x1ul)
#define SERIAL_PARITY_NONE   (0x0ul)
// #define SERIAL_PARITY_MARK   (0x4ul)
// #define SERIAL_PARITY_SPACE  (0x5ul)
#define SERIAL_PARITY_MASK   (0x3ul)

#define SERIAL_STOP_BIT_1    (0x00ul)
#define SERIAL_STOP_BIT_1_5  (0x10ul)
#define SERIAL_STOP_BIT_2    (0x20ul)
#define SERIAL_STOP_BIT_MASK (0x30ul)



// #define SERIAL_DATA_5        (0x100ul)
// #define SERIAL_DATA_6        (0x200ul)
// #define SERIAL_DATA_7        (0x300ul)
#define SERIAL_DATA_8        (0x400ul)

#define SERIAL_DATA_MASK     (0xF00ul)

// #define SERIAL_5N1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE  | SERIAL_DATA_5)
// #define SERIAL_6N1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE  | SERIAL_DATA_6)
// #define SERIAL_7N1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE  | SERIAL_DATA_7)
#define SERIAL_8N1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE  | SERIAL_DATA_8) //
// #define SERIAL_5N2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_NONE  | SERIAL_DATA_5)
// #define SERIAL_6N2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_NONE  | SERIAL_DATA_6)
// #define SERIAL_7N2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_NONE  | SERIAL_DATA_7)
#define SERIAL_8N2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_NONE  | SERIAL_DATA_8) //
// #define SERIAL_5E1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_EVEN  | SERIAL_DATA_5)
// #define SERIAL_6E1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_EVEN  | SERIAL_DATA_6)
// #define SERIAL_7E1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_EVEN  | SERIAL_DATA_7)
// #define SERIAL_8E1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_EVEN  | SERIAL_DATA_8)
// #define SERIAL_5E2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_EVEN  | SERIAL_DATA_5)
// #define SERIAL_6E2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_EVEN  | SERIAL_DATA_6)
// #define SERIAL_7E2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_EVEN  | SERIAL_DATA_7)
#define SERIAL_8E2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_EVEN  | SERIAL_DATA_8) //
// #define SERIAL_5O1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_ODD   | SERIAL_DATA_5)
// #define SERIAL_6O1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_ODD   | SERIAL_DATA_6)
// #define SERIAL_7O1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_ODD   | SERIAL_DATA_7)
#define SERIAL_8O1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_ODD   | SERIAL_DATA_8) //
// #define SERIAL_5O2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_ODD   | SERIAL_DATA_5)
// #define SERIAL_6O2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_ODD   | SERIAL_DATA_6)
// #define SERIAL_7O2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_ODD   | SERIAL_DATA_7)
#define SERIAL_8O2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_ODD   | SERIAL_DATA_8) //
// #define SERIAL_5M1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_MARK  | SERIAL_DATA_5)
// #define SERIAL_6M1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_MARK  | SERIAL_DATA_6)
// #define SERIAL_7M1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_MARK  | SERIAL_DATA_7)
// #define SERIAL_8M1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_MARK  | SERIAL_DATA_8)
// #define SERIAL_5M2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_MARK  | SERIAL_DATA_5)
// #define SERIAL_6M2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_MARK  | SERIAL_DATA_6)
// #define SERIAL_7M2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_MARK  | SERIAL_DATA_7)
// #define SERIAL_8M2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_MARK  | SERIAL_DATA_8)
// #define SERIAL_5S1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_SPACE | SERIAL_DATA_5)
// #define SERIAL_6S1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_SPACE | SERIAL_DATA_6)
// #define SERIAL_7S1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_SPACE | SERIAL_DATA_7)
// #define SERIAL_8S1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_SPACE | SERIAL_DATA_8)
// #define SERIAL_5S2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_SPACE | SERIAL_DATA_5)
// #define SERIAL_6S2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_SPACE | SERIAL_DATA_6)
// #define SERIAL_7S2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_SPACE | SERIAL_DATA_7)
// #define SERIAL_8S2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_SPACE | SERIAL_DATA_8)

class HardwareSerial : public Stream
{
  public:
    HardwareSerial();
    void begin(unsigned long baudrate, uart_device_number_t uart_num_ = UART_DEVICE_1, int rx_pin_ = 4, int tx_pin_ = 5);
    void begin(unsigned long baudrate, uint16_t config, uart_device_number_t uart_num_ = UART_DEVICE_1, int rx_pin_ = 4, int tx_pin_ = 5);
    void end();
    int available(void);
    int peek(void);
    int read(void);
    void flush(void);
    size_t write(uint8_t);
    using Print::write; // pull in write(str) and write(buf, size) from Print
    operator bool() const;

  private:
    static int on_irq_recv_callback_(void *userdata);
    void init_(unsigned long baudrate, uint16_t config, uart_device_number_t uart_num, int rx_pin, int tx_pin);


  private:
    uart_device_number_t uart;
    SemaphoreHandle_t receive_event_;
    RingBuffer *rb_;

    size_t read_timeout_ = 1000;
};

// XXX: Are we keeping the serialEvent API?
extern void serialEventRun(void) __attribute__((weak));

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL)
extern HardwareSerial Serial;
#endif

