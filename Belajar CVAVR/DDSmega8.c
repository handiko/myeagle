/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.3 Standard
Automatic Program Generator
© Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 10/11/2018
Author  : Handiko Gesang
Company : SDL Labs
Comments: 


Chip type               : ATmega8
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega8.h>
#include <delay.h>
#include <stdint.h>

#define DDS_CONST   4294967296
#define SYS_CLK     180000000

eeprom uint32_t FREQ=12345678;

unsigned long calc_word(uint32_t in_freq)
{
    uint32_t data_word = (in_freq * DDS_CONST)/SYS_CLK;   
    return (unsigned long) data_word;
}

void main(void)
{
    PORTD=0x00;
    DDRD=0xFF;
    
    ACSR=0x80;
    SFIOR=0x00;
    
    while (1)
    {
        calc_word(FREQ);
    }
}
