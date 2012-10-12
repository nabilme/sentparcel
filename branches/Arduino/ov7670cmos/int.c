#include "int.h"
#include "ILI9325.C"


void Init_INT0(void)
{
	SREG |= 0x80 ;//ʹ��ȫ���ж�
	MCUCR |= 0x03 ;//�������ж�
	GICR=(1<<INT0) ;//
	
}


SIGNAL( SIG_INTERRUPT0 )
{
	cli();
	
	 DISEN_EXCLK;//��ֹ�ⲿCLK��ʹ��Ƭ��WR��TFT WR����	
	 DISEN_245;//��ֹ�ⲿ�����ߣ�ʹ��Ƭ��������TFT����������	
     DATA_OUPUT();//�����������׼���������ߵ�TFT
	 DISEN_EXCLK;//��ֹ�ⲿCLK��ʹ��Ƭ��WR��TFT WR����	
	 DISEN_245;//��ֹ�ⲿ�����ߣ�ʹ��Ƭ��������TFT����������	
     DATA_OUPUT();//�����������׼���������ߵ�TFT
	 LCD_WR_REG(0x0020,0x00);//
	 LCD_WR_REG(0x0021,0x13f);//
	 LCD_WR_REG(0x0050,0x00);//ˮƽ GRAM��ʼλ��
	 LCD_WR_REG(0x0051,239);//ˮƽGRAM��ֹλ��
	 LCD_WR_REG(0x0052,0x00);//��ֱGRAM��ʼλ��
	 LCD_WR_REG(0x0053,319);//��ֱGRAM��ֹλ�� 
	 LCD_WR_REG(0x0003,0x1028); 
	 LCD_WR_REG16(0x0022);
	 LCD_CS_L();//����ʹ��
 
	 DATA_INPUT();//���������룬׼�������ⲿ�����ߵ�TFT	
	 LCD_RS_H();//����ʹ��
	 LCD_WR_L();//ʹ���ⲿʱ��
	 EN_245;//ʹ���ⲿ�����ߣ���TFT����������	
	 EN_EXCLK;//ʹ���ⲿCLK
	
	 sei();
}
