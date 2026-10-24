# Circuit and Pin Connections

This document uses the pin mapping previously provided for the project. The video shows the physical demonstration, but its close-up wiring is not clear enough to independently verify every connection.

| Component | Component pin | Arduino Uno connection |
|---|---|---|
| I2C LCD 16x2 | VCC | 5V |
| I2C LCD 16x2 | GND | GND |
| I2C LCD 16x2 | SDA | A4 |
| I2C LCD 16x2 | SCL | A5 |
| Servo motor | Signal | D8 |
| Servo motor | VCC | Suitable 5V supply |
| Servo motor | GND | Common GND |
| PIR sensor | VCC | 5V |
| PIR sensor | GND | GND |
| PIR sensor | OUT | D9 |
| Green LED | Anode through 220Ω resistor | D6 |
| Red LED | Anode through 220Ω resistor | D7 |
| HC-SR04 #1 | TRIG / ECHO | D10 / D13 |
| HC-SR04 #2 | TRIG / ECHO | A0 / A1 |
| HC-SR04 #3 | TRIG / ECHO | A2 / A3 |
| All sensors | VCC / GND | 5V / common GND |

## Safety and verification notes
- All component grounds must be connected together.
- Use a 220Ω–330Ω resistor in series with each LED.
- A servo can draw more current than the Arduino 5V output can comfortably provide. If the board resets or the LCD flickers, use a separate regulated 5V supply for the servo and connect its ground to Arduino GND.
- The Arduino Uno's A0–A3 pins can be used as digital I/O for the second and third ultrasonic sensors.
- Verify the final wiring physically before powering the circuit. The diagram is based on the project's previously stated pin mapping, not a frame-by-frame electrical verification.
