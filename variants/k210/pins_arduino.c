#include "pins_arduino.h"
const fpioa_cfg_t g_fpioa_cfg =
{
    .version = PIN_CFG_VERSION,
    .functions_count = 2,
    .functions =
    {
       // {12, FUNC_GPIOHS0},
        {13, FUNC_GPIOHS2},
        {14, FUNC_GPIOHS3}
    }
};
