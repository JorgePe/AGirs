# AGirs (formerly ArduinoGirs)
This project implements a [Girs
server](http://www.harctoolbox.org/Girs.html) for the Arduino. That
is, it is an interactive server that can send and receive IR signals,
with some bells and whistles. The interactive server is mainly meant
for interact with other programs. communicating over a serial line
(likely in USB disguise), TCP-, or UDP sockets, acting as server
(accepting incoming requests) or client (initiating connections).

It implements some of the functionality of [Chris Young's
IRLib](http://tech.cyborg5.com/irlib/,
https://github.com/cyborg5/IRLib), which is a major
rewrite of a previous library called IRremote, published by
Ken Shirriff in [his blog](http://www.righto.com/2009/08/multi-protocol-infrared-remote-library.html), but does not use it directly.
It uses Michael Dreher's
IrWidget [(article in
German)](http://www.mikrocontroller.net/articles/High-Speed_capture_mit_ATmega_Timer),
see also [this forum
contribution](http://www.hifi-remote.com/forums/viewtopic.php?p=111876#111876).
Michael's code is included, in somewhat modified form, in the files
IrWidget.[cpp,h] and IrWidgetAggregating.[cpp,h].

The project contains a library, contained in the directory GirsLib,
and a few applications, presently Girs, GirsLite, Girs4Lirc, Listener,
and others. The directory GirsLib should
be copied to
the library area, typically <b>$HOME/Arduino/libraries/GirsLib</b>, while the
application directories can be processed by the Arduino IDE
directly. The directory Girs contains the AGirs application
interactive program. Listener is a uni-directional program that just
emits decodes on the serial interface. It is intended to be used in
conjunction with my Java program
[dispatcher](https://github.com/bengtmartensson/dispatcher). (It may
possibly be discontinued in the future.)

## Configuration
It is a modular program that is heavily based on CPP symbols, defined
in the configuration file <code>config.h</code>. This determines the capacities of the
compiled program, and adapts the configuration to the underlying
hardware. The options are (somewhat) documented in <code>Girs/config.h</code>.
Not all combination are sensible or implemented. Some of the non-sensible
combinations will be detected and will generate a compilation error.

## Code organization
There is a "library" (in the Arduino sense), <code>src/GirsLib</code>, which should be copied/moved/linked to the Arduino library area,
typically <code>~/Arduino/libraries</code> or <code>C:\Arduino\libraries</code>.
The other sub-directories of <code>src</code> contain different sketches that can
be compiled and run on the Arduino.

Due to the quirks of the preprocessor of the Arduino IDE, the following rule is used:
The <code>_program_.ino</code> is kept empty, except for some dummy <code>#include</code>s,
necessary for the IDE to find the libraries. The real code goes into <code>_program_.cpp</code>.
For further motivation, see [this article](http://www.gammon.com.au/forum/?id=12625).
(however, "__Third__" therein does not appear to be valid with current software.)

## Hardware configuration
The hardware configuration is determined by including a suitable
header file. It describes the attach sensor(s) and the pins
they are connected to. To allow soldering sensors directly to the
holes in some boards, the program supports defining e.g. SENSOR_GND
and SENSOR_VSS, which will make the program define these pins as
digital outputs, being fed by constant 0 and 5 volts respectively.

Note that the sending pin and the capture pin
(as opposed to the receive pin) are not configurable, but has to
follow the following table:

<pre>
                          Sender Pin      Capture Pin
Uno/Nano (ATmega328P)          3             8
Leonardo/Micro (ATmega32U4)    9             4
Mega2560 (ATmega2560)          9            49
</pre>

## Sending non-modulated signals.
RF signals (433 MHz and other carrier frequencies) do not use the IR
typical modulation. Also there are a few IR protocols (like [Revox, Barco,
Archer](http://www.hifi-remote.com/forums/viewtopic.php?t=14186&start=40))
not using modulation. These signals can be sent by defining the symbol
__NON_MOD__, and connecting
some hardware capable of sending non-modulated signals (IR- _or_ RF-)
to the GPIO pin defined as NON_MOD_PIN. Then transmitted signals
having frequency 0 will be directed to that device. (Later versions
may use different syntax and semantic.)

## Testing
The flashed unit can be tested with a standard terminal program, like the
serial monitor of the Arduino IDE. For this, set the baud rate to 115200, and
the line ending to carriage return. It is now possible to communicate
with the unit using the [commands of
Girs](http://www.harctoolbox.org/Girs.html). Just type the command to
the program, and the unit will respond.
Exactly which commands are
available depends on the configuration. In all cases, the
<code>version</code> and the <code>modules</code> commands are
available. If <code>receive</code> is implemented, just type
"<code>r</code>" (without the
quotes), followed by return, and fire a suitable IR signal at the
receiver. The raw capture will be output to the terminal program. Using
the clipboard, it can be pasted to IrScrutinizer, and analyzed. Of course, also
the other commands can be tested in this way.

## Dependencies

* [Infrared4Arduino](https://github.com/bengtmartensson/Infrared4Arduino) by myself. (In earlier versions
  of this project, this was integrated.)
* Ethernet (if enabling the ETHERNET configure option). Contained in the Arduino IDE.
* SPI (if enabling the ETHERNET or LCD_I2C configure option). Contained in the Arduino IDE.
* Wire (if enabling the LCD_I2C configure option). Contained in the Arduino IDE.
* [Arduino-LiquidCrystal-I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) version 1.1.2.
Needed if defining LCD_I2C, i.e. connecting an LCD display with an I2C interface card.

## Questions and answers

* What is the difference between
  ["receive"](http://www.harctoolbox.org/Glossary.html#ReceivingIrSignals)
  and   ["capture"](http://www.harctoolbox.org/Glossary.html#Capturing)?

Please follow the links given. Differently put, "receive" uses a
demodulating receiver, "capture" a non-demodulating decoder. Note that
this is not universally accepted terminology (yet!).

* What Ethernet modules are supported?

Only cards based on the W5100 chip (and compatible), like the
[official
shield](https://www.arduino.cc/en/Main/ArduinoEthernetShield).  There are both cheap clones of the original available, as well as
smallish W5100-based cards.

* What about "GirsLite"?

"GirsLite" was a predecessor to the present program. As indicated by the
name, it is a minimalist Girs server
for the Arduino, that implements only the
[capture](http://www.harctoolbox.org/Girs.html#Capture) and the
[transmit](http://www.harctoolbox.org/Girs.html#Transmit) modules,
without all options. This was meant to be used with
[IrScrutinizer](http://www.harctoolbox.org/IrScrutinizer.html)
versions 1.1.*. Presently, it is not an independent program, it is just AGirs
with certain options enabled, namely
the CPP symbols TRANSMIT, CAPTURE, LED, and (optionally) NON_MOD
defined. Alternatively, if RECEIVE is defined, but not CAPTURE, the
program mimics the capture command with a demodulating sensor, for
usage with IrScrutinizer without a non-demodulating sensor.

* What about Girs4Lirc?

This is a version of Girs, "optimized" for Lirc, using the Lirc
<code>girs</code> driver by yours truly. At the time of this writing,
it is not yet found in the
released Lirc, but in the "master" branch in its Sourceforge
repository, which can be checkout with the command

<pre>git clone git://git.code.sf.net/p/lirc/git lirc-git</pre>

Like GirsLite, this is not an independent program, but corresponds to a version of AGirs supporting TRANSMIT,
NON_MOD (optionally), RECEIVE, LED, LCD, DECODE (only to the LCD), TRANSMITTERS
(only a dummy implementation). Documentation is found with the Lirc
driver, in the file <code>girs_driver.html</code>.

## License
The entire work is licensed under the GPL3 license. Chris' as well as Ken's
code is licensed under the LGPL 2.1-license. Michael's code carries the
GPL2-license, although he is [willing to agree to "or later
versions"](http://www.hifi-remote.com/forums/viewtopic.php?p=112586#112586).
