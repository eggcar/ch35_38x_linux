/*
 * PCI/PCIe to serial driver(pre) for ch351/352/353/355/356/357/358/359/382/384, etc.
 * This driver only needs to be used when the system does not assign an interrupt number for device.
 *
 * Copyright (C) 2022 Nanjing Qinheng Microelectronics Co., Ltd.
 * Web: http://wch.cn
 * Author: WCH <tech@wch.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Update Log:
 * V1.00 - initial version
 */

#include <linux/version.h>
#ifndef KERNEL_VERSION
#define KERNEL_VERSION(ver, rel, seq) ((ver << 16) | (rel << 8) | seq)
#endif
#include <linux/module.h>
#include <linux/pci.h>

#define WCH_DRIVER_AUTHOR "WCH GROUP"
#define WCH_DRIVER_DESC   "WCH Multi-I/O Board Driver Module(pre)"

#define VENDOR_ID_WCH_PCIE             0x1C00
#define SUB_VENDOR_ID_WCH_PCIE         0x1C00
#define VENDOR_ID_WCH_PCI              0x4348
#define SUB_VENDOR_ID_WCH_PCI          0x4348
#define VENDOR_ID_WCH_CH351            0x1C00
#define SUB_VENDOR_ID_WCH_CH351        0x1C00
#define DEVICE_ID_WCH_CH351_2S         0x2273
#define SUB_DEVICE_ID_WCH_CH351_2S     0x2273
#define DEVICE_ID_WCH_CH352_1S1P       0x5053
#define SUB_DEVICE_ID_WCH_CH352_1S1P   0x5053
#define DEVICE_ID_WCH_CH352_2S         0x3253
#define SUB_DEVICE_ID_WCH_CH352_2S     0x3253
#define DEVICE_ID_WCH_CH353_4S         0x3453
#define SUB_DEVICE_ID_WCH_CH353_4S     0x3453
#define DEVICE_ID_WCH_CH353_2S1P       0x7053
#define SUB_DEVICE_ID_WCH_CH353_2S1P   0x3253
#define DEVICE_ID_WCH_CH353_2S1PAR     0x5046
#define SUB_DEVICE_ID_WCH_CH353_2S1PAR 0x5046
#define DEVICE_ID_WCH_CH355_4S         0x7173
#define SUB_DEVICE_ID_WCH_CH355_4S     0x3473
#define DEVICE_ID_WCH_CH356_4S1P       0x7073
#define SUB_DEVICE_ID_WCH_CH356_4S1P   0x3473
#define DEVICE_ID_WCH_CH356_6S         0x3873
#define SUB_DEVICE_ID_WCH_CH356_6S     0x3873
#define DEVICE_ID_WCH_CH356_8S         0x3853
#define SUB_DEVICE_ID_WCH_CH356_8S     0x3853
#define DEVICE_ID_WCH_CH357_4S         0x5334
#define SUB_DEVICE_ID_WCH_CH357_4S     0x5053
#define DEVICE_ID_WCH_CH358_4S1P       0x5334
#define SUB_DEVICE_ID_WCH_CH358_4S1P   0x5334
#define DEVICE_ID_WCH_CH358_8S         0x5338
#define SUB_DEVICE_ID_WCH_CH358_8S     0x5338
#define DEVICE_ID_WCH_CH359_16S        0x5838
#define SUB_DEVICE_ID_WCH_CH359_16S    0x5838
#define DEVICE_ID_WCH_CH382_2S         0x3253
#define SUB_DEVICE_ID_WCH_CH382_2S     0x3253
#define DEVICE_ID_WCH_CH382_2S1P       0x3250
#define SUB_DEVICE_ID_WCH_CH382_2S1P   0x3250
#define DEVICE_ID_WCH_CH384_4S         0x3470
#define SUB_DEVICE_ID_WCH_CH384_4S     0x3470
#define DEVICE_ID_WCH_CH384_4S1P       0x3450
#define SUB_DEVICE_ID_WCH_CH384_4S1P   0x3450
#define DEVICE_ID_WCH_CH384_8S         0x3853
#define SUB_DEVICE_ID_WCH_CH384_8S     0x3853
#define DEVICE_ID_WCH_CH384_28S        0x4353
#define SUB_DEVICE_ID_WCH_CH384_28S    0x4353
#define DEVICE_ID_WCH_CH365_32S        0x5049
#define SUB_DEVICE_ID_WCH_CH365_32S    0x5049

enum {
    NONE_BOARD = 0,
    WCH_BOARD_CH351_2S,
    WCH_BOARD_CH352_2S,
    WCH_BOARD_CH352_1S1P,
    WCH_BOARD_CH353_4S,
    WCH_BOARD_CH353_2S1P,
    WCH_BOARD_CH353_2S1PAR,
    WCH_BOARD_CH355_4S,
    WCH_BOARD_CH356_4S1P,
    WCH_BOARD_CH356_6S,
    WCH_BOARD_CH356_8S,
    WCH_BOARD_CH357_4S,
    WCH_BOARD_CH358_4S1P,
    WCH_BOARD_CH358_8S,
    WCH_BOARD_CH359_16S,
    WCH_BOARD_CH382_2S,
    WCH_BOARD_CH382_2S1P,
    WCH_BOARD_CH384_4S,
    WCH_BOARD_CH384_4S1P,
    WCH_BOARD_CH384_8S,
    WCH_BOARD_CH384_28S,
    WCH_BOARD_CH365_32S,
};

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 0))
static struct pci_device_id wch_pci_board_id[] = {
    {VENDOR_ID_WCH_CH351, DEVICE_ID_WCH_CH351_2S, SUB_VENDOR_ID_WCH_CH351, SUB_DEVICE_ID_WCH_CH351_2S, 0, 0,
     WCH_BOARD_CH351_2S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH352_2S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH352_2S, 0, 0,
     WCH_BOARD_CH352_2S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH352_1S1P, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH352_1S1P, 0, 0,
     WCH_BOARD_CH352_1S1P},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH353_4S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH353_4S, 0, 0,
     WCH_BOARD_CH353_4S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH353_2S1P, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH353_2S1P, 0, 0,
     WCH_BOARD_CH353_2S1P},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH353_2S1PAR, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH353_2S1PAR, 0, 0,
     WCH_BOARD_CH353_2S1PAR},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH355_4S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH355_4S, 0, 0,
     WCH_BOARD_CH355_4S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH356_4S1P, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH356_4S1P, 0, 0,
     WCH_BOARD_CH356_4S1P},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH356_6S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH356_6S, 0, 0,
     WCH_BOARD_CH356_6S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH356_8S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH356_8S, 0, 0,
     WCH_BOARD_CH356_8S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH357_4S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH357_4S, 0, 0,
     WCH_BOARD_CH357_4S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH358_4S1P, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH358_4S1P, 0, 0,
     WCH_BOARD_CH358_4S1P},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH358_8S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH358_8S, 0, 0,
     WCH_BOARD_CH358_8S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH359_16S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH359_16S, 0, 0,
     WCH_BOARD_CH359_16S},
    {VENDOR_ID_WCH_PCIE, DEVICE_ID_WCH_CH382_2S, SUB_VENDOR_ID_WCH_PCIE, SUB_DEVICE_ID_WCH_CH382_2S, 0, 0,
     WCH_BOARD_CH382_2S},
    {VENDOR_ID_WCH_PCIE, DEVICE_ID_WCH_CH382_2S1P, SUB_VENDOR_ID_WCH_PCIE, SUB_DEVICE_ID_WCH_CH382_2S1P, 0, 0,
     WCH_BOARD_CH382_2S1P},
    {VENDOR_ID_WCH_PCIE, DEVICE_ID_WCH_CH384_4S, SUB_VENDOR_ID_WCH_PCIE, SUB_DEVICE_ID_WCH_CH384_4S, 0, 0,
     WCH_BOARD_CH384_4S},
    {VENDOR_ID_WCH_PCIE, DEVICE_ID_WCH_CH384_4S1P, SUB_VENDOR_ID_WCH_PCIE, SUB_DEVICE_ID_WCH_CH384_4S1P, 0, 0,
     WCH_BOARD_CH384_4S1P},
    {VENDOR_ID_WCH_PCIE, DEVICE_ID_WCH_CH384_8S, SUB_VENDOR_ID_WCH_PCIE, SUB_DEVICE_ID_WCH_CH384_8S, 0, 0,
     WCH_BOARD_CH384_8S},
    {VENDOR_ID_WCH_PCIE, DEVICE_ID_WCH_CH384_28S, SUB_VENDOR_ID_WCH_PCIE, SUB_DEVICE_ID_WCH_CH384_28S, 0, 0,
     WCH_BOARD_CH384_28S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH365_32S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH365_32S, 0, 0,
     WCH_BOARD_CH365_32S},
    {0}
};
MODULE_DEVICE_TABLE(pci, wch_pci_board_id);
#else
struct wch_pci_info {
    unsigned short vendor;
    unsigned short device;
    unsigned short subvendor;
    unsigned short subdevice;
    unsigned short driver_data;
};

static struct wch_pci_info wch_pci_board_id[] = {
    {VENDOR_ID_WCH_CH351, DEVICE_ID_WCH_CH351_2S, SUB_VENDOR_ID_WCH_CH351, SUB_DEVICE_ID_WCH_CH351_2S,
     WCH_BOARD_CH351_2S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH352_2S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH352_2S, WCH_BOARD_CH352_2S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH352_1S1P, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH352_1S1P,
     WCH_BOARD_CH352_1S1P},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH353_4S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH353_4S, WCH_BOARD_CH353_4S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH353_2S1P, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH353_2S1P,
     WCH_BOARD_CH353_2S1P},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH353_2S1PAR, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH353_2S1PAR,
     WCH_BOARD_CH353_2S1PAR},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH355_4S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH355_4S, WCH_BOARD_CH355_4S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH356_4S1P, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH356_4S1P,
     WCH_BOARD_CH356_4S1P},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH356_6S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH356_6S, WCH_BOARD_CH356_6S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH356_8S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH356_8S, WCH_BOARD_CH356_8S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH357_4S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH357_4S, WCH_BOARD_CH357_4S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH358_4S1P, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH358_4S1P,
     WCH_BOARD_CH358_4S1P},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH358_8S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH358_8S, WCH_BOARD_CH358_8S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH359_16S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH359_16S,
     WCH_BOARD_CH359_16S},
    {VENDOR_ID_WCH_PCIE, DEVICE_ID_WCH_CH382_2S, SUB_VENDOR_ID_WCH_PCIE, SUB_DEVICE_ID_WCH_CH382_2S,
     WCH_BOARD_CH382_2S},
    {VENDOR_ID_WCH_PCIE, DEVICE_ID_WCH_CH382_2S1P, SUB_VENDOR_ID_WCH_PCIE, SUB_DEVICE_ID_WCH_CH382_2S1P,
     WCH_BOARD_CH382_2S1P},
    {VENDOR_ID_WCH_PCIE, DEVICE_ID_WCH_CH384_4S, SUB_VENDOR_ID_WCH_PCIE, SUB_DEVICE_ID_WCH_CH384_4S,
     WCH_BOARD_CH384_4S},
    {VENDOR_ID_WCH_PCIE, DEVICE_ID_WCH_CH384_4S1P, SUB_VENDOR_ID_WCH_PCIE, SUB_DEVICE_ID_WCH_CH384_4S1P,
     WCH_BOARD_CH384_4S1P},
    {VENDOR_ID_WCH_PCIE, DEVICE_ID_WCH_CH384_8S, SUB_VENDOR_ID_WCH_PCIE, SUB_DEVICE_ID_WCH_CH384_8S,
     WCH_BOARD_CH384_8S},
    {VENDOR_ID_WCH_PCIE, DEVICE_ID_WCH_CH384_28S, SUB_VENDOR_ID_WCH_PCIE, SUB_DEVICE_ID_WCH_CH384_28S,
     WCH_BOARD_CH384_28S},
    {VENDOR_ID_WCH_PCI, DEVICE_ID_WCH_CH365_32S, SUB_VENDOR_ID_WCH_PCI, SUB_DEVICE_ID_WCH_CH365_32S,
     WCH_BOARD_CH365_32S},
    {0}
};
#endif

/*
 * Probe to serial board.
 */
static int wch_probe(struct pci_dev *dev, const struct pci_device_id *ent)
{
    printk("\n====================WCH Device Driver(pre) Module probe====================\n");
    printk("Probe Device VID: %4x, PID: 0x%4x\n", dev->vendor, dev->device);
    return 0;
}

static void wch_remove(struct pci_dev *dev)
{
    printk("\n====================WCH Device Driver(pre) Module exit====================\n");
    printk("Remove Device VID: %4x, PID: 0x%4x\n", dev->vendor, dev->device);
}

static struct pci_driver wchserial_pci_driver = {
    .name = "wchpciserial",
    .probe = wch_probe,
    .remove = wch_remove,
    .id_table = wch_pci_board_id,
};

module_pci_driver(wchserial_pci_driver);

MODULE_AUTHOR(WCH_DRIVER_AUTHOR);
MODULE_DESCRIPTION(WCH_DRIVER_DESC);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 4, 18))
MODULE_LICENSE("GPL");
#endif
