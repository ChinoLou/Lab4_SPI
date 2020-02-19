/*
 * File:   Lab4_SPI_Serial.X
 * Author: Josue Castillo Lou
 * Carné:  17169
 * LAB3:   SPI + USART PIC MASTER!!!
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
#include <pic16f887.h>  
#include "SPI_Lib.h"            //Librería para la comunicación SPI 

#define _XTAL_FREQ 4000000      // 4MHz

//------- Definición de Variables Globales ----// 
int POT1;
int POT2;
int count;

//------- Prototipos de Funciones ------------// 
void init_serial(void);
void init_config(void);


void main(void) {
    init_serial();
    init_config();

    // Loop infinito
    while(1){
       
       spiWrite(1);
       POT1 = spiRead();
       __delay_ms(5);
       spiWrite(0);
       POT2 = spiRead();
       __delay_ms(5);

        TXREG = POT1;
        while (PIR1bits.TXIF == 0){   
        }
        
        TXREG = POT2;
        while (PIR1bits.TXIF ==0){  
        }
        
        count = RCREG;
        PORTB = count;                  //Muestra en el PORTB el decimal enviado desde la PC
   
    }
    return;
  
}


void init_serial(void){
    // Configuración del serial
    TXSTAbits.SYNC = 0;     //Modo Asincrono
    TXSTAbits.BRGH = 1;
    TXSTAbits.TXEN = 1;     //habilitamos la transmisión de datos 
    
    BAUDCTLbits.BRG16 = 1;  //8 BITS BAURD RATE GENERATOR
    SPBRG = 103;
    SPBRGH = 0;
    
    RCSTAbits.SPEN = 1;     //habilitamos recibir datos
    RCSTAbits.RX9  = 0;     //8 bits
    RCSTAbits.CREN = 1;     //habilitamos la recepción de datos
    
    PIE1bits.RCIE = 1;      //Habilitamos la recepcion global
    PIR1bits.RCIF = 0;      
}

void init_config(void){
    
    TRISB  = 0x00;         //PORTB como salida para los 8 leds
    TRISC  = 0b00010000;   //SDO Desabilitado cofigurando RC5 como entrada! 
    ANSEL  = 0;            //Ninguna entrada analógia en el Master
    ANSELH = 0;            
                
    PORTB = 0;             //Inicializamos los puertos utilizados 
    PORTC = 0;  

    ADCON1 = 0;
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    
   }

