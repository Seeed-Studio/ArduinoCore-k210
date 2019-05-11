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
#include "Wire.h"
#include "pins_arduino.h"
#include "utils.h"
#include <inttypes.h>
extern "C" {
#include "sysctl.h"
#include <stdlib.h>
#include <string.h>

void i2c_set_address(i2c_device_number_t i2c_num, uint32_t address) {
    configASSERT(i2c_num < I2C_MAX_NUM);
    volatile i2c_t *i2c_adapter = i2c[i2c_num];
    i2c_adapter->enable = 0;
    if (i2c_adapter->con & (I2C_CON_MASTER_MODE | I2C_CON_SLAVE_DISABLE))
        i2c_adapter->tar = I2C_TAR_ADDRESS(address);
    else
        i2c_adapter->sar = I2C_SAR_ADDRESS(address);
    i2c_adapter->enable = I2C_ENABLE_ENABLE;
}

uint32_t i2c_get_address(i2c_device_number_t i2c_num) {
    configASSERT(i2c_num < I2C_MAX_NUM);
    volatile i2c_t *i2c_adapter = i2c[i2c_num];
    if (i2c_adapter->con & (I2C_CON_MASTER_MODE | I2C_CON_SLAVE_DISABLE))
        return i2c_adapter->tar;
    else
        return i2c_adapter->sar;
}

void i2c_set_clock(i2c_device_number_t i2c_num, uint32_t i2c_clk) {
    configASSERT(i2c_num < I2C_MAX_NUM);
    volatile i2c_t *i2c_adapter = i2c[i2c_num];

    uint32_t v_i2c_freq = sysctl_clock_get_freq((sysctl_clock_t)(SYSCTL_CLOCK_I2C0 + i2c_num));
    uint16_t v_period_clk_cnt = v_i2c_freq / i2c_clk / 2;

    if (v_period_clk_cnt == 0)
        v_period_clk_cnt = 1;

    i2c_adapter->enable = 0;
    i2c_adapter->ss_scl_hcnt = I2C_SS_SCL_HCNT_COUNT(v_period_clk_cnt);
    i2c_adapter->ss_scl_lcnt = I2C_SS_SCL_LCNT_COUNT(v_period_clk_cnt);
    i2c_adapter->enable = I2C_ENABLE_ENABLE;
}

void i2c_wrtedata(i2c_device_number_t i2c_num, uint32_t data) {
    configASSERT(i2c_num < I2C_MAX_NUM);
    volatile i2c_t *i2c_adapter = i2c[i2c_num];
    i2c_adapter->data_cmd = data;
}

} // extern "C"

// Initialize Class Variables //////////////////////////////////////////////////

uint8_t TwoWire::rxBuffer[BUFFER_LENGTH];
uint8_t TwoWire::rxBufferIndex = 0;
uint8_t TwoWire::rxBufferLength = 0;

uint8_t TwoWire::txAddress = 0;
uint8_t TwoWire::txBuffer[BUFFER_LENGTH];
uint8_t TwoWire::txBufferIndex = 0;
uint8_t TwoWire::txBufferLength = 0;

uint8_t TwoWire::transmitting = 0;
void (*TwoWire::user_onRequest)(void);
void (*TwoWire::user_onReceive)(int);

// Constructors ////////////////////////////////////////////////////////////////

TwoWire::TwoWire(int i2c_num, int sda_pin = 24, int scl_pin = 23) : _i2c_num((i2c_device_number_t)i2c_num) {
    fpioa_set_function(sda_pin, pin_map[sda_pin].PinType[PIO_I2C]);
    fpioa_set_function(scl_pin, pin_map[scl_pin].PinType[PIO_I2C]);
}

// Public Methods //////////////////////////////////////////////////////////////
// Master
void TwoWire::begin(void) { i2c_init(_i2c_num, 0x00, 7, 200000); }

// Slave
void TwoWire::begin(uint8_t address) {
    _slave_handler.on_event = TwoWire::onEventService, _slave_handler.on_receive = TwoWire::_onReceiveService,
    _slave_handler.on_transmit = TwoWire::_onRequestService;

    i2c_init_as_slave(_i2c_num, address, 7, &_slave_handler);
}

// Slave
void TwoWire::begin(int address) { begin((uint8_t)address); }

void TwoWire::end(void) {}

void TwoWire::setClock(uint32_t clock) { i2c_set_clock(_i2c_num, clock); }

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop) {
    if (i2c_get_address(_i2c_num) != address)
        i2c_set_address(_i2c_num, address);

    // clamp to buffer length
    if (quantity > BUFFER_LENGTH) {
        quantity = BUFFER_LENGTH;
    }
    // perform blocking read into buffer
#ifdef K210_I2C_USE_DMA
    i2c_recv_data_dma(DMAC_CHANNEL0, DMAC_CHANNEL1, _i2c_num, NULL, 0, rxBuffer, quantity);
#else
    if (i2c_recv_data(_i2c_num, NULL, 0, rxBuffer, quantity)) {
        return 0;
    }
#endif
    // set rx buffer iterator vars
    rxBufferIndex = 0;

    rxBufferLength = quantity;

    return quantity;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity) { return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t) true); }

uint8_t TwoWire::requestFrom(int address, int quantity) { return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t) true); }

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop) { return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop); }

void TwoWire::beginTransmission(uint8_t address) {
    // indicate that we are transmitting
    transmitting = 1;
    // set address of targeted slave
    if (i2c_get_address(_i2c_num) != address)
        i2c_set_address(_i2c_num, address);
    // reset tx buffer iterator vars
    txBufferIndex = 0;
    txBufferLength = 0;
}

void TwoWire::beginTransmission(int address) { beginTransmission((uint8_t)address); }

//
//	Originally, 'endTransmission' was an f(void) function.
//	It has been modified to take one parameter indicating
//	whether or not a STOP should be performed on the bus.
//	Calling endTransmission(false) allows a sketch to
//	perform a repeated start.
//
//	WARNING: Nothing in the library keeps track of whether
//	the bus tenure has been properly ended with a STOP. It
//	is very possible to leave the bus in a hung state if
//	no call to endTransmission(true) is made. Some I2C
//	devices will behave oddly if they do not see a STOP.
//
// Errors:
//  0 : Success
//  1 : Data too long
//  2 : NACK on transmit of address
//  3 : NACK on transmit of data
//  4 : Other error
// TODO: support send without Stop
uint8_t TwoWire::endTransmission(uint8_t sendStop) {
    // transmit buffer (blocking)
    uint8_t ret = 0;
#ifdef K210_I2C_USE_DMA
    i2c_send_data_dma(DMAC_CHANNEL0, _i2c_num, txBuffer, txBufferLength + 1);
#else
    ret = i2c_send_data(_i2c_num, txBuffer, txBufferLength + 1);
#endif
    // reset tx buffer iterator vars
    txBufferIndex = 0;
    txBufferLength = 0;
    // indicate that we are done transmitting
    transmitting = 0;
    return ret;
}

//	This provides backwards compatibility with the original
//	definition, and expected behaviour, of endTransmission
//
uint8_t TwoWire::endTransmission(void) { return endTransmission(true); }

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(uint8_t data) {
    if (transmitting) {
        // in master transmitter mode
        // don't bother if buffer is full
        if (txBufferLength >= BUFFER_LENGTH) {
            setWriteError();
            return 0;
        }
        // put byte in tx buffer
        txBuffer[txBufferIndex] = data;
        ++txBufferIndex;
        // update amount in buffer
        txBufferLength = txBufferIndex;
    } else {
        // in slave send mode
        // reply to master
        i2c_wrtedata(_i2c_num, data);
    }
    return 1;
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(const uint8_t *data, size_t quantity) {
    for (size_t i = 0; i < quantity; ++i) {
        write(data[i]);
    }
    return quantity;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::available(void) { return rxBufferLength - rxBufferIndex; }

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::read(void) {
    int value = -1;

    // get each successive byte on each call
    if (rxBufferIndex < rxBufferLength) {
        value = rxBuffer[rxBufferIndex];
        ++rxBufferIndex;
    }

    return value;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::peek(void) {
    int value = -1;

    if (rxBufferIndex < rxBufferLength) {
        value = rxBuffer[rxBufferIndex];
    }

    return value;
}

void TwoWire::flush(void) {
    // XXX: to be implemented.
}

void TwoWire::_onReceiveService(uint32_t inBytes) { onReceiveService((uint8_t *)&inBytes, 1); }
// behind the scenes function that is called when data is received
void TwoWire::onReceiveService(uint8_t *inBytes, int numBytes) {
    // don't bother if user hasn't registered a callback
    if (!user_onReceive) {
        return;
    }
    // don't bother if rx buffer is in use by a master requestFrom() op
    // i know this drops data, but it allows for slight stupidity
    // meaning, they may not have read all the master requestFrom() data yet
    if (rxBufferIndex < rxBufferLength) {
        return;
    }
    // copy twi rx buffer into local read buffer
    // this enables new reads to happen in parallel
    for (uint8_t i = 0; i < numBytes; ++i) {
        rxBuffer[i] = inBytes[i];
    }
    // set rx iterator vars
    rxBufferIndex = 0;
    rxBufferLength = numBytes;
    // alert user program
    user_onReceive(numBytes);
}

uint32_t TwoWire::_onRequestService(void) {
    onRequestService();
    return 0; // TODO
}
// behind the scenes function that is called when data is requested
void TwoWire::onRequestService(void) {
    // don't bother if user hasn't registered a callback
    if (!user_onRequest) {
        return;
    }
    // reset tx buffer iterator vars
    // !!! this will kill any pending pre-master sendTo() activity
    txBufferIndex = 0;
    txBufferLength = 0;
    // alert user program
    user_onRequest();
}

void TwoWire::onEventService(i2c_event_t event) { user_onEvent((int)event); }

// sets function called on slave write
void TwoWire::onReceive(void (*function)(int)) { user_onReceive = function; }

// sets function called on slave read
void TwoWire::onRequest(void (*function)(void)) { user_onRequest = function; }

void TwoWire::onEvent(void (*function)(int)) { user_onEvent = function; }

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_WIRE)
TwoWire Wire(1);
#endif
