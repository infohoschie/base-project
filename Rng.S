/**
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Thomas Vogt
 **/

#include "Rng.h"

.section .text
.align 2

.syntax unified
.thumb

.global Rng_init
.type Rng_init, %function

Rng_init:
  PUSH { R3, R4 }

  LDR R3, =RNG_BASE_ADDRESS

  // Fire the START event
  LDR R4, =1
  STR R4, [R3,#RNG_START]

  POP { R3, R4 }
  BX LR

.size Rng_init, . - Rng_init


.global Rng_get
.type Rng_get, %function

Rng_get:
  PUSH { R3, R4 }

  LDR R3, =RNG_BASE_ADDRESS
1:
  LDR R4, [R3, #RNG_VALRDY]
  CMP R4, #0
  BEQ 1b

  // we have to CLEAR the event before reading out from RXD
  MOV R4, #0
  STR R4, [R3, #RNG_VALRDY]

  // Read RNG Value
  LDR R0, [R3, #RNG_VALUE]

  POP { R3, R4 }
  BX LR

.size Rng_get, . - Rng_get

.end
