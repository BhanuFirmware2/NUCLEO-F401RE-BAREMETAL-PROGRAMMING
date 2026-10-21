# STM32F401RE Bare-Metal Timer Interrupt LED Blinking

## Project Overview

This project demonstrates LED blinking using the TIM2 hardware timer and interrupts on the STM32 NUCLEO-F401RE development board.

The program is written in Embedded C using direct register access. It does not use the STM32 HAL library.

The timer generates an interrupt at a fixed interval. Whenever the interrupt occurs, the CPU executes the interrupt handler and toggles the GPIO output pin.

## Project Objectives

- Understand direct register programming in STM32.
- Configure GPIO pins using registers.
- Enable peripheral clocks using RCC registers.
- Configure the TIM2 hardware timer.
- Understand timer update events and interrupt flags.
- Enable interrupts using the NVIC.
- Write and execute an interrupt service routine (ISR).
- Debug timer registers using STM32CubeIDE.

## Hardware Requirements

- STM32 NUCLEO-F401RE development board.
- USB cable for programming and debugging.
- External LED and current-limiting resistor, if using PA10.
- Breadboard and jumper wires, if required.

**Important:** PA10 is used as the output pin in this project. The onboard user LED (LD2) on the NUCLEO-F401RE is connected to PA5, not PA10. Use an external LED on PA10 or change the GPIO configuration to PA5 for the onboard LED.

## Software Requirements

- IDE: STM32CubeIDE
- Programming Language: Embedded C
- Programming Method: Bare-Metal Programming
- Peripheral Configuration: Direct register access
- Libraries: No STM32 HAL functions used

## Project Features

- Direct memory-mapped register access.
- GPIO output configuration.
- RCC peripheral clock enable.
- TIM2 prescaler and auto-reload configuration.
- Timer update interrupt generation.
- NVIC interrupt enable.
- Interrupt Service Routine implementation.
- GPIO output toggling inside the interrupt handler.

## Register Definitions

The program uses the following memory-mapped registers.

| Register | Address | Purpose |
|---|---|---|
| RCC_AHB1ENR | `0x40023830` | Enables GPIO peripheral clocks |
| RCC_APB1ENR | `0x40023840` | Enables TIM2 peripheral clock |
| GPIOA_MODER | `0x40020000` | Configures GPIOA pin modes |
| GPIOA_ODR | `0x40020014` | Controls GPIOA output states |
| TIM2_CR1 | `0x40000000` | Controls timer operation |
| TIM2_DIER | `0x4000000C` | Enables timer interrupt requests |
| TIM2_SR | `0x40000010` | Contains timer status flags |
| TIM2_EGR | `0x40000014` | Generates timer events |
| TIM2_CNT | `0x40000024` | Holds the current timer count |
| TIM2_PSC | `0x40000028` | Sets the timer prescaler |
| TIM2_ARR | `0x4000002C` | Sets the timer auto-reload value |
| NVIC_ISER0 | `0xE000E100` | Enables NVIC interrupts 0–31 |

## Working of Each Register

### 1. RCC_AHB1ENR — GPIO Clock Enable

```c
RCC_AHB1ENR |= (1U << 0);
```

- Enables the GPIOA peripheral clock.
- Bit 0 corresponds to GPIOAEN.
- GPIOA must have its clock enabled before configuring its registers.

### 2. RCC_APB1ENR — TIM2 Clock Enable

```c
RCC_APB1ENR |= (1U << 0);
```

- Enables the TIM2 peripheral clock.
- Bit 0 corresponds to TIM2EN.
- TIM2 requires its peripheral clock to operate.

### 3. GPIOA_MODER — GPIO Mode Register

```c
GPIOA_MODER &= ~(3U << 20);
GPIOA_MODER |=  (1U << 20);
```

Each GPIO pin uses two bits in GPIOx_MODER.

For PA10, the relevant bits are 21 and 20.

| MODER bits | Mode |
|---|---|
| `00` | Input |
| `01` | General-purpose output |
| `10` | Alternate function |
| `11` | Analog |

The first statement clears bits 21 and 20. The second sets bit 20, configuring PA10 as a general-purpose output.

### 4. GPIOA_ODR — Output Data Register

```c
GPIOA_ODR ^= (1U << 10);
```

- Controls the output state of PA10.
- Bit 10 corresponds to PA10.
- XOR toggles the output state.

If PA10 is LOW, it becomes HIGH. If PA10 is HIGH, it becomes LOW.

### 5. TIM2_CR1 — Timer Control Register 1

```c
TIM2_CR1 = 0U;
TIM2_CR1 |= 1U;
```

- Initializes the timer control register.
- Bit 0 is CEN (Counter Enable).
- `CEN = 0`: Timer counter stopped.
- `CEN = 1`: Timer counter enabled.

The timer starts counting when CEN is set.

### 6. TIM2_PSC — Prescaler Register

```c
TIM2_PSC = 15U;
```

The prescaler divides the timer input clock.

Prescaler division factor:

`PSC + 1 = 15 + 1 = 16`

Assuming the TIM2 input clock is 16 MHz:

`Counter frequency = 16 MHz / 16 = 1 MHz`

The counter increments once every 1 microsecond.

### 7. TIM2_ARR — Auto-Reload Register

```c
TIM2_ARR = 999999U;
```

- Defines the timer counter's update limit.
- The counter counts from 0 through ARR.
- After reaching ARR, it generates an update event and starts the next counting cycle.

With a 1 MHz counter frequency:

`Timer period = (ARR + 1) / Counter frequency`

`Timer period = 1,000,000 / 1,000,000 = 1 second`

This calculation assumes a 16 MHz TIM2 input clock.

### 8. TIM2_CNT — Counter Register

```c
TIM2_CNT = 0U;
```

- Resets the timer counter to zero.
- The hardware increments the counter while the timer is enabled.
- The application does not need to increment CNT manually.

### 9. TIM2_EGR — Event Generation Register

```c
TIM2_EGR = 1U;
```

- Bit 0 is UG (Update Generation).
- Setting UG generates an update event.
- It is used to load buffered timer settings, including the prescaler, into the active timer logic.

An update event can set the update flag. The program clears UIF afterward to avoid handling the initialization event as a normal timer interrupt.

### 10. TIM2_SR — Status Register

```c
TIM2_SR &= ~(1U << 0);
```

- Bit 0 is UIF (Update Interrupt Flag).
- UIF indicates that a timer update event occurred.
- The interrupt handler checks UIF before toggling the output.

The expression clears bit 0 while preserving the other status bits.

**Important:** Do not use `TIM2_SR = ~1U` to clear UIF. That writes ones to the other status flags, potentially leaving them set, and is not the correct initialization operation.

### 11. TIM2_DIER — DMA/Interrupt Enable Register

```c
TIM2_DIER = 1U;
```

- Bit 0 is UIE (Update Interrupt Enable).
- UIE enables the timer's update interrupt request.
- When an update event occurs, TIM2 can request an interrupt.

Enabling UIE alone is not sufficient. The corresponding interrupt must also be enabled in the NVIC.

### 12. NVIC_ISER0 — Interrupt Set-Enable Register

```c
NVIC_ISER0 |= (1U << 28);
```

- NVIC stands for Nested Vectored Interrupt Controller.
- TIM2 global interrupt uses IRQ number 28 on the STM32F401RE.
- NVIC_ISER0 covers interrupt numbers 0–31.
- Bit 28 enables the TIM2 interrupt in the NVIC.

The NVIC passes the enabled interrupt request to the CPU when the required conditions are satisfied.

## Interrupt Service Routine (ISR)

```c
void TIM2_IRQHandler(void)
{
    if (TIM2_SR & 1U)
    {
        TIM2_SR &= ~(1U << 0);

        GPIOA_ODR ^= (1U << 10);
    }
}
```

### ISR Working

1. The timer reaches its auto-reload value.
2. An update event occurs.
3. UIF becomes set in TIM2_SR.
4. TIM2 generates an interrupt request because UIE is enabled.
5. The NVIC delivers the interrupt to the CPU.
6. The CPU executes `TIM2_IRQHandler()`.
7. The ISR checks the UIF flag.
8. The ISR clears UIF.
9. PA10 toggles between HIGH and LOW.
10. The CPU returns to the interrupted program.

The startup file must also contain the correct TIM2 interrupt vector so that the handler is called.

## Interrupt Enable Sequence

The timer interrupt requires these configurations:

| Step | Register | Configuration |
|---|---|---|
| 1 | RCC_APB1ENR | Enable TIM2 clock |
| 2 | TIM2_PSC | Set prescaler |
| 3 | TIM2_ARR | Set update period |
| 4 | TIM2_EGR | Generate an update event |
| 5 | TIM2_SR | Clear the initialization UIF flag |
| 6 | TIM2_DIER | Set UIE bit 0 |
| 7 | NVIC_ISER0 | Set IRQ bit 28 |
| 8 | TIM2_CR1 | Set CEN bit 0 |

The interrupt is operational only when the peripheral clock, timer configuration, interrupt enable, NVIC enable and interrupt vector are all correct.

## Timer Delay Calculation

Assumptions:

- TIM2 input clock = 16 MHz
- Prescaler = 15
- Auto-reload value = 999999

Counter frequency:

`16,000,000 / (15 + 1) = 1,000,000 Hz`

Timer period:

`(999999 + 1) / 1,000,000 = 1 second`

Expected behavior:

- One timer update interrupt every second.
- PA10 toggles once per interrupt.
- One complete ON/OFF cycle takes approximately 2 seconds.
- Expected blink frequency is 0.5 Hz.

The actual period depends on the TIM2 input clock. Verify the clock configuration before relying on this calculation.

## Program Working Flow

```text
Start
  |
  v
Enable GPIOA Clock
  |
  v
Enable TIM2 Clock
  |
  v
Configure PA10 as Output
  |
  v
Configure PSC, ARR and CNT
  |
  v
Generate Update Event
  |
  v
Clear UIF Flag
  |
  v
Enable TIM2 Update Interrupt
  |
  v
Enable TIM2 in NVIC
  |
  v
Start Timer
  |
  v
Timer Counts
  |
  v
Update Event Occurs
  |
  v
TIM2_IRQHandler Executes
  |
  v
Clear UIF and Toggle PA10
  |
  v
Return to Main Loop
```

## Debugging Using STM32CubeIDE

Use the Expressions window to inspect these register values while debugging.

| Expression | Expected result |
|---|---|
| `*(volatile unsigned int *)0x40023830` | GPIOA clock enable bit is set |
| `*(volatile unsigned int *)0x40023840` | TIM2 clock enable bit is set |
| `*(volatile unsigned int *)0x40000000` | CR1 bit 0 = 1 |
| `*(volatile unsigned int *)0x4000000C` | DIER bit 0 = 1 |
| `*(volatile unsigned int *)0x40000010` | UIF may be 0 or 1, depending on timing |
| `*(volatile unsigned int *)0x40000024` | CNT changes as the timer counts |
| `*(volatile unsigned int *)0xE000E100` | NVIC bit 28 = 1 |
| `*(volatile unsigned int *)0x40020014` | PA10 output state is represented by bit 10 |

To check the timer interrupt:

1. Build the project.
2. Start debugging.
3. Add the register expressions to the Expressions window.
4. Set a breakpoint inside `TIM2_IRQHandler()`.
5. Press Resume to allow the timer to run.
6. Check whether the debugger stops at the interrupt handler.
7. Inspect UIF and the PA10 output state.
8. Remove the breakpoint to observe uninterrupted operation.

**Note:** A status register may show multiple set flags. Check the relevant bit rather than interpreting the entire register value as a single flag.


## Learning Outcomes

After completing this project, you should understand:

- STM32 memory-mapped registers.
- RCC clock enable configuration.
- GPIO mode and output registers.
- Timer prescaler and auto-reload calculations.
- Timer status flags and update events.
- Peripheral interrupt enable through DIER.
- NVIC interrupt enabling.
- Interrupt Service Routine execution.
- Register-level debugging in STM32CubeIDE.


## Conclusion

This project demonstrates how to configure a GPIO output and use the TIM2 hardware timer with interrupts on the STM32F401RE without relying on the HAL library. It provides a practical foundation for learning register-level embedded firmware development.
