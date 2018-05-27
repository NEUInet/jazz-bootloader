/*
 * iMX233 Boot Prep
 *
 * Copyright 2008-2010 Freescale Semiconductor, All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */


#include <debug.h>
#include "regsclkctrl.h"
#include "regsemi.h"
#include "regsdram.h"
#include "regspower.h"
#include "regsuartdbg.h"
#include "regspinctrl.h"
#include "regsdigctl.h"
#include "regsocotp.h"
#include <stdarg.h>

#define PIN_DRIVE_12mA 2
//#define EMI_96M
 /* Debug uart have been init by boot rom. */
void putc(char ch)
{
	int loop = 0;
	while (HW_UARTDBGFR_RD()&BM_UARTDBGFR_TXFF) {
		loop++;
		if (loop > 10000)
			break;
	};

	/* if(!(HW_UARTDBGFR_RD() &BM_UARTDBGFR_TXFF)) */
	HW_UARTDBGDR_WR(ch);
}
void delay(unsigned int us)
{
	unsigned int start , cur;
	start = cur = HW_DIGCTL_MICROSECONDS_RD();

	while (cur < start+us) {

		cur = HW_DIGCTL_MICROSECONDS_RD();
		/*printf("0x%x\r\n",cur);*/
	}

}

void init_mddr_mt46h32m16lf_96Mhz(int ce)
{
	HW_DRAM_CTL00_WR(0x01010001);
	HW_DRAM_CTL01_WR(0x00010100);
	HW_DRAM_CTL02_WR(0x01000101);
	HW_DRAM_CTL03_WR(0x00000001);
	HW_DRAM_CTL04_WR(0x00000101);
	HW_DRAM_CTL05_WR(0x00000001);
	HW_DRAM_CTL06_WR(0x00010000);
	HW_DRAM_CTL07_WR(0x01000001);
	HW_DRAM_CTL09_WR(0x00000001);
	HW_DRAM_CTL10_WR(0x07000200);
	HW_DRAM_CTL11_WR(0x00070203);
	HW_DRAM_CTL12_WR(0x02020002);
	HW_DRAM_CTL13_WR(0x06070a02);
	HW_DRAM_CTL14_WR(0x00000200|ce);
	HW_DRAM_CTL15_WR(0x03050000);
	HW_DRAM_CTL16_WR(0x02000000);
	HW_DRAM_CTL17_WR(0x2d000808);
	HW_DRAM_CTL18_WR(0x1f1f0000);
	HW_DRAM_CTL19_WR(0x020c1010);
	HW_DRAM_CTL20_WR(0x0305101c);
	HW_DRAM_CTL21_WR(0x00000007);
	HW_DRAM_CTL22_WR(0x00080008);
	HW_DRAM_CTL23_WR(0x00200020);
	HW_DRAM_CTL24_WR(0x00200020);
	HW_DRAM_CTL25_WR(0x00200020);
	HW_DRAM_CTL26_WR(0x000002e6);
	HW_DRAM_CTL29_WR(0x00000000);
	HW_DRAM_CTL30_WR(0x00000020);
	HW_DRAM_CTL31_WR(0x00000000);
	HW_DRAM_CTL32_WR(0x000c1a3b);
	HW_DRAM_CTL33_WR(0x0000000c);
	HW_DRAM_CTL34_WR(0x00004b0d);
	HW_DRAM_CTL36_WR(0x00000101);
	HW_DRAM_CTL37_WR(0x00040001);
	HW_DRAM_CTL38_WR(0x00400000);
	HW_DRAM_CTL39_WR(0x00400040);
	HW_DRAM_CTL40_WR(0x00030000);
	HW_DRAM_CTL08_WR(0x01010000);
}

void init_mddr_mt46h32m16lf_133Mhz(int ce)
{
	HW_DRAM_CTL00_WR(0x01010001);
	HW_DRAM_CTL01_WR(0x00010000);
	HW_DRAM_CTL02_WR(0x01000000);
	HW_DRAM_CTL03_WR(0x00000001);
	HW_DRAM_CTL04_WR(0x00000101);
	HW_DRAM_CTL05_WR(0x00000001);
	HW_DRAM_CTL06_WR(0x00010000);
	HW_DRAM_CTL07_WR(0x01000001);
	HW_DRAM_CTL09_WR(0x00000001);
	HW_DRAM_CTL10_WR(0x07000200);
	HW_DRAM_CTL11_WR(0x00070203);
	HW_DRAM_CTL12_WR(0x02020002);
	HW_DRAM_CTL13_WR(0x06070a02);
	HW_DRAM_CTL14_WR(0x00000200|ce);
	HW_DRAM_CTL15_WR(0x03050000);
	HW_DRAM_CTL16_WR(0x02000000);
	HW_DRAM_CTL17_WR(0x2000080a);
	HW_DRAM_CTL18_WR(0x1f1f0000);
	HW_DRAM_CTL19_WR(0x020C1010);
	HW_DRAM_CTL20_WR(0x0306101c);
	HW_DRAM_CTL21_WR(0x0000000a);
	HW_DRAM_CTL22_WR(0x00080008);
	HW_DRAM_CTL23_WR(0x00200020);
	HW_DRAM_CTL24_WR(0x00200020);
	HW_DRAM_CTL25_WR(0x00200020);
	HW_DRAM_CTL26_WR(0x00000408);  //TREF
	HW_DRAM_CTL29_WR(0x00000000);
	HW_DRAM_CTL30_WR(0x00000020);
	HW_DRAM_CTL31_WR(0x00000000);
	HW_DRAM_CTL32_WR(0x0010245f);
	HW_DRAM_CTL33_WR(0x00000010);
	HW_DRAM_CTL34_WR(0x00006808);
	HW_DRAM_CTL36_WR(0x00000101);
	HW_DRAM_CTL37_WR(0x00040001);
	HW_DRAM_CTL38_WR(0x00400162);
	HW_DRAM_CTL39_WR(0x00400040);
	HW_DRAM_CTL40_WR(0x00040000);
	HW_DRAM_CTL08_WR(0x01010000);
}

void init_ddr_mt46v32m16_133Mhz(int ce)
{
	HW_DRAM_CTL00_WR(0x01010001);
	HW_DRAM_CTL01_WR(0x00010100);
	HW_DRAM_CTL02_WR(0x01000101);
	HW_DRAM_CTL03_WR(0x00000001);
	HW_DRAM_CTL04_WR(0x00000101);
	HW_DRAM_CTL05_WR(0x00000000);
	HW_DRAM_CTL06_WR(0x00010000);
	HW_DRAM_CTL07_WR(0x01000001);
	HW_DRAM_CTL09_WR(0x00000001);
	HW_DRAM_CTL10_WR(0x07000200);  // TEMRS = 0
	HW_DRAM_CTL11_WR(0x00070202);
	HW_DRAM_CTL12_WR(0x02020000); //CKE = 0  TRRD = 0X02  TWR_INT =2
	HW_DRAM_CTL13_WR(0x04040a01); //TWTR =  0X1
	HW_DRAM_CTL14_WR(0x00000200|ce);

	HW_DRAM_CTL15_WR(0x02040000); //TDAL = 0X04  TRP = 0x02
	HW_DRAM_CTL16_WR(0x02000000); // TMRD = 0X02
	HW_DRAM_CTL17_WR(0x19000f08); // TRC = 0x08
	HW_DRAM_CTL18_WR(0x0d0d0000);
	HW_DRAM_CTL19_WR(0x02021313);
	HW_DRAM_CTL20_WR(0x02061521);  //TRAS_MIN = 0X06 TRCD_INT = 2
	HW_DRAM_CTL21_WR(0x0000000a);  //TRFC = 0x0a
	HW_DRAM_CTL22_WR(0x00080008);
	HW_DRAM_CTL23_WR(0x00200020);
	HW_DRAM_CTL24_WR(0x00200020);
	HW_DRAM_CTL25_WR(0x00200020);
	HW_DRAM_CTL26_WR(0x000003f7);  //TREF = 0x3f7
	HW_DRAM_CTL29_WR(0x00000020);
	HW_DRAM_CTL30_WR(0x00000020);
	HW_DRAM_CTL31_WR(0x00c80000); // TDLL = 0xc8
	HW_DRAM_CTL32_WR(0x000a23cd);  //TRAS_MAX =0x23cd  TXSNR  = 0xa
	HW_DRAM_CTL33_WR(0x000000c8);  //TXSR = 0xc8
	HW_DRAM_CTL34_WR(0x00006665);  //TINIT = 0X6665
	HW_DRAM_CTL36_WR(0x00000101);
	HW_DRAM_CTL37_WR(0x00040001);
	HW_DRAM_CTL38_WR(0x00000000);
	HW_DRAM_CTL39_WR(0x00000000);
	HW_DRAM_CTL40_WR(0x00010000);  //TPDEX = 0x01
	HW_DRAM_CTL08_WR(0x01000000);

}

void init_ddr_mt46v32m16_96Mhz(int ce)
{
	HW_DRAM_CTL00_WR(0x01010001);
	HW_DRAM_CTL01_WR(0x00010000);
	HW_DRAM_CTL02_WR(0x01000000);
	HW_DRAM_CTL03_WR(0x00000001);
	HW_DRAM_CTL04_WR(0x00000101);
	HW_DRAM_CTL05_WR(0x00000000);
	HW_DRAM_CTL06_WR(0x00010000);
	HW_DRAM_CTL07_WR(0x01000001);
	HW_DRAM_CTL09_WR(0x00000001);
	HW_DRAM_CTL10_WR(0x07000200);
	HW_DRAM_CTL11_WR(0x00070202);
	HW_DRAM_CTL12_WR(0x02020000);
	HW_DRAM_CTL13_WR(0x04040a01);
	HW_DRAM_CTL14_WR(0x00000200|ce);
	HW_DRAM_CTL15_WR(0x02040000);
	HW_DRAM_CTL16_WR(0x02000000);
	HW_DRAM_CTL17_WR(0x25001506);
	HW_DRAM_CTL18_WR(0x1f1f0000);
	HW_DRAM_CTL19_WR(0x027f1a1a);
	HW_DRAM_CTL20_WR(0x02051c22);
	HW_DRAM_CTL21_WR(0x00000007);
	HW_DRAM_CTL22_WR(0x00080008);
	HW_DRAM_CTL23_WR(0x00200020);
	HW_DRAM_CTL24_WR(0x00200020);
	HW_DRAM_CTL25_WR(0x00200020);
	HW_DRAM_CTL26_WR(0x000002e6);
	HW_DRAM_CTL29_WR(0x00000020);
	HW_DRAM_CTL30_WR(0x00000020);
	HW_DRAM_CTL31_WR(0x00c80000);
	HW_DRAM_CTL32_WR(0x00081a3b);
	HW_DRAM_CTL33_WR(0x000000c8);
	HW_DRAM_CTL34_WR(0x00004b0d);
	HW_DRAM_CTL36_WR(0x00000101);
	HW_DRAM_CTL37_WR(0x00040001);
	HW_DRAM_CTL38_WR(0x00000000);
	HW_DRAM_CTL39_WR(0x00000000);
	HW_DRAM_CTL40_WR(0x00010000);
	HW_DRAM_CTL08_WR(0x01000000);
}
void poweron_pll()
{
	HW_CLKCTRL_PLLCTRL0_SET(BM_CLKCTRL_PLLCTRL0_POWER);
}
void turnon_mem_rail(int mv)
{
	unsigned int value;
	HW_POWER_CTRL_CLR(BM_POWER_CTRL_CLKGATE);

	value = BM_POWER_VDDMEMCTRL_ENABLE_ILIMIT|
		BM_POWER_VDDMEMCTRL_ENABLE_LINREG|
		BM_POWER_VDDMEMCTRL_PULLDOWN_ACTIVE|
		(mv-1700)/50;

	HW_POWER_VDDMEMCTRL_WR(value);
	delay(20000);
	value &= ~(BM_POWER_VDDMEMCTRL_ENABLE_ILIMIT|
		 BM_POWER_VDDMEMCTRL_PULLDOWN_ACTIVE);
	HW_POWER_VDDMEMCTRL_WR(value);
}
void set_emi_frac(unsigned int div)
{
	HW_CLKCTRL_FRAC_SET(BM_CLKCTRL_FRAC_EMIFRAC);
	div = (~div);
	HW_CLKCTRL_FRAC_CLR(BF_CLKCTRL_FRAC_EMIFRAC(div));
}
void init_clock()
{
	HW_CLKCTRL_FRAC_SET(BM_CLKCTRL_FRAC_CLKGATEEMI);
#ifdef EMI_96M
	set_emi_frac(30);
#else //EMI_133M
	set_emi_frac(33);
#endif
	HW_CLKCTRL_FRAC_CLR(BM_CLKCTRL_FRAC_CLKGATEEMI);
	delay(11000);

#ifdef EMI_96M
	HW_CLKCTRL_EMI_WR(BF_CLKCTRL_EMI_DIV_XTAL(1)|
			  BF_CLKCTRL_EMI_DIV_EMI(3)
			 );
#else
	HW_CLKCTRL_EMI_WR(BF_CLKCTRL_EMI_DIV_XTAL(1)|
			  BF_CLKCTRL_EMI_DIV_EMI(2)
			 );
#endif

	/*choose ref_emi*/
	HW_CLKCTRL_CLKSEQ_CLR(BM_CLKCTRL_CLKSEQ_BYPASS_EMI);

	/*Reset EMI*/
	HW_EMI_CTRL_CLR(BM_EMI_CTRL_SFTRST);
	HW_EMI_CTRL_CLR(BM_EMI_CTRL_CLKGATE);
	printf("EMI_CTRL 0x%x\r\n" , HW_EMI_CTRL_RD());
	printf("FRAC 0x%x\r\n" , HW_CLKCTRL_FRAC_RD());

}

void disable_emi_padkeepers(void)
{
    HW_PINCTRL_CTRL_CLR(BM_PINCTRL_CTRL_SFTRST | BM_PINCTRL_CTRL_CLKGATE);

    HW_PINCTRL_PULL3_SET(
    BM_PINCTRL_PULL3_BANK3_PIN17 |
    BM_PINCTRL_PULL3_BANK3_PIN16 |
    BM_PINCTRL_PULL3_BANK3_PIN15 |
    BM_PINCTRL_PULL3_BANK3_PIN14 |
    BM_PINCTRL_PULL3_BANK3_PIN13 |
    BM_PINCTRL_PULL3_BANK3_PIN12 |
    BM_PINCTRL_PULL3_BANK3_PIN11 |
    BM_PINCTRL_PULL3_BANK3_PIN10 |
    BM_PINCTRL_PULL3_BANK3_PIN09 |
    BM_PINCTRL_PULL3_BANK3_PIN08 |
    BM_PINCTRL_PULL3_BANK3_PIN07 |
    BM_PINCTRL_PULL3_BANK3_PIN06 |
    BM_PINCTRL_PULL3_BANK3_PIN05 |
    BM_PINCTRL_PULL3_BANK3_PIN04 |
    BM_PINCTRL_PULL3_BANK3_PIN03 |
    BM_PINCTRL_PULL3_BANK3_PIN02 |
    BM_PINCTRL_PULL3_BANK3_PIN01 |
    BM_PINCTRL_PULL3_BANK3_PIN00);

}

#define PIN_VOL(pin , v) ((v) ? (pin) : 0)
void init_emi_pin(int pin_voltage,
		  int pin_drive
		  )
{

	HW_PINCTRL_CTRL_CLR(BM_PINCTRL_CTRL_SFTRST | BM_PINCTRL_CTRL_CLKGATE);
	/* EMI_A00-06 */
	/* Configure Bank-2 Pins 9-15 voltage and drive strength*/
	HW_PINCTRL_DRIVE9_CLR(
		BM_PINCTRL_DRIVE9_BANK2_PIN09_V |
		BM_PINCTRL_DRIVE9_BANK2_PIN09_MA |
		BM_PINCTRL_DRIVE9_BANK2_PIN10_V |
		BM_PINCTRL_DRIVE9_BANK2_PIN10_MA |
		BM_PINCTRL_DRIVE9_BANK2_PIN11_V |
		BM_PINCTRL_DRIVE9_BANK2_PIN11_MA |
		BM_PINCTRL_DRIVE9_BANK2_PIN12_V |
		BM_PINCTRL_DRIVE9_BANK2_PIN12_MA |
		BM_PINCTRL_DRIVE9_BANK2_PIN13_V |
		BM_PINCTRL_DRIVE9_BANK2_PIN13_MA |
		BM_PINCTRL_DRIVE9_BANK2_PIN14_V |
		BM_PINCTRL_DRIVE9_BANK2_PIN14_MA |
		BM_PINCTRL_DRIVE9_BANK2_PIN15_V |
		BM_PINCTRL_DRIVE9_BANK2_PIN15_MA);

	HW_PINCTRL_DRIVE9_SET(
		PIN_VOL(BM_PINCTRL_DRIVE9_BANK2_PIN09_V , pin_voltage) |
		BF_PINCTRL_DRIVE9_BANK2_PIN09_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE9_BANK2_PIN10_V , pin_voltage) |
		BF_PINCTRL_DRIVE9_BANK2_PIN10_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE9_BANK2_PIN11_V , pin_voltage) |
		BF_PINCTRL_DRIVE9_BANK2_PIN11_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE9_BANK2_PIN12_V , pin_voltage) |
		BF_PINCTRL_DRIVE9_BANK2_PIN12_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE9_BANK2_PIN13_V , pin_voltage) |
		BF_PINCTRL_DRIVE9_BANK2_PIN13_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE9_BANK2_PIN14_V , pin_voltage) |
		BF_PINCTRL_DRIVE9_BANK2_PIN14_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE9_BANK2_PIN15_V , pin_voltage) |
		BF_PINCTRL_DRIVE9_BANK2_PIN15_MA(pin_drive));

	/* EMI_A07-12, EMI_BA0-1 */
	/* Configure Bank-2 Pins 16-23 voltage and drive strength */
	HW_PINCTRL_DRIVE10_CLR(
		BM_PINCTRL_DRIVE10_BANK2_PIN16_V |
		BM_PINCTRL_DRIVE10_BANK2_PIN16_MA |
		BM_PINCTRL_DRIVE10_BANK2_PIN17_V |
		BM_PINCTRL_DRIVE10_BANK2_PIN17_MA |
		BM_PINCTRL_DRIVE10_BANK2_PIN18_V |
		BM_PINCTRL_DRIVE10_BANK2_PIN18_MA |
		BM_PINCTRL_DRIVE10_BANK2_PIN19_V |
		BM_PINCTRL_DRIVE10_BANK2_PIN19_MA |
		BM_PINCTRL_DRIVE10_BANK2_PIN20_V |
		BM_PINCTRL_DRIVE10_BANK2_PIN20_MA |
		BM_PINCTRL_DRIVE10_BANK2_PIN21_V |
		BM_PINCTRL_DRIVE10_BANK2_PIN21_MA |
		BM_PINCTRL_DRIVE10_BANK2_PIN22_V |
		BM_PINCTRL_DRIVE10_BANK2_PIN22_MA |
		BM_PINCTRL_DRIVE10_BANK2_PIN23_V |
		BM_PINCTRL_DRIVE10_BANK2_PIN23_MA);

	HW_PINCTRL_DRIVE10_SET(
		PIN_VOL(BM_PINCTRL_DRIVE10_BANK2_PIN16_V , pin_voltage) |
		BF_PINCTRL_DRIVE10_BANK2_PIN16_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE10_BANK2_PIN17_V , pin_voltage) |
		BF_PINCTRL_DRIVE10_BANK2_PIN17_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE10_BANK2_PIN18_V , pin_voltage) |
		BF_PINCTRL_DRIVE10_BANK2_PIN18_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE10_BANK2_PIN19_V , pin_voltage) |
		BF_PINCTRL_DRIVE10_BANK2_PIN19_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE10_BANK2_PIN20_V , pin_voltage) |
		BF_PINCTRL_DRIVE10_BANK2_PIN20_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE10_BANK2_PIN21_V , pin_voltage) |
		BF_PINCTRL_DRIVE10_BANK2_PIN21_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE10_BANK2_PIN22_V , pin_voltage) |
		BF_PINCTRL_DRIVE10_BANK2_PIN22_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE10_BANK2_PIN23_V , pin_voltage) |
		BF_PINCTRL_DRIVE10_BANK2_PIN23_MA(pin_drive));

	/* EMI_CAS,RAS,CE0-2,WEN,CKE */
	/* Configure Bank-2 Pins 24-31 voltage and drive strength */
	HW_PINCTRL_DRIVE11_CLR(
		BM_PINCTRL_DRIVE11_BANK2_PIN24_V |
		BM_PINCTRL_DRIVE11_BANK2_PIN24_MA |
		BM_PINCTRL_DRIVE11_BANK2_PIN25_V |
		BM_PINCTRL_DRIVE11_BANK2_PIN25_MA |
		BM_PINCTRL_DRIVE11_BANK2_PIN26_V |
		BM_PINCTRL_DRIVE11_BANK2_PIN26_MA |
		BM_PINCTRL_DRIVE11_BANK2_PIN29_V |
		BM_PINCTRL_DRIVE11_BANK2_PIN29_MA |
		BM_PINCTRL_DRIVE11_BANK2_PIN30_V |
		BM_PINCTRL_DRIVE11_BANK2_PIN30_MA |
		BM_PINCTRL_DRIVE11_BANK2_PIN31_V |
		BM_PINCTRL_DRIVE11_BANK2_PIN31_MA);

	HW_PINCTRL_DRIVE11_SET(
		PIN_VOL(BM_PINCTRL_DRIVE11_BANK2_PIN24_V , pin_voltage) |
		BF_PINCTRL_DRIVE11_BANK2_PIN24_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE11_BANK2_PIN25_V , pin_voltage) |
		BF_PINCTRL_DRIVE11_BANK2_PIN25_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE11_BANK2_PIN26_V , pin_voltage) |
		BF_PINCTRL_DRIVE11_BANK2_PIN26_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE11_BANK2_PIN29_V , pin_voltage) |
		BF_PINCTRL_DRIVE11_BANK2_PIN29_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE11_BANK2_PIN30_V , pin_voltage) |
		BF_PINCTRL_DRIVE11_BANK2_PIN30_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE11_BANK2_PIN31_V , pin_voltage) |
		BF_PINCTRL_DRIVE11_BANK2_PIN31_MA(pin_drive));

	/* Configure Bank-2 Pins 9-15 as EMI pins */
	HW_PINCTRL_MUXSEL4_CLR(
		BM_PINCTRL_MUXSEL4_BANK2_PIN09 |
		BM_PINCTRL_MUXSEL4_BANK2_PIN10 |
		BM_PINCTRL_MUXSEL4_BANK2_PIN11 |
		BM_PINCTRL_MUXSEL4_BANK2_PIN12 |
		BM_PINCTRL_MUXSEL4_BANK2_PIN13 |
		BM_PINCTRL_MUXSEL4_BANK2_PIN14 |
		BM_PINCTRL_MUXSEL4_BANK2_PIN15);

	/* Configure Bank-2 Pins 16-31 as EMI pins */
	HW_PINCTRL_MUXSEL5_CLR(
		BM_PINCTRL_MUXSEL5_BANK2_PIN16 |
		BM_PINCTRL_MUXSEL5_BANK2_PIN17 |
		BM_PINCTRL_MUXSEL5_BANK2_PIN18 |
		BM_PINCTRL_MUXSEL5_BANK2_PIN19 |
		BM_PINCTRL_MUXSEL5_BANK2_PIN20 |
		BM_PINCTRL_MUXSEL5_BANK2_PIN21 |
		BM_PINCTRL_MUXSEL5_BANK2_PIN22 |
		BM_PINCTRL_MUXSEL5_BANK2_PIN23 |
		BM_PINCTRL_MUXSEL5_BANK2_PIN24 |
		BM_PINCTRL_MUXSEL5_BANK2_PIN25 |
		BM_PINCTRL_MUXSEL5_BANK2_PIN26 |
		BM_PINCTRL_MUXSEL5_BANK2_PIN29 |
		BM_PINCTRL_MUXSEL5_BANK2_PIN30 |
		BM_PINCTRL_MUXSEL5_BANK2_PIN31);

	HW_PINCTRL_DRIVE12_CLR(
		BM_PINCTRL_DRIVE12_BANK3_PIN00_V |
		BM_PINCTRL_DRIVE12_BANK3_PIN00_MA |
		BM_PINCTRL_DRIVE12_BANK3_PIN01_V |
		BM_PINCTRL_DRIVE12_BANK3_PIN01_MA |
		BM_PINCTRL_DRIVE12_BANK3_PIN02_V |
		BM_PINCTRL_DRIVE12_BANK3_PIN02_MA |
		BM_PINCTRL_DRIVE12_BANK3_PIN03_V |
		BM_PINCTRL_DRIVE12_BANK3_PIN03_MA |
		BM_PINCTRL_DRIVE12_BANK3_PIN04_V |
		BM_PINCTRL_DRIVE12_BANK3_PIN04_MA |
		BM_PINCTRL_DRIVE12_BANK3_PIN05_V |
		BM_PINCTRL_DRIVE12_BANK3_PIN05_MA |
		BM_PINCTRL_DRIVE12_BANK3_PIN06_V |
		BM_PINCTRL_DRIVE12_BANK3_PIN06_MA |
		BM_PINCTRL_DRIVE12_BANK3_PIN07_V |
		BM_PINCTRL_DRIVE12_BANK3_PIN07_MA);

	HW_PINCTRL_DRIVE12_SET(
		PIN_VOL(BM_PINCTRL_DRIVE12_BANK3_PIN00_V , pin_voltage) |
		BF_PINCTRL_DRIVE12_BANK3_PIN00_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE12_BANK3_PIN01_V , pin_voltage) |
		BF_PINCTRL_DRIVE12_BANK3_PIN01_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE12_BANK3_PIN02_V , pin_voltage) |
		BF_PINCTRL_DRIVE12_BANK3_PIN02_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE12_BANK3_PIN03_V , pin_voltage) |
		BF_PINCTRL_DRIVE12_BANK3_PIN03_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE12_BANK3_PIN04_V , pin_voltage) |
		BF_PINCTRL_DRIVE12_BANK3_PIN04_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE12_BANK3_PIN05_V , pin_voltage) |
		BF_PINCTRL_DRIVE12_BANK3_PIN05_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE12_BANK3_PIN06_V , pin_voltage) |
		BF_PINCTRL_DRIVE12_BANK3_PIN06_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE12_BANK3_PIN07_V , pin_voltage) |
		BF_PINCTRL_DRIVE12_BANK3_PIN07_MA(pin_drive));

	/* EMI_D08-15
	  Configure Bank-3 Pins 08-15 voltage and drive strength
	*/
	HW_PINCTRL_DRIVE13_CLR(
		BM_PINCTRL_DRIVE13_BANK3_PIN08_V |
		BM_PINCTRL_DRIVE13_BANK3_PIN08_MA |
		BM_PINCTRL_DRIVE13_BANK3_PIN09_V |
		BM_PINCTRL_DRIVE13_BANK3_PIN09_MA |
		BM_PINCTRL_DRIVE13_BANK3_PIN10_V |
		BM_PINCTRL_DRIVE13_BANK3_PIN10_MA |
		BM_PINCTRL_DRIVE13_BANK3_PIN11_V |
		BM_PINCTRL_DRIVE13_BANK3_PIN11_MA |
		BM_PINCTRL_DRIVE13_BANK3_PIN12_V |
		BM_PINCTRL_DRIVE13_BANK3_PIN12_MA |
		BM_PINCTRL_DRIVE13_BANK3_PIN13_V |
		BM_PINCTRL_DRIVE13_BANK3_PIN13_MA |
		BM_PINCTRL_DRIVE13_BANK3_PIN14_V |
		BM_PINCTRL_DRIVE13_BANK3_PIN14_MA |
		BM_PINCTRL_DRIVE13_BANK3_PIN15_V |
		BM_PINCTRL_DRIVE13_BANK3_PIN15_MA);

	HW_PINCTRL_DRIVE13_SET(
		PIN_VOL(BM_PINCTRL_DRIVE13_BANK3_PIN08_V , pin_voltage) |
		BF_PINCTRL_DRIVE13_BANK3_PIN08_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE13_BANK3_PIN09_V , pin_voltage) |
		BF_PINCTRL_DRIVE13_BANK3_PIN09_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE13_BANK3_PIN10_V , pin_voltage) |
		BF_PINCTRL_DRIVE13_BANK3_PIN10_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE13_BANK3_PIN11_V , pin_voltage) |
		BF_PINCTRL_DRIVE13_BANK3_PIN11_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE13_BANK3_PIN12_V , pin_voltage) |
		BF_PINCTRL_DRIVE13_BANK3_PIN12_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE13_BANK3_PIN13_V , pin_voltage) |
		BF_PINCTRL_DRIVE13_BANK3_PIN13_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE13_BANK3_PIN14_V , pin_voltage) |
		BF_PINCTRL_DRIVE13_BANK3_PIN14_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE13_BANK3_PIN15_V , pin_voltage) |
		BF_PINCTRL_DRIVE13_BANK3_PIN15_MA(pin_drive));

	/* EMI_DQS0-1,DQM0-1,CLK,CLKN
	   Configure Bank-3 Pins 08-15 voltage and drive strength
	 */
	HW_PINCTRL_DRIVE14_CLR(
		BM_PINCTRL_DRIVE14_BANK3_PIN16_V  |
		BM_PINCTRL_DRIVE14_BANK3_PIN16_MA |
		BM_PINCTRL_DRIVE14_BANK3_PIN17_V  |
		BM_PINCTRL_DRIVE14_BANK3_PIN17_MA |
		BM_PINCTRL_DRIVE14_BANK3_PIN18_V  |
		BM_PINCTRL_DRIVE14_BANK3_PIN18_MA |
		BM_PINCTRL_DRIVE14_BANK3_PIN19_V  |
		BM_PINCTRL_DRIVE14_BANK3_PIN19_MA |
		BM_PINCTRL_DRIVE14_BANK3_PIN20_V  |
		BM_PINCTRL_DRIVE14_BANK3_PIN20_MA |
		BM_PINCTRL_DRIVE14_BANK3_PIN21_V  |
		BM_PINCTRL_DRIVE14_BANK3_PIN21_MA);

	HW_PINCTRL_DRIVE14_SET(
		PIN_VOL(BM_PINCTRL_DRIVE14_BANK3_PIN16_V , pin_voltage) |
		BF_PINCTRL_DRIVE14_BANK3_PIN16_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE14_BANK3_PIN17_V , pin_voltage) |
		BF_PINCTRL_DRIVE14_BANK3_PIN17_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE14_BANK3_PIN18_V , pin_voltage) |
		BF_PINCTRL_DRIVE14_BANK3_PIN18_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE14_BANK3_PIN19_V , pin_voltage) |
		BF_PINCTRL_DRIVE14_BANK3_PIN19_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE14_BANK3_PIN20_V , pin_voltage) |
		BF_PINCTRL_DRIVE14_BANK3_PIN20_MA(pin_drive) |
		PIN_VOL(BM_PINCTRL_DRIVE14_BANK3_PIN21_V , pin_voltage) |
		BF_PINCTRL_DRIVE14_BANK3_PIN21_MA(pin_drive));

	/* Configure Bank-3 Pins 0-15 as EMI pins*/
	HW_PINCTRL_MUXSEL6_CLR(
		BM_PINCTRL_MUXSEL6_BANK3_PIN00 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN01 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN02 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN03 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN04 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN05 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN06 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN07 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN08 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN09 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN10 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN11 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN12 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN13 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN14 |
		BM_PINCTRL_MUXSEL6_BANK3_PIN15);

	/* Configure Bank-3 Pins 16-21 as EMI pins */
	HW_PINCTRL_MUXSEL7_CLR(
		BM_PINCTRL_MUXSEL7_BANK3_PIN16 |
		BM_PINCTRL_MUXSEL7_BANK3_PIN17 |
		BM_PINCTRL_MUXSEL7_BANK3_PIN18 |
		BM_PINCTRL_MUXSEL7_BANK3_PIN19 |
		BM_PINCTRL_MUXSEL7_BANK3_PIN20 |
		BM_PINCTRL_MUXSEL7_BANK3_PIN21);
}
void exit_selfrefresh()
{
	unsigned int start;
	unsigned int value;
	value = HW_DRAM_CTL16_RD();
	value &= ~(1<<17);
	HW_DRAM_CTL16_WR(value);

	start = HW_DIGCTL_MICROSECONDS_RD();

	while ((HW_EMI_STAT_RD()&BM_EMI_STAT_DRAM_HALTED)) {

		if (HW_DIGCTL_MICROSECONDS_RD() > (start + 1000000)) {

			printf("exit self refresh timeout\r\n");
			return;
		}
	}
}

void set_port_priority()
{
	unsigned int value;

	HW_EMI_CTRL_CLR(BM_EMI_CTRL_PORT_PRIORITY_ORDER);
	HW_EMI_CTRL_SET(BF_EMI_CTRL_PORT_PRIORITY_ORDER(
				BV_EMI_CTRL_PORT_PRIORITY_ORDER__PORT1230)
		       );

	HW_EMI_CTRL_CLR(BM_EMI_CTRL_PORT_PRIORITY_ORDER);
	HW_EMI_CTRL_SET(BF_EMI_CTRL_PORT_PRIORITY_ORDER(0x2));

}
void entry_auto_clock_gate()
{
	unsigned int value;
	value =  HW_DRAM_CTL16_RD();
	value |= 1<<19;
	HW_DRAM_CTL16_WR(value);

	value =  HW_DRAM_CTL16_RD();
	value |= 1<<11;
	HW_DRAM_CTL16_WR(value);
}
void change_cpu_freq()
{
	int value = 0;
	printf("power 0x%x\r\n" , HW_POWER_VDDDCTRL_RD());


	value = HW_POWER_VDDDCTRL_RD();
	value &= ~BM_POWER_VDDDCTRL_TRG;
	value |= BF_POWER_VDDDCTRL_TRG(30); /*change to 1.550v*/
	HW_POWER_VDDDCTRL_WR(value);

	delay(10000);

	printf("Frac 0x%x\r\n", HW_CLKCTRL_FRAC_RD());

	value = HW_CLKCTRL_FRAC_RD();
	value &= ~BM_CLKCTRL_FRAC_CPUFRAC;
	value |= BF_CLKCTRL_FRAC_CPUFRAC(19);
	value &= ~BM_CLKCTRL_FRAC_CLKGATECPU;

	HW_CLKCTRL_FRAC_WR(value); /*Change cpu to 454Mhz*/

	HW_CLKCTRL_CLKSEQ_SET(BM_CLKCTRL_CLKSEQ_BYPASS_CPU);

	HW_CLKCTRL_HBUS_SET(BM_CLKCTRL_HBUS_DIV);
	HW_CLKCTRL_HBUS_CLR(((~3)&BM_CLKCTRL_HBUS_DIV));

	delay(10000);
	printf("start change cpu freq\r\n");

	if ((HW_POWER_5VCTRL.B.PWD_CHARGE_4P2 == 1) ||
		(HW_POWER_5VCTRL.B.CHARGE_4P2_ILIMIT != 0x20))
		HW_CLKCTRL_CLKSEQ_CLR(BM_CLKCTRL_CLKSEQ_BYPASS_CPU);

	printf("hbus 0x%x\r\n" , HW_CLKCTRL_HBUS_RD());
	printf("cpu 0x%x\r\n" , HW_CLKCTRL_CPU_RD());

}
#define  HW_PINCTRL_MUXSEL3_T (*(volatile reg32_t *) HW_PINCTRL_MUXSEL3_ADDR)
#define  HW_PINCTRL_DRIVE7_T  (*(volatile reg32_t *) HW_PINCTRL_DRIVE7_ADDR )
#define  HW_PINCTRL_DOUT1_T   (*(volatile reg32_t *) HW_PINCTRL_DOUT1_ADDR )
#define  HW_PINCTRL_DOE1_T   (*(volatile unsigned *) HW_PINCTRL_DOE1_ADDR )
void Buzzer_Delay(unsigned int microSec)
{
	unsigned int currentTime = HW_DIGCTL_MICROSECONDS_RD();
	while ((HW_DIGCTL_MICROSECONDS_RD() - currentTime) <  microSec);
}
//pwm4
void buzzer(void)
{  int i;
   //HW_PINCTRL_MUXSEL0_T &= ~(3 << 28);
    HW_PINCTRL_MUXSEL3_T |= (3 << 28);

   // HW_PINCTRL_DRIVE1_T &= ~(3 << 24);
    HW_PINCTRL_DRIVE7_T |= (1 << 24);

    HW_PINCTRL_DOUT1_T |= (1 << 30);
    HW_PINCTRL_DOE1_T |= (1 << 30);
    
    HW_PINCTRL_DOUT1_T |= (1 << 30);
    Buzzer_Delay(300*1000);
    HW_PINCTRL_DOUT1_T &=(!(1 << 30));
    
 
}

#define  HW_PINCTRL_MUXSEL4_T (*(volatile reg32_t *) HW_PINCTRL_MUXSEL4_ADDR)
#define  HW_PINCTRL_DRIVE8_T  (*(volatile reg32_t *) HW_PINCTRL_DRIVE8_ADDR )
#define  HW_PINCTRL_DOUT2_T   (*(volatile reg32_t *) HW_PINCTRL_DOUT2_ADDR )
#define  HW_PINCTRL_DOE2_T   (*(volatile unsigned *) HW_PINCTRL_DOE2_ADDR )

#define  HW_PINCTRL_DRIVE6_T  (*(volatile reg32_t *) HW_PINCTRL_DRIVE6_ADDR )

#define LCD_SDO_1	HW_PINCTRL_DOUT2_T	|= 1<<0
#define LCD_SDI_1	HW_PINCTRL_DOUT2_T	|= 1<<2
#define LCD_SCK_1	HW_PINCTRL_DOUT2_T	|= 1<<6
#define LCD_CS_1	HW_PINCTRL_DOUT2_T	|= 1<<5

#define LCD_RESET_1	HW_PINCTRL_DOUT1_T	|= 1<<18


#define LCD_SDO_0	HW_PINCTRL_DOUT2_T &=(!(1 << 0))
#define LCD_SDI_0	HW_PINCTRL_DOUT2_T &=(!(1 << 2))
#define LCD_SCK_0	HW_PINCTRL_DOUT2_T &=(!(1 << 6))
#define LCD_CS_0	HW_PINCTRL_DOUT2_T &=(!(1 << 5))

#define LCD_RESET_0	HW_PINCTRL_DOUT1_T &=(!(1 << 18))

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
void initLCD_IO(void)
{
    //spi_di	SSP1_CMD:SPI1_MOSI	->	BANK2_PIN00
    //spi_do	SSP1_DATA0:SPI1_MIS	->	BANK2_PIN02
    //spi_clk	SSP1_SCK:SPI1_SCK	->	BANK2_PIN06
    //spi_cs	SSP1_DATA3:SPI1_SS	->	BANK2_PIN05

    //reset 	LCD_RESET       	->	BANK1_PIN18



    HW_PINCTRL_MUXSEL4_T |= 3<<0;		//BANK2_PIN00
    HW_PINCTRL_DRIVE8_T |= 1<<0;		//8mA
    HW_PINCTRL_DOUT2_T |= 1<<0;
    HW_PINCTRL_DOE2_T |= 1<<0;


    HW_PINCTRL_MUXSEL4_T |= 3<<4;		//BANK2_PIN02
    HW_PINCTRL_DRIVE8_T |= 1<<8;		//8mA
    HW_PINCTRL_DOUT2_T |= 1<<2;
    HW_PINCTRL_DOE2_T |= 1<<2;

    HW_PINCTRL_MUXSEL4_T |= 3<<12;		//BANK2_PIN06
    HW_PINCTRL_DRIVE8_T |= 1<<24;		//8mA
    HW_PINCTRL_DOUT2_T |= 1<<6;
    HW_PINCTRL_DOE2_T |= 1<<6;

    HW_PINCTRL_MUXSEL4_T |= 3<<10;		//BANK2_PIN05
    HW_PINCTRL_DRIVE8_T |= 1<<20;		//8mA
    HW_PINCTRL_DOUT2_T |= 1<<5;
    HW_PINCTRL_DOE2_T |= 1<<5;


    HW_PINCTRL_MUXSEL3_T |= 3<<4;		//BANK1_PIN18
    HW_PINCTRL_DRIVE6_T |= 1<<8;		//8mA
    HW_PINCTRL_DOUT1_T |= 1<<18;
    HW_PINCTRL_DOE1_T |= 1<<18;

/*
    while(1)
    {


        printf("test 1111111111111111\r\n");
    HW_PINCTRL_DOUT2_T |= 1<<0;
    HW_PINCTRL_DOUT2_T |= 1<<2;
    HW_PINCTRL_DOUT2_T |= 1<<6;
    HW_PINCTRL_DOUT2_T |= 1<<5;

    HW_PINCTRL_DOUT1_T |= (1 << 30);//buzz


delay(1*1000*1000);
        printf("test 0000000000000000\r\n");
    HW_PINCTRL_DOUT2_T &= (~(1 << 0));
    HW_PINCTRL_DOUT2_T &= (~(1 << 2));
    HW_PINCTRL_DOUT2_T &= (~(1 << 6));
    HW_PINCTRL_DOUT2_T &= (~(1 << 5));


    HW_PINCTRL_DOUT1_T &=(~(1 << 30));//buzz

    delay(1*1000*1000);

    }
*/

}

/*
void delay1(int v)
{
    delay(v);
 //   while(v--)delay(3);
}
*/
void TFT_SPI_Write_Byte(u8 da)
{
    u8 i;
    for(i=0;i<8;i++)
    {
//        delay1(1);
        LCD_SCK_0;
//        delay1(1);
        if(da&0x80)
            LCD_SDO_1;
        else
            LCD_SDO_0;
        da <<= 1;
//        delay1(1);
        LCD_SCK_1;
    }
}
void LCD_RegisterIndex(u8 CMD)
{
  //      delay1(1);
        LCD_CS_0;       //  delay1(1);
        LCD_SCK_0;      //  delay1(1);
        LCD_SDO_0;      //  delay1(1);
        LCD_SCK_1;      //  delay1(1);
        TFT_SPI_Write_Byte(CMD);      //  delay1(1);
        LCD_CS_1;

}

void LCD_RegisterValue(u8 DATA)
{
//    delay1(1);
    LCD_CS_0;     //  delay1(1);
    LCD_SCK_0;    //  delay1(1);
    LCD_SDO_1;    //  delay1(1);
    LCD_SCK_1;    //  delay1(1);
    TFT_SPI_Write_Byte(DATA);      //  delay1(1);
    LCD_CS_1;
}
u32 LCD_Read(u8 count)
{
    u8 i;
    u32 ret = 0;
    LCD_CS_0;
    LCD_SCK_0;
    for(i=0;i<8*count;i++)
    {

        LCD_SCK_0;
        ret <<= 1;
//        if(GPIO_ReadInputDataBit(io_sdi.gpio,io_sdi.pin))
            ret |= 1;
        LCD_SCK_1;
    }
    LCD_CS_1;
    return ret;
}

#define LCD_WR_REG(d) LCD_RegisterIndex(d)
#define LCD_WR_DATA(d) LCD_RegisterValue(d)
void initLCD_Para(void);
void initLCD_Para2(void);
//设置光标位置
//Xpos:横坐标
//Ypos:纵坐标
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
    LCD_WR_REG(0x2A);
    LCD_WR_DATA(Xpos>>8);
  LCD_WR_DATA(0xFF&Xpos);				 //设定X坐标

  LCD_WR_REG(0x2B);
    LCD_WR_DATA(Ypos>>8);
  LCD_WR_DATA(0xFF&Ypos);				 //设定Y坐标

}



    //画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE         	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色

u16 colorTab[]={WHITE,BLUE,BRED,GRED,GBLUE,RED,MAGENTA,GREEN,CYAN,YELLOW,BROWN,BRRED,GRAY};
void testLCD(void)
{
    u16 j = 0;
    u32 index=0;
    u16 color;
    u16 colorIndex = 1;
    printf("tttttttttttt --- 1  \r\n");
    printf("tttttttttttt --- 2  \r\n");
//    while(1)
    {
        printf("tttttttttttt --- 3  \r\n");
        LCD_SetCursor(0x0000,0x0000);//设置光标位置
        LCD_WR_REG(0X2C);

        for(j=0;j<240;j++)
        {
            color = colorTab[j/30];
            for(index=0;index<320;index++)
            {
                LCD_WR_DATA(color>>8);
                LCD_WR_DATA(color);
            }
        }

        if(++colorIndex>sizeof(colorTab)/sizeof(int))
            colorIndex = 0;

        printf("-------------------index = %d \r\n",index);
    //    delayMs(2000);
    }


}
void testLCD2()
{
    u32 index=0;
    u16 color;
    u16 colorIndex = 0;
    while(1)
    {
//        LCD_WR_REG(0x28);

        LCD_SetCursor(0x0000,0x0000);//设置光标位置
        LCD_WR_REG(0X2C);
        color = colorTab[colorIndex];
        for(index=0;index<320*240;index++)
        {
            LCD_WR_DATA(color>>8);
            LCD_WR_DATA(color);
        }

            LCD_WR_REG(0x29);
        if(++colorIndex>sizeof(colorTab)/sizeof(int))
            colorIndex = 0;
//        printf("-------------------colorIndex = %d \r\n",colorIndex);
//        printf("-------------------color ====== %x \r\n",color);
        delayMs(2000);
    }
}

int _start(int arg)
{
	unsigned int value;
	volatile int *pTest = 0x40000000;
	unsigned int CE = 0x03;
	int i;
	printf(__DATE__ __TIME__);
        buzzer();
	printf("\r\n");
    printf("Fuse 0x%x\r\n",HW_OCOTP_CUSTCAP_RD());

    initLCD_IO();
    initLCD_Para();
//    initLCD_Para2();
//    testLCD();
//    testLCD2();
	if ((HW_OCOTP_CUSTCAP_RD() & 0x30000000) > 0) {
		/*EVK board*/
		printf("EVK board\r\n");
		CE = 0x3;
		/*increas VDDIO 1.8v*/
		value = HW_POWER_VDDACTRL_RD() ;
		value &= ~BM_POWER_VDDACTRL_TRG;
		value |= 12;
		HW_POWER_VDDACTRL_WR(value);
		delay(20000);

		/*increass VDDIO 3.440v */
		value = HW_POWER_VDDIOCTRL_RD();
		value &= ~BM_POWER_VDDIOCTRL_TRG;
		value |= 20;
		HW_POWER_VDDIOCTRL_WR(value);
		delay(20000);
	}

	poweron_pll();
	delay(11000);
#define     MEM_MDDR
#ifdef MEM_MDDR
	turnon_mem_rail(1800);
#else
	turnon_mem_rail(2500); 
#endif

	delay(11000);

	init_emi_pin(
		0,
		PIN_DRIVE_12mA
		);

	disable_emi_padkeepers();

	init_clock();

	delay(10000);


#ifdef MEM_MDDR
#ifdef EMI_96M
	init_mddr_mt46h32m16lf_96Mhz(CE);
	printf("init_mddr_mt46h32m16lf_96Mhz\r\n");
#else
	init_mddr_mt46h32m16lf_133Mhz(CE);
printf("init_mddr_mt46h32m16lf_133Mhz\r\n");
#endif

#else

	init_ddr_mt46v32m16_133Mhz(CE);
	printf("init_ddr_mt46v32m16_133Mhz\r\n");
#endif


	value = HW_DRAM_CTL08_RD();
	value |= BM_DRAM_CTL08_START;
	HW_DRAM_CTL08_WR(value);

	exit_selfrefresh();

	set_port_priority();

	entry_auto_clock_gate();

	change_cpu_freq();

#ifdef MEM_MDDR 
	//set GPMI_D14 to low  to enable the power setting
	power_enable_gpmi_d14();
	power_enable_gpmi_d15();
#endif

#if 0
	for (i = 0; i <= 40; i++) {
		printf("mem %x - 0x%x\r\n",
			i, *(volatile int*)(0x800E0000 + i * 4));
	}
#endif
#if 0
	/*Test Memory;*/
	printf("start test memory accress");
	for (i = 0; i < 100; i++)
		*pTest++ = i;

	pTest = (volatile int *)0x40000000;

	for (i = 0; i < 100; i++) {
		if (*pTest != (i)) {
			printf("0x%x error value 0x%x\r\n", i, *pTest);
		}
		pTest++;
	}
#endif


	return 0;
}
#define HW_PINCTRL_MUXSEL0_T  (* (volatile unsigned *) 0x80018100) 	
#define HW_PINCTRL_DRIVE1_T		(*(volatile unsigned *) 0x80018210)
#define HW_PINCTRL_DOUT0_T		(*(volatile unsigned *) 0x80018500)
#define HW_PINCTRL_DOE0_T	(*(volatile unsigned *) 0x80018700)

void power_enable_gpmi_d14()//auart2_rx
{
    //gpio set low for GPMI_D14  BANK0_PIN14 
    HW_PINCTRL_MUXSEL0_T &= ~(3 << 28);
    HW_PINCTRL_MUXSEL0_T |= (3 << 28);

    HW_PINCTRL_DRIVE1_T &= ~(3 << 24);
    HW_PINCTRL_DRIVE1_T |= (1 << 25);

    HW_PINCTRL_DOUT0_T |= (1 << 14);
    HW_PINCTRL_DOE0_T |= (1 << 14);
    HW_PINCTRL_DOUT0_T |= (1 << 14);
 
}

void power_enable_gpmi_d15() //auart2_tx
{
    //gpio set low for GPMI_D14  BANK0_PIN14 
    HW_PINCTRL_MUXSEL0_T &= ~(3 << 30);
    HW_PINCTRL_MUXSEL0_T |= (3 << 30);

    HW_PINCTRL_DRIVE1_T &= ~(3 << 28);
    HW_PINCTRL_DRIVE1_T |= (1 << 29);

    HW_PINCTRL_DOUT0_T |= (1 << 15);
    HW_PINCTRL_DOE0_T |= (1 << 15);
    HW_PINCTRL_DOUT0_T |= (1 << 15);
 
}

void delayMs(int ms)
{
    delay(ms*1000);
}

void initLCD_Para(void)
{

    LCD_RESET_1;
    LCD_SCK_1;
    LCD_SDI_1;
    LCD_SDO_1;
    LCD_CS_1;

    delayMs(2);
    LCD_RESET_1;
    delayMs(20);
    LCD_RESET_0;
    delayMs(10);
    LCD_RESET_1;
    delayMs(220);

    printf("tttttttttttt --- 8  \r\n");
    LCD_RegisterIndex(0x11);    // 退出睡眠模式
//        Delay(120);
    delayMs(500);

    printf("tttttttttttt --- 9  \r\n");
    LCD_WR_REG(0xCF);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0xC1);
        LCD_WR_DATA(0X30);
        LCD_WR_REG(0xED);
        LCD_WR_DATA(0x64);
        LCD_WR_DATA(0x03);
        LCD_WR_DATA(0X12);
        LCD_WR_DATA(0X81);
        LCD_WR_REG(0xE8);
        LCD_WR_DATA(0x85);
        LCD_WR_DATA(0x10);
        LCD_WR_DATA(0x7A);
        LCD_WR_REG(0xCB);
        LCD_WR_DATA(0x39);
        LCD_WR_DATA(0x2C);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x34);
        LCD_WR_DATA(0x02);
        LCD_WR_REG(0xF7);
        LCD_WR_DATA(0x20);
        LCD_WR_REG(0xEA);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);
        LCD_WR_REG(0xC0);    //Power control
        LCD_WR_DATA(0x1B);   //VRH[5:0]
        LCD_WR_REG(0xC1);    //Power control
        LCD_WR_DATA(0x01);   //SAP[2:0];BT[3:0]
        LCD_WR_REG(0xC5);    //VCM control
        LCD_WR_DATA(0x30); 	 //3F
        LCD_WR_DATA(0x30); 	 //3C
        LCD_WR_REG(0xC7);    //VCM control2
        LCD_WR_DATA(0XB7);

        LCD_WR_REG(0x36);    // Memory Access Control
        LCD_WR_DATA(0x08);

        LCD_WR_REG(0x3A);
        LCD_WR_DATA(0x55);

        LCD_WR_REG(0xB1);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x1A);

        LCD_WR_REG(0xB6);    // Display Function Control
        LCD_WR_DATA(0x0A);
        LCD_WR_DATA(0xA2);

        LCD_WR_REG(0xF2);    // 3Gamma Function Disable
        LCD_WR_DATA(0x00);
        LCD_WR_REG(0x26);    //Gamma curve selectednto GR
        LCD_WR_DATA(0x01);

        LCD_WR_REG(0xE0);    //Set Gamma
        LCD_WR_DATA(0x0F);
        LCD_WR_DATA(0x2A);
        LCD_WR_DATA(0x28);
        LCD_WR_DATA(0x08);
        LCD_WR_DATA(0x0E);
        LCD_WR_DATA(0x08);
        LCD_WR_DATA(0x54);
        LCD_WR_DATA(0XA9);
        LCD_WR_DATA(0x43);
        LCD_WR_DATA(0x0A);
        LCD_WR_DATA(0x0F);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);

        LCD_WR_REG(0XE1);    //Set Gamma
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x15);
        LCD_WR_DATA(0x17);
        LCD_WR_DATA(0x07);
        LCD_WR_DATA(0x11);
        LCD_WR_DATA(0x06);
        LCD_WR_DATA(0x2B);
        LCD_WR_DATA(0x56);
        LCD_WR_DATA(0x3C);
        LCD_WR_DATA(0x05);
        LCD_WR_DATA(0x10);
        LCD_WR_DATA(0x0F);
        LCD_WR_DATA(0x3F);
        LCD_WR_DATA(0x3F);
        LCD_WR_DATA(0x0F);


        LCD_WR_REG(0xf6);//
        LCD_WR_DATA(0x01);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x06);

        LCD_WR_REG(0xB0);//
        LCD_WR_DATA(0xe0);//

        LCD_WR_REG(0x2A);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0xef);
        LCD_WR_REG(0x2B);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x01);
        LCD_WR_DATA(0x3f);

        LCD_WR_REG(0x11); //Exit Sleep
//        msleep(120);
        delayMs(120);
        printf("tttttttttttt --- b  \r\n");
        LCD_WR_REG(0x29); //display on

}

//#define LCD_RegisterIndex LCD_WR_REG
//#define LCD_RegisterValue LCD_WR_DATA
void initLCD_Para2()
{

    LCD_RESET_1;
    LCD_SCK_1;
    LCD_SDI_1;
    LCD_SDO_1;
    LCD_CS_1;

    delayMs(2);
    LCD_RESET_1;
    delayMs(20);
    LCD_RESET_0;
    delayMs(10);
    LCD_RESET_1;
    delayMs(220);

    printf("tttttttttttt --- 8  \r\n");
    LCD_RegisterIndex(0x11);    // 退出睡眠模式
//        Delay(120);
    delayMs(500);
    LCD_RegisterIndex(0xEF);
    LCD_RegisterValue(0x03);
    LCD_RegisterValue(0x80);
    LCD_RegisterValue(0x02);

    LCD_RegisterIndex(0xCF);
    LCD_RegisterValue(0x00);
    LCD_RegisterValue(0xAA);
    LCD_RegisterValue(0XB0);

    LCD_RegisterIndex(0xED);
    LCD_RegisterValue(0x64);
    LCD_RegisterValue(0x03);
    LCD_RegisterValue(0X12);
    LCD_RegisterValue(0X81);

    LCD_RegisterIndex(0xE8);
    LCD_RegisterValue(0x85);
    LCD_RegisterValue(0x00);
    LCD_RegisterValue(0x78);


    LCD_RegisterIndex(0xCB);
    LCD_RegisterValue(0x39);
    LCD_RegisterValue(0x2C);
    LCD_RegisterValue(0x00);
    LCD_RegisterValue(0x34);
    LCD_RegisterValue(0x02);

    LCD_RegisterIndex(0xF7);
    LCD_RegisterValue(0x20);

    LCD_RegisterIndex(0xEA);
    LCD_RegisterValue(0x00);
    LCD_RegisterValue(0x00);


    //LCD_RegisterIndex(0xb6);
    //LCD_RegisterValue(0x0a);
    //LCD_RegisterValue(0xa2);

    LCD_RegisterIndex(0xC0);       //Power control
    LCD_RegisterValue(0x26);     //VRH[5:0]

    LCD_RegisterIndex(0xC1);       //Power control
    LCD_RegisterValue(0x11);     //SAP[2:0];BT[3:0]

    LCD_RegisterIndex(0xC5);       //VCM control
    LCD_RegisterValue(0x40);
    LCD_RegisterValue(0x3C);

    LCD_RegisterIndex(0xC7);       //VCM control2
    LCD_RegisterValue(0xfe);

    LCD_RegisterIndex(0x36);       // Memory Access Control
    LCD_RegisterValue(0x28);

    LCD_RegisterIndex(0x3A);
    LCD_RegisterValue(0x55);

    LCD_RegisterIndex(0xB1);       //VCM control
    LCD_RegisterValue(0x00);
    LCD_RegisterValue(0x1b);



    LCD_RegisterIndex(0xf6);
    LCD_RegisterValue(0x01);
    LCD_RegisterValue(0x00);
    LCD_RegisterValue(0x06);


    LCD_RegisterIndex(0xB0);
    LCD_RegisterValue(0xe0); ///Add20110430


    LCD_RegisterIndex(0xF2);       // 3Gamma Function Disable
    LCD_RegisterValue(0x00);

    LCD_RegisterIndex(0x26);       //Gamma curve selected
    LCD_RegisterValue(0x01);

    LCD_RegisterIndex(0xE0);       //Set Gamma
    LCD_RegisterValue(0x0F);
    LCD_RegisterValue(0x1d);
    LCD_RegisterValue(0x1a);
    LCD_RegisterValue(0x09);
    LCD_RegisterValue(0x0f);
    LCD_RegisterValue(0x09);
    LCD_RegisterValue(0x46);
    LCD_RegisterValue(0x88);
    LCD_RegisterValue(0x39);
    LCD_RegisterValue(0x05);
    LCD_RegisterValue(0x0f);
    LCD_RegisterValue(0x03);
    LCD_RegisterValue(0x07);
    LCD_RegisterValue(0x05);
    LCD_RegisterValue(0x00);

    LCD_RegisterIndex(0XE1);       //Set Gamma
    LCD_RegisterValue(0x00);
    LCD_RegisterValue(0x22);
    LCD_RegisterValue(0x25);
    LCD_RegisterValue(0x06);
    LCD_RegisterValue(0x10);
    LCD_RegisterValue(0x06);
    LCD_RegisterValue(0x39);
    LCD_RegisterValue(0x22);
    LCD_RegisterValue(0x4a);
    LCD_RegisterValue(0x0a);
    LCD_RegisterValue(0x10);
    LCD_RegisterValue(0x0C);
    LCD_RegisterValue(0x38);
    LCD_RegisterValue(0x3a);
    LCD_RegisterValue(0x0F);


    LCD_WR_REG(0x2A);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x01);
    LCD_WR_DATA(0x3f);
    LCD_WR_REG(0x2B);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0xef);

    delayMs(120);
    LCD_RegisterIndex(0x11);       //Exit Sleep
    delayMs(120);
    LCD_RegisterIndex(0x29);       //Displa
/*
    // Write the display data into GRAM here
    LCD_RegisterIndex(0x2A);
    LCD_RegisterValue(0x00);
    LCD_RegisterValue(0x00);
    LCD_RegisterValue(0x00);
    LCD_RegisterValue(0xEF);

    LCD_RegisterIndex(0x2B);
    LCD_RegisterValue(0x00);
    LCD_RegisterValue(0x00);
    LCD_RegisterValue(0x01);
    LCD_RegisterValue(0x3F);

    LCD_RegisterIndex(0x2C); //GRAM start writing
    */
}

/* kiss gcc's ass to make it happy */
void __aeabi_unwind_cpp_pr0() {}
void __aeabi_unwind_cpp_pr1() {}
