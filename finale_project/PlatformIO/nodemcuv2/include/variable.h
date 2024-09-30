/*! @file variable.h
 *  @version 1.0.0
*/

#pragma once

#include "Arduino.h"

// #define LED_RED           D4
// #define LED_YELLOW        D2

#define LED_YELLOW        D5
#define LED_RED           D6

#define TRIG_PIN          D7
#define ECHO_PIN          D8

// #define RX_TX             D5
// #define TX_RX             D6

#define SCL_PIN           D1
#define SDA_PIN           D2

#define BOOTBUTTON        D3

#define EMPTY             14
#define FULL              5

#define I2C_SLAVE_ADDR    0x08
#define JSONSIZE          200

#define EEPROM_BLYNK_ADDR 0x4 // don't replace it...