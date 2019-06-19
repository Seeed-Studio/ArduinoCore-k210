/*
  Arduino API main include
  Copyright (c) 2016 Arduino LLC. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef ARDUINO_API_H
#define ARDUINO_API_H
// version 1.0.0

// No FreeRTOS is used

#ifndef ARDUINO_API_VERSION
#define ARDUINO_API_VERSION 10000
#endif

#ifndef KENDRYTE_K210
#define KENDRYTE_K210 1
#endif

#include "Binary.h"

#ifdef __cplusplus

#include <algorithm>
#include <cmath>

#include "Client.h"
#include "HardwareI2C.h"
#include "HardwareSerial.h"
#include "Interrupts.h"
#include "IPAddress.h"
#include "Print.h"
#include "Printable.h"
#include "PluggableUSB.h"
#include "Server.h"
#include "WString.h"
#include "Stream.h"
#include "Udp.h"
#include "USBAPI.h"
#include "WCharacter.h"

using ::round;
using std::isinf;
using std::isnan;
using std::max;
using std::min;
#endif

/* Standard C library includes */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// Misc Arduino core functions
#include "Common.h"

#include "pins_arduino.h"
#ifdef ARDUINO_DEBUG
#define DEBUGV(_f, ...)  printf(_f, ## __VA_ARGS__)
#else
#define DEBUGV(...)
#endif
#endif
