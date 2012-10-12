#include "SCCB.h"
#include "delay.h"

/*
-----------------------------------------------
   ����: ��ʼ��ģ��SCCB�ӿ�
   ����: ��
 ����ֵ: ��
-----------------------------------------------
*/
void InitSCCB(void)
{
	SCCB_DDR|=(1<<SCCB_SIO_C)|(1<<SCCB_SIO_D);
	SCCB_PORT|=(1<<SCCB_SIO_C)|(1<<SCCB_SIO_D);
}
/*
-----------------------------------------------
   ����: start����,SCCB����ʼ�ź�
   ����: ��
 ����ֵ: ��
-----------------------------------------------
*/
void startSCCB(void)
{
	SIO_D_SET;     //�����߸ߵ�ƽ
    delay_us(100);

    SIO_C_SET;	   //��ʱ���߸ߵ�ʱ���������ɸ�����
    delay_us(100);
 
    SIO_D_CLR;
    delay_us(100);

    SIO_C_CLR;	 //�����߻ָ��͵�ƽ��������������Ҫ
    delay_us(100);


}
/*
-----------------------------------------------
   ����: stop����,SCCB��ֹͣ�ź�
   ����: ��
 ����ֵ: ��
-----------------------------------------------
*/
void stopSCCB(void)
{
	SIO_D_CLR;
    delay_us(100);
 
    SIO_C_SET;
    delay_us(100);
  

    SIO_D_SET;
    delay_us(100);
 //   SCCB_DDR&= ~(SCCB_SIO_D);

}

/*
-----------------------------------------------
   ����: noAck,����������ȡ�е����һ����������
   ����: ��
 ����ֵ: ��
-----------------------------------------------
*/
void noAck(void)
{
	
	SIO_D_SET;
	delay_us(100);
	
	SIO_C_SET;
	delay_us(100);
	
	SIO_C_CLR;
	delay_us(100);
	
	SIO_D_CLR;
	delay_us(100);

}

/*
-----------------------------------------------
   ����: д��һ���ֽڵ����ݵ�SCCB
   ����: д������
 ����ֵ: ���ͳɹ�����1������ʧ�ܷ���0
-----------------------------------------------
*/
uchar SCCBwriteByte(uchar m_data)
{
	unsigned char j,tem;

	for(j=0;j<8;j++) //ѭ��8�η�������
	{
		if((m_data<<j)&0x80)
		{
			SIO_D_SET;
		}
		else
		{
			SIO_D_CLR;
		}
		delay_us(100);
		SIO_C_SET;
		delay_us(100);
		SIO_C_CLR;
		delay_us(100);

	}
	delay_us(100);
	
	SIO_D_IN;/*����SDAΪ����*/
	delay_us(100);
	SIO_C_SET;
	delay_us(1000);
	if(SIO_D_STATE)
	{
		tem=0;   //SDA=1����ʧ�ܣ�����0
	}
	else
	{
		tem=1;   //SDA=0���ͳɹ�������1
	}
	SIO_C_CLR;
	delay_us(100);	
    SIO_D_OUT;/*����SDAΪ���*/

	return(tem);  
}

/*
-----------------------------------------------
   ����: һ���ֽ����ݶ�ȡ���ҷ���
   ����: ��
 ����ֵ: ��ȡ��������
-----------------------------------------------
*/
uchar SCCBreadByte(void)
{
	unsigned char read,j;
	read=0x00;
	
	SIO_D_IN;/*����SDAΪ����*/
	delay_us(100);
	for(j=8;j>0;j--) //ѭ��8�ν�������
	{		     
		delay_us(100);
		SIO_C_SET;
		delay_us(100);
		read=read<<1;
		if(SIO_D_STATE) 
		{
			read=read+1;
		}
		SIO_C_CLR;
		delay_us(100);
	}	
	return(read);
}
