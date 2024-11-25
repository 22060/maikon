/***********************************************************************/
/*  A/D�ϊ���̘A���X�L�������[�h���g�������K                    */
/***********************************************************************/

#include "iodefine.h"
#include "typedefine.h"

#define ex6

#define printf ((int (*)(const char *, ...))0x00007c7c)
#define SW6 (PD.DR.BIT.B18)
#define SW4 (PD.DR.BIT.B16)

#ifdef ex3
#define LCD_RS (PA.DR.BIT.B22)
#define LCD_E (PA.DR.BIT.B23)
#define LCD_RW (PD.DR.BIT.B23)
#define LCD_DATA (PD.DR.BYTE.HH)

void wait_us(_UINT);
void LCD_inst(_SBYTE);
void LCD_data(_SBYTE);
void LCD_cursor(_UINT, _UINT);
void LCD_putch(_SBYTE);
void LCD_putstr(_SBYTE *);
void LCD_cls(void);
void LCD_init(void);
#endif

#ifdef ex4
#define LCD_RS (PA.DR.BIT.B22)
#define LCD_E (PA.DR.BIT.B23)
#define LCD_RW (PD.DR.BIT.B23)
#define LCD_DATA (PD.DR.BYTE.HH)

void wait_us(_UINT);
void LCD_inst(_SBYTE);
void LCD_data(_SBYTE);
void LCD_cursor(_UINT, _UINT);
void LCD_putch(_SBYTE);
void LCD_putstr(_SBYTE *);
void LCD_cls(void);
void LCD_init(void);
#endif

#ifdef ex6
#define LCD_RS (PA.DR.BIT.B22)
#define LCD_E (PA.DR.BIT.B23)
#define LCD_RW (PD.DR.BIT.B23)
#define LCD_DATA (PD.DR.BYTE.HH)

void wait_us(_UINT);
void LCD_inst(_SBYTE);
void LCD_data(_SBYTE);
void LCD_cursor(_UINT, _UINT);
void LCD_putch(_SBYTE);
void LCD_putstr(_SBYTE *);
void LCD_cls(void);
void LCD_init(void);
#endif

void main(void);

void main(void)
{

#ifdef ex1
	STB.CR4.BIT._AD0 = 0;
	AD0.ADCSR.BIT.ADM = 3;
	AD0.ADCSR.BIT.ADCS = 1;
	AD0.ADCSR.BIT.CH = 1;
	AD0.ADCR.BIT.ADST = 1;
	while (1)
	{
		while (!AD0.ADCSR.BIT.ADF)
			;
		AD0.ADCSR.BIT.ADF = 0;
		printf("ADDR0 = %04dnADDR1 = %04d \n",
			   AD0.ADDR0 >> 6, AD0.ADDR1 >> 6);
	}

#endif

#ifdef ex2
	STB.CR4.BIT._AD0 = 0;
	AD0.ADCSR.BIT.ADM = 3;
	AD0.ADCSR.BIT.ADCS = 1;
	AD0.ADCSR.BIT.CH = 1;
	AD0.ADCR.BIT.ADST = 0;

	PFC.PDIORH.BIT.B16 = 0; // PD16(SW4) .. ????
	PFC.PDIORH.BIT.B17 = 0; // PD17(SW5) .. ????
	PFC.PDIORH.BIT.B18 = 0; // PD18(SW6) .. ????
	while (1)
	{
		// printf("%d %d \n", SW6,SW4);
		if (AD0.ADCR.BIT.ADST)
		{
			// printf("%d", SW6);
			while (!AD0.ADCSR.BIT.ADF)
				;
			AD0.ADCSR.BIT.ADF = 0;
			printf("ADDR0 = %04dnADDR1 = %04d \n",
				   AD0.ADDR0 >> 6, AD0.ADDR1 >> 6);
		}
		if (SW6 == 1)
		{
			AD0.ADCR.BIT.ADST = 1;
		}
		if (SW4 == 1)
		{
			AD0.ADCR.BIT.ADST = 0;
		}
	}

#endif

#ifdef ex3
	_UWORD ad_rst = 0;
	_SBYTE str[16] = {' ', ' ', 'A', 'D', 'D', 'R', '0', ' ', '=', ' ', '0', '0', '0', ' ', ' ', '\0'};
	STB.CR4.BIT._AD0 = 0;
	STB.CR4.BIT._CMT = 0;
	AD0.ADCSR.BIT.ADM = 3;
	AD0.ADCSR.BIT.ADCS = 1;
	AD0.ADCSR.BIT.CH = 1;
	AD0.ADCR.BIT.ADST = 1;

	CMT0.CMCSR.BIT.CKS = 1;
	CMT0.CMCSR.BIT.CKS = 1; // ?@ CKS???(0:1/8, 1:1/32, 2:1/128, 3:1/512)
	CMT0.CMCOR = 1;			// ?A
	LCD_init();
	while (1)
	{

		if (AD0.ADCR.BIT.ADST)
		{
			while (!AD0.ADCSR.BIT.ADF)
				;
			AD0.ADCSR.BIT.ADF = 0;
			ad_rst = AD0.ADDR0 >> 6;
			str[9] = (ad_rst / 100 == 10) ? '1' : ' ';
			str[10] = (ad_rst / 100 == 10) ? '0' : ad_rst / 100 + '0';
			str[11] = (ad_rst / 10) % 10 + '0';
			str[12] = ad_rst % 10 + '0';
			LCD_cursor(0, 0);
			LCD_putstr(str);
			ad_rst = AD0.ADDR1 >> 6;
			str[9] = (ad_rst / 100 == 10) ? '1' : ' ';
			str[10] = (ad_rst / 100 == 10) ? '0' : ad_rst / 100 + '0';
			str[11] = (ad_rst / 10) % 10 + '0';
			str[12] = ad_rst % 10 + '0';
			LCD_cursor(0, 1);
			LCD_putstr(str);
		}

		if (SW6 == 1)
		{
			AD0.ADCR.BIT.ADST = 1;
		}
		if (SW4 == 1)
		{
			AD0.ADCR.BIT.ADST = 0;
		}
	}

#endif

#ifdef ex4
	_UWORD ad_rst = 0;
	_SBYTE str[16] = {' ', ' ', 'A', 'D', 'D', 'R', '0', ' ', '=', ' ', '0', '0', '0', ' ', ' ', '\0'};
	STB.CR4.BIT._AD0 = 0;
	STB.CR4.BIT._CMT = 0;
	AD0.ADCSR.BIT.ADM = 3;
	AD0.ADCSR.BIT.ADCS = 1;
	AD0.ADCSR.BIT.CH = 1;
	AD0.ADCR.BIT.ADST = 1;

	CMT0.CMCSR.BIT.CKS = 1;
	CMT0.CMCSR.BIT.CKS = 1; // ?@ CKS???(0:1/8, 1:1/32, 2:1/128, 3:1/512)
	CMT0.CMCOR = 1;			// ?A
	CMT1.CMCSR.BIT.CKS = 1;
	CMT1.CMCSR.BIT.CKS = 3; // ?@ CKS???(0:1/8, 1:1/32, 2:1/128, 3:1/512)
	CMT1.CMCOR = 1;			// ?A
	CMT1.CMCOR = 19531 - 1;
	LCD_init();
	while (1)
	{

		if (AD0.ADCR.BIT.ADST)
		{
			if (CMT1.CMCSR.BIT.CMF)
			{
				CMT1.CMCSR.BIT.CMF = 0;
				while (!AD0.ADCSR.BIT.ADF)
					;
				AD0.ADCSR.BIT.ADF = 0;
				ad_rst = AD0.ADDR0 >> 6;
				str[9] = (ad_rst / 100 == 10) ? '1' : ' ';
				str[10] = (ad_rst / 100 == 10) ? '0' : ad_rst / 100 + '0';
				str[11] = (ad_rst / 10) % 10 + '0';
				str[12] = ad_rst % 10 + '0';
				LCD_cursor(0, 0);
				LCD_putstr(str);
				ad_rst = AD0.ADDR1 >> 6;
				str[9] = (ad_rst / 100 == 10) ? '1' : ' ';
				str[10] = (ad_rst / 100 == 10) ? '0' : ad_rst / 100 + '0';
				str[11] = (ad_rst / 10) % 10 + '0';
				str[12] = ad_rst % 10 + '0';
				LCD_cursor(0, 1);
				LCD_putstr(str);
			}
		}

		if (SW6 == 1)
		{
			printf("%d", SW6);
			CMT.CMSTR.BIT.STR1 = 1;
			CMT1.CMCSR.BIT.CMF &= 0;
			AD0.ADCR.BIT.ADST = 1;
		}
		if (SW4 == 1)
		{
			AD0.ADCR.BIT.ADST = 0;
			CMT.CMSTR.BIT.STR1 = 0;
		}
	}

#endif

#ifdef ex5
	int count = 0;
	int tmc = 0;
	CMT0.CMCSR.BIT.CKS = 1;
	CMT0.CMCSR.BIT.CKS = 0; // ?@ CKS???(0:1/8, 1:1/32, 2:1/128, 3:1/512)
	CMT0.CMCOR = 1;			// ?A
	CMT1.CMCSR.BIT.CKS = 1;
	CMT1.CMCSR.BIT.CKS = 3; // ?@ CKS???(0:1/8, 1:1/32, 2:1/128, 3:1/512)
	CMT1.CMCOR = 1;			// ?A
	CMT1.CMCOR = 19531 - 1;
	while (1)
	{
		if (CMT1.CMCSR.BIT.CMF)
		{
			CMT1.CMCSR.BIT.CMF = 0;
			printf("%d %d\n", count * 1000, 500);
		}
		if (CMT0.CMCSR.BIT.CMF)
		{
			CMT0.CMCSR.BIT.CMF = 0;
			tmc++;
		}
		if (tmc < 5)
		{
			tmc = 0;
			count++;
		}
	}
#endif

#ifdef ex6
	typedef struct
	{
		int RS;
		int RW;

	} LCD;
	_UWORD ad_rst = 0;
	_SBYTE str[16] = {' ', ' ', 'A', 'D', 'D', 'R', '0', ' ', '=', ' ', '0', '0', '0', ' ', ' ', '\0'};
	LCD inst = {0, 0};
	LCD data = {1, 0};
	int time = 0;
	int count;
	int flag[2] = {0, 2};
	int loopc = 0;
	int tms[5] = {0, 1, 40, 1, 40};
	STB.CR4.BIT._AD0 = 0;
	STB.CR4.BIT._CMT = 0;
	AD0.ADCSR.BIT.ADM = 3;
	AD0.ADCSR.BIT.ADCS = 1;
	AD0.ADCSR.BIT.CH = 1;
	AD0.ADCR.BIT.ADST = 1;

	CMT0.CMCSR.BIT.CKS = 1;
	CMT0.CMCSR.BIT.CKS = 1; // ?@ CKS???(0:1/8, 1:1/32, 2:1/128, 3:1/512)
	CMT0.CMCOR = 1;			// ?A
	CMT1.CMCSR.BIT.CKS = 1;
	CMT1.CMCSR.BIT.CKS = 3; // ?@ CKS???(0:1/8, 1:1/32, 2:1/128, 3:1/512)
	CMT1.CMCOR = 1;			// ?A
	CMT1.CMCOR = 19531 - 1;
	LCD_init();
	time = count;
	while (1)
	{

		if (AD0.ADCR.BIT.ADST)
		{
			if (CMT1.CMCSR.BIT.CMF)
			{
				CMT1.CMCSR.BIT.CMF = 0;
				while (!AD0.ADCSR.BIT.ADF)
					;
				AD0.ADCSR.BIT.ADF = 0;
				ad_rst = AD0.ADDR0 >> 6;
				str[9] = (ad_rst / 100 == 10) ? '1' : ' ';
				str[10] = (ad_rst / 100 == 10) ? '0' : ad_rst / 100 + '0';
				str[11] = (ad_rst / 10) % 10 + '0';
				str[12] = ad_rst % 10 + '0';
				// LCD_cursor(0, 0);
				if (count - time > tms[loopc])
				{
					time = count;
					switch (loopc - 1)
					{
					case 0:
						LCD_E = 0;
						LCD_RS = inst.RS;
						LCD_RW = inst.RW;
						LCD_E = 1;
						LCD_DATA = (0x80 | 0 | 0 << 6);
						break;
					case 1:
						LCD_E = 0;
						break;
					case 2:
						LCD_E = 0;
						LCD_RS = data.RS;
						LCD_RW = data.RW;
						LCD_E = 1;
						LCD_DATA = str;
						break;
					case 3:
						LCD_E = 0;
						break;
					}
				}
				ad_rst = AD0.ADDR1 >> 6;
				str[9] = (ad_rst / 100 == 10) ? '1' : ' ';
				str[10] = (ad_rst / 100 == 10) ? '0' : ad_rst / 100 + '0';
				str[11] = (ad_rst / 10) % 10 + '0';
				str[12] = ad_rst % 10 + '0';

				if (count - time > tms[loopc])
				{
					time = count;
					switch (loopc - 1)
					{
					case 0:
						LCD_E = 0;
						LCD_RS = inst.RS;
						LCD_RW = inst.RW;
						LCD_E = 1;
						LCD_DATA = (0x80 | 0 | 0 << 6);
						break;
					case 1:
						LCD_E = 0;
						break;
					case 2:
						LCD_E = 0;
						LCD_RS = data.RS;
						LCD_RW = data.RW;
						LCD_E = 1;
						LCD_DATA = str;
						break;
					case 3:
						LCD_E = 0;
						break;
					}
				}
				loopc++;
				if (loopc == 5)
				{
					loopc = 0;
				}
			}
		}

		if (SW6 == 1)
		{
			printf("%d", SW6);
			CMT.CMSTR.BIT.STR1 = 1;
			CMT1.CMCSR.BIT.CMF &= 0;
			AD0.ADCR.BIT.ADST = 1;
		}
		if (SW4 == 1)
		{
			AD0.ADCR.BIT.ADST = 0;
			CMT.CMSTR.BIT.STR1 = 0;
		}
	}

#endif
}

#ifdef ex3
void wait_us(_UINT us)
{
	_UINT val;

	val = us * 10 / 16;
	if (val >= 0xffff)
		val = 0xffff;

	CMT0.CMCOR = val;
	CMT0.CMCSR.BIT.CMF &= 0;
	CMT.CMSTR.BIT.STR0 = 1;
	while (!CMT0.CMCSR.BIT.CMF)
		;
	CMT0.CMCSR.BIT.CMF = 0;
	CMT.CMSTR.BIT.STR0 = 0;
}

void LCD_inst(_SBYTE inst)
{
	LCD_E = 0;
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_E = 1;
	LCD_DATA = inst;
	wait_us(1);
	LCD_E = 0;
	wait_us(40);
}

void LCD_data(_SBYTE data)
{
	LCD_E = 0;
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_E = 1;
	LCD_DATA = data;
	wait_us(1);
	LCD_E = 0;
	wait_us(40);
}

void LCD_cursor(_UINT x, _UINT y)
{
	if (x > 15)
		x = 15;
	if (y > 1)
		y = 1;
	LCD_inst(0x80 | x | y << 6);
}

void LCD_putch(_SBYTE ch)
{
	LCD_data(ch);
}

void LCD_putstr(_SBYTE *str)
{
	_SBYTE ch;

	while (ch = *str++)
		LCD_putch(ch);
}

void LCD_cls(void)
{
	LCD_inst(0x01);
	wait_us(1640);
}

void LCD_init(void)
{
	wait_us(45000);
	LCD_inst(0x30);
	wait_us(4100);
	LCD_inst(0x30);
	wait_us(100);
	LCD_inst(0x30);

	LCD_inst(0x38);
	LCD_inst(0x08);
	LCD_inst(0x01);
	wait_us(1640);
	LCD_inst(0x06);
	LCD_inst(0x0c);
}
#endif

#ifdef ex4
void wait_us(_UINT us)
{
	_UINT val;

	val = us * 10 / 16;
	if (val >= 0xffff)
		val = 0xffff;

	CMT0.CMCOR = val;
	CMT0.CMCSR.BIT.CMF &= 0;
	CMT.CMSTR.BIT.STR0 = 1;
	while (!CMT0.CMCSR.BIT.CMF)
		;
	CMT0.CMCSR.BIT.CMF = 0;
	CMT.CMSTR.BIT.STR0 = 0;
}

void LCD_inst(_SBYTE inst)
{
	LCD_E = 0;
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_E = 1;
	LCD_DATA = inst;
	wait_us(1);
	LCD_E = 0;
	wait_us(40);
}

void LCD_data(_SBYTE data)
{
	LCD_E = 0;
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_E = 1;
	LCD_DATA = data;
	wait_us(1);
	LCD_E = 0;
	wait_us(40);
}

void LCD_cursor(_UINT x, _UINT y)
{
	if (x > 15)
		x = 15;
	if (y > 1)
		y = 1;
	LCD_inst(0x80 | x | y << 6);
}

void LCD_putch(_SBYTE ch)
{
	LCD_data(ch);
}

void LCD_putstr(_SBYTE *str)
{
	_SBYTE ch;

	while (ch = *str++)
		LCD_putch(ch);
}

void LCD_cls(void)
{
	LCD_inst(0x01);
	wait_us(1640);
}

void LCD_init(void)
{
	wait_us(45000);
	LCD_inst(0x30);
	wait_us(4100);
	LCD_inst(0x30);
	wait_us(100);
	LCD_inst(0x30);

	LCD_inst(0x38);
	LCD_inst(0x08);
	LCD_inst(0x01);
	wait_us(1640);
	LCD_inst(0x06);
	LCD_inst(0x0c);
}
#endif

#ifdef ex6
void wait_us(_UINT us)
{
	_UINT val;

	val = us * 10 / 16;
	if (val >= 0xffff)
		val = 0xffff;

	CMT0.CMCOR = val;
	CMT0.CMCSR.BIT.CMF &= 0;
	CMT.CMSTR.BIT.STR0 = 1;
	while (!CMT0.CMCSR.BIT.CMF)
		;
	CMT0.CMCSR.BIT.CMF = 0;
	CMT.CMSTR.BIT.STR0 = 0;
}

void LCD_inst(_SBYTE inst)
{
	LCD_E = 0;
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_E = 1;
	LCD_DATA = inst;
	wait_us(1);
	LCD_E = 0;
	wait_us(40);
}

void LCD_data(_SBYTE data)
{
	LCD_E = 0;
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_E = 1;
	LCD_DATA = data;
	wait_us(1);
	LCD_E = 0;
	wait_us(40);
}

void LCD_cursor(_UINT x, _UINT y)
{
	if (x > 15)
		x = 15;
	if (y > 1)
		y = 1;
	LCD_inst(0x80 | x | y << 6);
}

void LCD_putch(_SBYTE ch)
{
	LCD_data(ch);
}

void LCD_putstr(_SBYTE *str)
{
	_SBYTE ch;

	while (ch = *str++)
		LCD_putch(ch);
}

void LCD_cls(void)
{
	LCD_inst(0x01);
	wait_us(1640);
}

void LCD_init(void)
{
	wait_us(45000);
	LCD_inst(0x30);
	wait_us(4100);
	LCD_inst(0x30);
	wait_us(100);
	LCD_inst(0x30);

	LCD_inst(0x38);
	LCD_inst(0x08);
	LCD_inst(0x01);
	wait_us(1640);
	LCD_inst(0x06);
	LCD_inst(0x0c);
}
#endif