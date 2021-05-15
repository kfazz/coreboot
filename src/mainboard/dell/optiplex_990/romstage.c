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

#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <timestamp.h>
#include <arch/byteorder.h>
#include <arch/io.h>
#include <device/pci_def.h>
#include <device/pci_ops.h>
#include <device/pnp_def.h>
#include <cpu/x86/lapic.h>
#include <acpi/acpi.h>
#include <console/console.h>
#include <northbridge/intel/sandybridge/sandybridge.h>
#include <northbridge/intel/sandybridge/raminit_native.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <southbridge/intel/common/gpio.h>
#include <superio/smsc/smscsuperio/smscsuperio.h>
#include <superio/smsc/sch5545/sch5545.h>
#include <arch/cpu.h>
#include <cpu/x86/msr.h>

#define SERIAL_DEV PNP_DEV(0x2e, 7)

/*
void pch_enable_lpc(void)
{
	//decode CNF2,CNF1,MC,KBC,FDD,LPT,COM,COMA
	pci_write_config16(PCI_DEV(0, 0x1f, 0), LPC_EN, 0x3c0f);
	pci_write_config32(PCI_DEV(0, 0x1f, 0), LPC_GEN1_DEC, 0x007c0681); //0x680-0x6FF
	pci_write_config32(PCI_DEV(0, 0x1f, 0), LPC_GEN2_DEC, 0x000c1641); //0x640-0x64F
	pci_write_config32(PCI_DEV(0, 0x1f, 0), LPC_GEN3_DEC, 0x000400e1); // 0xE0-0xE7
	pci_write_config32(PCI_DEV(0, 0x1f, 0), LPC_GEN4_DEC, 0x001c02d1); //0x2D0-0x2DF
	pci_write_config16(PCI_DEV(0, 0x1f, 0), LPC_IO_DEC, 0x0010);
}

void mainboard_rcba_config(void)
{
}
*/

const struct southbridge_usb_port mainboard_usb_ports[] = {
	{ 1, 0, 0 },
	{ 1, 0, 0 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 0, 2 },
	{ 1, 0, 2 },
	{ 1, 0, 3 },
	{ 1, 0, 3 },
	{ 1, 1, 5 },
	{ 1, 1, 5 },
	{ 1, 0, 7 },
	{ 1, 0, 6 },
	{ 1, 0, 6 },
	{ 1, 0, 7 },
};

void mainboard_early_init(int s3resume)
{
	//set BAR addresses of periphs
	//sch5545_early_init(0x2e);
	//smscsuperio_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);
}

/*
void mainboard_config_superio(void)
{
}
*/

void mainboard_get_spd(spd_raw_data *spd, bool id_only)
{
	read_spd(&spd[0], 0x50, id_only);
	read_spd(&spd[1], 0x51, id_only);
	read_spd(&spd[2], 0x52, id_only);
	read_spd(&spd[3], 0x53, id_only);
}
