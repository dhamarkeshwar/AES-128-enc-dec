//
//  mix_columns.c
//  AES
//
//  Created by S Dheeraj Kumar on 07/01/23.
//

#include <stdio.h>

static uint8_t xtime(uint8_t x)
{
  return ((x<<1) ^ (((x>>7) & 1) * 0x1b));
}

static void mix_columns(uint8_t *arr)
{
    int y[16];
    int i=0,j;
    for(j=0;j<13;j+=4)
    {
        for(i=0;i<4;++i)
            *(y+(i+j))=xtime(*(arr+(i+j)%16))^xtime(*(arr+((i+1)%4+j)%16))^*(arr+((i+1)%4+j)%16)^*(arr+((i+2)%4+j)%16)^*(arr+((i+3)%4+j)%16);
        for(i=0;i<4;++i)
            *(arr+(i+j))=*(y+(i+j));
    }

}

static void inv_mixcolumns(uint8_t *arr)
{
    for(int i=0;i<3;++i)
        mix_columns(arr);
}
