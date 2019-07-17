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
#include "SPIClass.h"
#include "pins_arduino.h"
#include "sysctl.h"
#include <assert.h>
#include <stdint.h>
#include <wiring_private.h>

#undef configASSERT
#include "utils.h"
extern "C"{
static spi_transfer_width_t spi_get_frame_size(size_t data_bit_length) {
    if (data_bit_length < 8)
        return SPI_TRANS_CHAR;
    else if (data_bit_length < 16)
        return SPI_TRANS_SHORT;
    return SPI_TRANS_INT;
}

static void spi_set_tmod(uint8_t spi_num, uint32_t tmod) {
    //configASSERT(spi_num < SPI_DEVICE_MAX);
    volatile spi_t *spi_handle = spi[spi_num];
    uint8_t tmod_offset = 0;
    switch (spi_num) {
    case 0:
    case 1:
    case 2:
        tmod_offset = 8;
        break;
    case 3:
    default:
        tmod_offset = 10;
        break;
    }
    set_bit(&spi_handle->ctrlr0, 3 << tmod_offset, tmod << tmod_offset);
}

static void spi_send_receive_data_standard(spi_device_num_t spi_num, int8_t chip_select, const uint8_t *tx_buff, uint8_t *rx_buff, size_t len) {
    //configASSERT(spi_num < SPI_DEVICE_MAX && spi_num != 2);
    //configASSERT(len > 0);
    size_t index, fifo_len;
    size_t rx_len = len;
    size_t tx_len = rx_len;
    spi_set_tmod(spi_num, SPI_TMOD_TRANS_RECV);

    volatile spi_t *spi_handle = spi[spi_num];

    uint8_t dfs_offset = 0;
    switch (spi_num) {
    case 0:
    case 1:
        dfs_offset = 16;
        break;
    case 2:
        //configASSERT(!"Spi Bus 2 Not Support!");
        break;
    case 3:
    default:
        dfs_offset = 0;
        break;
    }
    uint32_t data_bit_length = (spi_handle->ctrlr0 >> dfs_offset) & 0x1F;
    spi_transfer_width_t frame_width = spi_get_frame_size(data_bit_length);
    spi_handle->ctrlr1 = (uint32_t)(tx_len / frame_width - 1);
    spi_handle->ssienr = 0x01;
    spi_handle->ser = 1U << chip_select;
    uint32_t i = 0;
    while (tx_len) {
        fifo_len = 32 - spi_handle->txflr;
        fifo_len = fifo_len < tx_len ? fifo_len : tx_len;
        switch (frame_width) {
        case SPI_TRANS_INT:
            fifo_len = fifo_len / 4 * 4;
            for (index = 0; index < fifo_len / 4; index++)
                spi_handle->dr[0] = ((uint32_t *)tx_buff)[i++];
            break;
        case SPI_TRANS_SHORT:
            fifo_len = fifo_len / 2 * 2;
            for (index = 0; index < fifo_len / 2; index++)
                spi_handle->dr[0] = ((uint16_t *)tx_buff)[i++];
            break;
        default:
            for (index = 0; index < fifo_len; index++)
                spi_handle->dr[0] = tx_buff[i++];
            break;
        }
        tx_len -= fifo_len;
    }

    while ((spi_handle->sr & 0x05) != 0x04)
        ;
    if (rx_buff) {
        i = 0;
        while (rx_len) {
            fifo_len = spi_handle->rxflr;
            fifo_len = fifo_len < rx_len ? fifo_len : rx_len;
            switch (frame_width) {
            case SPI_TRANS_INT:
                fifo_len = fifo_len / 4 * 4;
                for (index = 0; index < fifo_len / 4; index++)
                    ((uint32_t *)rx_buff)[i++] = spi_handle->dr[0];
                break;
            case SPI_TRANS_SHORT:
                fifo_len = fifo_len / 2 * 2;
                for (index = 0; index < fifo_len / 2; index++)
                    ((uint16_t *)rx_buff)[i++] = (uint16_t)spi_handle->dr[0];
                break;
            default:
                for (index = 0; index < fifo_len; index++)
                    rx_buff[i++] = (uint8_t)spi_handle->dr[0];
                break;
            }

            rx_len -= fifo_len;
        }
    }
    spi_handle->ser = 0x00;
    spi_handle->ssienr = 0x00;
}

}
SPIClass::SPIClass(uint8_t spi_num, uint8_t spi_clk, uint8_t spi_mosi, uint8_t spi_miso, uint8_t spi_cs) {
    _spi_num = spi_num;
    _spi_clk = spi_clk;
    _spi_mosi = spi_mosi;
    _spi_miso = spi_miso;
    _spi_cs = (spi_chip_select_t)spi_cs;
}

void SPIClass::begin() { init(); }

void SPIClass::init() {
    dmac_init();
    fpioa_set_function(_spi_clk, pin_map[_spi_clk].PinType[PIO_SPI]);
    fpioa_set_function(_spi_mosi, pin_map[_spi_mosi].PinType[PIO_SPI]);
    fpioa_set_function(_spi_miso, pin_map[_spi_miso].PinType[PIO_SPI]);
    // fpioa_set_function(_spi_cs, pin_map[_spi_cs].PinType[PIO_SPI]);


    spi_init((spi_device_num_t)_spi_num, (spi_work_mode_t)_settings._mode, SPI_FF_STANDARD, 8, _settings._order);
    spi_set_clk_rate((spi_device_num_t)_spi_num, _settings._clock);

}

void SPIClass::end() {}

/**
 * @description: If your program will perform SPI transactions within an interrupt,
 * call this function to register the interrupt number or name wisetBitOrderth the SPI library.
 * This allows SPI.beginTransaction() to prevent usage conflicts.setBitOrder
 * Note that the interrupt specified in the call to usingInterrupsetBitOrdert() will be disabled
 *  on a call to beginTransaction() and re-enabled in endTransaction().
 *
 * @param {type}
 * @return:
 */
void SPIClass::usingInterrupt(int interruptNumber) {}

void SPIClass::notUsingInterrupt(int interruptNumber) {}

void SPIClass::beginTransaction(SPISettings settings) {
    _settings = settings;
    spi_init((spi_device_num_t)_spi_num, (spi_work_mode_t)_settings._mode, SPI_FF_STANDARD, 8, _settings._order);
}

void SPIClass::endTransaction(void) {}

void SPIClass::setBitOrder(uint8_t order) {
    _settings._order = order;
    spi_init((spi_device_num_t)_spi_num, (spi_work_mode_t)_settings._mode, SPI_FF_STANDARD, 8, _settings._order);
}
void SPIClass::setDataMode(uint8_t mode) {
    _settings._mode = mode;
    spi_init((spi_device_num_t)_spi_num, (spi_work_mode_t)_settings._mode, SPI_FF_STANDARD, 8, _settings._order);
}

void SPIClass::setClockDivider(uint8_t clock) {
    _settings._clock = clock;
    spi_init((spi_device_num_t)_spi_num, (spi_work_mode_t)_settings._mode, SPI_FF_STANDARD, 8, _settings._order);
}

byte SPIClass::transfer(uint8_t data) {
    uint8_t ret;
    spi_send_receive_data_standard((spi_device_num_t)_spi_num,_spi_cs,&data,&ret,1);
    //spi_dup_send_receive_data_dma(DMAC_CHANNEL0, DMAC_CHANNEL1, (spi_device_num_t)_spi_num, _spi_cs, &data, 1, &ret, 1);
    return ret;
}

uint16_t SPIClass::transfer16(uint16_t data) {
    union {
        uint16_t val;
        struct {
            uint8_t lsb;
            uint8_t msb;
        };
        uint8_t data2[2];
    } tx, rx;

    tx.val = data;
    spi_dup_send_receive_data_dma(DMAC_CHANNEL0, DMAC_CHANNEL1, (spi_device_num_t)_spi_num, _spi_cs, tx.data2, 2, rx.data2, 2);
    return rx.val;
}

void SPIClass::transfer(void *buf, size_t count) {
    spi_send_data_normal_dma(DMAC_CHANNEL0, (spi_device_num_t)_spi_num, _spi_cs, (const uint8_t *)buf, count, SPI_TRANS_CHAR);
}

void SPIClass::attachInterrupt() {
    // Should be enableInterrupt()
}

void SPIClass::detachInterrupt() {
    // Should be disableInterrupt()
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SPI)
SPIClass SPI(SPI_DEVICE_1, SPI0_SCK, SPI0_MOSI, SPI0_MISO, 0);
SPIClass SPI1(SPI_DEVICE_0, SPI1_SCK, SPI1_MOSI, SPI1_MISO, 0);

#endif
