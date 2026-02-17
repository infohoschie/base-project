# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
# If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required( VERSION 3.22 )

project( base-project-sysprog2-2026 LANGUAGES ASM C )

add_executable( testApp)

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
    drivers/timer.h
    drivers/timer.c
    drivers/uart.h
    drivers/uart.c
    drivers/Uarte.h
    drivers/Wdt.h
    drivers/Wdt.c

    utils/Strings.h
    utils/Strings.c

    tests/timer_test.h
    tests/timer_test.c )

#target_compile_options( testApp PRIVATE -save-temps )

#target_link_libraries( testApp PRIVATE gcc )

target_include_directories(
  testApp
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} )

target_link_options(
  testApp
  PRIVATE
    # Create mapfile
    -Wl,-Map=$<TARGET_FILE_BASE_NAME:testApp>.map
    # Use linker script
    -T ${CMAKE_SOURCE_DIR}/linker_script.lds )

set_target_properties(
  testApp
  PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/linker_script.lds )

add_custom_command(
  TARGET testApp
  POST_BUILD
    COMMAND ${OBJ_COPY}
    ARGS -O binary $<TARGET_FILE:testApp> $<TARGET_FILE_BASE_NAME:testApp>.bin )

set_target_properties(
  testApp
  PROPERTIES ADDITIONAL_CLEAN_FILES $<TARGET_FILE_BASE_NAME:testApp>.bin )

# Renode Configuration
set( RENODE_BINARY_FILE testApp.elf )

configure_file( renode/platform.resc.in platform.resc )
configure_file( renode/nrf52840.repl.in nrf52840.repl )
