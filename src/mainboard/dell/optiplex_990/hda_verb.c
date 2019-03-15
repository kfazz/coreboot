/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008-2009 coresystems GmbH
 * Copyright (C) 2014 Vladimir Serbinenko
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <device/azalia_device.h>

const u32 cim_verb_data[] = {
	0x10ec0269, /* Codec Vendor / Device ID: Realtek */
	0x1028047e, /* Subsystem ID */

	0x0000000b, /* Number of 4 dword sets */
	/* NID 0x01: Subsystem ID.  */
	AZALIA_SUBVENDOR(0x0, 0x1028047e),

	/* NID 0x12.  */
	AZALIA_PIN_CFG(0x0, 0x12, 0x411111f0),

	/* NID 0x14.  */
	AZALIA_PIN_CFG(0x0, 0x14, 0x99130110),

	/* NID 0x17.  */
	AZALIA_PIN_CFG(0x0, 0x17, 0x411111f0),

	/* NID 0x18.  */
	AZALIA_PIN_CFG(0x0, 0x18, 0x02a19830),

	/* NID 0x19.  */
	AZALIA_PIN_CFG(0x0, 0x19, 0x01a19840),

	/* NID 0x1a.  */
	AZALIA_PIN_CFG(0x0, 0x1a, 0x411111f0),

	/* NID 0x1b.  */
	AZALIA_PIN_CFG(0x0, 0x1b, 0x01014020),

	/* NID 0x1d.  */
	AZALIA_PIN_CFG(0x0, 0x1d, 0x411111f0),

	/* NID 0x1e.  */
	AZALIA_PIN_CFG(0x0, 0x1e, 0x411111f0),

	/* NID 0x21.  */
	AZALIA_PIN_CFG(0x0, 0x21, 0x0221402f),
};

const u32 pc_beep_verbs[0] = {};

AZALIA_ARRAY_SIZES;
