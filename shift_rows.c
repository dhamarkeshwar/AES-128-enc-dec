//
//  shift_rows.c
//  AES
//
//  Created by S Dheeraj Kumar on 04/01/23.
//

#include <stdio.h>

//int arr[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};


static void shift_rows(uint8_t *arr)
{
    uint8_t y[16];
    uint8_t i=0,j;
    for(j=0;j<4;++j)
        for(i=0+j;i<13+j;i+=4)
            *(y+i)=*(arr+(i+4*j)%16);
    for(i=0;i<16;++i)
        *(arr+i)=y[i];
}

static void inv_shift_rows(uint8_t *arr)
{
    for(int i=0;i<3;++i)
        shift_rows(arr);
}
