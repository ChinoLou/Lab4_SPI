 /*
 * File            : spi.c
 * Author          : Ligo George
 * Company         : electroSome
 * Project         : SPI Library for MPLAB XC8
 * Microcontroller : PIC 16F877A
 * Created on April 15, 2017, 5:59 PM
 */

#include <xc.h>
#include "SPI_Lib.h"

void spiInit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
  TRISC5 = 0;
  if(sType & 0b00000100) //If Slave Mode
  {
    SSPSTAT = sTransmitEdge;
    TRISC3 = 1;
  }
  else //If Master Mode
  {
    SSPSTAT = sDataSample | sTransmitEdge;
    TRISC3 = 0;
  }
  SSPCON = sType | sClockIdle;
}


static void spiReceiveWait()
{
  while ( !SSPSTATbits.BF ); // Wait for Data Receipt complete
}


void spiWrite(char dat) //Write data to SPI bus
{
  SSPBUF = dat;
}


unsigned spiDataReady() //Check whether the data is ready to read
{
  if(SSPSTATbits.BF)
    return 1;
  else
    return 0;
}


char spiRead()    // Read the received data
{
  spiReceiveWait();      // Wait until all bits receive
  return(SSPBUF); // Read the received data from the buffer
}


