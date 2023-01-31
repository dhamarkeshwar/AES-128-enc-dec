//
//  padding PKCS #7.c
//  AES
//
//  Created by S Dheeraj Kumar on 19/01/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//char *data={"Hi! I'm S Dheeraj Kumar...."};

static uint8_t array[][16];

static int n_blocks;

static void split_text_into_array_with_nonce(int size,char *text)
{
    n_blocks=(size +16-(size%16))/16+1;
    for(int i=0;i<16;++i)
        array[0][i]=rand()%256;
    for(int i=1;i<n_blocks-1;++i)
        for(int j=0;j<16;++j)
            array[i][j]=text[(i-1)*16+j];
    if (size%16!=0)
    {
        for(int i=0;i<size%16;++i)
            array[n_blocks-1][i]=text[(n_blocks-2)*16+i];
        for(int i=size%16;i<16;++i)
            array[n_blocks-1][i]=16-size%16;
    }
    else
        for(int j=0;j<16;++j)
            array[n_blocks-1][j]=text[(n_blocks-1)*16+j];
}

//static __uint128_t arr_text[];


//static void split_text(int size,char text[])
//{
//    for(int i=0;i<size;++i)
//        *(arr_text+i)=text[i];
//    for(int i=size;i<size+16-size%16;++i)
//        *(arr_text+i)=16-size%16;
//    n=(size +16-(size%16))/16
//    struct text_arr arr_text[n];
//    for (i=0;i<size)
//}

//struct text_arr{
//    uint8_t arr[16];
//    int size;
//};
//
//static struct text_arr arr_text[];
//
//static int n_blocks;
//
//static void split_text_into_array_with_nonce(int size,char text[])
//{
//    n_blocks=(size +16-(size%16))/16+1;
//    for(int i=0;i<16;++i)
//        arr_text[0].arr[i]=rand()%256;
//    for(int i=1;i<n_blocks-1;++i)
//        for(int j=0;j<16;++j)
//            arr_text[i].arr[j]=text[(i-1)*16+j];
//    if (size%16!=0)
//    {
//        for(int i=0;i<size%16;++i)
//            arr_text[n_blocks-1].arr[i]=text[(n_blocks-2)*16+i];
//        for(int i=size%16;i<16;++i)
//            arr_text[n_blocks-1].arr[i]=16-size%16;
//    }
//    else
//        for(int j=0;j<16;++j)
//            arr_text[n_blocks-1].arr[j]=text[(n_blocks-1)*16+j];
//}

//static void split_text_into_array(int size,char text[])
//{
//    n_blocks=(size +16-(size%16))/16;
//    for(int i=0;i<n_blocks-1;++i)
//        for(int j=0;j<16;++j)
//            arr_text[i].arr[j]=text[i*16+j];
//    if (n_blocks%16!=0)
//    {
//        for(int i=0;i<size%16;++i)
//            arr_text[n_blocks-1].arr[i]=text[(n_blocks-1)*16+i];
//        for(int i=size%16;i<16;++i)
//            arr_text[n_blocks-1].arr[i]=16-size%16;
//    }
//    else
//        for(int j=0;j<16;++j)
//            arr_text[n_blocks-1].arr[j]=text[(n_blocks-1)*16+j];
//}

//static void split_text_into_array(int size,char text[])
//{
//    int n=(size +16-(size%16))/16;
////    struct text_arr arr_text[n];
//    for(int i=0;i<n-1;++i)
//        for(int j=0;j<16;++j)
//            arr_text[i].arr[j]=text[i*16+j];
//    if (n%16!=0)
//    {
//        for(int i=0;i<size%16;++i)
//            arr_text[n-1].arr[i]=text[(n-1)*16+i];
//        for(int i=size%16;i<16;++i)
//            arr_text[n-1].arr[i]=16-size%16;
//    }
//    else
//        for(int j=0;j<16;++j)
//            arr_text[n-1].arr[j]=text[(n-1)*16+j];
////    for(int i=0;i<n;++i)
////        for(int j=0;j<16;++j)
////            printf("%x is element\n",arr_text[i].arr[j]);
//}


//#final_test_case
//char text[]="Hello!";
//
//split_text_into_array_with_nonce(sizeof(text)/sizeof(text[0]),text);
//
//for(int i=0;i<(sizeof(text)/sizeof(text[0]) +16-((sizeof(text)/sizeof(text[0]))%16))/16+1;++i)
//{
//    printf("The row is %d\n",i);
//    for(int j=0;j<16;++j)
//        printf("%x\n",arr_text[i].arr[j]);
//}

//#test case for array of arrays

//char text[]="Hello! 12rhershfshufgfdshfdkniong sdgb kjbfawebf/kdnvkabg";
//
//split_text_into_array(sizeof(text)/sizeof(text[0]),text);
//
//for(int i=0;i<(sizeof(text)/sizeof(text[0]) +16-(sizeof(text)/sizeof(text[0])%16))/16;++i)
//{
//    printf("The row is %d\n",i);
//    for(int j=0;j<16;++j)
//        printf("%x\n",arr_text[i].arr[j]);
//}


//#test case for array

//char ch[]={"Hi!!haqsi1234"};
//
//
//
//split_text(sizeof(ch)/sizeof(ch[0]),ch);
//
//for(int i=0;i<sizeof(ch)/sizeof(ch[0])+16-sizeof(ch)/sizeof(ch[0]);++i)
//    printf("asc %x with index %d\n",*(arr_text+i),i);


//last test case
//split_text_into_array_with_nonce(sizeof(text)/sizeof(text[0]),text);
//
//for(int i=0;i<n_blocks;++i)
//{
////        printf("The row is %d\n",i);
//    for(int j=0;j<16;++j)
//        printf("%x",array[i][j]);
//}
//
//printf("pause\n");
//
//CBC_encrypt(sizeof(text)/sizeof(text[0]), text);
//for(int i=0;i<n_blocks;++i)
//{
////        printf("The row is %d\n",i);
//    for(int j=0;j<16;++j)
//        printf("%x",array[i][j]);
//}
//
//printf("paause\n");
//
//for(int i=0;i<n_blocks;++i)
//    for(int j=0;j<16;++j)
//    {
//        text[i*16+j]=array[i][j];
//        printf("%c",text[i*16+j]);
//    }
//
//printf("pause\n");
//
//CBC_decrypt(array);
//
//for(int i=0;i<n_blocks;++i)
//{
////        printf("The row is %d\n",i);
//    for(int j=0;j<16;++j)
//        printf("%x",array[i][j]);
//}
//
//printf("pause\n");
//
//for(int i=1;i<n_blocks;++i)
//    for(int j=0;j<16;++j)
//    {
//        text[i*16+j]=array[i][j];
//        printf("%c",text[i*16+j]);
//    }
//
//
//
