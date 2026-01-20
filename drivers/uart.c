#include "uart.h"
#include "register_access.h"
#include "nvic.h"

#include <stdint.h>

void Interrupt2_Handler( void );

void Interrupt2_Handler( void )
{
  register_write(UART_BASE_ADDRESS | UART_RXDRDY, 0 );
  register_write( Interrupt_ICPR, Interrupt_ID2 );
}

void uart_init( void )
{
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
  register_write( ( UART_BASE_ADDRESS + UART_ENABLE ), 4 );


  // Fire the START event for the Transmitter: ------------------------------
  register_write( ( UART_BASE_ADDRESS + UART_STARTTX ), UART_TASK_START );

  // Fire the START event for the Receiver: ---------------------------------
  register_write( ( UART_BASE_ADDRESS + UART_STARTRX ), UART_TASK_START );


  // Enable Interrupt
  register_write((UART_BASE_ADDRESS | UART_INTENSET), UART_INT_RXDRDY ); // Interrupt on Compare[0]

  // Enable User-Interrupt from Cortex-M0
  // ID2 ist der UART
  register_write( Interrupt_Set_Enable, Interrupt_ID2 );
}

void uart_writeByte( const uint8_t data )
{
  // write the data to the TXD register
  register_write( ( UART_BASE_ADDRESS | UART_TXD ), data );

  // need to "wait" until its transmitted
  while ( register_read( UART_BASE_ADDRESS | UART_TXDRDY ) == 0x00 )
  {
  }

  register_write( UART_BASE_ADDRESS | UART_TXDRDY, 0 );
}

uint8_t uart_readByte( void )
{
  // if not ready, return 0
  uint32_t receiveIsReady = register_read( ( UART_BASE_ADDRESS + UART_RXDRDY ) );

  if ( receiveIsReady )
  {

    // we have to CLEAR the event before reading out from RXD
    register_write( ( UART_BASE_ADDRESS + UART_RXDRDY ), UART_EVENT_CLEAR );

    // FIFO is ready to read something out of it
    return register_read( ( UART_BASE_ADDRESS + UART_RXD ) );
  }

  // FIFO is not ready to read, so return 0 instead
  return 0;
}

uint8_t uart_readByteBlocking( void )
{
  // TODO: Maybe this is a good idea ?
  // OR
  // You can use Interrupts to receive an EVENT, if some RX data is pending
  // but don't forget to clear it.
  // Feel free ;-)

  return 0;
}
