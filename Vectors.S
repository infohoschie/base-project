/**
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Thomas Vogt
 **/

.section .vectors, "ax"
.align 2

.globl __Vectors
#.type __Vectors, %object
__Vectors:
.long __StackTop        /*     Top of Stack */
.long ResetHandler      /*     Reset Handler */
.long NMIHandler        /* -14 NMI Handler */
.long HardFaultHandler  /* -13 Hard Fault Handler */
.long MemManageHandler  /* -12 MPU Fault Handler */
.long BusFaultHandler   /* -11 Bus Fault Handler */
.long UsageFaultHandler /* -10 Usage Fault Handler */
.long 0                 /*     Reserved */
.long 0                 /*     Reserved */
.long 0                 /*     Reserved */
.long 0                 /*     Reserved */
.long SVCHandler        /*  -5 SVC Handler */
.long DebugMonHandler   /*  -4 Debug Monitor Handler */
.long 0                  /*     Reserved */
.long PendSVHandler     /*  -2 PendSV Handler */
.long SysTickHandler    /*  -1 SysTick Handler */

/* Interrupts */
.long Interrupt0Handler /*   0 Interrupt 0 */
.long Interrupt1Handler /*   1 Interrupt 1 */
.long Interrupt2Handler /*   2 Interrupt 2 */
.long Interrupt3Handler /*   3 Interrupt 3 */
.long Interrupt4Handler /*   4 Interrupt 4 */
.long Interrupt5Handler /*   5 Interrupt 5 */
.long Interrupt6Handler /*   6 Interrupt 6 */
.long Interrupt7Handler /*   7 Interrupt 7 */
.long Interrupt8Handler /*   8 Interrupt 8 */
.long Interrupt9Handler /*   9 Interrupt 9 */

.space   (214 * 4)                          /* Interrupts 10 .. 224 are left out */
.globl __Vectors_End
__Vectors_End:

.globl __Vectors_Size
.equ     __Vectors_Size, __Vectors_End - __Vectors
.size    __Vectors, . - __Vectors

.end
