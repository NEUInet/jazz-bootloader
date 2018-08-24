#include <stmp3xxx.h>
#include <init.h>
#include <debug.h>
#include "regsclkctrl.h"
#include "regsuartdbg.h"
#include "regspinctrl.h"
#include "regsdigctl.h"
#include <stdarg.h>

#define RGB888_RED      0x00ff0000
#define RGB888_GREEN    0x0000ff00
#define RGB888_BLUE     0x000000ff


#define  HW_PINCTRL_MUXSEL3_T (*(volatile reg32_t *) HW_PINCTRL_MUXSEL3_ADDR)
#define  HW_PINCTRL_DRIVE7_T  (*(volatile reg32_t *) HW_PINCTRL_DRIVE7_ADDR )
#define  HW_PINCTRL_DOUT1_T   (*(volatile reg32_t *) HW_PINCTRL_DOUT1_ADDR )
#define  HW_PINCTRL_DOE1_T   (*(volatile unsigned *) HW_PINCTRL_DOE1_ADDR )

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
#define LINUX_LOGO_CLUT224	3	/* 224 colors */
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

void delayMs(int ms)
{
    delay(ms*1000);
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

void printhex(int data)
{
	int i = 0;
	char c;
	for (i = sizeof(int)*2-1; i >= 0; i--) {
		c = data>>(i*4);
		c &= 0xf;
		if (c > 9)
			putc(c-10+'A');
		else
			putc(c+'0');
	}
}
void printf(char *fmt, ...)
{
	va_list args;
	int one;
	va_start(args, fmt);
	while (*fmt) {

		if (*fmt == '%') {
			fmt++;
			switch (*fmt) {

			case 'x':
			case 'X':
				printhex(va_arg(args,int));
				break;
			case '%':
				putc('%');
				break;
			default:
				break;
			}

		} else {
			putc(*fmt);
		}
		fmt++;
	}
	va_end(args);
}

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
}
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

static void display_init (void)
{
        struct linux_logo * logo_descriptor = 0x40800000;
        int clutsize=logo_descriptor->clutsize * 3;
        if(clutsize % 4){
                clutsize = (clutsize/4 + 1) * 4;
        }
        //int struct_lenth=sizeof(struct linux_logo);
        int width = logo_descriptor->width;
        int height = logo_descriptor->height;
        unsigned short n565color;
        //寻找索引和颜色表的首地址
        unsigned char * clut = 0x40800018;
        unsigned char * logo = 0x40800018 + clutsize;
        //printf("0x%x  \n",sizeof(struct linux_logo));
        //printf("0x%x   ",clut);
        //printf("0x%x   \n",logo);
        int index=0;
        int i=0,j=0,a=0;
        unsigned int color_table[logo_descriptor->clutsize];
        unsigned short color_table_565[logo_descriptor->clutsize];
        printf("sssssssssssstart.......\n");
        for(a=0;a<logo_descriptor->clutsize;a++)
        {
        switch(logo_descriptor->type){
        case LINUX_LOGO_CLUT224:
             color_table[a] = (clut[3*a]<<16)+(clut[3*a+1]<<8)+clut[3*a+2];
        //printf("0x%x,  ",color_table[a]);
        //获取RGB单色，并截取高位
	unsigned char cRed = (color_table[a] & RGB888_RED) >> 19;
	unsigned char cGreen = (color_table[a] & RGB888_GREEN) >> 10;
	unsigned char cBlue = (color_table[a] & RGB888_BLUE) >> 3;
	// R5,G6,B5合并
	n565color = (cRed<< 11) + (cGreen<< 5) + (cBlue<< 0);
        color_table_565[a]=n565color;
        //printf("0x%x,  ",color_table_565[a]);
        break;
        default:
             printf("want more colorType?There is an Error!");  
        }
        }
        printf("color merge complete!\n");
        
        initLCD_IO();
        initLCD_Para();
        //向LCD屏写入数据
        //while(1){
                LCD_SetCursor(0x0000,0x0000);//设置光标位置
                LCD_WR_REG(0X2C);
                //LCD_WR_REG(0X28);
                //printf("0x%x",logo);
                for(i=0;i<height;i++)
                {
                        for(j=0;j<width;j++)
                        {
                           unsigned short color_565=color_table_565[logo[index]-32];
                           LCD_WR_DATA(color_565>>8);
                           LCD_WR_DATA(color_565); 
                           index++;        
                       }
                }
                LCD_WR_REG(0x29);
               /* for(j=0;j<240;j++)
                {
                    color = colorTab[j/30];
                    for(i=0;i<320;i++)
                    {
                        LCD_WR_DATA(color>>8);
                        LCD_WR_DATA(color);
                    }
                }*/
        //}
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
        LCD_WR_DATA(0x00);

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
        //LCD_WR_REG(0x29); //display on

}

        hw_initcall(display_init);
