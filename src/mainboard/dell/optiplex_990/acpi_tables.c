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

#include <southbridge/intel/bd82x6x/nvs.h>

/* FIXME: check this function.  */
void acpi_create_gnvs(global_nvs_t *gnvs)
{

        gnvs->apic = 1;
        gnvs->mpen = 1; /* Enable Multi Processing */
       // gnvs->pcnt = dev_count_cpu();

        /* Enable USB ports in S3 */
        gnvs->s3u0 = 1;
        gnvs->s3u1 = 1;

        gnvs->s5u0 = 1;
        gnvs->s5u1 = 1;

        /* IGD Displays */
        gnvs->ndid = 3;
        gnvs->did[0] = 0x80000100;
        gnvs->did[1] = 0x80000240;
        gnvs->did[2] = 0x80000410;
        gnvs->did[3] = 0x80000410;
        gnvs->did[4] = 0x00000005;

	gnvs->tcrt = 100;
	gnvs->tpsv = 90;


}
