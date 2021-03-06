// Configuration for Arduino Nano with components soldered on the PCB.

#ifndef GIRS_PINS_NANO_LCD_H
#define GIRS_PINS_NANO_LCD_H

#ifndef ARDUINO_AVR_NANO
#error This file is for Nano only
#endif

#ifdef LED
#define SIGNAL_LED_1 13
#define SIGNAL_LED_2 A1
#define SIGNAL_LED_2_GND A0
#define SIGNAL_LED_3 A3
#define SIGNAL_LED_3_GND A2
#define SIGNAL_LED_4 11
//#define SIGNAL_LED_4_GND A4
//#define SIGNAL_LED_5 A7
//#define SIGNAL_LED_5_GND A6
#endif

#if defined(CAPTURE)
// capture pin (ICP) 8
#ifndef ETHERNET
#define SENSOR_GND 9
#define SENSOR_VSS 10
#endif
#endif

#ifdef RECEIVE
#define IRRECEIVER_1_PIN 12
#endif

#ifdef TRANSMIT
// Send pin 3
#endif

#endif // ! GIRS_PINS_NANO_LCD_H
