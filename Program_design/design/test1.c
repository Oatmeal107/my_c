#include <stdio.h>
#include <stdlib.h>
 
/* ����WORDΪ�����ֽڵ����� */
typedef unsigned short WORD;
/* ����DWORDΪ�ĸ��ֽڵ����� */
typedef unsigned long DWORD;
 
/* λͼ�ļ�ͷ��Ҫ�Ƕ�λͼ�ļ���һЩ���� λͼ��Ϣͷ��Ҫ�Ƕ�λͼͼ������Ϣ������ */
/*************************** λͼ��׼��Ϣ(54�ֽ�) ******************************************/
/* λͼ�ļ�ͷ ��λͼͷ���ֽ��� = λͼ�ļ��ֽ��� - λͼͼ�������ֽ�����*/
typedef struct tagBITMAPFILEHEADER {
  unsigned short bfType;   // 19778��������BM�ַ�������Ӧ��ʮ������Ϊ0x4d42,ʮ����Ϊ19778
  unsigned int bfSize;    // �ļ���С
  unsigned short bfReserved1; // һ��Ϊ0
  unsigned short bfReserved2; // һ��Ϊ0
  unsigned int bfOffBits;   // ���ļ�ͷ���������ݵ�ƫ�ƣ�Ҳ��������
} BITMAPFILEHEADER;
 
/* λͼ��Ϣͷ */
typedef struct tagBITMAPINFOHEADER {
  unsigned int biSize;    // �˽ṹ��Ĵ�С
  int biWidth;        // ͼ��Ŀ�
  int biHeight;        // ͼ��ĸ�
  unsigned short biPlanes;  // 1
  unsigned short biBitCount; // һ������ռ��λ����һ��Ϊ24
  unsigned int biCompression; // 0
  unsigned int biSizeImage;  // ����������ռ��С, ���ֵӦ�õ��������ļ�ͷ�ṹ��bfSize-bfOffBits
  int biXPelsPerMeter;    // 0
  int biYPelsPerMeter;    // 0
  unsigned int biClrUsed;   // 0 
  unsigned int biClrImportant;// 0
} BITMAPINFOHEADER;
 
/* ��ɫ��:��ɫ�� */
typedef struct RGB_QUAD 
{
	WORD rgbBlue;     // ��ɫǿ�� 
	WORD rgbGreen;    // ��ɫǿ�� 
	WORD rgbRed;      // ��ɫǿ�� 
	WORD rgbReversed; // ����ֵ 
} RGBQUAD;
 
 
int main()
{
	int i = sizeof(BITMAPFILEHEADER);
	int j = sizeof(long);
	FILE *fp;                     // ����һ���ļ�ָ��
	BITMAPFILEHEADER bmpFileHeader;  // ����һ�� BMP �ļ�ͷ�Ľṹ��
    #pragma pack(1);
	BITMAPINFOHEADER bmpInfo;               // ����һ�� BMP �ļ���Ϣ�ṹ�� 
 
 
	// "rb" ֻ����һ���������ļ���ֻ��������ݡ�'b'ָ����������⺯���Զ�������ʽ�򿪴��ļ���
	// ��ȡʧ�ܻ᷵�ؿ�ָ�룬��ȡ�ɹ���fp ��ָ��һ����� bmp ���Ե��ڴ�,���ǿ��Զ�����ڴ濪ʼ����
	if((fp = fopen("d:/1.bmp", "rb")) == NULL) // fp = 0x00426aa0
	{
		printf("Cann't open the file!\n");
		return 0;
	}
 
	// �� fp ָ�� bmp �ļ��Ŀ�ʼ 
	// �� 2 ��������ƫ���� �������������ļ���ʼ��ַ ���Դ˺���ִ�гɹ����ļ�ָ���ָ���ļ��Ŀ�ʼ
	fseek(fp, 0, SEEK_SET);                            // fp = 0x00426aa0
 
	// ��ȡ�ļ���Ϣ
	/*
		����1: �������ݵĴ�Ż�����
		����2: ��ȡ���ٸ��ֽڵ�����
		����3: ��ȡ��������������
		����4: �ļ�ָ�루Դ���ݣ�
	*/
	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp); 
	
	fread(&bmpInfo, sizeof(bmpInfo), 1, fp);
 
 
	// ���BMP�ļ���λͼ�ļ�ͷ��������Ϣ
	printf("λͼ�ļ�ͷ��Ҫ�Ƕ�λͼ�ļ���һЩ����:BMPFileHeader\n\n");
	printf("�ļ���ʶ�� = 0X%X\n", bmpFileHeader.bfType);
	printf("BMP �ļ���С = %d �ֽ�\n", bmpFileHeader.bfSize);
	printf("����ֵ1 = %d \n", bmpFileHeader.bfReserved1);
	printf("����ֵ2 = %d \n", bmpFileHeader.bfReserved2);
	printf("�ļ�ͷ�����ͼ������λ��ʼ��ƫ���� = %d �ֽ�\n", bmpFileHeader.bfOffBits);
 
	// ���BMP�ļ���λͼ��Ϣͷ��������Ϣ
	printf("\n\nλͼ��Ϣͷ��Ҫ�Ƕ�λͼͼ������Ϣ������:BMPInfo\n\n");
	printf("��Ϣͷ�Ĵ�С = %d �ֽ�\n", bmpInfo.biSize);
	printf("λͼ�ĸ߶� = %d \n", bmpInfo.biHeight);
	printf("λͼ�Ŀ�� = %d \n", bmpInfo.biWidth);
	printf("ͼ���λ����(λ�����ǵ�ɫ�������,Ĭ��Ϊ1����ɫ��) = %d \n", bmpInfo.biPlanes); 
	printf("ÿ�����ص�λ�� = %d λ\n", bmpInfo.biBitCount);
	printf("ѹ������ = %d \n", bmpInfo.biCompression);
	printf("ͼ��Ĵ�С = %d �ֽ�\n", bmpInfo.biSizeImage);
	printf("ˮƽ�ֱ��� = %d \n", bmpInfo.biXPelsPerMeter);
	printf("��ֱ�ֱ��� = %d \n", bmpInfo.biYPelsPerMeter);
	printf("ʹ�õ�ɫ���� = %d \n", bmpInfo.biClrUsed);
	printf("��Ҫ��ɫ���� = %d \n", bmpInfo.biClrImportant);
 
	printf("\n\n\nѹ��˵������0����ѹ������1��RLE 8��8λRLEѹ������2��RLE 4��4λRLEѹ����3��Bitfields��λ���ţ�");
 
	fclose(fp);
 
	while(1);
 
	return 0;
 
}