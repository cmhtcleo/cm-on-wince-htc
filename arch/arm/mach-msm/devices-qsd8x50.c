/*
 * Copyright (C) 2008 Google, Inc.
 * Copyright (c) 2008-2010, Code Aurora Forum. All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

//#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
//#include <linux/interrupt.h>

#include <linux/dma-mapping.h>
#include <mach/irqs.h>
#include <mach/msm_iomap.h>
#include <mach/dma.h>
#include <mach/board.h>

#include "devices.h"
//#include "proc_comm.h"

#include <asm/mach/flash.h>
//#include <asm/mach/mmc.h>
//#include <linux/mtd/nand.h>
//#include <linux/mtd/partitions.h>

#include <mach/mmc.h>

#include "clock.h"

#include <mach/msm_hsusb.h>
#include <mach/msm_rpcrouter.h>
#include <mach/msm_hsusb_hw.h>
#ifdef CONFIG_USB_FUNCTION
#include <linux/usb/mass_storage_function.h>
#endif
#ifdef CONFIG_PMIC8058
#include <linux/mfd/pmic8058.h>
#endif

static char *df_serialno = "000000000000";
static char *board_sn;
//int usb_phy_error;

#define HSUSB_API_INIT_PHY_PROC	2
#define HSUSB_API_PROG		0x30000064
#define HSUSB_API_VERS MSM_RPC_VERS(1, 1)

#define MFG_GPIO_TABLE_MAX_SIZE        0x400
static unsigned char mfg_gpio_table[MFG_GPIO_TABLE_MAX_SIZE];

#if 0

static struct resource resources_uart1[] = {
	{
		.start	= INT_UART1,
		.end	= INT_UART1,
		.flags	= IORESOURCE_IRQ,
	},
	{
		.start	= MSM_UART1_PHYS,
		.end	= MSM_UART1_PHYS + MSM_UART1_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
};

static struct resource resources_uart2[] = {
	{
		.start	= INT_UART2,
		.end	= INT_UART2,
		.flags	= IORESOURCE_IRQ,
	},
	{
		.start	= MSM_UART2_PHYS,
		.end	= MSM_UART2_PHYS + MSM_UART2_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
};

static struct resource resources_uart3[] = {
	{
		.start	= INT_UART3,
		.end	= INT_UART3,
		.flags	= IORESOURCE_IRQ,
	},
	{
		.start	= MSM_UART3_PHYS,
		.end	= MSM_UART3_PHYS + MSM_UART3_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
};

struct platform_device msm_device_uart1 = {
	.name	= "msm_serial",
	.id	= 0,
	.num_resources	= ARRAY_SIZE(resources_uart1),
	.resource	= resources_uart1,
};

struct platform_device msm_device_uart2 = {
	.name	= "msm_serial",
	.id	= 1,
	.num_resources	= ARRAY_SIZE(resources_uart2),
	.resource	= resources_uart2,
};

struct platform_device msm_device_uart3 = {
	.name	= "msm_serial",
	.id	= 2,
	.num_resources	= ARRAY_SIZE(resources_uart3),
	.resource	= resources_uart3,
};

static struct resource msm_uart1_dm_resources[] = {
	{
		.start = MSM_UART1DM_PHYS,
		.end   = MSM_UART1DM_PHYS + PAGE_SIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = INT_UART1DM_IRQ,
		.end   = INT_UART1DM_IRQ,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = INT_UART1DM_RX,
		.end   = INT_UART1DM_RX,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = DMOV_HSUART1_TX_CHAN,
		.end   = DMOV_HSUART1_RX_CHAN,
		.name  = "uartdm_channels",
		.flags = IORESOURCE_DMA,
	},
	{
		.start = DMOV_HSUART1_TX_CRCI,
		.end   = DMOV_HSUART1_RX_CRCI,
		.name  = "uartdm_crci",
		.flags = IORESOURCE_DMA,
	},
};

static u64 msm_uart_dm1_dma_mask = DMA_BIT_MASK(32);

struct platform_device msm_device_uart_dm1 = {
	.name = "msm_serial_hs",
	.id = 0,
	.num_resources = ARRAY_SIZE(msm_uart1_dm_resources),
	.resource = msm_uart1_dm_resources,
	.dev		= {
		.dma_mask = &msm_uart_dm1_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
};

static struct resource msm_uart2_dm_resources[] = {
	{
		.start = MSM_UART2DM_PHYS,
		.end   = MSM_UART2DM_PHYS + PAGE_SIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = INT_UART2DM_IRQ,
		.end   = INT_UART2DM_IRQ,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = INT_UART2DM_RX,
		.end   = INT_UART2DM_RX,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = DMOV_HSUART2_TX_CHAN,
		.end   = DMOV_HSUART2_RX_CHAN,
		.name  = "uartdm_channels",
		.flags = IORESOURCE_DMA,
	},
	{
		.start = DMOV_HSUART2_TX_CRCI,
		.end   = DMOV_HSUART2_RX_CRCI,
		.name  = "uartdm_crci",
		.flags = IORESOURCE_DMA,
	},
};

static u64 msm_uart_dm2_dma_mask = DMA_BIT_MASK(32);

struct platform_device msm_device_uart_dm2 = {
	.name = "msm_serial_hs",
	.id = 1,
	.num_resources = ARRAY_SIZE(msm_uart2_dm_resources),
	.resource = msm_uart2_dm_resources,
	.dev		= {
		.dma_mask = &msm_uart_dm2_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
};

static struct resource resources_i2c[] = {
	{
		.start	= MSM_I2C_PHYS,
		.end	= MSM_I2C_PHYS + MSM_I2C_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_PWB_I2C,
		.end	= INT_PWB_I2C,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device msm_device_i2c = {
	.name		= "msm_i2c",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(resources_i2c),
	.resource	= resources_i2c,
};

#define GPIO_I2C_CLK 95
#define GPIO_I2C_DAT 96
static int gpio_i2c_clk = -1;
static int gpio_i2c_dat = -1;
void msm_set_i2c_mux(bool gpio, int *gpio_clk, int *gpio_dat, int clk_str, int dat_str)
{
	unsigned id;

	if (gpio_i2c_clk < 0) {
		gpio_request(GPIO_I2C_CLK, "i2c-clk");
		gpio_i2c_clk = GPIO_I2C_CLK;
	}
	if (gpio_i2c_dat < 0) {
		gpio_request(GPIO_I2C_DAT, "i2c-dat");
		gpio_i2c_dat = GPIO_I2C_DAT;
	}

	if (gpio) {
		id = PCOM_GPIO_CFG(GPIO_I2C_CLK, 0, GPIO_OUTPUT,
				   GPIO_NO_PULL, GPIO_2MA);
		msm_proc_comm(PCOM_RPC_GPIO_TLMM_CONFIG_EX, &id, 0);
		id = PCOM_GPIO_CFG(GPIO_I2C_DAT, 0, GPIO_OUTPUT,
				   GPIO_NO_PULL, GPIO_2MA);
		msm_proc_comm(PCOM_RPC_GPIO_TLMM_CONFIG_EX, &id, 0);
		*gpio_clk = GPIO_I2C_CLK;
		*gpio_dat = GPIO_I2C_DAT;
	} else {
		id = PCOM_GPIO_CFG(GPIO_I2C_CLK, 1, GPIO_INPUT,
				   GPIO_NO_PULL, clk_str);
		msm_proc_comm(PCOM_RPC_GPIO_TLMM_CONFIG_EX, &id, 0);
		id = PCOM_GPIO_CFG(GPIO_I2C_DAT , 1, GPIO_INPUT,
				   GPIO_NO_PULL, dat_str);
		msm_proc_comm(PCOM_RPC_GPIO_TLMM_CONFIG_EX, &id, 0);
	}
}

static struct resource resources_hsusb[] = {
	{
		.start	= MSM_HSUSB_PHYS,
		.end	= MSM_HSUSB_PHYS + MSM_HSUSB_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_USB_HS,
		.end	= INT_USB_HS,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device msm_device_hsusb = {
	.name		= "msm_hsusb",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(resources_hsusb),
	.resource	= resources_hsusb,
	.dev		= {
		.coherent_dma_mask	= 0xffffffff,
	},
};

struct flash_platform_data msm_nand_data = {
	.parts		= NULL,
	.nr_parts	= 0,
};

static struct resource resources_nand[] = {
	[0] = {
		.start	= 7,
		.end	= 7,
		.flags	= IORESOURCE_DMA,
	},
};

struct platform_device msm_device_nand = {
	.name		= "msm_nand",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(resources_nand),
	.resource	= resources_nand,
	.dev		= {
		.platform_data	= &msm_nand_data,
	},
};

struct platform_device msm_device_smd = {
	.name	= "msm_smd",
	.id	= -1,
};

static struct resource resources_sdc1[] = {
	{
		.start	= MSM_SDC1_PHYS,
		.end	= MSM_SDC1_PHYS + MSM_SDC1_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_SDC1_0,
		.end	= INT_SDC1_0,
		.flags	= IORESOURCE_IRQ,
		.name	= "cmd_irq",
	},
	{
		.start	= INT_SDC1_1,
		.end	= INT_SDC1_1,
		.flags	= IORESOURCE_IRQ,
		.name	= "pio_irq",
	},
	{
		.flags	= IORESOURCE_IRQ | IORESOURCE_DISABLED,
		.name	= "status_irq"
	},
	{
		.start	= 8,
		.end	= 8,
		.flags	= IORESOURCE_DMA,
	},
};

static struct resource resources_sdc2[] = {
	{
		.start	= MSM_SDC2_PHYS,
		.end	= MSM_SDC2_PHYS + MSM_SDC2_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_SDC2_0,
		.end	= INT_SDC2_0,
		.flags	= IORESOURCE_IRQ,
		.name	= "cmd_irq",
	},
		{
		.start	= INT_SDC2_1,
		.end	= INT_SDC2_1,
		.flags	= IORESOURCE_IRQ,
		.name	= "pio_irq",
	},
	{
		.flags	= IORESOURCE_IRQ | IORESOURCE_DISABLED,
		.name	= "status_irq"
	},
	{
		.start	= 8,
		.end	= 8,
		.flags	= IORESOURCE_DMA,
	},
};

static struct resource resources_sdc3[] = {
	{
		.start	= MSM_SDC3_PHYS,
		.end	= MSM_SDC3_PHYS + MSM_SDC3_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_SDC3_0,
		.end	= INT_SDC3_0,
		.flags	= IORESOURCE_IRQ,
		.name	= "cmd_irq",
	},
		{
		.start	= INT_SDC3_1,
		.end	= INT_SDC3_1,
		.flags	= IORESOURCE_IRQ,
		.name	= "pio_irq",
	},
	{
		.flags	= IORESOURCE_IRQ | IORESOURCE_DISABLED,
		.name	= "status_irq"
	},
	{
		.start	= 8,
		.end	= 8,
		.flags	= IORESOURCE_DMA,
	},
};

static struct resource resources_sdc4[] = {
	{
		.start	= MSM_SDC4_PHYS,
		.end	= MSM_SDC4_PHYS + MSM_SDC4_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_SDC4_0,
		.end	= INT_SDC4_0,
		.flags	= IORESOURCE_IRQ,
		.name	= "cmd_irq",
	},
		{
		.start	= INT_SDC4_1,
		.end	= INT_SDC4_1,
		.flags	= IORESOURCE_IRQ,
		.name	= "pio_irq",
	},
	{
		.flags	= IORESOURCE_IRQ | IORESOURCE_DISABLED,
		.name	= "status_irq"
	},
	{
		.start	= 8,
		.end	= 8,
		.flags	= IORESOURCE_DMA,
	},
};

struct platform_device msm_device_sdc1 = {
	.name		= "msm_sdcc",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(resources_sdc1),
	.resource	= resources_sdc1,
	.dev		= {
		.coherent_dma_mask	= 0xffffffff,
	},
};

struct platform_device msm_device_sdc2 = {
	.name		= "msm_sdcc",
	.id		= 2,
	.num_resources	= ARRAY_SIZE(resources_sdc2),
	.resource	= resources_sdc2,
	.dev		= {
		.coherent_dma_mask	= 0xffffffff,
	},
};

struct platform_device msm_device_sdc3 = {
	.name		= "msm_sdcc",
	.id		= 3,
	.num_resources	= ARRAY_SIZE(resources_sdc3),
	.resource	= resources_sdc3,
	.dev		= {
		.coherent_dma_mask	= 0xffffffff,
	},
};

struct platform_device msm_device_sdc4 = {
	.name		= "msm_sdcc",
	.id		= 4,
	.num_resources	= ARRAY_SIZE(resources_sdc4),
	.resource	= resources_sdc4,
	.dev		= {
		.coherent_dma_mask	= 0xffffffff,
	},
};

static struct platform_device *msm_sdcc_devices[] __initdata = {
	&msm_device_sdc1,
	&msm_device_sdc2,
	&msm_device_sdc3,
	&msm_device_sdc4,
};

int __init msm_add_sdcc(unsigned int controller, struct mmc_platform_data *plat,
			unsigned int stat_irq, unsigned long stat_irq_flags)
{
	struct platform_device	*pdev;
	struct resource *res;

	if (controller < 1 || controller > 4)
		return -EINVAL;

	pdev = msm_sdcc_devices[controller-1];
	pdev->dev.platform_data = plat;

	res = platform_get_resource_byname(pdev, IORESOURCE_IRQ, "status_irq");
	if (!res)
		return -EINVAL;
	else if (stat_irq) {
		res->start = res->end = stat_irq;
		res->flags &= ~IORESOURCE_DISABLED;
		res->flags |= stat_irq_flags;
	}

	return platform_device_register(pdev);
}

static struct resource resources_mddi0[] = {
	{
		.start	= MSM_PMDH_PHYS,
		.end	= MSM_PMDH_PHYS + MSM_PMDH_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_MDDI_PRI,
		.end	= INT_MDDI_PRI,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct resource resources_mddi1[] = {
	{
		.start	= MSM_EMDH_PHYS,
		.end	= MSM_EMDH_PHYS + MSM_EMDH_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_MDDI_EXT,
		.end	= INT_MDDI_EXT,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device msm_device_mddi0 = {
	.name = "msm_mddi",
	.id = 0,
	.num_resources = ARRAY_SIZE(resources_mddi0),
	.resource = resources_mddi0,
	.dev = {
		.coherent_dma_mask      = 0xffffffff,
	},
};

struct platform_device msm_device_mddi1 = {
	.name = "msm_mddi",
	.id = 1,
	.num_resources = ARRAY_SIZE(resources_mddi1),
	.resource = resources_mddi1,
	.dev = {
		.coherent_dma_mask      = 0xffffffff,
	},
};

static struct resource resources_mdp[] = {
	{
		.start	= MSM_MDP_PHYS,
		.end	= MSM_MDP_PHYS + MSM_MDP_SIZE - 1,
		.name	= "mdp",
		.flags	= IORESOURCE_MEM
	},
	{
		.start	= INT_MDP,
		.end	= INT_MDP,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device msm_device_mdp = {
	.name = "msm_mdp",
	.id = 0,
	.num_resources = ARRAY_SIZE(resources_mdp),
	.resource = resources_mdp,
};

static struct resource resources_tssc[] = {
	{
		.start	= MSM_TSSC_PHYS,
		.end	= MSM_TSSC_PHYS + MSM_TSSC_SIZE - 1,
		.name	= "tssc",
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_TCHSCRN1,
		.end	= INT_TCHSCRN1,
		.name	= "tssc1",
		.flags	= IORESOURCE_IRQ | IRQF_TRIGGER_RISING,
	},
	{
		.start	= INT_TCHSCRN2,
		.end	= INT_TCHSCRN2,
		.name	= "tssc2",
		.flags	= IORESOURCE_IRQ | IRQF_TRIGGER_RISING,
	},
};

struct platform_device msm_device_touchscreen = {
	.name = "msm_touchscreen",
	.id = 0,
	.num_resources = ARRAY_SIZE(resources_tssc),
	.resource = resources_tssc,
};

static struct resource resources_spi[] = {
	{
		.start	= MSM_SPI_PHYS,
		.end	= MSM_SPI_PHYS + MSM_SPI_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= INT_SPI_INPUT,
		.end	= INT_SPI_INPUT,
		.name	= "irq_in",
		.flags	= IORESOURCE_IRQ,
	},
	{
		.start	= INT_SPI_OUTPUT,
		.end	= INT_SPI_OUTPUT,
		.name	= "irq_out",
		.flags	= IORESOURCE_IRQ,
	},
	{
		.start	= INT_SPI_ERROR,
		.end	= INT_SPI_ERROR,
		.name	= "irq_err",
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device msm_device_spi = {
	.name		= "msm_spi",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(resources_spi),
	.resource	= resources_spi,
};
#endif

struct clk msm_clocks_8x50[] = {
	CLK_PCOM("adm_clk",	ADM_CLK,	NULL, 0),
	CLK_PCOM("ebi1_clk",	EBI1_CLK,	NULL, CLK_MIN | CLKFLAG_SHARED),
	CLK_PCOM("ebi2_clk",	EBI2_CLK,	NULL, 0),
	CLK_PCOM("ecodec_clk",	ECODEC_CLK,	NULL, 0),
	CLK_PCOM("mddi_clk",	EMDH_CLK,	&msm_device_mddi1.dev, OFF | CLK_MINMAX),
	CLK_PCOM("gp_clk",	GP_CLK,		NULL, 0),
	CLK_PCOM("grp_clk",	GRP_3D_CLK,	NULL, 0),
	CLK_PCOM("i2c_clk",	I2C_CLK,	&msm_device_i2c.dev, 0),
	CLK_PCOM("icodec_rx_clk",	ICODEC_RX_CLK,	NULL, 0),
	CLK_PCOM("icodec_tx_clk",	ICODEC_TX_CLK,	NULL, 0),
	CLK_PCOM("imem_clk",	IMEM_CLK,	NULL, OFF),
	CLK_PCOM("mdc_clk",	MDC_CLK,	NULL, 0),
	CLK_PCOM("mddi_clk",	PMDH_CLK,	&msm_device_mddi0.dev, OFF | CLK_MINMAX),
	CLK_PCOM("mdp_clk",	MDP_CLK,	&msm_device_mdp.dev, OFF),
	CLK_PCOM("lcdc_pclk_clk", MDP_LCDC_PCLK_CLK, &msm_device_mdp.dev, 0),
	CLK_PCOM("lcdc_pad_pclk_clk", MDP_LCDC_PAD_PCLK_CLK, &msm_device_mdp.dev, 0),
	CLK_PCOM("mdp_vsync_clk",	MDP_VSYNC_CLK,	&msm_device_mdp.dev, 0),
	CLK_PCOM("pbus_clk",	PBUS_CLK,	NULL, CLK_MIN),
	CLK_PCOM("pcm_clk",	PCM_CLK,	NULL, 0),
	CLK_PCOM("sdac_clk",	SDAC_CLK,	NULL, OFF),
	CLK_PCOM("spi_clk",	SPI_CLK,	NULL, 0),
	CLK_PCOM("sdc_clk",	SDC1_CLK,	&msm_device_sdc1.dev, OFF),
	CLK_PCOM("sdc_pclk",	SDC1_P_CLK,	&msm_device_sdc1.dev, OFF),
	CLK_PCOM("sdc_clk",	SDC2_CLK,	&msm_device_sdc2.dev, OFF),
	CLK_PCOM("sdc_pclk",	SDC2_P_CLK,	&msm_device_sdc2.dev, OFF),
	CLK_PCOM("sdc_clk",	SDC3_CLK,	&msm_device_sdc3.dev, OFF),
	CLK_PCOM("sdc_pclk",	SDC3_P_CLK,	&msm_device_sdc3.dev, OFF),
	CLK_PCOM("sdc_clk",	SDC4_CLK,	&msm_device_sdc4.dev, OFF),
	CLK_PCOM("sdc_pclk",	SDC4_P_CLK,	&msm_device_sdc4.dev, OFF),
	CLK_PCOM("tsif_clk",	TSIF_CLK,	NULL, 0),
	CLK_PCOM("tsif_ref_clk",	TSIF_REF_CLK,	NULL, 0),
	CLK_PCOM("tv_dac_clk",	TV_DAC_CLK,	NULL, 0),
	CLK_PCOM("tv_enc_clk",	TV_ENC_CLK,	NULL, 0),
	CLK_PCOM("uart_clk",	UART1_CLK,	&msm_device_uart1.dev, OFF),
	CLK_PCOM("uart_clk",	UART2_CLK,	&msm_device_uart2.dev, OFF),
	CLK_PCOM("uart_clk",	UART3_CLK,	&msm_device_uart3.dev, OFF),
	CLK_PCOM("uartdm_clk",	UART1DM_CLK,	&msm_device_uart_dm1.dev, OFF),
	CLK_PCOM("uartdm_clk",	UART2DM_CLK,	&msm_device_uart_dm2.dev, OFF),
	CLK_PCOM("usb_hs_clk",	USB_HS_CLK,	&msm_device_hsusb.dev, OFF),
	CLK_PCOM("usb_hs_pclk",	USB_HS_P_CLK,	&msm_device_hsusb.dev, OFF),
	CLK_PCOM("usb_otg_clk",	USB_OTG_CLK,	NULL, 0),
	CLK_PCOM("vdc_clk",	VDC_CLK,	NULL, OFF | CLK_MIN),
	CLK_PCOM("vfe_clk",	VFE_CLK,	NULL, OFF),
	CLK_PCOM("vfe_mdc_clk",	VFE_MDC_CLK,	NULL, OFF),
	CLK_PCOM("vfe_axi_clk",	VFE_AXI_CLK,	NULL, OFF),
	CLK_PCOM("usb_hs2_clk",	USB_HS2_CLK,	NULL, OFF),
	CLK_PCOM("usb_hs2_pclk",	USB_HS2_P_CLK,	NULL, OFF),
	CLK_PCOM("usb_hs3_clk",	USB_HS3_CLK,	NULL, OFF),
	CLK_PCOM("usb_hs3_pclk",	USB_HS3_P_CLK,	NULL, OFF),
	CLK_PCOM("usb_phy_clk",	USB_PHY_CLK,	NULL, 0),
#ifdef CONFIG_MACH_HTCLEO
	CLOCK(NULL, 0, NULL, 0),
#endif
};

unsigned msm_num_clocks_8x50 = ARRAY_SIZE(msm_clocks_8x50);

static int mfg_mode;
int __init board_mfg_mode_init(char *s)
{
	if (!strcmp(s, "normal"))
		mfg_mode = 0;
	else if (!strcmp(s, "factory2"))
		mfg_mode = 1;
	else if (!strcmp(s, "recovery"))
		mfg_mode = 2;
	else if (!strcmp(s, "charge"))
		mfg_mode = 3;
	else if (!strcmp(s, "power_test"))
		mfg_mode = 4;
	else if (!strcmp(s, "offmode_charging"))
		mfg_mode = 5;

	return 1;
}
__setup("androidboot.mode=", board_mfg_mode_init);


int board_mfg_mode(void)
{
	return mfg_mode;
}

EXPORT_SYMBOL(board_mfg_mode);

static int __init board_serialno_setup(char *serialno)
{
	char *str;

	/* use default serial number when mode is factory2 */
	if (board_mfg_mode() == 1 || !strlen(serialno))
		str = df_serialno;
	else
		str = serialno;
#ifdef CONFIG_USB_FUNCTION
	msm_hsusb_pdata.serial_number = str;
#endif
	board_sn = str;
	return 1;
}
__setup("androidboot.serialno=", board_serialno_setup);

char *board_serialno(void)
{
	return board_sn;
}

#define ATAG_SKUID 0x4d534D73
int __init parse_tag_skuid(const struct tag *tags)
{
	int skuid = 0, find = 0;
	struct tag *t = (struct tag *)tags;

	for (; t->hdr.size; t = tag_next(t)) {
		if (t->hdr.tag == ATAG_SKUID) {
			printk(KERN_DEBUG "find the skuid tag\n");
			find = 1;
			break;
		}
	}

	if (find)
		skuid = t->u.revision.rev;
	printk(KERN_DEBUG "parse_tag_skuid: hwid = 0x%x\n", skuid);
	return skuid;
}
__tagtable(ATAG_SKUID, parse_tag_skuid);

#define ATAG_HERO_PANEL_TYPE 0x4d534D74
int panel_type;
int __init tag_panel_parsing(const struct tag *tags)
{
	panel_type = tags->u.revision.rev;

	printk(KERN_DEBUG "%s: panel type = %d\n", __func__,
		panel_type);

	return panel_type;
}
__tagtable(ATAG_HERO_PANEL_TYPE, tag_panel_parsing);

#define ATAG_ENGINEERID 0x4d534D75
unsigned engineer_id;
int __init parse_tag_engineerid(const struct tag *tags)
{
	int engineerid = 0, find = 0;
	struct tag *t = (struct tag *)tags;

	for (; t->hdr.size; t = tag_next(t)) {
		if (t->hdr.tag == ATAG_ENGINEERID) {
			printk(KERN_DEBUG "find the engineer tag\n");
			find = 1;
			break;
		}
	}

	if (find) {
		engineer_id = t->u.revision.rev;
		engineerid = t->u.revision.rev;
	}
	printk(KERN_DEBUG "parse_tag_engineerid: 0x%x\n", engineerid);
	return engineerid;
}
__tagtable(ATAG_ENGINEERID, parse_tag_engineerid);

#define ATAG_MFG_GPIO_TABLE 0x59504551
int __init parse_tag_mfg_gpio_table(const struct tag *tags)
{
       unsigned char *dptr = (unsigned char *)(&tags->u);
       __u32 size;

       size = min((__u32)(tags->hdr.size - 2) * sizeof(__u32), (__u32)MFG_GPIO_TABLE_MAX_SIZE);
       memcpy(mfg_gpio_table, dptr, size);
       return 0;
}
__tagtable(ATAG_MFG_GPIO_TABLE, parse_tag_mfg_gpio_table);

char * board_get_mfg_sleep_gpio_table(void)
{
        return mfg_gpio_table;
}
EXPORT_SYMBOL(board_get_mfg_sleep_gpio_table);

static char *emmc_tag;
static int __init board_set_emmc_tag(char *get_hboot_emmc)
{
	if (strlen(get_hboot_emmc))
		emmc_tag = get_hboot_emmc;
	else
		emmc_tag = NULL;
	return 1;
}
__setup("androidboot.emmc=", board_set_emmc_tag);

int board_emmc_boot(void)
{
	if (emmc_tag) {
		if (!strcmp(emmc_tag, "true"))
			return 1;
	}

	return 0;
}
