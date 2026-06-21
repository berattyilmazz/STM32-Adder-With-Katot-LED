STM32F407VGT6 – 4 Digit 7-Segment Display & ADC Project

Project Overview

This project is implemented using the STM32F407VGT6 microcontroller. It features 4 common cathode 7-segment displays, 
2 potentiometers connected via ADC inputs, and an interrupt-based control system for dynamic operation.

Hardware Components
  - STM32F407VGT6 microcontroller
  - 4 × common cathode 7-segment displays
  - 2 × potentiometers
  - ADC (Analog-to-Digital Converter) usage
  - External / internal interrupt structure
    
ADC Channel Connections
  - PC3 → ADC2 Channel 13
  - PA1 → ADC3 Channel 1
    
Display Layout
  - The physical arrangement of the displays is:
    - 4 | 3 | 2 | 1

7-Segment Pin Connections
  - LED 4
    - PA3 → A
    - PA2 → B
    - PD11 → C
    - PD10 → D
    - PD9 → E
    - PA4 → F
    - PA5 → G
      
  - LED 3
    - PA7 → A
    - PA6 → B
    - PD8 → C
    - PB15 → D
    - PB14 → E
    - PC4 → F
    - PC5 → G
      
  - LED 2
    - PB1 → A
    - PB0 → B
    - PB13 → C
    - PB12 → D
    - PB11 → E
    - PB2 → F
    - PE7 → G
      
  - LED 1
    - PE9 → A
    - PE8 → B
    - PE14 → C
    - PE13 → D
    - PE12 → E
    - PE10 → F
    - PE11 → G
