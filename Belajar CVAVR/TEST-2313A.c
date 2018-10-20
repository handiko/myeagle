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


Chip type               : ATtiny2313
AVR Core Clock frequency: 10.000000 MHz
Memory model            : Tiny
External RAM size       : 0
Data Stack size         : 32
*****************************************************/

#include <tiny2313.h>
#include <stdint.h>
#include <delay.h>

#define RESET   PORTD.2
#define DATA    PORTD.3
#define FQ_UD   PORTD.4
#define W_CLK   PORTD.5

//#define DELAY   ; //delay_us(1);

#define MHZ     1000000.0

#define AD9850_125      0
#define AD9851_30       1
#define AD9851_180      2

#define DDS_TYPE        AD9851_180

#if     DDS_TYPE == AD9850_125
#define TUNING_RATIO    34.35973837
#define PH_WORD         0x00

#elif   DDS_TYPE == AD9851_30
#define TUNING_RATIO    143.1655765
#define PH_WORD         0x00

#else
#define TUNING_RATIO    23.86092942
#define PH_WORD         0x01
#endif

//eeprom unsigned long set_freq=12345678;
float set_freq=9.65*MHZ;

void reset_dds(void);
void init_dds(void);
void write_freq(void);

void reset_dds(void)
{
        DATA=0;
        W_CLK=0;
        FQ_UD=0;
        RESET=1;
        //DELAY;
        RESET=0;
}

void init_dds(void)
{
        reset_dds(); 
        
        W_CLK=1;
        //DELAY;
        W_CLK=0;
        //DELAY;
        
        FQ_UD=1;
        //DELAY;
        FQ_UD=0;
        //DELAY;
        
        write_freq();
}

void write_freq(void)
{
        char i=0;                                
        
        uint32_t data_word = set_freq*TUNING_RATIO; 
        
        for(i=0;i<32;i++)
        {
                DATA=(data_word & 0x01);
                data_word >>= 1;
                
                //DELAY;
                W_CLK=1;
                //DELAY;
                W_CLK=0;
        }
               
        #if     DDS_TYPE == AD9851_180  
                
                DATA=1;   
                
                //DELAY;
                W_CLK=1;
                //DELAY;
                W_CLK=0;   
                
                DATA=0;
                
                for(i=0;i<7;i++)
                {
                        //DELAY;
                        W_CLK=1;
                        //DELAY;
                        W_CLK=0;
                }
        
        #else
                for(i=0;i<8;i++)
                {
                        DATA=0;
                        
                        //DELAY;
                        W_CLK=1;
                        //DELAY;
                        W_CLK=0;
                }
        #endif
        
        FQ_UD=1;
        //DELAY;
        FQ_UD=0;
        //DELAY;      
        DATA=0;
}

void main(void)
{
#pragma optsize-
        CLKPR=0x80;
        CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif 
 
        PORTB=0x00;
        DDRB=0x00;
 
        PORTD=0x00;
        DDRD=0x7F;

        ACSR=0x80;
        DIDR=0x00;
                   
        reset_dds(); 
        init_dds();    
        write_freq();
        
        while (1)
        {
                //write_freq();
        }
}
