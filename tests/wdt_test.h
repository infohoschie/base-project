// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief Declaration of Module WDT Test.
 **/

#ifndef TESTS_WDT_TEST_H
#define TESTS_WDT_TEST_H

#include <drivers/uart.h>

void Wdt_test( UartDevice * uart );

#endif
