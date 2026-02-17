// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief Declaration of Module Watchdog (WDT).
 **/

#ifndef DRIVERS_WDT_H
#define DRIVERS_WDT_H

#include <stdint.h>
#include <stdbool.h>

void Wdt_initialise( uint32_t crValue, bool intEnable, uint8_t enableReloadRequestRegister );

void Wdt_start( void );

void Wdt_reloadRequest( uint8_t reloadRequestRegister );

#endif
