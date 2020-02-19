/*
 * File:   Lab4_SPI_Serial.X
 * Author: Josue Castillo Lou
 * Carné:  17169
 * LAB3:   SPI + USART PIC SLAVE!!!
 * Created on 14 de febrero de 2020, 11:21 AM
 */

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

//-------- Librerías a utilizar ---------------//  
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "ADC_CH.h"             //Librería del cambio del ADC   
#include "SPI_Lib.h"            //Librería para la comunicación SPI 

#define _XTAL_FREQ 4000000      // 4MHz

//------- Definición de Variables Globales ----// 
int selector;   //variabe para SPI
int VOLT1;
int VOLT2;

// Código de Interrupción 
//*****************************************************************************
void __interrupt() isr(void){
   if(PIR1bits.SSPIF == 1){
        selector = spiRead();
        if (selector == 1 ){
            spiWrite(VOLT1);
        }
        else{
            spiWrite(VOLT2);
        }
        SSPIF = 0;
        
    }
}

//------- Prototipos de Funciones ------------// 
void init_config(void);


//------------------------ Programa Principal del Slave ---------------------// 
void main(void) {
    init_config();
    
    // Loop infinito
    while(1){
   
        ADC_chanel(0);          // Seleccionamos el Canal 0 del ADC con la Libreria del ADC
        PIR1bits.ADIF = 0;
        ADCON0bits.GO = 1;       
        VOLT1 = ADRESH;
       
        __delay_ms(5);          // Delay recomendado para hacer cambio de canal
                
        ADC_chanel(1);          // Seleccionamos el Canal 1 del ADC con la Libreria del ADC
        PIR1bits.ADIF = 0;
        ADCON0bits.GO = 1;     
        VOLT2 = ADRESH;
        
        __delay_ms(5);          // Delay recomendado para hacer cambio de canal
    }
    return;
    
}


void init_config(void){ 
    TRISA = 0b00000011;         // RA0 Y RA1 como entradas
    ANSEL = 0b00000011;         // AN0 Y ANS1 como entradas analógicas asociadas a RA0 y RA1
    TRISC = 0b00011000; 

    ANSELH = 0x00;              //ANSELH deshabilitado        
    ADCON1 = 0;
    
    PORTA = 0;                  //Inicializamos los puertos utilizados 
    PORTC = 0; 
   
    INTCONbits.GIE  = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF  = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE  = 1;         // Habilitamos interrupción MSSP
    //TRISAbits.TRISA5 = 1;     // Slave Select (no usamos porque solo es 1 slave)
   
    spiInit(SPI_SLAVE_SS_DIS, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
 
   }