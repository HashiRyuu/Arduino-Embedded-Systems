# Arduino Embedded Systems

Three independent Arduino C/C++ projects exploring microcontroller programming, digital I/O, PWM, hardware interrupts, sensor interfacing, and real-time measurement.

## Projects

### 1. RGB LED control and color switching

[Source code](controlAndSwitchColor/controlAndSwitchColor.ino)

A push button toggles between a fixed green output and a continuously changing RGB color pattern. The sketch uses PWM through `analogWrite()`, active-low button input, and a 100 ms debounce interval.

| Signal | Arduino pin |
| --- | --- |
| Red | D6 |
| Green | D5 |
| Blue | D3 |
| Push button | D9 |

Use current-limiting resistors for each LED channel and connect the button to ground with the internal pull-up enabled. Verify LED polarity; the code's brightness mapping assumes active-high LED drive.

### 2. Fan tachometer and RPM measurement

[Source code](fanControl/fanControl.ino)

A falling-edge interrupt increments a volatile pulse counter. The main loop snapshots the count after a nominal two-second measurement window, temporarily disabling interrupts to prevent concurrent access during the reset and read.

| Signal | Arduino pin |
| --- | --- |
| Tachometer input | D2 |

The sketch assumes two tachometer pulses per revolution:

```text
RPM = (pulse count / pulses per revolution) × (60 / measurement time in seconds)
    = 15 × pulse count
```

Serial output runs at 9600 baud. Verify the fan's actual pulses-per-revolution specification, signal voltage, grounding, and pull-up requirements before connecting it. Use a compatible power supply for the fan, not a GPIO pin. This sketch measures speed; it does not implement closed-loop fan speed control.

### 3. DHT11 temperature and humidity monitor

[Source code](LCDRead/LCDRead.ino)

Reads a DHT11 sensor and displays temperature in Celsius and relative humidity on a 16×2 character LCD. Invalid sensor readings are detected using `isnan()` and reported on the display. The normal loop includes a 1500 ms delay.

| Signal | Arduino pin |
| --- | --- |
| DHT11 data | D7 |
| LCD RS | D12 |
| LCD E | D11 |
| LCD D4 | D5 |
| LCD D5 | D4 |
| LCD D6 | D3 |
| LCD D7 | D2 |

Dependencies: Arduino LiquidCrystal and a compatible DHT sensor library (e.g. Adafruit DHT sensor library and its required dependencies). Follow the specific LCD and sensor datasheets for power, contrast, pull-ups, and wiring. The sensor's supported sampling interval should be checked against the library and hardware specifications.

## Getting started

1. Install the Arduino IDE.
2. Select a compatible Arduino board and serial port. An Uno-style pin mapping is assumed; check PWM and external interrupt support on your board.
3. Open one sketch from its matching directory. These are separate projects, not a single combined firmware.
4. Install any required libraries, wire the hardware according to the sketch and component specifications, then compile and upload.
5. For the fan measurement, open Serial Monitor at 9600 baud.

## Engineering concepts

- PWM duty-cycle control and digital inputs
- Debouncing and state management
- Interrupt service routines and shared volatile state
- Pulse-frequency measurement and unit conversion
- Sensor data acquisition and parallel LCD interfacing
- Embedded error handling and serial diagnostics

## Verification status

The original sketches are preserved unchanged. Documentation is based on source inspection; compilation and physical hardware operation have not been independently verified. Pin assignments, timing assumptions, electrical compatibility, and library versions should be validated before deployment.
