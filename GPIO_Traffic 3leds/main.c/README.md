# STM32F401RE - GPIO LED Blinking Using Bare-Metal C

## 1. Project Description

This project demonstrates GPIO output control using bare-metal Embedded C on the STM32 NUCLEO-F401RE development board.

Three GPIO pins are used to control three LEDs. The LEDs turn ON one by one in a continuous sequence using direct register programming without HAL.

## 2. Hardware Requirements

- STM32 NUCLEO-F401RE development board
- 3 LEDs
- 3 current-limiting resistors
- Breadboard
- Jumper wires
- USB cable
- Computer with STM32CubeIDE

## 3. Software Requirements

- STM32CubeIDE
- Embedded C
- Bare-metal register programming

## 4. GPIO Pin Connections

| Arduino Pin | STM32 GPIO Pin | LED |
|---|---|---|
| D2 | PA10 | LED 1 |
| D4 | PB5 | LED 2 |
| D7 | PA8 | LED 3 |

Connect each GPIO pin to the LED through a suitable current-limiting resistor. Connect the LED return side to GND for active-HIGH operation.

Verify the pin mapping using the NUCLEO-F401RE board pinout before wiring.

## 5. Registers Used

### 5.1 RCC_AHB1ENR — GPIO Clock Enable

**Address:** `0x40023830`

This register enables the clock for GPIO peripherals.

- Bit 0 = 1: Enable GPIOA clock.
- Bit 1 = 1: Enable GPIOB clock.

Code:
```c
RCC_AHB1ENR |= (1U << 0);
RCC_AHB1ENR |= (1U << 1);
```

### 5.2 GPIOA_MODER — GPIOA Mode Register

**Address:** `0x40020000`

This register configures GPIOA pin modes.

Each pin uses two mode bits:
- `00` = Input mode
- `01` = General-purpose output mode
- `10` = Alternate function mode
- `11` = Analog mode

PA10 uses bits 21:20. Setting them to `01` configures PA10 as an output.

PA8 uses bits 17:16. Setting them to `01` configures PA8 as an output.

Code:
```c
GPIOA_MODER &= ~(3U << 20);
GPIOA_MODER |=  (1U << 20);

GPIOA_MODER &= ~(3U << 16);
GPIOA_MODER |=  (1U << 16);
```

### 5.3 GPIOB_MODER — GPIOB Mode Register

**Address:** `0x40020400`

PB5 uses bits 11:10.

Setting bits 11:10 to `01` configures PB5 as an output.

Code:
```c
GPIOB_MODER &= ~(3U << 10);
GPIOB_MODER |=  (1U << 10);
```

### 5.4 GPIOA_ODR — GPIOA Output Data Register

**Address:** `0x40020014`

This register controls the output state of GPIOA pins.

- Bit 10 controls PA10.
- Bit 8 controls PA8.
- Setting a bit to `1` drives the pin HIGH.
- Clearing a bit to `0` drives the pin LOW.

### 5.5 GPIOB_ODR — GPIOB Output Data Register

**Address:** `0x40020414`

This register controls the output state of GPIOB pins.

- Bit 5 controls PB5.
- Setting bit 5 to `1` drives PB5 HIGH.
- Clearing bit 5 to `0` drives PB5 LOW.

## 6. Working Principle

### Step 1: Enable GPIO clocks
Enable GPIOA and GPIOB clocks using RCC_AHB1ENR.

### Step 2: Configure output pins
Configure PA10, PB5, and PA8 as general-purpose outputs using their MODER registers.

### Step 3: Turn ON LED 1
Set PA10 HIGH and keep PB5 and PA8 LOW.

### Step 4: Turn ON LED 2
Set PB5 HIGH and keep PA10 and PA8 LOW.

### Step 5: Turn ON LED 3
Set PA8 HIGH and keep PA10 and PB5 LOW.

### Step 6: Repeat
The sequence repeats continuously inside the `while(1)` loop.

## 7. Expected Output

The three external LEDs turn ON one after another:

1. LED 1 — PA10 (D2)
2. LED 2 — PB5 (D4)
3. LED 3 — PA8 (D7)

The sequence repeats continuously.

## 8. Delay Function

The delay function uses a software loop to create a pause between LED transitions.

The delay is approximate and depends on the CPU clock frequency and compiler optimization. The `ms` parameter is not used to calculate milliseconds, so `delay(4000)` does not guarantee a 4000 ms delay.

## 9. Learning Outcomes

- Understanding the STM32 memory-mapped GPIO registers
- Enabling peripheral clocks using RCC
- Configuring GPIO pins as outputs
- Using bitwise operations to set and clear register bits
- Controlling multiple LEDs using GPIO
- Writing bare-metal Embedded C without HAL

## 10. Source Code

See `main.c` in this folder for the complete implementation.
