/*
* crc16afci.c
*
*  Created on: Jan 17, 2019
*      Author: Rahul B.
*/

//---------------------------------------------------------------
//  unsigned int crc16_ccitt(unsigned int *data_p, long len)
//  data_p - pointer to the memory
//  len    - length of the region
//
//  ALGORITHM CRC16-CCITT IEEE Standard 802.15.4
//
//  Tested on : 
//  32 Bit Processor / 16-Bit Memory Location
//  Datasize  :
//  long - 32 bit / int 16 bit / short 8-bits
//---------------------------------------------------------------

#define LOWER_BYTE(data)  (data & 0x00ff)
#define HIGHR_BYTE(data)  (data & 0xff00)>>8

#define POLY_CRC16_CCITT 0x1021

unsigned int crc16_ccitt(unsigned int *data_p, long len)
{
    // CRC16 CCITT ALGORITHM

    unsigned long crc  = 0x0000;
    unsigned long mask = 0XFFFF;

    unsigned int  data;
    unsigned long octet;

    unsigned long bit, crc_tbl;
    unsigned long high_bit = (1ul << 15);

    int idx, jdx,n;

    unsigned long term1,term2;

    for (idx = 0; idx < len; idx++)
    {
          data = *data_p++;

          for (n = 0; n < 2; n++)
          {
                 if(n==0)   octet = LOWER BYTE(data);       // LOWER BYTE
                 else       octet = HIGHR_BYTE(data)>>8;    // HIGHER_BYTE

                 term1 = (crc << 8);
                 term2 = ((crc >> 8) & 0xff) ^ octet;

                 crc_tbl = term2 << 8;
                 for (jdx = 0; jdx < 8; jdx++)
                 {
                     bit = crc_tbl & high_bit;
                     crc_tbl <<= 1;
                     if (bit) crc_tbl^= POLY_CRC16_CCITT;
                 }
                 crc_tbl &= mask;
                 crc = term1 ^ crc_tbl;
          }
    }

    return crc & mask;
}

