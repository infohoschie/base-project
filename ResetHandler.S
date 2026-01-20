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

.extern (entry_c)

/**
 * @brief The Reset Handler.
 **/
.global ResetHandler
.type ResetHandler, %function

ResetHandler:
  /* TODO: Implement code here - Replace NOP by your code */
  NOP

  BL entry_c

  /* finally stop execution. Don't remove! */
1:
  NOP
  b 1b

.size ResetHandler, . - ResetHandler

.end
