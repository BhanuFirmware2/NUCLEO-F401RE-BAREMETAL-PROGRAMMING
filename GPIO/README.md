# STM32F401RE Bare-Metal LED Blinking

## Project Description

This project demonstrates LED blinking using the STM32 Nucleo-F401RE development board.

The LED is controlled using direct register access in Embedded C without using STM32 HAL libraries.

GPIO pin PA10 is configured as an output pin. The program turns the LED ON and OFF continuously using a software delay loop.

## Hardware Requirements

- STM32 Nucleo-F401RE development board
- External LED
- 220–330 Ω current-limiting resistor
- Breadboard and jumper wires
- USB cable

## Software Requirements

- Windows 10 / Windows 11
- STM32CubeIDE
- GNU Arm Embedded Toolchain
- ST-LINK debugger

## Hardware Connections

| STM32 Pin | Connection |
|---|---|
| PA10 | LED anode (+) through a resistor |
| GND | LED cathode (−) |

**Note:** Use a current-limiting resistor in series with the LED.

## Registers Used

| Register | Purpose |
|---|---|
| RCC_AHB1ENR | Enables the GPIOA peripheral clock |
| GPIOA_MODER | Configures PA10 as an output |
| GPIOA_ODR | Sets PA10 HIGH or LOW |

## Working Principle

1. Enable the GPIOA peripheral clock using RCC_AHB1ENR.
2. Configure PA10 as a general-purpose output using GPIOA_MODER.
3. Set PA10 HIGH to turn the external LED ON.
4. Execute the software delay loop.
5. Set PA10 LOW to turn the LED OFF.
6. Execute the delay loop again.
7. Repeat continuously inside the `while(1)` loop.

## Programming Method

- Bare-Metal Programming
- Direct register access
- Embedded C
- No STM32 HAL functions used

## Expected Output

The external LED connected to PA10 blinks continuously.

**Note:** The delay loop is a software delay, so its actual duration depends on the clock frequency, compiler optimization, and generated machine instructions.
