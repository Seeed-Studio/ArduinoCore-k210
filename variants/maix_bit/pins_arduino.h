#pragma once
#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>
#include <fpioa.h>
#define LED_BUILTIN 13
typedef enum _EPioType
{
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

typedef struct _PinDescription
{
    fpioa_function_t PinType[PIO_DEBUG + 1];
} PinDescription;

PinDescription __attribute__((weak)) pin_map[] = {
    {
        //0
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //1
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //2
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //3
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //4
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //5
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //6
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //7
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //8
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //9
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //10
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //11
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //12
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //13
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //14
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //15
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //16
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //17
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //18
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //19
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //20
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //21
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //22
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //23
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //24
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //25
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //26
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //27
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //28
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //29
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //30
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //31
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //32
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //33
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //34
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //35
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //36
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //37
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //38
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //39
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //40
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //41
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //42
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //43
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //44
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //45
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //46
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //47
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
    {
        //48
        FUNC_DEBUG0, //PIO_GPIO
        FUNC_DEBUG0, //PIO_GPIOHS
        FUNC_DEBUG0, //PIO_I2C
        FUNC_DEBUG0, //PIO_SPI
        FUNC_DEBUG0, //PIO_UART
        FUNC_DEBUG0, //PIO_TIMER
        FUNC_DEBUG0, //PIO_I2S
        FUNC_DEBUG0, //PIO_CMOS
        FUNC_DEBUG0, //PIO_JTAG
        FUNC_DEBUG0, //PIO_DEBUG
    },
};

#endif /* Pins_Arduino_h */
