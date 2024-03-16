// @File		AD5204.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		16/03/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//

#ifndef AD5204_H
#define AD5204_H

#define AD5204_SCK PORTCbits.RC0
#define AD5204_DIN PORTCbits.RC1
#define AD5204_CS PORTCbits.RC3

#define AD5204_SCK_TRIS TRISCbits.RC0
#define AD5204_DIN_TRIS TRISCbits.RC1
#define AD5204_CS_TRIS TRISCbits.RC3

// B10: A2
// B9: A1
// B8: A0
// B7: DATA BIT7
// B6: DATA BIT6
// B5: DATA BIT5
// B4: DATA BIT4
// B3: DATA BIT3
// B2: DATA BIT2
// B1: DATA BIT1
// B0: DATA BIT0
void SPI_transfer(unsigned int data)
{     
    for(unsigned int mask = 0x400; mask; mask >>= 1)
    {
        if(data & mask) AD5204_DIN = 1; else AD5204_DIN = 0;
            
         __asm__ __volatile__("nop");
         AD5204_SCK = 1;
         __asm__ __volatile__("nop");
         AD5204_SCK = 0;
         __asm__ __volatile__("nop");    
    }
}

void AD5204_Write(unsigned char chan, unsigned int value)
{
    value |= (unsigned int)(chan << 8);
    
    AD5204_CS = 0;
    SPI_transfer(value);
    AD5204_CS = 1;
}

void AD5204_Init(void)
{
    AD5204_SCK_TRIS = 0;
    AD5204_DIN_TRIS = 0;
    AD5204_CS_TRIS = 0;
    
    AD5204_CS = 1;
}

#endif 
