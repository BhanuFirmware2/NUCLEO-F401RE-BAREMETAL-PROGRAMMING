# STM32F401RE GPIO Button Control Using Bare-Metal Programming

## 1. Project Overview

This project uses a push button to control an output pin on the STM32 Nucleo-F401RE board.

- PA9 is used as an input pin.
- PA10 is used as an output pin.
- When the button is pressed, PA10 becomes HIGH.
- When the button is released, PA10 becomes LOW.

This project uses direct register programming without HAL functions.

## 2. Hardware Requirements

- STM32 Nucleo-F401RE development board
- Push button
- Jumper wires
- External LED and resistor (optional)
- USB cable

## 3. Software Requirements

- STM32CubeIDE
- Embedded C
- Bare-metal register programming

## 4. GPIO Pin Configuration

| Pin | Mode | Purpose |
|---|---|---|
| PA9 | Input with pull-up | Read button state |
| PA10 | Output | Control the output |

## 5. Registers Used

| Register | Purpose |
|---|---|
| RCC_AHB1ENR | Enable the GPIOA clock |
| GPIOA_MODER | Configure GPIO pins as input or output |
| GPIOA_PUPDR | Enable the internal pull-up resistor |
| GPIOA_IDR | Read the input pin state |
| GPIOA_ODR | Set or reset the output pin |

## 6. Working Principle

1. Enable the GPIOA clock using the RCC register.
2. Configure PA10 as an output pin.
3. Configure PA9 as an input pin.
4. Enable the internal pull-up resistor on PA9.
5. Read the button state continuously.
6. If PA9 is LOW, set PA10 HIGH.
7. If PA9 is HIGH, set PA10 LOW.

## 7. Code Explanation

### Enable GPIOA Clock

`RCC_AHB1ENR |= (1U << 0);`

This enables the clock for GPIO port A.

### Configure PA10 as Output

`GPIOA_MODER &= ~(3U << 20);`

`GPIOA_MODER |= (1U << 20);`

These statements configure PA10 as an output pin.

### Configure PA9 as Input

`GPIOA_MODER &= ~(3U << 18);`

This configures PA9 as an input pin.

### Enable Pull-Up Resistor

`GPIOA_PUPDR &= ~(3U << 18);`

`GPIOA_PUPDR |= (1U << 18);`

These statements enable the internal pull-up resistor on PA9.

### Read Button State

`GPIOA_IDR & (1U << 9)`

This checks the logic level of PA9.

### Control Output

`GPIOA_ODR |= (1U << 10);`

Sets PA10 HIGH.

`GPIOA_ODR &= ~(1U << 10);`

Sets PA10 LOW.

## 8. Expected Output

- Button pressed: PA9 becomes LOW and PA10 becomes HIGH.
- Button released: PA9 becomes HIGH and PA10 becomes LOW.

## 9. Concepts Learned

- GPIO input and output
- RCC clock enable
- Memory-mapped registers
- Register addresses
- Bit shifting and bitwise operators
- Internal pull-up resistor
- IDR and ODR registers
- Bare-metal Embedded C programming


