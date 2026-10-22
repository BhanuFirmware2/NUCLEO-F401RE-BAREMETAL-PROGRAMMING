# USART2 Communication – STM32F401RE

## Project Overview
This project demonstrates USART2 serial communication using bare-metal register programming on the STM32 Nucleo-F401RE development board.

The program transmits predefined strings to a serial terminal, receives a character from the user, and displays the received character.

**No STM32 HAL functions are used in the application code.**

## Hardware Requirements
- STM32 Nucleo-F401RE development board
- USB cable
- Computer
- ST-LINK Virtual COM Port

## Software Requirements
- Windows 10/11
- STM32CubeIDE
- Serial terminal software (PuTTY)
- Embedded C
- GNU Arm Embedded Toolchain

## USART2 Pin Connections

| STM32 Pin | USART2 Function | Arduino Header |
|---|---|---|
| PA2 | USART2_TX | D1 |
| PA3 | USART2_RX | D0 |
| GND | Ground | GND |

The board's ST-LINK USB connection provides the Virtual COM Port for serial communication.

## Registers Used

| Register | Address | Purpose |
|---|---|---|
| RCC_AHB1ENR | 0x40023830 | Enable GPIOA clock |
| RCC_APB1ENR | 0x40023840 | Enable USART2 clock |
| GPIOA_MODER | 0x40020000 | Configure PA2 and PA3 modes |
| GPIOA_AFRL | 0x40020020 | Select USART2 alternate function AF7 |
| USART2_SR | 0x40004400 | Check transmission and reception status |
| USART2_DR | 0x40004404 | Transmit and receive data |
| USART2_BRR | 0x40004408 | Configure baud rate |
| USART2_CR1 | 0x4000440C | Enable USART, transmitter and receiver |
| USART2_CR2 | 0x40004410 | Configure stop bits |
| USART2_CR3 | 0x40004414 | Configure additional USART features |

## Working Principle

1. Enable the GPIOA and USART2 peripheral clocks.
2. Configure PA2 and PA3 in Alternate Function mode.
3. Select AF7 for USART2 communication.
4. Configure the baud rate and USART control registers.
5. Enable the transmitter and receiver.
6. Transmit predefined strings through USART2.
7. Receive a character by polling the RXNE status flag.
8. Display the received character through the serial terminal.

## Important Status Bits

- **TXE (Bit 7):** Transmit data register is empty.
- **RXNE (Bit 5):** Received data is available.
- **TC (Bit 6):** Transmission is complete.
- **TE (Bit 3):** Transmitter enable.
- **RE (Bit 2):** Receiver enable.
- **UE (Bit 13):** USART enable.

## Baud Rate Configuration

The example uses:

`USART2_BRR = 0x0683U`

This value is suitable for approximately 9600 baud when the USART2 peripheral clock is 16 MHz. If APB1 operates at 42 MHz, the BRR value must be recalculated for the same baud rate.

## Expected Serial Terminal Output

```text
BHANU PRAKASH
RAVINUTHALA
Type :
```

When a character is entered in the terminal, the program displays the received character and prompts for another character.

## Concepts Learned

- Bare-metal register programming
- RCC peripheral clock enable
- GPIO alternate function configuration
- USART2 initialization
- Baud rate configuration
- Polling using TXE and RXNE flags
- Serial data transmission and reception

## Author
Bhanu Prakash Ravinuthala
