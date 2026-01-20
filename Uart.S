/**
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Thomas Vogt
 **/

#include "Uart.h"

.section .text
.align 2

.syntax unified
.thumb

.global Uart_init
.type Uart_init, %function

Uart_init:
  PUSH { R3, R4 }

  LDR R3, =UART_BASE_ADDRESS

  // Enable UART
  LDR R4, =4
  STR R4, [R3,#UART_ENABLE]

  // Fire the START event for the Transmitter
  LDR R4, =UART_TASK_START
  STR R4, [R3,#UART_STARTTX]

  // Fire the START event for the Receiver
  LDR R4, =UART_TASK_START
  STR R4, [R3,#UART_STARTRX]

  POP { R3, R4 }
  BX LR

.size Uart_init, . - Uart_init


.global Uart_readByte
.type Uart_readByte, %function

Uart_readByte:
  PUSH { R3, R4 }

  // initialise return values
  MOV R0,#0
  MOV R1,#0

  LDR R3, =UART_BASE_ADDRESS

  LDR R4, [R3, #UART_RXDRDY]

  CBZ R4, 1f

  // we have to CLEAR the event before reading out from RXD
  MOV R4, #0
  STR R4, [R3, #UART_RXDRDY]

  // FIFO is ready to read something out of it
  MOV R0, #1
  LDR R1, [R3, #UART_RXD]

1:
  POP { R3, R4 }
  BX LR

.size Uart_readByte, . - Uart_readByte


.global Uart_writeByte
.type Uart_writeByte, %function

Uart_writeByte:
  PUSH { R3 }

  LDR R3, =UART_BASE_ADDRESS

  STR R0, [R3,#UART_TXD]

  POP { R3 }
  BX LR

.size Uart_writeByte, . - Uart_writeByte

.end
