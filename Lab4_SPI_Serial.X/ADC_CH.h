/*
 * File:   ADC_CH.c
 * Author: Josue
 *
 * Created on 14 de febrero de 2020, 11:47 AM
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __ADC_CH_H
#define	__ADC_CH_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void init_ADC(uint8_t channel);
void init_serial(void);

#endif	/* XC_HEADER_TEMPLATE_H */

