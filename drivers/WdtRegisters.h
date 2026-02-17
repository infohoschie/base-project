// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief WDT Registers Definition.
 **/

#ifndef DRIVERS_WDTREGISTERS_H
#define DRIVERS_WDTREGISTERS_H

#define WDT_BASE_ADDRESS          0x40010000U
#define WDT_TASKS_START_OFFSET    0x000U
#define WDT_EVENTS_TIMEOUT_OFFSET 0x100U
#define WDT_INTENSET_OFFSET       0x304U
#define WDT_INTENCLR_OFFSET       0x308U
#define WDT_RUNSTATUS_OFFSET      0x400U
#define WDT_REQSTATUS_OFFSET      0x404U
#define WDT_CRV_OFFSET            0x504U
#define WDT_RREN_OFFSET           0x508U
#define WDT_CONFIG_OFFSET         0x50CU
#define WDT_RR_OFFSET( N )        ( 0x600U + ( N  * 4U ) )

#endif
