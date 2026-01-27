// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief Definition of Module UART.
 **/

#include "uart.h"

#include <drivers/register_access.h>
#include <drivers/nvic.h>

#include <utils/Strings.h>

#include <stdint.h>
#include <stddef.h>

struct UartDevice
{
  uint32_t offset;
};

void Interrupt2_Handler( void );

void Interrupt2_Handler( void )
{
  register_write( UART_BASE_ADDRESS | UART_RXDRDY, 0 );
  register_write( Interrupt_ICPR, Interrupt_ID2 );
}

UartDevice * uart_init( void )
{
  static UartDevice uartDevice;

  uartDevice.offset = UART_BASE_ADDRESS;

  // set Flow-Controll and/or Parity (see Table 288, page 156) --------------
  // Hardware flow control: Disabled = 0 (default)
  // Parity: Exclude parity bit = 0x0    (default)
  // register_write((UART_BASE_ADDRESS + UART_CONFIG), 0); // Optional

  // set PSELRXD, PSELRTS, PSELTRTS and PSELTXD -----------------------------

  // PSELRTS - disconnected (default)
  // register_write((UART_BASE_ADDRESS + UART_PSELRTS), 0xFFFFFFFF); // Optional

  // configure GPIO Pins to RXD, TXD ----------------------------------------

  // Set Interrupts on RX ---------------------------------------------------
  // RXDRDY = enabled (..000100)
  // register_write((UART_BASE_ADDRESS + UART_INTEN), 4);

  // set baudrate (see Table 287 on page 156) -------------------------------
  // Baud9600   = 0x00275000
  // Baud19200  = 0x004EA000
  // Baud115200 = 0x01D7E000
  // Baud250000 = 0x04000000 (default)

  // register_write((UART_BASE_ADDRESS + UART_BAUDRATE), 0x01D7E000);

  // Enable UART ------------------------------------------------------------
  register_write( ( uartDevice.offset + UART_ENABLE ), 4 );


  // Fire the START event for the Transmitter: ------------------------------
  register_write( ( uartDevice.offset + UART_STARTTX ), UART_TASK_START );

  // Fire the START event for the Receiver: ---------------------------------
  register_write( ( uartDevice.offset + UART_STARTRX ), UART_TASK_START );


  // Enable Interrupt
  register_write(( uartDevice.offset | UART_INTENSET), UART_INT_RXDRDY ); // Interrupt on Compare[0]

  // Enable User-Interrupt from Cortex-M0
  // ID2 ist der UART
  register_write( Interrupt_Set_Enable, Interrupt_ID2 );

  return &uartDevice;
}

void uart_writeByte( UartDevice * device, const uint8_t data )
{
  if ( NULL == device )
  {
    return;
  }

  // write the data to the TXD register
  register_write( ( device->offset | UART_TXD ), data );

  // need to "wait" until its transmitted
  while ( register_read( device->offset | UART_TXDRDY ) == 0x00 )
  {
  }

  register_write( device->offset | UART_TXDRDY, 0 );
}

uint8_t uart_readByte( UartDevice * device )
{
  if ( NULL == device )
  {
    return 0;
  }


  // if not ready, return 0
  uint32_t receiveIsReady = register_read( ( device->offset + UART_RXDRDY ) );

  if ( receiveIsReady )
  {

    // we have to CLEAR the event before reading out from RXD
    register_write( ( device->offset + UART_RXDRDY ), UART_EVENT_CLEAR );

    // FIFO is ready to read something out of it
    return register_read( ( device->offset + UART_RXD ) );
  }

  // FIFO is not ready to read, so return 0 instead
  return 0;
}

void uart_writeString( UartDevice * device, char const * const string )
{
  if ( NULL == string )
  {
    return;
  }

  for ( char const * ch = string; *ch != '\0'; ++ch )
  {
    uart_writeByte( device, *ch );
  }
}

void uart_writeNumber( UartDevice * device, const uint32_t number )
{
  char numberString[ 11 ];

  Strings_numberToString( numberString, number );
  uart_writeString( device, numberString );
}
