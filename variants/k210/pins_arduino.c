#include "pins_arduino.h"
const fpioa_cfg_t g_fpioa_cfg =
{
    .version = PIN_CFG_VERSION,
    .functions_count = 2,
    .functions =
    {
        {6, FUNC_GPIOHS2},
        {7, FUNC_GPIOHS3}
    }
};
