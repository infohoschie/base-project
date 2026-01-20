# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
# If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required( VERSION 3.22 )

project( skeleton-project LANGUAGES ASM C )

add_executable( testApp )

target_sources(
  testApp

  PRIVATE
    Vectors.S
    DefaultHandlers.S
    ResetHandler.S
    Uart.h
    Uart.S
    Rng.h
    Rng.S
    SysTick.h
    SysTick.S
    entry_c.h
    entry_c.c
    main.c

    drivers/nvic.h
    drivers/random.h
    drivers/random.c
    drivers/register_access.h
    drivers/register_access.c
    drivers/uart.h
    drivers/uart.c

    utils/Strings.h
    utils/Strings.c )

#target_compile_options( testApp PRIVATE -save-temps )

#target_link_libraries( testApp PRIVATE gcc )

target_include_directories(
  testApp
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} )

target_link_options(
  testApp
  PRIVATE
    -Wl,-Map=$<TARGET_FILE_BASE_NAME:testApp>.map
    -T ${CMAKE_SOURCE_DIR}/linker_script.lds )

set_target_properties(
  testApp
  PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/linker_script.lds )


#####################################################################
# Post Build Commands:
# - extract binary


# To copy out the binary:
#arm-none-eabi-objcopy -O binary base.elf output.bin

add_custom_command(
  TARGET testApp
  POST_BUILD
  COMMAND "${OBJ_COPY}"
  ARGS -O binary $<TARGET_FILE:testApp> $<TARGET_FILE_BASE_NAME:testApp>.bin )

set_target_properties(
  testApp
  PROPERTIES ADDITIONAL_CLEAN_FILES $<TARGET_FILE_BASE_NAME:testApp>.bin )

# Renode Configuration
set( RENODE_BINARY_FILE testApp.elf )

configure_file( platform.resc.in platform.resc )
configure_file( nrf52840.repl.in nrf52840.repl )
