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

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED
#include <inttypes.h>
#include "Common.h"
#include "spi.h"

class SPISettings {
  public:
    SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) { init_AlwaysInline(clock, bitOrder, dataMode); }
    SPISettings() { init_AlwaysInline(4000000, LSBFIRST, 0); }

  private:
    void init_AlwaysInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) __attribute__((__always_inline__)) {
        _order = bitOrder;
        _mode = dataMode;
        _clock = clock;
    }
    uint8_t _order = LSBFIRST;
    uint8_t _mode = 0;
    uint32_t _clock = 4000000;
    friend class SPIClass;
};

class SPIClass {
  public:
    SPIClass(uint8_t _spi_num, uint8_t _spi_clk, uint8_t _spi_mosi, uint8_t _spi_miso, uint8_t _spi_cs);

    byte transfer(uint8_t data);
    uint16_t transfer16(uint16_t data);
    void transfer(void *buf, size_t count);

    // Transaction Functions
    void usingInterrupt(int interruptNumber);
    void notUsingInterrupt(int interruptNumber);
    void beginTransaction(SPISettings settings);
    void endTransaction(void);

    // SPI Configuration methods
    void attachInterrupt();
    void detachInterrupt();

    void begin();
    void end();

    void setBitOrder(uint8_t order);
    void setDataMode(uint8_t uc_mode);
    void setClockDivider(uint8_t uc_div);

  private:
    void init();

    uint8_t _spi_clk;
    uint8_t _spi_mosi;
    uint8_t _spi_miso;
    spi_chip_select_t _spi_cs;
    uint8_t _spi_num;

    SPISettings _settings;

    bool initialized;
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SPI)
extern SPIClass SPI;
extern SPIClass SPI1;
#endif

#endif
