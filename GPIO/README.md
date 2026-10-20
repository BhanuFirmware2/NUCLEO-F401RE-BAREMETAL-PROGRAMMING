# STM32F401RE - GPIO Control Using Bare-Metal C

## 1. Project Description
This project demonstrates GPIO output control using bare-metal Embedded C on the STM32F401RE microcontroller.

The program configures PA10 as an output pin and continuously switches it between HIGH and LOW states.

## 2. Hardware Requirements
- STM32 NUCLEO-F401RE development board
- USB cable
- External LED
- Current-limiting resistor
- Connecting wires

## 3. Software Requirements
- STM32CubeIDE
- Embedded C

## 4. GPIO Pin Configuration
- GPIO Port: GPIOA
- Pin Number: PA10
- Pin Mode: General-purpose output

## 5. Registers Used

### RCC_AHB1ENR
Enables the clock for GPIOA by setting bit 0.

### GPIOA_MODER
Configures PA10 as an output by setting bits 21:20 to `01`.

### GPIOA_ODR
Controls the output state of PA10.
- HIGH: Set bit 10.
- LOW: Clear bit 10.

## 6. Working Principle
1. Enable the GPIOA clock.
2. Configure PA10 as an output pin.
3. Set PA10 HIGH.
4. Execute a software delay loop.
5. Set PA10 LOW.
6. Execute another delay loop.
7. Repeat continuously.

## 7. Expected Output
PA10 continuously switches between HIGH and LOW.

An external LED connected correctly to PA10 will blink.

## 8. Important Note
The software delay is approximate. Its duration depends on CPU frequency and compiler optimization.

The onboard green LED on the NUCLEO-F401RE is connected to PA5, not PA10.

## 9. Learning Outcomes
- GPIO register programming
- Peripheral clock enabling
- GPIO output configuration
- Bitwise operations in Embedded C
- Bare-metal programming without HAL
