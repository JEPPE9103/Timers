## Overview
This project demonstrates how to control an LED using an AVR microcontroller. It includes features for blinking the LED at a configurable frequency, controlling the LED intensity with PWM, and reading and printing the voltage from a potentiometer.

## Hardware
- AVR microcontroller (e.g., ATmega328P)
- LED
- Potentiometer
- Resistors
- Connecting wires
## Software
- Arduino IDE or avr-gcc
## Setup
- Clone this repository.
- Connect the AVR microcontroller to your computer using a programmer.
- Open Arduino IDE or avr-gcc and upload the code to the microcontroller.
## Usage
- Blinking LED: The frequency of the blinking LED can be adjusted using a potentiometer. Turn the potentiometer to change the frequency.
- LED intensity: The intensity of the LED can be controlled using a command sent via serial communication. Send the command ledpowerfreq <intensity> <period> where <intensity> is a number between 0 and 255 (0 is 
  off, 255 is maximum intensity) and <period> is a number between 200 and 5000 (in milliseconds).
- Voltage reading: The voltage from the potentiometer is read and printed to the serial port.
## Contributions
All contributions are welcome! You can contribute by submitting pull requests to this repository.

License
This project is licensed under the MIT License.
