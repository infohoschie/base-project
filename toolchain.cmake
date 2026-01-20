# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
# If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

set( CMAKE_SYSTEM_NAME Generic )
set( CMAKE_SYSTEM_PROCESSOR arm )

# Use the following Compiler:
set( CMAKE_C_COMPILER    "arm-none-eabi-gcc"     )
set( CMAKE_CXX_COMPILER  "arm-none-eabi-g++"     )
set( CMAKE_ASM_COMPILER  "arm-none-eabi-gcc"     )
set( OBJ_COPY_PATH       "arm-none-eabi-objcopy" )

# Complete the output with .elf extension
set( CMAKE_EXECUTABLE_SUFFIX ".elf" )
set( CMAKE_EXECUTABLE_SUFFIX_C   ".elf" )
set( CMAKE_EXECUTABLE_SUFFIX_CXX ".elf" )
set( CMAKE_EXECUTABLE_SUFFIX_ASM ".elf" )

# Set the Flags for Cortex-M0
set( CMAKE_C_FLAGS       "-nostdlib -mcpu=cortex-m4" )
set( CMAKE_CXX_FLAGS     "-nostdlib -mcpu=cortex-m4" )
set( CMAKE_ASM_FLAGS     "-nostdlib -mcpu=cortex-m4" )

# With startup files (auto-init):
#set(CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs" CACHE INTERNAL "")

# WITHOUT startup files:
set( CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs -nostartfiles" CACHE INTERNAL "" )

# Only use the Compiler in the given Path:
set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY )

# Find ObjCopy (Specified in Toolchain):
find_program( OBJ_COPY "${OBJ_COPY_PATH}" )
if( NOT OBJ_COPY )
  message( FATAL "objcopy not found")
endif()
