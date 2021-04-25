/* uio_usbdebug - Run coreboot's usbdebug driver in userspace */
/* SPDX-License-Identifier: GPL-2.0-only */

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include <pci/pci.h>

/* coreboot's arch/io.h conflicts with libc's sys/io.h, so declare this here: */
int ioperm(unsigned long from, unsigned long num, int turn_on);

#include <arch/io.h>
#include <console/usb.h>

void *ehci_bar;
struct pci_access *pci_access;

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <uio-dev>\n", argv[0]);
		return 1;
	}
	const int fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		perror("Failed to open uio device");
		return 2;
	}
	ehci_bar =
		mmap(NULL, 1 << 8, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (MAP_FAILED == ehci_bar) {
		perror("Failed to map ehci bar");
		close(fd);
		return 3;
	}

	ioperm(0x80, 1, 1);

	pci_access = pci_alloc();
	pci_init(pci_access);

	usbdebug_init();

	pci_cleanup(pci_access);
	munmap(ehci_bar, 1 << 8);
	close(fd);
	return 0;
}
