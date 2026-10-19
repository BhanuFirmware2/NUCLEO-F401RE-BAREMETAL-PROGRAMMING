# STM32F401RE - GPIO LED Blinking

## 1. Project Description
This project demonstrates GPIO output control using bare-metal Embedded C on the STM32F401RE microcontroller.

The program configures PA10 as an output pin and repeatedly turns the output ON and OFF.

## 2. Hardware Requirements
- STM32 NUCLEO-F401RE development board
- USB cable
- External LED
- Current-limiting resistor
- Connecting wires
- Computer with STM32CubeIDE

## 3. Software Requirements
- STM32CubeIDE
- Embedded C

## 4. Registers Used

**RCC_AHB1ENR**
- Enables the GPIOA peripheral clock.
- Bit 0 is set to enable GPIOA.

**GPIOA_MODER**
- Configures the GPIO pin mode.
- Bits 21:20 are configured as `01` to set PA10 as output.

**GPIOA_ODR**
- Controls the GPIO output state.
- Bit 10 is set to turn the output HIGH.
- Bit 10 is cleared to turn the output LOW.

## 5. Working Principle
1. Enable the GPIOA clock.
2. Configure PA10 as an output.
3. Set PA10 HIGH.
4. Execute a delay loop.
5. Set PA10 LOW.
6. Execute another delay loop.
7. Repeat continuously.

## 6. Expected Output
The output at PA10 alternates between HIGH and LOW continuously.

When an LED is connected correctly, it blinks continuously.

## 7. Important Note
The delay is generated using a software loop. Its actual timing depends on the CPU clock and compiler optimization settings.

## 8. Learning Outcomes
- Understanding GPIO registers
- Enabling peripheral clocks
- Configuring GPIO output mode
- Setting and clearing output bits
- Writing bare-metal Embedded C programs
