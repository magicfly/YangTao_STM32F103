#ifndef __CAR_H
#define __CAR_H	
const unsigned char car_pic[] =                  // ���ݱ�
{
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0xFC,0xFE,0x0E,0x1C,
      0x18,0x1C,0x0E,0xFE,0xFC,0x00,0x7C,0xFC,
      0x80,0xFC,0xFC,0x00,0x00,0x00,0x7C,0xFE,
      0xC6,0xC6,0xC6,0x00,0x40,0xE8,0xA8,0xF8,
      0xF0,0x00,0xF8,0xF8,0x10,0x18,0x00,0x00,
      0xC0,0xC0,0x00,0xC0,0xC0,0x00,0xC0,0xC0,
      0x00,0x00,0x06,0x09,0x12,0x09,0x06,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,
      0x12,0x22,0x44,0x22,0x12,0x0C,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x81,0x41,0x40,0x80,
      0x40,0x40,0x80,0x01,0x01,0x00,0x04,0x05,
      0x05,0x07,0x03,0xC0,0x20,0x40,0x20,0xC1,
      0x01,0x01,0x01,0x00,0x00,0x01,0x01,0x01,
      0x81,0x80,0x81,0xC1,0xC0,0x40,0xC0,0xC0,
      0xE1,0xE1,0xE0,0xE1,0xE1,0xE0,0xE1,0xE1,
      0xE0,0xE0,0xE0,0x60,0x60,0x40,0x40,0xC0,
      0xE0,0xE0,0xA0,0x90,0x8C,0x02,0x01,0x00,
      0x00,0x00,0x00,0x00,0x10,0x28,0x50,0x28,
      0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x01,0x02,0x04,0x08,
      0x04,0x02,0x01,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x01,0xC2,0xE1,0xF0,
      0x30,0x18,0x08,0x3C,0xF6,0xFE,0xFB,0x1D,
      0x0D,0x02,0xC2,0xCB,0x09,0x09,0x09,0x09,
      0x08,0x08,0x08,0x08,0x08,0x08,0x00,0xC0,
      0xFF,0xFC,0xFC,0xF9,0xE1,0xC1,0x11,0x12,
      0x02,0xC6,0xC5,0xC9,0xD9,0xF3,0xE3,0xC6,
      0x0E,0x0C,0x1C,0x38,0x38,0xF0,0xE0,0xC0,
      0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x12,
      0x24,0x12,0x0C,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x80,0x40,0x70,0xF0,
      0x38,0x18,0x0C,0x0C,0x0E,0x0E,0x0E,0x86,
      0x8E,0x0B,0x0B,0x0B,0x03,0x13,0x31,0x36,
      0x57,0xE7,0x87,0x07,0x07,0x07,0x07,0x07,
      0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
      0x03,0x03,0x03,0x03,0x03,0x03,0x33,0x3B,
      0x33,0x33,0xF3,0x03,0x03,0x03,0x03,0x03,
      0x03,0x83,0x83,0xC3,0x63,0x33,0x91,0x91,
      0x89,0x08,0x00,0x84,0x84,0x84,0x85,0x87,
      0x07,0x07,0x06,0x1E,0x38,0x78,0xE0,0xC0,
      0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x78,0xFC,0xEF,0xFF,0x7B,0x1B,0x08,
      0xF0,0xF8,0xFC,0xFE,0xFF,0xEF,0x0F,0x1F,
      0x1F,0x0F,0xFF,0xFF,0xFE,0xFC,0xF9,0xF2,
      0x04,0x00,0x03,0xFE,0x80,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,
      0x9E,0x7F,0x73,0x18,0x0E,0xF3,0xFF,0xFF,
      0xFF,0xFF,0xFF,0x0F,0x1F,0x1F,0x0F,0x7F,
      0xFF,0xFF,0xFE,0xFC,0xFC,0xF8,0x18,0xFD,
      0xFF,0xFF,0x7E,0x1C,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x01,0x03,0x27,0x26,0x30,0x30,
      0x3F,0x3F,0x3F,0x3F,0x3E,0x26,0x22,0x39,
      0x39,0x20,0x3C,0x3E,0x3F,0x3F,0x3F,0x3F,
      0x3E,0x38,0x38,0x39,0x39,0x38,0x38,0x3A,
      0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,
      0x3A,0x3A,0x3A,0x3B,0x3B,0x3B,0x3B,0x3B,
      0x3B,0x3B,0x39,0x38,0x38,0x39,0x39,0x39,
      0x39,0x38,0x38,0x38,0x3E,0x3F,0x3F,0x3F,
      0x3F,0x3E,0x3E,0x31,0x39,0x39,0x30,0x34,
      0x3E,0x3F,0x3F,0x3F,0x3F,0x3B,0x3A,0x33,
      0x33,0x31,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
#endif