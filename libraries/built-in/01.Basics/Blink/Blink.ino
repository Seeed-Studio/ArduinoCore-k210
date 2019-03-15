/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
#include "Arduino.h"
#include <stdio.h>

//# define REG32_PTR(x)  (*reinterpret_cast<volatile uint32_t *>(x))


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}
void dump_reg(uint32_t reg, uint32_t size){
  # define REG32_VAL(x) (*reinterpret_cast<volatile uint32_t *>(x))

    // int i;
    // for(i = 0;i < size ; i += 4){
    //   printf("reg: %x ,val: %x \r\n",reg, REG32_VAL(reg));
    //   reg += i;
    // }
    printf("reg: 0x38001000U ,val: %x \r\n", REG32_VAL(0x38001000U));
    printf("reg: 0x38001004U ,val: %x \r\n", REG32_VAL(0x38001004U));
    printf("reg: 0x38001008U ,val: %x \r\n", REG32_VAL(0x38001008U));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x3800100cU));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x38001010U));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x38001014U));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x38001018U));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x3800101CU));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x38001020U));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x38001024U));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x38001028U));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x3800102CU));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x38001030U));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x38001034U));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x38001038U));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x3800103CU));
    printf("reg: 0x3800100CU ,val: %x \r\n", REG32_VAL(0x38001040U));
}
// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  dump_reg(0x38001000U,0x40);
   printf("---------- \r\n");
}

