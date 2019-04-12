# ArduinoCore-k210

 ArduinoCore-k210. Based on [kendryte-standalone-sdk](https://github.com/kendryte/kendryte-standalone-sdk), we added the full ArduinoCore-API interface to support Arduino IDE, Linux, Windows, Mac OS X and other development environments. With the support of the ArduinoCore-k210, all k210-based development boards can run Grove Arduino Library and many excellent [Arduino libraries](https://www.arduinolibraries.info/) in the community of Arduino. If you're not familiar with Arduino, you can find the documentation you need [here](https://www.arduino.cc/en/Guide/HomePage).


## Add the k210-based board to the Arduino IDE

### Step 1. Download the latest Arduino IDE

You need a Arduino IDE that after version 1.6.4, please download one if there's no Arduino IDE in your computer.

[![](https://raw.githubusercontent.com/SeeedDocument/Seeeduino_Stalker_V3_1/master/images/Download_IDE.png)](https://www.arduino.cc/en/Main/Software)

### Step 2. Setting your Arduino IDE

Open your Arudino IDE, click on **File > Preferences**, and copy below url to *Additional Boards Manager URLs*

```
https://raw.githubusercontent.com/Seeed-Studio/Seeed_Platform/master/package_seeeduino_boards_index.json
```

Note:No additional Settings are required on Windows, but on Linux and Macosx platforms, kflash requires python3 environment and you will need to execute the following command to install the dependent software.`
```
#Maciosx
brew install python  pip
pip3 install pyserial
brew install isl
brew install libmpc
```
```
#ubuntu or debian
sudo apt update
sudo apt install python3 python3-pip
sudo pip3 install pyserial

```

## Build ArduinoCore-k210 with cmake

```
git clone https://github.com/kendryte/kendryte-standalone-sdk
git clone https://github.com/seeed-Studio/ArduinoCore-k210 kendryte-standalone-sdk/src
mkdir build && cd build
cmake .. -DPROJ=ArduinoCore-k210  -DSKETCH=Blink -DTOOLCHAIN=/opt/kendryte-toolchain/bin && make -j8
```
cmake is very friendly on Linux and Macosx. You can even add a lot of third-party libraries. Here's an [example](https://github.com/Seeed-Studio/ArduinoCore-k210/blob/kendryte-standalone-sdk/micropython.cmake) of adding miropython as a third party

##  Developing kendryte-standalone-sdk
ArduinoCore-k210 is also supported as a normal IDE. For example, when developing kendryte-standalone-sdk, you also can use the [Arduino Library WS2812FX](https://github.com/kitesurfer1404/WS2812FX). This way you can run all the [kendryte-standalone-demo](https://github.com/kendryte/kendryte-standalone-demo) in the Arduino IDE.
```cpp
#include <WS2812FX.h>

#define LED_COUNT 32
#define LED_PIN 13

#define TIMER_MS 5000

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

unsigned long last_change = 0;
unsigned long now = 0;

extern "C" {
#include <stdio.h>
#include <unistd.h>
#include "fpioa.h"
#include "gpiohs.h"
#include "sysctl.h"

uint32_t irq_flag;

#define PIN_LED 25
#define PIN_KEY 26

#define GPIO_LED 3
#define GPIO_KEY 2

uint32_t g_count;

int irq_gpiohs2(void* ctx)
{
    irq_flag = gpiohs_get_pin(GPIO_KEY);

    printf("IRQ The PIN is %d\n", irq_flag);

    uint32_t *tmp = (uint32_t *)(ctx);
    printf("count is %d\n", (*tmp)++);

    if (!irq_flag)
        gpiohs_set_pin(GPIO_LED, GPIO_PV_LOW);
    else
        gpiohs_set_pin(GPIO_LED, GPIO_PV_HIGH);
    return 0;
}

int main(){
#define NOFREERTOS 1

  plic_init();
  sysctl_enable_irq();

  fpioa_set_function(PIN_LED, FUNC_GPIOHS3);
  gpiohs_set_drive_mode(GPIO_LED, GPIO_DM_OUTPUT);
  gpio_pin_value_t value = GPIO_PV_HIGH;
  gpiohs_set_pin(GPIO_LED, value);

  fpioa_set_function(PIN_KEY, FUNC_GPIOHS2);
  gpiohs_set_drive_mode(GPIO_KEY, GPIO_DM_INPUT_PULL_UP);
  gpiohs_set_pin_edge(GPIO_KEY, GPIO_PE_BOTH);

  gpiohs_irq_register(GPIO_KEY, 1, irq_gpiohs2, &g_count);


  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setSpeed(1000);
  ws2812fx.setColor(0x007BFF);
  ws2812fx.setMode(FX_MODE_STATIC);
  ws2812fx.start();
  while(1){
      now = millis();
    
      ws2812fx.service();
    
      if(now - last_change > TIMER_MS) {
        ws2812fx.setMode((ws2812fx.getMode() + 1) % ws2812fx.getModeCount());
        last_change = now;
      }    
    }
 return 0; 
 }
}

```

## FAQ
ArduinoCore-k210 is a very interesting software project to help all of you develop AI in an easier way. We can't guarantee that there is no any of bug.  If you encounter any compatibility issues or have any new ideas, feel free to check our [GitHub link](https://github.com/Seeed-Studio/ArduinoCore-k210/issues) and forum to communicate with us, we will try our best to solve the problems you have encountered. 