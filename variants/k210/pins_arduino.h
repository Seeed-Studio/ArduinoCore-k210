#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>
#include <fpioa.h>
#define LED_BUILTIN 13

fpioa_function_t __attribute__((weak)) pin_map[48] = {
    FUNC_DEBUG0, //0
    FUNC_DEBUG0, //1
    FUNC_DEBUG0, //2
    FUNC_DEBUG0, //3
    FUNC_UART1_RX, //4
    FUNC_UART1_TX, //5
    FUNC_DEBUG0, //6
    FUNC_DEBUG0, //7
    FUNC_DEBUG0, //8
    FUNC_DEBUG0, //9
    FUNC_DEBUG0, //10
    FUNC_DEBUG0, //11
    FUNC_GPIOHS12, //12
    FUNC_GPIOHS13, //13
    FUNC_GPIOHS14, //14
    FUNC_DEBUG0, //15
    FUNC_DEBUG0, //16
    FUNC_DEBUG0, //17
    FUNC_DEBUG0, //18
    FUNC_DEBUG0, //19
    FUNC_DEBUG0, //20
    FUNC_DEBUG0, //21
    FUNC_DEBUG0, //22
    FUNC_DEBUG0, //23
    FUNC_DEBUG0, //24
    FUNC_DEBUG0, //25
    FUNC_DEBUG0, //26
    FUNC_DEBUG0, //27
    FUNC_DEBUG0, //28
    FUNC_DEBUG0, //29
    FUNC_DEBUG0, //30
    FUNC_DEBUG0, //31
    FUNC_DEBUG0, //32
    FUNC_DEBUG0, //33
    FUNC_DEBUG0, //34
    FUNC_DEBUG0, //35
    FUNC_DEBUG0, //36
    FUNC_DEBUG0, //37
    FUNC_DEBUG0, //38
    FUNC_DEBUG0, //39
    FUNC_DEBUG0, //40
    FUNC_DEBUG0, //41
    FUNC_DEBUG0, //42
    FUNC_DEBUG0, //43
    FUNC_DEBUG0, //44
    FUNC_DEBUG0, //45
    FUNC_DEBUG0, //46
    FUNC_DEBUG0, //47
};

#endif /* Pins_Arduino_h */