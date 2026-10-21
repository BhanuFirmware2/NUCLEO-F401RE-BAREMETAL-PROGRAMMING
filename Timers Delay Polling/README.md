# STM32F401RE – LED Blinking Using TIM2 Polling

## Project Description

This project demonstrates LED blinking on the STM32 Nucleo-F401RE board using bare-metal Embedded C programming.

The onboard D2 LED is connected to PA10. The LED is toggled every 1 second using the TIM2 hardware timer and polling method.

No STM32 HAL functions or system clock configuration are used. The program accesses peripheral registers directly using their memory addresses.

## Hardware Requirements

- STM32 Nucleo-F401RE development board
- USB cable
- Computer with Windows 10 or Windows 11

## Software Requirements

- STM32CubeIDE
- GNU Arm Embedded Toolchain
- ST-LINK debugger

## Technical Details

| Parameter | Description |
|---|---|
| Microcontroller | STM32F401RE |
| Programming Language | Embedded C |
| Programming Method | Bare-metal programming |
| Clock Source | Internal HSI oscillator |
| HSI Frequency | 16 MHz |
| Timer | TIM2 |
| Delay Method | Timer polling |
| LED Pin | PA10 |
| Arudino Pin| D2 |
| HAL Library | Not used |
| System Clock Configuration | Not used |

## Working Principle

1. Enable the GPIOA peripheral clock using RCC_AHB1ENR.
2. Enable the TIM2 peripheral clock using RCC_APB1ENR.
3. Configure PA10 as a GPIO output.
4. Configure TIM2 prescaler and auto-reload registers.
5. Reset the timer counter and generate an update event.
6. Start TIM2.
7. Poll the update interrupt flag (UIF) in TIM2_SR until it becomes 1.
8. Stop the timer and clear the update flag.
9. Toggle the LED connected to PA10.
10. Repeat the process continuously.

## Timer Configuration

The intended timer input clock is 16 MHz.

- Prescaler (PSC) = 15
- Auto-reload value (ARR) = 999999
- Counter starts from 0

Prescaler calculation:

Timer counter frequency:

16 MHz / (15 + 1) = 1 MHz

Counter period:

(999999 + 1) / 1 MHz = 1 second

Therefore, the timer update event occurs after approximately 1 second, provided the TIM2 input clock is actually 16 MHz.

## Register-Level Programming

The program directly accesses these registers:

- RCC_AHB1ENR – Enables the GPIOA clock.
- RCC_APB1ENR – Enables the TIM2 clock.
- GPIOA_MODER – Configures PA10 as an output.
- GPIOA_ODR – Toggles the LED output.
- TIM2_CR1 – Controls the timer.
- TIM2_PSC – Sets the prescaler.
- TIM2_ARR – Sets the auto-reload value.
- TIM2_CNT – Holds the timer counter value.
- TIM2_EGR – Generates a timer update event.
- TIM2_SR – Contains the timer status flags.

## Learning Outcomes

- Understanding STM32 memory-mapped registers.
- Enabling peripheral clocks using RCC registers.
- Configuring GPIO output pins.
- Understanding timer prescalers and auto-reload values.
- Implementing a delay using timer polling.
- Learning bare-metal embedded C programming without HAL.

## Important Note

This implementation assumes that the TIM2 input clock is 16 MHz. On STM32F401RE, the default clock configuration after reset normally uses HSI at 16 MHz, but the actual clock configuration must be verified if startup code or other software changes it.

The timer delay depends on the actual TIM2 input clock frequency.

