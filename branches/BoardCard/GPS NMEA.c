/*
AVR GPS ���ݽ���ģ�顣
��GPS ��NMEMA ��Ϣ���룬Ȼ��ͨ��I2C ���ߴ��ݵ�����
*/

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#define INT_ON sei();
#define INT_OFF cli();

typedef struct tagGPSPosition
{
	//float fLon; // ���� Longitude
	USHORT nLonHigh;
	USHORT nLonLow;
	BYTE WE;
	BYTE Reserved1; // ����AVR ��8 λ��Ƭ�������Դ洢�ṹ�Ͽ��԰���1 �ֽڶ��롣
	// ��ARM ��PC ��32 λ��Ƭ�������Ա��벹��һ��������ֽڡ�
	
	//float fLat; // γ�� Latitude
	USHORT nLatHigh;
	USHORT nLatLow;
	BYTE NS;
	BYTE Reserved2;
}GPSPOSITION;

#define NOP asm("nop");
#define TX_BUFFER_SIZE 20
#define UDR_EMPTY (1<<UDRE)

BOOL g_bState = FALSE; // GPS ��λ״̬
GPSPOSITION g_Position = {0};
BYTE tx_buffer[TX_BUFFER_SIZE]={0};
BYTE tx_wr_index=0;
BYTE tx_rd_index=0;
BYTE tx_counter=0;

void GPS_Decode(BYTE nData)
{
	/*
	����������Ϣ��
	$GPRMC,121252.000,A,3958.3032,N,11629.6046,E,15.15,359.95,070306,,,A*54
	$GPRMC,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,<10>,<11>,<12>*hh<CR><LF>
	<1> UTC ʱ�䣬hhmmss��ʱ���룩��ʽ
	<2> ��λ״̬��A=��Ч��λ��V=��Ч��λ
	<3> γ��ddmm.mmmm���ȷ֣���ʽ��ǰ���0 Ҳ�������䣩
	<4> γ�Ȱ���N�������򣩻�S���ϰ���
	<5> ����dddmm.mmmm���ȷ֣���ʽ��ǰ���0 Ҳ�������䣩
	<6> ���Ȱ���E����������W��������
	<7> �������ʣ�000.0~999.9 �ڣ�ǰ���0 Ҳ�������䣩
	<8> ���溽��000.0~359.9 �ȣ����汱Ϊ�ο���׼��ǰ���0 Ҳ�������䣩
	<9> UTC ���ڣ�ddmmyy�������꣩��ʽ
	<10> ��ƫ�ǣ�000.0~180.0 �ȣ�ǰ���0 Ҳ�������䣩
	<11> ��ƫ�Ƿ���E��������W������
	<12> ģʽָʾ����NMEA0183 3.00 �汾�����A=������λ��D=��֣�E=���㣬N=������Ч��
	*/
	
	static int nDataIndex = 0;
	static BOOL bDataFieldOK = FALSE;
	static int nItemIndex = 0;
	static char szBuffer[15] = {0};
	static char *pBufferIndex = 0;
	BYTE i = 0;
	USHORT nData1 = 0;
	USHORT nData2 = 0;
	
	if (nData == '$')
	{
		// �µ�һ�����ݿ�ʼ��
		nDataIndex = 0;
		nItemIndex = 0;
		pBufferIndex = &szBuffer[0];
		bDataFieldOK = FALSE;
	}
	else
	{
		nDataIndex ++;
	}	
	if ((nDataIndex == 5) && (nData == 'C')) // ȷ�ϵ�6 ���ַ���C��Ҳ����GPS ģ�鷵�ص�$GPRMC ������Ŀ
	{
		if (!g_bState)
		{
			PORTB |= (1<<PB0);
		}
		// ����ɨ�������Ϣ��
		bDataFieldOK = TRUE;
	}
	else if ((nDataIndex == 5) && (nData != 'C')) // �ֶγ����㹻��������$GPRMC ������Ŀ
	{
		// ����������Ҫ���ֶΣ����Բ�ȥ����
	}
	
	if ((bDataFieldOK) && (nDataIndex > 6))
	{
		// ���������Ѿ������ˣ���Ҫ���в�֡�
		if ((nData == ',') || (nData == '*'))
		{
			PORTB &= ~(1<<PB0);
			*pBufferIndex = 0; // д����ֹ����
			// ������һ������
			switch(nItemIndex)
			{			
				case 0:
					// UTC ʱ�䣬hhmmss
					//TRACE("UTC Time: %s",szBuffer);
					break;
				case 1:
					// ��λ״̬��A=��Ч��λ��V=��Ч��λ
					//TRACE("��λ״̬: %s",szBuffer);
					if (strcmp(szBuffer,"A") == 0)
					{
						PORTB |= (1<<PB2);
						g_bState = TRUE;
					}
					else
					{
						PORTB &= ~(1<<PB2);
						g_bState = FALSE;
					}
					break;
				case 2:
					// γ��ddmm.mmmm���ȷ֣���ʽ��ǰ���0 Ҳ�������䣩
					// ����AVR ��Intel32 λ������ĸ������洢��ʽ����һ�������Բ���ֱ��ת�ɸ��㴫�ݡ�
					//g_Position.fLat = atof(szBuffer);
					for (i=0;i<sizeof(szBuffer);i++)
					{
						if (szBuffer[i] == '.')
						{
							szBuffer[i] = 0;
							nData1 = atoi(szBuffer);
							nData2 = atoi(&szBuffer[i+1]);
							g_Position.nLatHigh = nData1;
							g_Position.nLatLow = nData2;
							break;
						}
					}
					break;
				case 3:
					// γ�Ȱ���N�������򣩻�S���ϰ���
					g_Position.NS = szBuffer[0];
					break;
				case 4:
					// ����dddmm.mmmm���ȷ֣���ʽ��ǰ���0 Ҳ�������䣩
					// g_Position.fLon = atof(szBuffer);
					// ����AVR ��Intel32 λ������ĸ������洢��ʽ����һ�������Բ���ֱ��ת�ɸ��㴫�ݡ�
					for (i=0;i<sizeof(szBuffer);i++)
					{
						if (szBuffer[i] == '.')
						{
							szBuffer[i] = 0;
							nData1 = atoi(szBuffer);
							nData2 = atoi(&szBuffer[i+1]);
							g_Position.nLonHigh = nData1;
							g_Position.nLonLow = nData2;
							break;
						}
					}
					break;
				case 5:
					// ���Ȱ���E����������W��������
					g_Position.WE = szBuffer[0];
					break;
				case 6:
					// �������ʣ�000.0~999.9 �ڣ�ǰ���0 Ҳ�������䣩
					break;
				case 7:
					// ���溽��000.0~359.9 �ȣ����汱Ϊ�ο���׼��ǰ���0 Ҳ�������䣩
					break;
				case 8:
					// UTC ���ڣ�ddmmyy�������꣩��ʽ
					break;
				case 9:
					// ��ƫ�ǣ�000.0~180.0 �ȣ�ǰ���0 Ҳ�������䣩
					break;
				case 10:
					// ��ƫ�Ƿ���E��������W������
					break;
				case 11:
					// ģʽָʾ����NMEA0183 3.00 �汾�����A=������λ��D=��֣�E=���㣬N=������Ч��
					// ����$GPRMC �����һ�����ݡ�
					// ������Ҫ�������Ѿ�����ˣ���������ݾ�Ҫ�ȴ���һ��1s �������ˡ�
					// ���ڿ�������ɼ��¶��ˡ�
					g_bAllowGetTemperature = FALSE;
					break;
				default:
					break;
}

			// ���ţ���Ҫ�л�����һ�����ݡ�
			nItemIndex++;
			// �������û�������ʼλ�á�
			pBufferIndex = &szBuffer[0];
		}
		else
		{
			// ����д�뻺������
			*pBufferIndex = nData;
			pBufferIndex++;
		}
	}
}