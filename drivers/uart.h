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

// Base Address (Instance)
#define UARTE0_BASE_ADDRESS  0x40002000
#define UARTE1_BASE_ADDRESS  0x40028000

typedef struct UartDevice UartDevice;

/**
 * @brief Initializing the UART with the following Settings:
 * 115200-8-N-1
 */
UartDevice * uart_init( uint32_t baseAddress );

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
