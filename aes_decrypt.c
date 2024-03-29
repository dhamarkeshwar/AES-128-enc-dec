//
//  aes_decrypt.c
//  AES
//
//  Created by S Dheeraj Kumar on 11/01/23.
//

#include "aes_decrypt.h"


static int n_blocks;

static uint32_t words[44]={0x1634269b,0x46a0eac4,0x2a9cc849,0x39fd0a63,0xef26dd89,0xa986374d,0x831aff04,0xbae7f567,0x6ed2587d,0xc7546f30,0x444e9034,0xfea96553,0x8b69b5c6,0x4c3ddaf6,0x8734ac2,0xf6da2f91,0x1a2b3484,0x5616ee72,0x5e65a4b0,0xa8bf8b21,0xc7e9c946,0x91ff2734,0xcf9a8384,0x672508a5,0x816ccfc3,0x1093e8f7,0xdf096b73,0xb82c63d6,0xf70039af,0xe793d158,0x389aba2b,0x80b6d9fd,0xb8cd6d62,0x5f5ebc3a,0x67c40611,0xe772dfec,0x4059a3f6,0x1f071fcc,0x78c319dd,0x9fb1c631,0x8782642d,0x98857be1,0xe046623c,0x7ff7a40d};

static uint8_t round_key[11][16];

static void round_key_construction(void)
{
    for(int i=0;i<11;++i)
        for(int j=4*i;j<4*i+4;++i)
        {
            uint8_t y[4];
            int l=0;
            for(int k=0;k<4;++k)
                *(y+k)=words[j]>>(24-8*k);
            ++l;
            for(int k=0;k<4;++k)
                *(*(round_key+i)+(l-1)*4+k)=*(y+k);
        }
}

static const uint8_t rsbox[256] = {
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

static void inv_sub_bytes(uint8_t *arr)
{
    for(int i=0;i<16;++i)
        *(arr+i)=rsbox[*(arr+i)];
}

static uint8_t xtime(uint8_t x)
{
  return ((x<<1) ^ (((x>>7) & 1) * 0x1b));
}

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

static void inv_shift_rows(uint8_t *arr)
{
    for(int i=0;i<3;++i)
        shift_rows(arr);
}

static void inv_mixcolumns(uint8_t *arr)
{
    for(int i=0;i<3;++i)
        mix_columns(arr);
}


static void initial_decrypt(uint8_t *arr)
{
    for(int i=0;i<16;++i)
        *(arr+i)=*(arr+i)^round_key[10][i];
    
}

static void normal_decrypt_round(uint8_t *arr,int t)
{
    for(int i=0;i<16;++i)
        *(arr+i)=*(arr+i)^round_key[10-t][i];
    inv_mixcolumns(arr);
    inv_shift_rows(arr);
    inv_sub_bytes(arr);
}

static void last_decrypt_round(uint8_t *arr)
{
    for(int i=0;i<16;++i)
        *(arr+i)=*(arr+i)^round_key[0][i];
}

static void decrypt(uint8_t *arr)
{
    initial_decrypt(arr);
    for(int i=0;i<10;++i)
        normal_decrypt_round(arr,i);
    last_decrypt_round(arr);
}

static void CBC_decrypt(uint8_t arr[][16])
{
    for(int i=1;i<n_blocks;++i)
    {
        decrypt(*(arr+n_blocks-i));
        for(int j=0;j<16;++j)
            *(arr+n_blocks-i)[j]^=*(arr+n_blocks-i-1)[j];
    }
}
