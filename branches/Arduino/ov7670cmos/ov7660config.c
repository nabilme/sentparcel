 #include"ov7660.h"



const prog_char change_reg[CHANGE_REG_NUM][2]=
{


	{0x3a, 0x04},
	{0x40, 0x10},
	{0x12, 0x14},
	{0x32, 0x80},
	{0x17, 0x16},
	{0x18, 0x04},
	{0x19, 0x02},
	{0x1a, 0x7b},//0x7a,
	{0x03, 0x06},//0x0a,
	{0x0c, 0x04},
	{0x3e, 0x19},
	{0x70, 0x3a},
	{0x71, 0x35},
	{0x72, 0x11},
	{0x73, 0xf1},
	{0xa2, 0x02},
	
	{0x7a, 0x20},
	{0x7b, 0x1c},
	{0x7c, 0x28},
	{0x7d, 0x3c},
	{0x7e, 0x55},
	{0x7f, 0x68},
	{0x80, 0x76},
	{0x81, 0x80},
	{0x82, 0x88},
	{0x83, 0x8f},
	{0x84, 0x96},
	{0x85, 0xa3},
	{0x86, 0xaf},
	{0x87, 0xc4},
	{0x88, 0xd7},
	{0x89, 0xe8},
	
	{0x13, 0xe0},
	{0x00, 0x00},
	{0x10, 0x00},
	{0x0d, 0x40},
	{0x14, 0x28},//0x38, limit the max gain
	{0xa5, 0x05},
	{0xab, 0x07},
	{0x24, 0x65},
	{0x25, 0x33},
	{0x26, 0xe3},
	{0x9f, 0x78},
	{0xa0, 0x68},
	{0xa1, 0x03},//0x0b,
	{0xa6, 0xdf},//0xd8,
	{0xa7, 0xdf},//0xd8,
	{0xa8, 0xf0},
	{0xa9, 0x90},
	{0xaa, 0x94},
	{0x13, 0xe5},

	{0x0e, 0x61},
	{0x0f, 0x4b},
	{0x16, 0x02},
	{0x1e, 0x37},//0x07,
	{0x21, 0x02},
	{0x22, 0x91},
	{0x29, 0x07},
	{0x33, 0x0b},
	{0x35, 0x0b},
	{0x37, 0x1d},
	{0x38, 0x71},
	{0x39, 0x2a},
	{0x3c, 0x78},
	{0x4d, 0x40},
	{0x4e, 0x20},
	{0x69, 0x00},
	{0x6b, 0x4a},
	{0x74, 0x19},
	{0x8d, 0x4f},
	{0x8e, 0x00},
	{0x8f, 0x00},
	{0x90, 0x00},
	{0x91, 0x00},
	{0x92, 0x00},//0x19,//0x66
	{0x96, 0x00},
	{0x9a, 0x80},
	{0xb0, 0x84},
	{0xb1, 0x0c},
	{0xb2, 0x0e},
	{0xb3, 0x82},
	{0xb8, 0x0a},



	{0x43, 0x14},
	{0x44, 0xf0},
	{0x45, 0x34},
	{0x46, 0x58},
	{0x47, 0x28},
	{0x48, 0x3a},
	{0x59, 0x88},
	{0x5a, 0x88},
	{0x5b, 0x44},
	{0x5c, 0x67},
	{0x5d, 0x49},
	{0x5e, 0x0e},
	{0x64, 0x04},
	{0x65, 0x20},
	{0x66, 0x05},
	{0x94, 0x04},
	{0x95, 0x08},
	{0x6c, 0x0a},
	{0x6d, 0x55},
	{0x6e, 0x11},
	{0x6f, 0x9f},//0x9e for advance AWB
	{0x6a, 0x40},
	{0x01, 0x40},
	{0x02, 0x40},
	{0x13, 0xe7},
	
	{0x4f, 0x80},
	{0x50, 0x80},
	{0x51, 0x00},
	{0x52, 0x22},
	{0x53, 0x5e},
	{0x54, 0x80},
	{0x58, 0x9e},
	
	{0x41, 0x08},
	{0x3f, 0x00},
	{0x75, 0x05},
	{0x76, 0xe1},
	{0x4c, 0x00},
	{0x77, 0x01},
	{0x3d, 0xc2},	//0xc0,
	{0x4b, 0x09},
	{0xc9, 0x60},
	{0x41, 0x38},
	{0x56, 0x45},//0x40,  change according to Jim's request
	
	{0x34, 0x11},
	{0x3b, 0x02},//0x00,//0x02,
	{0xa4, 0x89},//0x88,
	{0x96, 0x00},
	{0x97, 0x30},
	{0x98, 0x20},
	{0x99, 0x30},
	{0x9a, 0x84},
	{0x9b, 0x29},
	{0x9c, 0x03},
	{0x9d, 0x4c},
	{0x9e, 0x3f},
	{0x78, 0x04},
	
	{0x79, 0x01},
	{0xc8, 0xf0},
	{0x79, 0x0f},
	{0xc8, 0x00},
	{0x79, 0x10},
	{0xc8, 0x7e},
	{0x79, 0x0a},
	{0xc8, 0x80},
	{0x79, 0x0b},
	{0xc8, 0x01},
	{0x79, 0x0c},
	{0xc8, 0x0f},
	{0x79, 0x0d},
	{0xc8, 0x20},
	{0x79, 0x09},
	{0xc8, 0x80},
	{0x79, 0x02},
	{0xc8, 0xc0},
	{0x79, 0x03},
	{0xc8, 0x40},
	{0x79, 0x05},
	{0xc8, 0x30},
	{0x79, 0x26},
	
	//88 f1 10
	//88 0f 1d
	//88 0f 1f
	
	{0x3b, 0xc2},//0x82,//0xc0,//0xc2,	//night mode











/*	
{0x17,0x13},
{0x18,0x01},
{0x32,0xB6},

{0x0c,0x00},
{0x3e,0x00},
{0x70,0x3a},
{0x71,0x35},
{0x72,0x11},
{0x73,0xf0},
{0xa2,0x02},
{0x12,0x14 }, //COM7  QVGA RGB


	{ 0x00 , 0x00 },//COM1	
	{ 0x01 , 0x00 },//COM1	
	{ 0x02 , 0x00 },//COM1	
	{ 0x03 , 0x00 },//COM1
	{ 0x04 , 0x00 },//COM1	
	{ 0x09 , 0x03 },//COM2	
	{ 0x10 , 0x40 },//
	{ 0x0C , 0x04 },//COM3 0x42=MSB LSB swap	
	{ 0x0F , 0xcB },//COM6	
	{ 0x11 , 0xff },//CLKRC  2M PCLK
	{ 0x12 , 0x14 }, //COM7  QVGA RGB
	{ 0x13 , 0x8F }, //COM8
	{ 0x14 , 0x4a },//COM9
	{ 0x15 , 0x00 }, //COM10  PCLK reverse
	{ 0x24 , 0x30 }, //AEW
	{ 0x25 , 0x85 }, //AEB	
	{ 0x37 , 0x00 }, //
	{ 0x3D , 0x00 }, //	
	{ 0x40 , 0xd0 }, //COM15  RGB565 out	
	{ 0x69 , 0x50 }, //HV
	{ 0x27 , 0x95 }, //HV
	{ 0x28 , 0xe0 }, //HV
	{ 0x41 , 0x20 }, //HV 

    { 0x4F , 0x80 }, //HV 
    { 0x50 , 0x86 }, //HV 
    { 0x51 , 0x06 }, //HV 
	{ 0x52 , 0x20 }, //HV 
    { 0x53 , 0x50 }, //HV 
    { 0x54 , 0x70 }, //HV 
	*//*
	
    { 0x7C , 0x04 },
    { 0x7D , 0x07 },
    { 0x7E , 0x10 },
    { 0x7F , 0x28 },
    { 0x80 , 0x36 },
    { 0x81 , 0x44 },
    { 0x82 , 0x52 },
    { 0x83 , 0x60 },
    { 0x84 , 0x6C },
    { 0x85 , 0x78 },
    { 0x86 , 0x8C },
    { 0x87 , 0x9E },
    { 0x88 , 0xBB },
    { 0x89 , 0xD2 },
    { 0x8A , 0xE6 },
    { 0x6C , 0x40 },
    { 0x6D , 0x30 },
    { 0x6E , 0x4B },
    { 0x6F , 0x60 },
    { 0x70 , 0x70 },
    { 0x71 , 0x70 },
    { 0x72 , 0x70 },
    { 0x73 , 0x70 },
    { 0x74 , 0x60 },
    { 0x75 , 0x60 },
    { 0x76 , 0x50 },
    { 0x77 , 0x48 },
    { 0x78 , 0x3A },
    { 0x79 , 0x2E },
    { 0x7A , 0x28 },
	*/
	
	//{ 0x20,  0xff }, //COM7  QVGA RGB		
	
};



