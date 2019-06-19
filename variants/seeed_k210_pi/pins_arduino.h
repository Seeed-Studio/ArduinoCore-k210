#pragma once
#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#define NOFREERTOS 

#ifndef NOFREERTOS
#define FREERTOS 
#endif

#include <fpioa.h>
#include <stdint.h>
#define LED_BUILTIN 13

#define A0 0
#define A1 1
#define A2 2
#define A3 3

#define TIMER_PWM 0
#define TIMER_PWM_CHN1 0
#define TIMER_PWM_CHN2 1

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _EPioType {
    PIO_GPIO = 0,
    PIO_GPIOHS,
    PIO_I2C,
    PIO_SPI,
    PIO_UART,
    PIO_TIMER,
    PIO_I2S,
    PIO_CMOS,
    PIO_JTAG,
    PIO_DEBUG,
} EPioType;

typedef struct _PinDescription {
    fpioa_function_t PinType[PIO_DEBUG + 1];
} PinDescription;

PinDescription
    __attribute__((weak)) pin_map[] =
        {
            {
                .PinType =
                    {
                        // 0
                        FUNC_DEBUG0,    // PIO_GPIO
                        FUNC_DEBUG0,    // PIO_GPIOHS
                        FUNC_DEBUG0,    // PIO_I2C
                        FUNC_DEBUG0,    // PIO_SPI
                        FUNC_DEBUG0,    // PIO_UART
                        FUNC_DEBUG0,    // PIO_TIMER
                        FUNC_DEBUG0,    // PIO_I2S
                        FUNC_DEBUG0,    // PIO_CMOS
                        FUNC_JTAG_TCLK, // PIO_JTAG
                        FUNC_DEBUG0,    // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 1
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_DEBUG0,   // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_JTAG_TDI, // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 2
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_DEBUG0,   // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_JTAG_TMS, // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 3
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_DEBUG0,   // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_JTAG_TDO, // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 4
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS0,  // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_UART1_RX, // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 5
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS1,  // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_UART1_TX, // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 6
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS2,  // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_UART2_RX, // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 7
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS3,  // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_UART2_TX, // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 8
                        FUNC_DEBUG0,  // PIO_GPIO
                        FUNC_GPIOHS4, // PIO_GPIOHS
                        FUNC_DEBUG0,  // PIO_I2C
                        FUNC_DEBUG0,  // PIO_SPI
                        FUNC_DEBUG0,  // PIO_UART
                        FUNC_DEBUG0,  // PIO_TIMER
                        FUNC_DEBUG0,  // PIO_I2S
                        FUNC_DEBUG0,  // PIO_CMOS
                        FUNC_DEBUG0,  // PIO_JTAG
                        FUNC_DEBUG0,  // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 9
                        FUNC_DEBUG0,  // PIO_GPIO
                        FUNC_GPIOHS5, // PIO_GPIOHS
                        FUNC_DEBUG0,  // PIO_I2C
                        FUNC_DEBUG0,  // PIO_SPI
                        FUNC_DEBUG0,  // PIO_UART
                        FUNC_DEBUG0,  // PIO_TIMER
                        FUNC_DEBUG0,  // PIO_I2S
                        FUNC_DEBUG0,  // PIO_CMOS
                        FUNC_DEBUG0,  // PIO_JTAG
                        FUNC_DEBUG0,  // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 10
                        FUNC_DEBUG0,  // PIO_GPIO
                        FUNC_GPIOHS6, // PIO_GPIOHS
                        FUNC_DEBUG0,  // PIO_I2C
                        FUNC_DEBUG0,  // PIO_SPI
                        FUNC_DEBUG0,  // PIO_UART
                        FUNC_DEBUG0,  // PIO_TIMER
                        FUNC_DEBUG0,  // PIO_I2S
                        FUNC_DEBUG0,  // PIO_CMOS
                        FUNC_DEBUG0,  // PIO_JTAG
                        FUNC_DEBUG0,  // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 11
                        FUNC_DEBUG0,         // PIO_GPIO
                        FUNC_GPIOHS7,        // PIO_GPIOHS
                        FUNC_DEBUG0,         // PIO_I2C
                        FUNC_DEBUG0,         // PIO_SPI
                        FUNC_UART2_TX,       // PIO_UART
                        FUNC_TIMER0_TOGGLE2, // PIO_TIMER
                        FUNC_DEBUG0,         // PIO_I2S
                        FUNC_DEBUG0,         // PIO_CMOS
                        FUNC_DEBUG0,         // PIO_JTAG
                        FUNC_DEBUG0,         // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 12
                        FUNC_DEBUG0,         // PIO_GPIO
                        FUNC_GPIOHS8,        // PIO_GPIOHS
                        FUNC_DEBUG0,         // PIO_I2C
                        FUNC_DEBUG0,         // PIO_SPI
                        FUNC_UART2_RX,       // PIO_UART
                        FUNC_TIMER0_TOGGLE1, // PIO_TIMER
                        FUNC_DEBUG0,         // PIO_I2S
                        FUNC_DEBUG0,         // PIO_CMOS
                        FUNC_DEBUG0,         // PIO_JTAG
                        FUNC_DEBUG0,         // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 13
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS9,  // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_UART3_RX, // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 14
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS10, // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_UART3_TX, // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 15
                        FUNC_DEBUG0,    // PIO_GPIO
                        FUNC_GPIOHS11,  // PIO_GPIOHS
                        FUNC_I2C0_SCLK, // PIO_I2C
                        FUNC_DEBUG0,    // PIO_SPI
                        FUNC_DEBUG0,    // PIO_UART
                        FUNC_DEBUG0,    // PIO_TIMER
                        FUNC_DEBUG0,    // PIO_I2S
                        FUNC_DEBUG0,    // PIO_CMOS
                        FUNC_DEBUG0,    // PIO_JTAG
                        FUNC_DEBUG0,    // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 16
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS12, // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 17
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS13, // PIO_GPIOHS
                        FUNC_I2C0_SDA, // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 18
                        FUNC_DEBUG0,    // PIO_GPIO
                        FUNC_GPIOHS14,  // PIO_GPIOHS
                        FUNC_I2C1_SCLK, // PIO_I2C
                        FUNC_DEBUG0,    // PIO_SPI
                        FUNC_DEBUG0,    // PIO_UART
                        FUNC_DEBUG0,    // PIO_TIMER
                        FUNC_DEBUG0,    // PIO_I2S
                        FUNC_DEBUG0,    // PIO_CMOS
                        FUNC_DEBUG0,    // PIO_JTAG
                        FUNC_DEBUG0,    // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 19
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS15, // PIO_GPIOHS
                        FUNC_I2C1_SDA, // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 20
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS16, // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 21
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS17, // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 22
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS18, // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 23
                        FUNC_DEBUG0,    // PIO_GPIO
                        FUNC_GPIOHS19,  // PIO_GPIOHS
                        FUNC_I2C1_SCLK, // PIO_I2C
                        FUNC_DEBUG0,    // PIO_SPI
                        FUNC_DEBUG0,    // PIO_UART
                        FUNC_DEBUG0,    // PIO_TIMER
                        FUNC_DEBUG0,    // PIO_I2S
                        FUNC_DEBUG0,    // PIO_CMOS
                        FUNC_DEBUG0,    // PIO_JTAG
                        FUNC_DEBUG0,    // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 24
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS20, // PIO_GPIOHS
                        FUNC_I2C1_SDA, // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 25
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS21, // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_SPI1_SS1, // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 26
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS22, // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_SPI1_D1,  // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 27
                        FUNC_DEBUG0,    // PIO_GPIO
                        FUNC_GPIOHS23,  // PIO_GPIOHS
                        FUNC_DEBUG0,    // PIO_I2C
                        FUNC_SPI1_SCLK, // PIO_SPI
                        FUNC_DEBUG0,    // PIO_UART
                        FUNC_DEBUG0,    // PIO_TIMER
                        FUNC_DEBUG0,    // PIO_I2S
                        FUNC_DEBUG0,    // PIO_CMOS
                        FUNC_DEBUG0,    // PIO_JTAG
                        FUNC_DEBUG0,    // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 28
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS24, // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_SPI1_D0,  // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 29
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS25, // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_SPI1_SS0, // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 30
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS26, // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 31
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS27, // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 32
                        FUNC_DEBUG0,     // PIO_GPIO
                        FUNC_GPIOHS28,   // PIO_GPIOHS
                        FUNC_DEBUG0,     // PIO_I2C
                        FUNC_SPI0_D0,     // PIO_SPI
                        FUNC_DEBUG0,     // PIO_UART
                        FUNC_DEBUG0,     // PIO_TIMER
                        FUNC_I2S0_IN_D0, // PIO_I2S
                        FUNC_DEBUG0,     // PIO_CMOS
                        FUNC_DEBUG0,     // PIO_JTAG
                        FUNC_DEBUG0,     // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 33
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_GPIOHS29, // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_SPI0_D1,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_I2S0_WS,  // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 34
                        FUNC_DEBUG0,      // PIO_GPIO
                        FUNC_GPIOHS30,    // PIO_GPIOHS
                        FUNC_DEBUG0,      // PIO_I2C
                        FUNC_SPI0_SCLK,      // PIO_SPI
                        FUNC_DEBUG0,      // PIO_UART
                        FUNC_DEBUG0,      // PIO_TIMER
                        FUNC_I2S0_OUT_D0, // PIO_I2S
                        FUNC_DEBUG0,      // PIO_CMOS
                        FUNC_DEBUG0,      // PIO_JTAG
                        FUNC_DEBUG0,      // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 35
                        FUNC_DEBUG0,    // PIO_GPIO
                        FUNC_GPIOHS31,  // PIO_GPIOHS
                        FUNC_DEBUG0,    // PIO_I2C
                        FUNC_SPI0_SS0,    // PIO_SPI
                        FUNC_DEBUG0,    // PIO_UART
                        FUNC_DEBUG0,    // PIO_TIMER
                        FUNC_I2S0_SCLK, // PIO_I2S
                        FUNC_DEBUG0,    // PIO_CMOS
                        FUNC_DEBUG0,    // PIO_JTAG
                        FUNC_DEBUG0,    // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 36
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_DEBUG0,   // PIO_GPIOHS
                        FUNC_DEBUG0,   // PIO_I2C
                        FUNC_SPI0_SS3, // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 37
                        FUNC_DEBUG0, // PIO_GPIO
                        FUNC_DEBUG0, // PIO_GPIOHS
                        FUNC_DEBUG0, // PIO_I2C
                        FUNC_DEBUG0, // PIO_SPI
                        FUNC_DEBUG0, // PIO_UART
                        FUNC_DEBUG0, // PIO_TIMER
                        FUNC_DEBUG0, // PIO_I2S
                        FUNC_DEBUG0, // PIO_CMOS
                        FUNC_DEBUG0, // PIO_JTAG
                        FUNC_DEBUG0, // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 38
                        FUNC_DEBUG0, // PIO_GPIO
                        FUNC_DEBUG0, // PIO_GPIOHS
                        FUNC_DEBUG0, // PIO_I2C
                        FUNC_DEBUG0, // PIO_SPI
                        FUNC_DEBUG0, // PIO_UART
                        FUNC_DEBUG0, // PIO_TIMER
                        FUNC_DEBUG0, // PIO_I2S
                        FUNC_DEBUG0, // PIO_CMOS
                        FUNC_DEBUG0, // PIO_JTAG
                        FUNC_DEBUG0, // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 39
                        FUNC_DEBUG0,    // PIO_GPIO
                        FUNC_DEBUG0,    // PIO_GPIOHS
                        FUNC_DEBUG0,    // PIO_I2C
                        FUNC_SPI0_SCLK, // PIO_SPI
                        FUNC_DEBUG0,    // PIO_UART
                        FUNC_DEBUG0,    // PIO_TIMER
                        FUNC_DEBUG0,    // PIO_I2S
                        FUNC_DEBUG0,    // PIO_CMOS
                        FUNC_DEBUG0,    // PIO_JTAG
                        FUNC_DEBUG0,    // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 40
                        FUNC_DEBUG0,   // PIO_GPIO
                        FUNC_DEBUG0,   // PIO_GPIOHS
                        FUNC_I2C1_SDA, // PIO_I2C
                        FUNC_DEBUG0,   // PIO_SPI
                        FUNC_DEBUG0,   // PIO_UART
                        FUNC_DEBUG0,   // PIO_TIMER
                        FUNC_DEBUG0,   // PIO_I2S
                        FUNC_DEBUG0,   // PIO_CMOS
                        FUNC_DEBUG0,   // PIO_JTAG
                        FUNC_DEBUG0,   // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 41
                        FUNC_DEBUG0,    // PIO_GPIO
                        FUNC_DEBUG0,    // PIO_GPIOHS
                        FUNC_I2C1_SCLK, // PIO_I2C
                        FUNC_DEBUG0,    // PIO_SPI
                        FUNC_DEBUG0,    // PIO_UART
                        FUNC_DEBUG0,    // PIO_TIMER
                        FUNC_DEBUG0,    // PIO_I2S
                        FUNC_DEBUG0,    // PIO_CMOS
                        FUNC_DEBUG0,    // PIO_JTAG
                        FUNC_DEBUG0,    // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 42
                        FUNC_DEBUG0, // PIO_GPIO
                        FUNC_DEBUG0, // PIO_GPIOHS
                        FUNC_DEBUG0, // PIO_I2C
                        FUNC_DEBUG0, // PIO_SPI
                        FUNC_DEBUG0, // PIO_UART
                        FUNC_DEBUG0, // PIO_TIMER
                        FUNC_DEBUG0, // PIO_I2S
                        FUNC_DEBUG0, // PIO_CMOS
                        FUNC_DEBUG0, // PIO_JTAG
                        FUNC_DEBUG0, // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 43
                        FUNC_DEBUG0, // PIO_GPIO
                        FUNC_DEBUG0, // PIO_GPIOHS
                        FUNC_DEBUG0, // PIO_I2C
                        FUNC_DEBUG0, // PIO_SPI
                        FUNC_DEBUG0, // PIO_UART
                        FUNC_DEBUG0, // PIO_TIMER
                        FUNC_DEBUG0, // PIO_I2S
                        FUNC_DEBUG0, // PIO_CMOS
                        FUNC_DEBUG0, // PIO_JTAG
                        FUNC_DEBUG0, // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 44
                        FUNC_DEBUG0, // PIO_GPIO
                        FUNC_DEBUG0, // PIO_GPIOHS
                        FUNC_DEBUG0, // PIO_I2C
                        FUNC_DEBUG0, // PIO_SPI
                        FUNC_DEBUG0, // PIO_UART
                        FUNC_DEBUG0, // PIO_TIMER
                        FUNC_DEBUG0, // PIO_I2S
                        FUNC_DEBUG0, // PIO_CMOS
                        FUNC_DEBUG0, // PIO_JTAG
                        FUNC_DEBUG0, // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 45
                        FUNC_DEBUG0, // PIO_GPIO
                        FUNC_DEBUG0, // PIO_GPIOHS
                        FUNC_DEBUG0, // PIO_I2C
                        FUNC_DEBUG0, // PIO_SPI
                        FUNC_DEBUG0, // PIO_UART
                        FUNC_DEBUG0, // PIO_TIMER
                        FUNC_DEBUG0, // PIO_I2S
                        FUNC_DEBUG0, // PIO_CMOS
                        FUNC_DEBUG0, // PIO_JTAG
                        FUNC_DEBUG0, // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 46
                        FUNC_DEBUG0, // PIO_GPIO
                        FUNC_DEBUG0, // PIO_GPIOHS
                        FUNC_DEBUG0, // PIO_I2C
                        FUNC_DEBUG0, // PIO_SPI
                        FUNC_DEBUG0, // PIO_UART
                        FUNC_DEBUG0, // PIO_TIMER
                        FUNC_DEBUG0, // PIO_I2S
                        FUNC_DEBUG0, // PIO_CMOS
                        FUNC_DEBUG0, // PIO_JTAG
                        FUNC_DEBUG0, // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 47
                        FUNC_DEBUG0, // PIO_GPIO
                        FUNC_DEBUG0, // PIO_GPIOHS
                        FUNC_DEBUG0, // PIO_I2C
                        FUNC_DEBUG0, // PIO_SPI
                        FUNC_DEBUG0, // PIO_UART
                        FUNC_DEBUG0, // PIO_TIMER
                        FUNC_DEBUG0, // PIO_I2S
                        FUNC_DEBUG0, // PIO_CMOS
                        FUNC_DEBUG0, // PIO_JTAG
                        FUNC_DEBUG0, // PIO_DEBUG
                    },
            },
            {
                .PinType =
                    {
                        // 48
                        FUNC_DEBUG0, // PIO_GPIO
                        FUNC_DEBUG0, // PIO_GPIOHS
                        FUNC_DEBUG0, // PIO_I2C
                        FUNC_DEBUG0, // PIO_SPI
                        FUNC_DEBUG0, // PIO_UART
                        FUNC_DEBUG0, // PIO_TIMER
                        FUNC_DEBUG0, // PIO_I2S
                        FUNC_DEBUG0, // PIO_CMOS
                        FUNC_DEBUG0, // PIO_JTAG
                        FUNC_DEBUG0, // PIO_DEBUG
                    },
            },
};

#ifdef __cplusplus
}
#endif

#endif /* Pins_Arduino_h */
