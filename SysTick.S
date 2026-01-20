/**
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Thomas Vogt
 **/

#include "SysTick.h"

.section .text
.align 2

.syntax unified
.thumb

.global SysTick_init
.type SysTick_init, %function

SysTick_init:
  PUSH { R3, R4 }

  // Load SysTick Reset Value Register
  LDR R3, =SYST_RVR
  LDR R4, =0x00FFFFFF
  STR R4, [R3]

  // Enable SysTick + Interrupt in SYST_CSR
  LDR R3, =SYST_CSR
  LDR R4, [R3]
  ORR R4,R4,#3   // TICKINT + ENABLE
  STR R4, [R3]

  POP { R3, R4 }
  BX LR

.size SysTick_init, . - SysTick_init


.global SysTickHandler
.type SysTickHandler, %function

SysTickHandler:
  PUSH { LR }
  MOV R0,#'.'
  BL print_rng
  POP { LR }

  BX LR

.size SysTickHandler, . - SysTickHandler

.end
