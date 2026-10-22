# STM32F401RE ADC with LDR Sensor

## Project Overview

This project reads light intensity using an LDR sensor connected to the STM32 Nucleo-F401RE board.

The ADC (Analog-to-Digital Converter) converts the analog voltage from the LDR module into a digital value. The program compares this value with a predefined threshold and controls an external LED.

This project uses **Bare-Metal Embedded C programming with direct register access, without STM32 HAL functions**.

## Hardware Requirements

- STM32 Nucleo-F401RE development board
- LDR sensor module with analog output (A0)
- 3.3 kΩ resistor for the voltage-divider circuit, if required by the sensor arrangement
- External LED
- LED current-limiting resistor
- Breadboard and jumper wires
- USB cable

## Software Requirements

- IDE: STM32CubeIDE
- Programming Language: Embedded C
- Debugger: ST-LINK
- Programming Method: Bare-Metal Programming
- Peripheral Configuration: Direct register access


## Hardware Connections

### LDR Sensor Module

| LDR Module Pin | STM32 Nucleo-F401RE |
|---|---|
| VCC | 3.3V |
| GND | GND |
| A0 | PA0 |

The A0 pin provides an analog voltage corresponding to the sensor's light level. PA0 is configured as an analog input for ADC1 channel 0.

### External LED

| LED Connection | STM32 Connection |
|---|---|
| PA10 | Current-limiting resistor, then LED anode (+) |
| LED cathode (-) | GND |

Ensure the LED resistor is connected in series and the circuit shares a common ground.

**Note:** PA10 is used for the external LED in this program. The Nucleo-F401RE built-in user LED is connected to PA5.

## Working Principle

1. The LDR module senses changes in light intensity.
2. Its analog output voltage is connected to PA0.
3. ADC1 converts the analog voltage into a digital value.
4. The program reads the ADC conversion result.
5. The digital value is compared with a threshold of 1500.
6. If the ADC value is greater than 1500, the LED turns ON.
7. Otherwise, the LED turns OFF.
8. The process repeats continuously.

## ADC Configuration

The STM32F401RE uses a 12-bit ADC.

The ADC output range is **0 to 4095**.

| Configuration | Register | Purpose |
|---|---|---|
| GPIOA clock | RCC_AHB1ENR | Enables GPIOA |
| ADC1 clock | RCC_APB2ENR | Enables ADC1 |
| GPIO mode | GPIOA_MODER | Sets PA0 to analog and PA10 to output |
| ADC prescaler | ADC_CCR | Configures the common ADC clock prescaler |
| ADC resolution | ADC1_CR1 | Selects 12-bit resolution |
| Conversion sequence | ADC1_SQR1 | Sets one conversion |
| Channel selection | ADC1_SQR3 | Selects channel 0 (PA0) |
| Sampling time | ADC1_SMPR2 | Sets channel 0 sampling time |
| ADC control | ADC1_CR2 | Enables ADC and starts conversion |
| Status flag | ADC1_SR | Checks End Of Conversion (EOC) |
| Data register | ADC1_DR | Provides the converted value |
| LED output | GPIOA_ODR | Controls the external LED |

## Sampling Time

The program configures channel 0 sampling time using ADC1_SMPR2.

The setting `7U` selects **480 ADC clock cycles**.

Sampling time allows the ADC's internal sampling capacitor to acquire the analog input voltage before conversion.

## Threshold Logic

The threshold is defined as:

`#define ldr_threshold 1500U`

The program uses this condition:

`if (ldr_value > ldr_threshold)`

- ADC value greater than 1500: LED ON.
- ADC value less than or equal to 1500: LED OFF.

The threshold is an example value. Adjust it according to the sensor module, lighting conditions, and measured ADC readings.

With an LDR connected toward 3.3V and a fixed resistor toward GND, the ADC value generally increases as light intensity increases. Actual behavior depends on the circuit arrangement.

## Important C Programming Concepts

### Direct Register Access

The program accesses peripheral registers using their memory-mapped addresses.

### Volatile Keyword

The `volatile` keyword ensures that hardware register accesses are not optimized away as ordinary memory accesses.

### Bitwise Operators

- `|=` sets selected register bits.
- `&= ~` clears selected register bits.
- `<<` shifts a bit pattern to the required bit position.

### Static Functions

The `static` keyword restricts these functions to the current C source file.

## Learning Outcomes

- Understand ADC operation in STM32F401RE.
- Configure GPIO pins using registers.
- Enable peripheral clocks using RCC.
- Configure ADC resolution, channel, and sampling time.
- Start ADC conversion and check the EOC flag.
- Read ADC data from the data register.
- Control an LED based on sensor input.
- Practice bare-metal Embedded C programming.

## Conclusion

This project demonstrates analog sensor interfacing with STM32F401RE using ADC and direct register programming. It provides practical experience with GPIO, RCC, ADC conversion, bitwise operations, and threshold-based LED control without using STM32 HAL functions.
