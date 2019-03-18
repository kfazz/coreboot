/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 Advanced Micro Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/* RAM driver for the SMSC KBC1100 Super I/O chip */

#include <arch/io.h>
#include <device/device.h>
#include <device/pnp.h>
#include <superio/conf_mode.h>
#include <console/console.h>
#include <pc80/keyboard.h>
#include <stdlib.h>

/* Register defines */
#define DEVICE_ID_REG   0x20    /* Device ID register */
#define DEVICE_REV_REG  0x21    /* Device revision register */
#define DEVICE_TEST7_REG 0x29   /* Device test 7 register */

#include "sch5545.h"

/* Static variables for the Super I/O device ID and revision. */
static int first_time = 1;
static u8 superio_id = 0;
static u8 superio_rev = 0;


static void sch5545_init(struct device *dev)
{
	int ld;
        /* Do not initialize disabled devices. */
        if (!dev->enabled)
                return;
        ld = dev->path.pnp.device;
        if (ld == SCH5545_LDN_KBC) {
                pc_keyboard_init(NO_AUX_DEVICE);
        }
}

static struct device_operations ops = {
	.read_resources   = pnp_read_resources,
	.set_resources    = pnp_set_resources,
	.enable_resources = pnp_enable_resources,
	.enable           = pnp_alt_enable,
	.init             = sch5545_init,
	.ops_pnp_mode     = &pnp_conf_mode_55_aa,
};

static struct pnp_info pnp_dev_info[] = {
        { &ops, SCH5545_LDN_FLOPPY, PNP_IO0 | PNP_IRQ0 | PNP_DRQ0, 0x07f8, },
        { &ops, SCH5545_LDN_PARPORT,  PNP_IO0 | PNP_IRQ0 | PNP_DRQ0, 0x07f8, },
        { &ops, SCH5545_LDN_UART1, PNP_IO0 | PNP_IRQ0, 0x07f8, },
        { &ops, SCH5545_LDN_UART2, PNP_IO0 | PNP_IRQ0, 0x07f8, },
        { &ops, SCH5545_LDN_KBC, PNP_IO0 | PNP_IO1 | PNP_IRQ0 | PNP_IRQ1,0x07ff, 0x07ff, },
        { &ops, SCH5545_LDN_RT,  PNP_IO0, 0x0780, },
};

static void enable_dev(struct device *dev)
{
        if (first_time) {

                pnp_enter_conf_mode_55(dev);

                /* Read the device ID and revision of the Super I/O chip. */
                superio_id = pnp_read_config(dev, DEVICE_ID_REG);
                superio_rev = pnp_read_config(dev, DEVICE_REV_REG);

                /* TODO: Error handling? */

                printk(BIOS_INFO, "Found SMSC SCH5544 Super I/O (ID = 0x%02x, "
                       "rev = 0x%02x)\n", superio_id, superio_rev);
                first_time = 0;

		pnp_exit_conf_mode_aa(dev);
	}

	//pnp_enable_devices(dev, &pnp_ops, ARRAY_SIZE(pnp_dev_info), pnp_dev_info);
        /* Enable the specified devices (if present on the chip). */
        pnp_enable_devices(dev, &ops, ARRAY_SIZE(pnp_dev_info), pnp_dev_info);

}

struct chip_operations superio_smsc_sch5545_ops = {
	CHIP_NAME("SMSC SCH5545 Super I/O")
		.enable_dev = enable_dev,
};

