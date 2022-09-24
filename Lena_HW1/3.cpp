#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<Windows.h>

int main()
{
    char RawFileName[30] = "raw_image.raw";
    char InFileName[30] = "lena_bmp_512x512_new.bmp";
    char OutFileName[30] = "new_raw_image.bmp";
    const int width = 512;
    FILE* infile;
    FILE* rawfile;
    infile = fopen(InFileName, "rb");
    rawfile = fopen(RawFileName, "rb");
    BITMAPFILEHEADER HF;
    BITMAPINFOHEADER IF;
    RGBQUAD hRGB[256];
    fread(&HF, sizeof(BITMAPFILEHEADER), 1, infile);
    fread(&IF, sizeof(BITMAPINFOHEADER), 1, infile);
    fread(hRGB, sizeof(RGBQUAD), 256, infile);
    BYTE* lpImg = new BYTE[IF.biSizeImage];
    fread(lpImg, sizeof(char), IF.biSizeImage, rawfile);
    unsigned char temp = 0;
    for (int i = 0; i < 256; i++) 
    {
        for (int j = 0; j < 512; j++)
        {
            temp = lpImg[(i * 512) + j];
            lpImg[(i * 512) + j] = lpImg[((511 * 512) - (i * 512)) + j];
            lpImg[((511 * 512) - (i * 512)) + j] = temp;
        }
    }
    [출처] C언어 Gray Scale image& Bitmap& raw File 다루기 | 작성자 jinu0124
    FILE* outfile = fopen(OutFileName, "wb");
    fwrite(&HF, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);
    fwrite(&IF, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);
    fwrite(hRGB, sizeof(RGBQUAD), 256, outfile); 
    fwrite(lpImg, sizeof(char), IF.biSizeImage, outfile);
    fclose(outfile);
    return 0;
}﻿