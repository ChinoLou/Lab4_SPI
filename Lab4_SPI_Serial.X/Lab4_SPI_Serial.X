/*
 * File:   Lab4_SPI_Serial.X
 * Author: Josue Castillo Lou
 * Carné:  17169
 * LAB3:   SPI + USART
 * Created on 14 de febrero de 2020, 11:21 AM
 */

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
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

#define _XTAL_FREQ 4000000      // 4MHz


//------- Definición de Variables Globales ----// 


//------- Definición de Variables Globales ----// 
void init_serial(void);


void main(void) {
    return;
}


void init_serial(void){
    // Configuración del serial
    
    TXSTAbits.SYNC = 0;   //asincrono
    TXSTAbits.BRGH = 1;  
    BAUDCTLbits.BRG16 = 1;  //8 BITS BAURD RATE GENERATOR
    SPBRG = 103;
    SPBRGH = 0;
    
    RCSTAbits.SPEN = 1;     //habilitamos recibir datos
    RCSTAbits.RX9 = 0;      //8 bits
    RCSTAbits.CREN = 1;     //habilitamos la recepción de datos
    
    TXSTAbits.TXEN = 1;     //habilitamos la transmisión de datos 
}