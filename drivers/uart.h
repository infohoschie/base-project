// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief Declaration of Module UART.
 **/

#ifndef DRIVERS_UART_H
#define DRIVERS_UART_H

#include <stdint.h>

// Definitions ----------------------------------------------------------------

// Base Address (Instance)
#define UART_BASE_ADDRESS  0x40002000

// Register Offsets (from Table 275, page 154)
// Tasks:
#define UART_STARTRX       0x000    // Start UART receiver
#define UART_STOPRX        0x004    // Stop UART receiver
#define UART_STARTTX       0x008    // Start UART transmitter
#define UART_STOPTX        0x00C    // Stop UART transmitter
#define UART_SUSPEND       0x01C    // Suspend UART

// Events:
#define UART_CTS           0x100    // CTS is activated (set low). Clear To Send.
#define UART_NCTS          0x104    // CTS is deactivated (set high). Not Clear To Send.
#define UART_RXDRDY        0x108    // Data received in RXD
#define UART_TXDRDY        0x11C    // Data sent from TXD
#define UART_ERROR         0x124    // Error detected
#define UART_RXTO          0x144    // Receiver timeout

// Registers:
#define UART_INTEN         0x300    // Enable or disable interrupt
#define UART_INTENSET      0x304    // Enable interrupt
#define UART_INTENCLR      0x308    // Disable interrupt
#define UART_ERRORSRC      0x480    // Error source
#define UART_ENABLE        0x500    // Enable UART
#define UART_PSELRTS       0x508    // Pin select for RTS
#define UART_PSELTXD       0x50C    // Pin select for TXD
#define UART_PSELCTS       0x510    // Pin select for CTS
#define UART_PSELRXD       0x514    // Pin select for RXD
#define UART_RXD           0x518    // RXD register
#define UART_TXD           0x51C    // TXD register
#define UART_BAUDRATE      0x524    // Baud rate
#define UART_CONFIG        0x56C    // Configuration of parity and hardware flow control

// Other:
#define UART_TASK_START        1    // Value for starting a Task
#define UART_EVENT_TRIGGER     1    // Value for setting/starting an Event
#define UART_EVENT_CLEAR       0    // Value for clearing/stopping an Event

#define UART_INT_RXDRDY (1 << 2 )

// C Function Definitions -----------------------------------------------------

typedef struct UartDevice UartDevice;

/**
 * @brief Initializing the UART with the following Settings:
 * 115200-8-N-1
 */
UartDevice * uart_init( void );

/**
 * @brief Writes/Sends a byte over the serial Port
 *
 * @param data byte to send (ASCII)
 **/
void uart_writeByte( UartDevice * device, uint8_t data );

/**
 * @brief Read/Receive a byte from the serial Port
 *
 * @return uint8_t received Byte or 0 (zero) if nothing was received
 **/
uint8_t uart_readByte( UartDevice * device );

/**
 * @brief Writes a null-terminated string to the UART interface.
 *
 * The function sends each character of the given string through the UART
 * interface by calling the @ref uart_writeByte function.
 * Transmission continues until the null terminator character (`\0`) is
 * encountered in the input string.
 * If a null pointer is passed to this function, it returns immediately without
 * transmitting any data.
 *
 * @param[in] string
 *   A pointer to the null-terminated string to be written via UART.
 **/
void uart_writeString( UartDevice * device, char const * string );

/**
 * @brief Writes an unsigned 32-bit integer to the UART as a string of characters.
 *
 * This function converts the given number into its ASCII string representation
 * and outputs it via the UART.
 * This is useful for sending numeric data over the UART interface.
 *
 * @param[in] number
 *   The unsigned 32-bit integer to be transmitted.
 **/
void uart_writeNumber( UartDevice * device, uint32_t number );

#endif
