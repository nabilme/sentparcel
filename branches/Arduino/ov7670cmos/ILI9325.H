
#include<avr/io.h>

///////////////////////////////////////////////////////
#define	BLACK	0x0000
#define	BLUE	0x001F
#define	RED 	0xF800
#define	GREEN 	0x07E0
#define CYAN	0x07FF
#define MAGENTA 0xF81F
#define YELLOW	0xFFE0
#define WHITE	0xFFFF		


#define ID_AM         011


#define DATA_LCD_DDR  DDRA
#define DATA_LCD_PORT PORTA
#define DATA_LCD_PIN  PINA

#define DATA_INPUT()   DATA_LCD_DDR = 0x00;
#define DATA_OUPUT()   DATA_LCD_DDR = 0xFF;

#define LCD_CS_DDR  DDRC
#define LCD_CS_PORT PORTC
#define LCD_CS_PIN  PINC
#define LCD_CS_BIT  6

#define LCD_RS_DDR  DDRC
#define LCD_RS_PORT PORTC
#define LCD_RS_PIN  PINC
#define LCD_RS_BIT  7

#define LCD_RD_DDR  DDRB
#define LCD_RD_PORT PORTB
#define LCD_RD_PIN  PINB
#define LCD_RD_BIT  2

#define LCD_WR_DDR  DDRB
#define LCD_WR_PORT PORTB
#define LCD_WR_PIN  PINB
#define LCD_WR_BIT  3

#define LCD_RST_DDR  DDRB
#define LCD_RST_PORT PORTB
#define LCD_RST_PIN  PINB
#define LCD_RST_BIT  1


#define LCD_BL_DDR  DDRD
#define LCD_BL_PORT PORTD
#define LCD_BL_PIN  PIND
#define LCD_BL_BIT  6

#define LCD_CS_H() LCD_CS_PORT |= 1<<LCD_CS_BIT
#define LCD_CS_L() LCD_CS_PORT &= ~(1<<LCD_CS_BIT)

#define LCD_RS_H() LCD_RS_PORT |= 1<<LCD_RS_BIT
#define LCD_RS_L() LCD_RS_PORT &= ~(1<<LCD_RS_BIT)

#define LCD_WR_L() LCD_WR_PORT |= 1<<LCD_WR_BIT//
#define LCD_WR_H() LCD_WR_PORT &= ~(1<<LCD_WR_BIT)//

#define LCD_RD_H() LCD_RD_PORT |= 1<<LCD_RD_BIT
#define LCD_RD_L() LCD_RD_PORT &= ~(1<<LCD_RD_BIT)

#define LCD_RST_H() LCD_RST_PORT |= 1<<LCD_RST_BIT
#define LCD_RST_L() LCD_RST_PORT &= ~(1<<LCD_RST_BIT)

#define LCD_BL_H() LCD_BL_PORT |= 1<<LCD_BL_BIT
#define LCD_BL_L() LCD_BL_PORT &= ~(1<<LCD_BL_BIT)

#define LCD_PORT_INI(){ LCD_BL_DDR |= 1<<LCD_BL_BIT;\
						LCD_CS_DDR |= 1<<LCD_CS_BIT;\
						LCD_RS_DDR |= 1<<LCD_RS_BIT;\
						LCD_WR_DDR |= 1<<LCD_WR_BIT;\
						LCD_RD_DDR |= 1<<LCD_RD_BIT;\
						LCD_RST_DDR|= 1<<LCD_RST_BIT;\
					   }



void LCD_WR_REG(unsigned int index,unsigned int data);
void LCD_WR_REG16(unsigned int index);//д����������
void LCD_WR_DATA16(unsigned int data);//������������
void LCD_Init(void);
void LCD_Clear(unsigned int Color);
void LCD_write_english(unsigned char data,unsigned int color,unsigned int xcolor);//д�ַ�
void LCD_write_english_string(unsigned int x,unsigned char y,unsigned char *s,unsigned int color,unsigned int xcolor);//Ӣ���ַ�����ʾ
void LCD_SetCursor(unsigned char Xpos, unsigned char Ypos);
void Lcd_SetBox(unsigned char xStart,unsigned int yStart,unsigned char xLong,unsigned int yLong);
void Test(void);


