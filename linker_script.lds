/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief ARM Cortex-M4 Linker Script.
 **/

/*---------------------- Flash Configuration ----------------------------------
  <h> Flash Configuration
    <o0> Flash Base Address <0x0-0xFFFFFFFF:8>
    <o1> Flash Size (in Bytes) <0x0-0xFFFFFFFF:8>
  </h>
  -----------------------------------------------------------------------------*/
__ROM_BASE = 0x00000000;
__ROM_SIZE = 0x00040000;

/*--------------------- Embedded RAM Configuration ----------------------------
  <h> RAM Configuration
    <o0> RAM Base Address    <0x0-0xFFFFFFFF:8>
    <o1> RAM Size (in Bytes) <0x0-0xFFFFFFFF:8>
  </h>
 -----------------------------------------------------------------------------*/
__RAM_BASE = 0x20000000;
__RAM_SIZE = 0x00004000;

/*--------------------- Stack / Heap Configuration ----------------------------
  <h> Stack / Heap Configuration
    <o0> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
    <o1> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
  </h>
  -----------------------------------------------------------------------------*/
__STACK_SIZE = 0x00000400;
__HEAP_SIZE  = 0x00000C00;


ENTRY ( ResetHandler )

MEMORY
{
  FLASH (rx)  : ORIGIN = __ROM_BASE, LENGTH = __ROM_SIZE
  RAM   (rwx) : ORIGIN = __RAM_BASE, LENGTH = __RAM_SIZE
}

SECTIONS
{
  /* Text Section contains all code .vectors, .boot, .text */
  .text :
  {
    KEEP( *(.vectors) )
    *(.text*)
  } > FLASH

  /* Read Only Data directly placed into Flash */
  .rodata :
  {
    . = ALIGN(4);
    __ro_data_start__ = .;

    *(.rodata*)

    . = ALIGN( 4 );
    __ro_data_end__ = .;
  } > FLASH

  .data :
  {
    . = ALIGN(4);
    __data_start__ = .;
    __data_start_rom__ = LOADADDR( .data );

    *(.data)
    *(.data.*)

    . = ALIGN( 4 );
    __data_end__ = .;
  } > RAM AT > FLASH

  .bss :
  {
    . = ALIGN(4);

    __bss_start__ = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)

    . = ALIGN(4);
    __bss_end__ = .;
  } > RAM AT > RAM

  /* Stack is located on top of RAM */
 .stack ( ORIGIN(RAM) + LENGTH(RAM) - __STACK_SIZE ) (NOLOAD) :
  {
    . = ALIGN(8);
    __StackLimit = .;
    . = . + __STACK_SIZE;
    . = ALIGN(8);
    __StackTop = .;
  } > RAM
  PROVIDE( __stack = __StackTop );
}
