#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<Windows.h>

int main()
{
    char RawFileName[30] = "raw_image.raw";
    char InFileName[30] = "lena_bmp_512x512_new";
    char OutFileName[30] = "lena_raw_image.bmp";

    BITMAPFILEHEADER HF;
    BITMAPINFOHEADER IF;
    RGBQUAD hRGB[256];

    FILE* infile = fopen(InFileName, "rb");
    FILE* rawfile = fopen(RawFileName, "rb");
    if (infile == NULL) { printf("영상파일 없음!"); 
    return 0;
    }
    fread(&HF, sizeof(BITMAPFILEHEADER), 1, infile);
    fread(&IF, sizeof(BITMAPINFOHEADER), 1, infile);
    if (IF.biBitCount != 8) {
        printf("Bad file format!");
            return 0;
    }

    fread(hRGB, sizeof(RGBQUAD), 256, infile);

    BYTE* lpImg = new BYTE[IF.biSizeImage];
    fread(lpImg, sizeof(char), IF.biSizeImage, rawfile);
    fclose(infile);
    fclose(rawfile);
    FILE* outfile = fopen(OutFileName, "wb");
    fwrite(&HF, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);
    fwrite(&IF, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);
    fwrite(hRGB, sizeof(RGBQUAD), 256, outfile); 
    fwrite(lpImg, sizeof(char), IF.biSizeImage, outfile);
    fclose(outfile);
    return 0;
}﻿