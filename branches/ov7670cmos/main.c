#include <avr/io.h>
#include <avr/interrupt.h>
#include "ILI9325.H"
#include "ov7660.H"
#include "int.H"
#include "delay.h"


//CPU��ʼ��//
int main(void) 
{
	
	EXCLK_DDR|=1<<EXCLK_BIT ;//en_exclk �������
	HC245_OE_DDR|=1<<HC245_OE_BIT;//en_245�������
	CMOS_CLK_DDR|=1<<CMOS_CLK_BIT;//7660ʱ�������������	
	DISEN_EXCLK;//��ֹ�ⲿCLK��ʹ��Ƭ��WR��TFT WR����	
	DISEN_245;//��ֹ�ⲿ�����ߣ�ʹ��Ƭ��������TFT����������
	CLK_init();//���ʱ�ӵ�7660
	DATA_OUPUT(); //�����������׼���������ߵ�TFT
    LCD_Init();
	//DATA_LCD_PORT=0xff;
	LCD_write_english_string(20,60,"Guanfu_Wang  2009-08-26",BLACK,RED);
	LCD_write_english_string(20,76,"Atmega32 & ILI9325 FOR OV7660 REV2.0",BLACK,RED);
	delay_ms(10000);
	LCD_write_english_string(20,96,"OV7660 Init......",BLACK,RED);
	while(1!=OV7660_init());//��ʼ��ov7660
	LCD_write_english_string(20,96,"OV7660 Init  0K  ",BLACK,RED);
	delay_ms(10000);
	LCD_Clear(RED);
    DATA_INPUT(); 
	Init_INT0();
	/**/
    while(1)
    {
	}

}

