/*
 * This file is part of msrtool.
 *
 * Copyright (C) 2013 Olivier Langlois <olivier@olivierlanglois.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "msrtool.h"

int intel_pentium_m_probe(const struct targetdef *target, const struct cpuid_t *id) {
	return (0x6 == id->family) &&
		(0xd == id->model);
}

const struct msrdef intel_pentium_m_msrs[] = {
	{0x0, MSRTYPE_RDWR, MSR2(0,0), "IA32_P5_MC_ADDR", "Pentium Processor\
			 Machine-Check Exception Address", {
		{ BITS_EOT }
	}},
	{0x1, MSRTYPE_RDWR, MSR2(0,0), "IA32_P5_MC_TYPE", "Pentium Processor\
			 Machine-Check Exception Type", {
		{ BITS_EOT }
	}},
	{0x10, MSRTYPE_RDWR, MSR2(0,0), "IA32_TIME_STEP_COUNTER", "TSC", {
		{ BITS_EOT }
	}},
	{0x17, MSRTYPE_RDWR, MSR2(0,0), "IA32_PLATFORM_ID", "", {
		{ BITS_EOT }
	}},
	{0x2a, MSRTYPE_RDWR, MSR2(0,0), "MSR_EBL_CR_POWERON", "", {
		{ BITS_EOT }
	}},
	{0x40, MSRTYPE_RDWR, MSR2(0,0), "MSR_LASTBRANCH_0", "", {
		{ BITS_EOT }
	}},
	{0x41, MSRTYPE_RDWR, MSR2(0,0), "MSR_LASTBRANCH_1", "", {
		{ BITS_EOT }
	}},
	{0x42, MSRTYPE_RDWR, MSR2(0,0), "MSR_LASTBRANCH_2", "", {
		{ BITS_EOT }
	}},
	{0x43, MSRTYPE_RDWR, MSR2(0,0), "MSR_LASTBRANCH_3", "", {
		{ BITS_EOT }
	}},
	{0x44, MSRTYPE_RDWR, MSR2(0,0), "MSR_LASTBRANCH_4", "", {
		{ BITS_EOT }
	}},
	{0x45, MSRTYPE_RDWR, MSR2(0,0), "MSR_LASTBRANCH_5", "", {
		{ BITS_EOT }
	}},
	{0x46, MSRTYPE_RDWR, MSR2(0,0), "MSR_LASTBRANCH_6", "", {
		{ BITS_EOT }
	}},
	{0x47, MSRTYPE_RDWR, MSR2(0,0), "MSR_LASTBRANCH_7", "", {
		{ BITS_EOT }
	}},
	{0x119, MSRTYPE_RDWR, MSR2(0,0), "MSR_BBL_CR_CTL", "", {
		{ BITS_EOT }
	}},
	{0x11e, MSRTYPE_RDWR, MSR2(0,0), "MSR_BBL_CR_CTL3", "", {
		{ BITS_EOT }
	}},
	{0x179, MSRTYPE_RDWR, MSR2(0,0), "IA32_MCG_CAP", "", {
		{ BITS_EOT }
	}},
	{0x17a, MSRTYPE_RDWR, MSR2(0,0), "IA32_MCG_STATUS", "", {
		{ 63, 61, RESERVED },
		{ 2, 1, "MCIP", "R/W", PRESENT_BIN, {
			/* When set, bit indicates that a machine check has been
			 * generated. If a second machine check is detected while
			 * this bit is still set, the processor enters a shutdown state.
			 * Software should write this bit to 0 after processing
			 * a machine check exception.
			 */
			{ MSR1(0), "Nothing" },
			{ MSR1(1), "Machine check has been generated" },
			{ BITVAL_EOT }
		}},
		{ 1, 1, "EPIV", "R/W", PRESENT_BIN, {
			/* When set, bit indicates that the instruction addressed
			 * by the instruction pointer pushed on the stack (when
			 * the machine check was generated) is directly associated
			 * with the error
			 */
			{ MSR1(0), "Nothing" },
			{ MSR1(1), "Instruction addressed directly associated with the error" },
			{ BITVAL_EOT }
		}},
		{ 0, 1, "RIPV", "R/W", PRESENT_BIN, {
			/* When set, bit indicates that the instruction addressed
			 * by the instruction pointer pushed on the stack (when
			 * the machine check was generated) can be used to restart
			 * the program. If cleared, the program cannot be reliably restarted
			 */
			{ MSR1(0), "Program cannot be reliably restarted" },
			{ MSR1(1), "Instruction addressed can be used to restart the program" },
			{ BITVAL_EOT }
		}},
		{ BITS_EOT }
	}},

	{0xcd, MSRTYPE_RDONLY, MSR2(0,0), "MSR_FSB_FREQ", "Scaleable Bus Speed", {
		{ BITS_EOT }
	}},
	{0xfe, MSRTYPE_RDWR, MSR2(0,0), "IA32_MTRRCAP", "", {
		{ BITS_EOT }
	}},
	{0x11e, MSRTYPE_RDWR, MSR2(0,0), "MSR_BBL_CR_CTL3", "", {
		{ BITS_EOT }
	}},
	{0x198, MSRTYPE_RDWR, MSR2(0,0), "IA32_PERF_STATUS", "", {
		{ 63, 19, RESERVED },
		{ 44, 5,  "Maximum Bus Ratio", "R/O", PRESENT_DEC, {
			{ BITVAL_EOT }
		}},
		{ 39, 24, RESERVED },
		{ 15, 16, "Current Performance State Value", "R/O", PRESENT_HEX, {
			{ BITVAL_EOT }
		}},
		{ BITS_EOT }
	}},
	{0x199, MSRTYPE_RDWR, MSR2(0,0), "IA32_PERF_CTL", "", {
		{ BITS_EOT }
	}},
	{0x19a, MSRTYPE_RDWR, MSR2(0,0), "IA32_CLOCK_MODULATION",
			"Clock Modulation", {
		{ 63, 59, RESERVED },
		{ 4, 1, "On demand Clock Modulation", "R/W", PRESENT_BIN, {
			{ MSR1(0), "On demand Clock Modulation is disabled" },
			{ MSR1(1), "On demand Clock Modulation is enabled" },
			{ BITVAL_EOT }
		}},
		{ 3, 3, "On demand Clock Modulation Duty Cycle", "R/W", PRESENT_HEX, {
			{ BITVAL_EOT }
		}},
		{ 0, 1, RESERVED },
		{ BITS_EOT }
	}},
	{0x19b, MSRTYPE_RDWR, MSR2(0,0), "IA32_THERM_INTERRUPT",
			"Thermal Interrupt Control", {
		{ BITS_EOT }
	}},
	{0x19c, MSRTYPE_RDWR, MSR2(0,0), "IA32_THERM_STATUS",
			"Thermal Monitor Status", {
		{ BITS_EOT }
	}},
	{0x19d, MSRTYPE_RDWR, MSR2(0,0), "MSR_THERM2_CTL", "", {
		{ BITS_EOT }
	}},
	{0x1a0, MSRTYPE_RDWR, MSR2(0,0), "IA32_MISC_ENABLE",
			"Enable miscellaneous processor features", {
		{ 63, 25, RESERVED },
		/* Note: [38] bit using for whole package,
		 * while some other bits can be Core or Thread
		 * specific.
		 */
		{ 38, 1, "Turbo Mode", "R/W", PRESENT_BIN, {
			/* When set to a 0 on processors that support IDA,
			 * CPUID.06H: EAX[1] reports the processor's
			 * support of turbo mode is enabled.
			 */
			{ MSR1(0), "Turbo Mode enabled" },
			/* When set 1 on processors that support Intel Turbo Boost
			 * technology, the turbo mode feature is disabled and
			 * the IDA_Enable feature flag will be clear (CPUID.06H: EAX[1]=0).
			 */
			{ MSR1(1), "Turbo Mode disabled" },
			{ BITVAL_EOT }
			/* Note: the power-on default value is used by BIOS to detect
			 * hardware support of turbo mode. If power-on default value is 1,
			 * turbo mode is available in the processor. If power-on default
			 * value is 0, turbo mode not available.
			 */
		}},
		{ 37, 3, RESERVED },
		{ 34, 1, "XD Bit Disable", "R/W", PRESENT_BIN, {
			{ BITVAL_EOT }
		}},
		{ 33, 10, RESERVED },
		{ 23, 1, "xTPR Message Disable", "R/W", PRESENT_BIN, {
			{ BITVAL_EOT }
		}},
		{ 22, 1, "Limit CPUID Maxval", "R/W", PRESENT_BIN, {
			{ BITVAL_EOT }
		}},
		{ 21, 3, RESERVED },
		{ 18, 1, "Enable Monitor FSM", "R/W", PRESENT_BIN, {
			{ BITVAL_EOT }
		}},
		{ 17, 1, "UNDOCUMENTED", "R/W", PRESENT_BIN, {
			{ BITVAL_EOT }
		}},
		/* Note: [16] bit using for whole package,
		 * while some other bits can be Core or Thread
		 * specific.
		 */
		{ 16, 1, "Enhanced Intel SpeedStep Technology Enable", "R/W",
				PRESENT_BIN, {
			{ BITVAL_EOT }
		}},
		{ 15, 3, RESERVED },
		{ 12, 1, "Precise Event Based Sampling Unavailable", "R/O",
				PRESENT_BIN, {
			{ BITVAL_EOT }
		}},
		{ 11, 1, "Branch Trace Storage Unavailable", "R/O", PRESENT_BIN, {
			{ BITVAL_EOT }
		}},
		{ 10, 3, RESERVED },
		{ 7, 1, "Performance Monitoring Available", "R", PRESENT_BIN, {
			{ BITVAL_EOT }
		}},
		{ 6, 3, RESERVED },
		{ 3, 1, "Automatic Thermal Control Circuit Enable", "R/W"
				, PRESENT_BIN, {
			{ BITVAL_EOT }
		}},
		{ 2, 2, RESERVED },
		{ 0, 1, "Fast-Strings Enable", "R/W", PRESENT_BIN, {
			{ BITVAL_EOT }
		}},
		{ BITS_EOT }
	}},
	{0x1c9, MSRTYPE_RDONLY, MSR2(0,0), "MSR_LASTBRANCH_TOS",
		"Last Branch Record Stack TOS", {
	/* Contains an index (bits 0-3) that points to the MSR containing
	 * the most recent branch record. See also MSR_LASTBRANCH_0_FROM_IP (0x680).
	 */
		{ BITS_EOT }
	}},
	{0x1d9, MSRTYPE_RDWR, MSR2(0,0), "IA32_DEBUGCTL",
		"Debug/Trace/Profile Resource Control", {
	/* (MSR_DEBUGCTTLA, MSR_DEBUGCTLB) */
		{ 63, 49, RESERVED },
		/* Only if IA32_PERF_CAPABILITIES[12] = 1 */
		{ 14, 1, "FREEZE_WHILE_SMM", "R/O", PRESENT_BIN, {
			{ MSR1(0), "Nothing" },
			{ MSR1(1), "Freeze perfmon and trace messages while in SMM" },
			{ BITVAL_EOT }
		}},
		{ 13, 1, "ENABLE_UNCORE_PMI", "R/O", PRESENT_BIN, {
			{ MSR1(0), "Nothing" },
			{ MSR1(1), "Logical processor can receive and generate PMI \
				on behalf of the uncore" },
			{ BITVAL_EOT }
		}},
		/* Only if CPUID.01H: ECX[15] = 1 and CPUID.0AH: EAX[7:0]>1 */
		{ 12, 1, "FREEZE_PERFMON_ON_PMI", "R/O", PRESENT_BIN, {
			{ MSR1(0), "Nothing" },
			{ MSR1(1), "Each ENABLE bit of the global counter control MSR \
				are frozen (address 0x3bf) on PMI request" },
			{ BITVAL_EOT }
		}},
		/* Only if CPUID.01H: ECX[15] = 1 and CPUID.0AH: EAX[7:0]>1 */
		{ 11, 1, "FREEZE_LBRS_ON_PMI", "R/O", PRESENT_BIN, {
			{ MSR1(0), "Nothing" },
			{ MSR1(1), "LBR stack is frozen on PMI request" },
			{ BITVAL_EOT }
		}},
		{ 10, 1, "BTS_OFF_USR", "R/O", PRESENT_BIN, {
			{ MSR1(0), "Nothing" },
			{ MSR1(1), "BTS or BTM is skipped if CPL > 0" },
			{ BITVAL_EOT }
		}},
		{ 9, 1, "BTS_OFF_OS", "R/O", PRESENT_BIN, {
			{ MSR1(0), "Nothing" },
			{ MSR1(1), "BTS or BTM is skipped if CPL = 0" },
			{ BITVAL_EOT }
		}},
		{ 8, 1, "BTINT", "R/O", PRESENT_BIN, {
			{ MSR1(0), "BTMs are logged in a BTS buffer in circular fashion" },
			{ MSR1(1), "An interrupt is generated by the BTS facility \
				when the BTS buffer is full" },
			{ BITVAL_EOT }
		}},
		{ 7, 1, "BTS", "R/O", PRESENT_BIN, {
			{ MSR1(0), "Logging of BTMs (branch trace messages) \
				in BTS buffer is disabled" },
			{ MSR1(1), "Logging of BTMs (branch trace messages) \
				in BTS buffer is enabled" },
			{ BITVAL_EOT }
		}},
		{ 6, 1, "TR", "R/O", PRESENT_BIN, {
			{ MSR1(0), "Branch trace messages are disabled" },
			{ MSR1(1), "Branch trace messages are enabled" },
			{ BITVAL_EOT }
		}},
		{ 5, 4, RESERVED },
		{ 1, 1, "BTF", "R/O", PRESENT_BIN, {
			{ MSR1(0), "Nothing" },
			{ MSR1(1), "Enabled treating EFLAGS.TF as single-step on \
				branches instead of single-step on instructions" },
			{ BITVAL_EOT }
		}},
		{ 0, 1, "LBR", "R/O", PRESENT_BIN, {
			{ MSR1(0), "Nothing" },
			{ MSR1(1), "Enabled recording a running trace of the most \
				recent branches taken by the processor in the LBR stack" },
			{ BITVAL_EOT }
		}},
		{ BITS_EOT }
	}},
	{0x1dd, MSRTYPE_RDONLY, MSR2(0,0), "MSR_LER_TO_LIP",
		"Last Exception Record To Linear IP", {
	/* Contains a pointer to the last branch instruction
	 * that the processor executed prior to the last exception
	 * that was generated or the last interrupt that was handled.
	 */
		{ BITS_EOT }
	}},
	{0x1de, MSRTYPE_RDONLY, MSR2(0,0), "MSR_LER_FROM_LIP",
		"Last Exception Record From Linear IP", {
	/* This area contains a pointer to the target of the
	 * last branch instruction that the processor executed
	 * prior to the last exception that was generated or
	 * the last interrupt that was handled
	 */
		{ BITS_EOT }
	}},
	{0x2ff, MSRTYPE_RDWR, MSR2(0,0), "IA32_MTRR_DEF_TYPE",
			"Default Memory Types", {
		{ 63, 52, RESERVED },
		{ 11, 1, "MTRR Enable", "R/W", PRESENT_BIN, {
			{ BITVAL_EOT }
		}},
		{ 10, 1, "Fixed Range MTRR Enable", "R/W", PRESENT_BIN, {
			{ BITVAL_EOT }
		}},
		{ 9, 7, RESERVED },
		{ 2, 3, "Default Memory Type", "R/W", PRESENT_HEX, {
			{ BITVAL_EOT }
		}},
		{ BITS_EOT }
	}},
	{0x400, MSRTYPE_RDWR, MSR2(0,0), "IA32_MCO_CTL", "", {
		{ BITS_EOT }
	}},
	{0x401, MSRTYPE_RDWR, MSR2(0,0), "IA32_MCO_STATUS", "", {
		{ BITS_EOT }
	}},
	{0x402, MSRTYPE_RDWR, MSR2(0,0), "IA32_MCO_ADDR", "", {
		{ BITS_EOT }
	}},
	{0x404, MSRTYPE_RDWR, MSR2(0,0), "IA32_MC1_CTL", "", {
		{ BITS_EOT }
	}},
	{0x405, MSRTYPE_RDWR, MSR2(0,0), "IA32_MC1_STATUS", "", {
		{ BITS_EOT }
	}},
	{0x408, MSRTYPE_RDWR, MSR2(0,0), "IA32_MC2_CTL", "", {
		{ BITS_EOT }
	}},
	{0x409, MSRTYPE_RDWR, MSR2(0,0), "IA32_MC2_STATUS", "", {
		{ BITS_EOT }
	}},
	{0x40a, MSRTYPE_RDWR, MSR2(0,0), "IA32_MC2_ADDR", "", {
		{ BITS_EOT }
	}},
#if 0
	{0x40c, MSRTYPE_RDWR, MSR2(0,0), "IA32_MC4_CTL", "", {
		{ BITS_EOT }
	}},
	{0x40d, MSRTYPE_RDWR, MSR2(0,0), "IA32_MC4_STATUS", "", {
		{ BITS_EOT }
	}},
	{0x40e, MSRTYPE_RDWR, MSR2(0,0), "IA32_MC4_ADDR", "", {
		{ BITS_EOT }
	}},
#endif
	{0x410, MSRTYPE_RDWR, MSR2(0,0), "IA32_MC3_CTL", "", {
		{ BITS_EOT }
	}},
	{0x411, MSRTYPE_RDWR, MSR2(0,0), "IA32_MC3_STATUS", "", {
		{ BITS_EOT }
	}},
	{0x412, MSRTYPE_RDWR, MSR2(0,0), "IA32_MC3_ADDR", "", {
		{ BITS_EOT }
	}},
	{0x600, MSRTYPE_RDWR, MSR2(0,0), "IA32_DS_AREA", "DS Save Area", {
		/* Additional info available at Section 18.10.4 of Intel 64
		 * and IA-32 Architectures Software Developer's Manual,
		 * "Debug Store (DS) Mechanism".
		 */
		{ 63, 32, RESERVED }, // reserved if not in IA-32e mode
		{ 31, 32, "Linear address of DS buffer management area",
				"R/W", PRESENT_HEX, {
			{ BITVAL_EOT }
		}},
		{ BITS_EOT }
	}},
	{ MSR_EOT }
};
