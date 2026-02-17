/**
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Thomas Vogt
 **/

.section .text
.align 2

.syntax unified
.thumb

/**
 * @brief The default macro is not used for HardFault_Handler because this results in a poor debug illusion.
 **/
.global HardFaultHandler
.type HardFaultHandler, %function
.weak HardFaultHandler
/* .fnstart */
HardFaultHandler:
  b .
/* .fnend */
.size HardFaultHandler, . - HardFaultHandler

/**
 * @brief Default Exception Handler.
 **/
.global DefaultHandler
.type DefaultHandler, %function
.weak DefaultHandler
/* .fnstart */
DefaultHandler:
  b .
/* .fnend */
.size DefaultHandler, . - DefaultHandler


/* Macro to define default exception/interrupt handlers.
 * Default handler are weak symbols with an endless loop.
 * They can be overwritten by real handlers.
 */
.macro   Set_Default_Handler  Handler_Name
.global  \Handler_Name
.weak    \Handler_Name
.set     \Handler_Name, DefaultHandler
.endm

/* Default exception/interrupt handler */
Set_Default_Handler  NMIHandler
Set_Default_Handler  MemManageHandler
Set_Default_Handler  BusFaultHandler
Set_Default_Handler  UsageFaultHandler
Set_Default_Handler  SVCHandler
Set_Default_Handler  DebugMonHandler
Set_Default_Handler  PendSVHandler
Set_Default_Handler  SysTickHandler

Set_Default_Handler  Interrupt0Handler
Set_Default_Handler  Interrupt1Handler
Set_Default_Handler  Interrupt2Handler
Set_Default_Handler  Interrupt3Handler
Set_Default_Handler  Interrupt4Handler
Set_Default_Handler  Interrupt5Handler
Set_Default_Handler  Interrupt6Handler
Set_Default_Handler  Interrupt7Handler
Set_Default_Handler  Interrupt8Handler
Set_Default_Handler  Interrupt9Handler
Set_Default_Handler  Interrupt10Handler
Set_Default_Handler  Interrupt11Handler
Set_Default_Handler  Interrupt12Handler
Set_Default_Handler  Interrupt13Handler
Set_Default_Handler  Interrupt14Handler
Set_Default_Handler  Interrupt15Handler
Set_Default_Handler  Interrupt16Handler

.end
