#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

int main()
{
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	RGBQUAD bmpColorTable[256];
	BYTE bmpValue[512 * 512];
	FILE *fp;

	fp = fopen("d:/1.bmp", "rb");
	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);//����
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(bmpColorTable, sizeof(RGBQUAD), 256, fp);
	fread(bmpValue, 1, 512 * 512, fp);	
	
	//��ͼ��Ҷ�ֵ����һλ������
	int grayValue[512 * 512] = { 0 };
	for (int i = 0; i < 512 * 512; i++)
	{
		grayValue[i] = bmpColorTable[bmpValue[i]].rgbBlue;
	}

	//ֱ��ͼ
	int grayCount[256] = { 0 };
	double grayFrequency[256] = { 0.0 };
	for (int i = 0; i < 512 * 512; i++)
	{
		grayCount[grayValue[i]]++;
	}
	for (int i = 0; i < 256; i++){
		if (grayCount[i]){
			grayFrequency[i] = grayCount[i] / (512.0*512.0);
			printf("�Ҷ�ֵ:%3d Ƶ��:%6d Ƶ��:%f\n", i, grayCount[i], grayFrequency[i]);
		}	
	}

	//���ֵ
	int grayMax = 0;
	for (int i = 0; i < 256; i++){
		if (grayCount[i] && (i > grayMax)){
			grayMax = i;
		}
	}
	printf("���Ҷ�ֵ: %d\n", grayMax);

	//��Сֵ
	int grayMin = 255;
	for (int i = 0; i < 256; i++){
		if (grayCount[i] && (i < grayMin)){
			grayMin = i;
		}
	}
	printf("��С�Ҷ�ֵ: %d\n", grayMin);
  

	printf("�ļ���С: %d �ֽ�\n", bmpFileHeader.bfSize);

	printf("ͼ��Ŀ��: %d\n", bmpInfoHeader.biWidth);
	printf("ͼ��ĸ߶�: %d\n", bmpInfoHeader.biHeight);
	printf("ÿ�����ص�λ��: %d\n", bmpInfoHeader.biBitCount);
	printf("��ɫ����ʵ��ʹ�õ���ɫ��: %d\n", bmpInfoHeader.biClrUsed	);
	printf("��ʵλͼʱ����ʹ�õ���ɫ��: %d\n", bmpInfoHeader.biClrImportant);
	fclose(fp);
	return 0;

}