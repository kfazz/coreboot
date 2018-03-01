/*
 * This file is part of the coreboot project.
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

#include <console/console.h>
#include <device/device.h>
#include <string.h>
#include <cpu/cpu.h>
#include <cpu/x86/mtrr.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/lapic.h>
#include <cpu/intel/speedstep.h>
#include <cpu/intel/microcode.h>
#include <cpu/x86/cache.h>
#include <cpu/x86/name.h>
#include <cpu/intel/common/common.h>


#define IA32_MISC_ENABLE	0x1a0
static void configure_misc(void)
{
	msr_t msr;

	msr = rdmsr(IA32_MISC_ENABLE);
	msr.lo |= (1 << 3);	/* TM1 enable */
	msr.lo |= (1 << 10);	/* FERR# multiplexing */

	// TODO: Only if  IA32_PLATFORM_ID[17] = 0 and IA32_PLATFORM_ID[50] = 1
	msr.lo |= (1 << 16);	/* Enhanced SpeedStep Enable */

	wrmsr(IA32_MISC_ENABLE, msr);
#if 0
	// set maximum CPU speed
	msr = rdmsr(IA32_PERF_STATUS);
	int busratio_max = (msr.hi >> (40-32)) & 0x1f;

	msr = rdmsr(IA32_PLATFORM_ID);
	int vid_max = msr.lo & 0x3f;

	msr.lo &= ~0xffff;
	msr.lo |= busratio_max << 8;
	msr.lo |= vid_max;

	wrmsr(IA32_PERF_CTL, msr);
#endif
}



static void model_6dx_init(struct device *dev)
{
	char processor_name[49];

	/* Turn on caching if we haven't already */
	x86_enable_cache();

	/* Update the microcode */
	intel_update_microcode_from_cbfs();

	/* Print processor name */
	fill_processor_name(processor_name);
	printk(BIOS_INFO, "CPU: %s.\n", processor_name);

	/* Setup MTRRs */
	x86_setup_mtrrs();
	x86_mtrr_check();

	/* Enable the local CPU APICs */
	setup_lapic();

	/* Configure Enhanced SpeedStep and Thermal Sensors */
	configure_misc();
};

static struct device_operations cpu_dev_ops = {
	.init     = model_6dx_init,
};

static const struct cpu_device_id cpu_table[] = {
	/* Pentium M on 90nm with 2MiB of L2 cache */
	{ X86_VENDOR_INTEL, 0x06D0 },
	{ X86_VENDOR_INTEL, 0x06D6 },
	{ X86_VENDOR_INTEL, 0x06D8 },
	{ 0, 0 },
};

static const struct cpu_driver driver __cpu_driver = {
	.ops      = &cpu_dev_ops,
	.id_table = cpu_table,
};
