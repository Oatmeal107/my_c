#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	FILE *fp1, *fp2;
	char c;//�洢ÿһ�ζ������ַ� 
    int lineNum = 1;//��ӵ��к�
	fp1 = fopen("d:/test.c", "r");//����Ҫ���ĵĲ����ļ�
	fp2 = fopen("d:/test1.c", "w");//�½�һ���ļ��洢	 
	while(!feof(fp1))//�����ȡ�ַ�
    {   
		c = fgetc(fp1);
		if(c == EOF)
			continue;
		if(c == '/')
        {
			c = fgetc(fp1);//�������з���������������������з� 
			if(c == '/')
            {
				while(c != '\n' && c != EOF)
                {
					c = fgetc(fp1);
				}
				fputc('\n',fp2);
			}
			else//����ע�ͷ���ֻ�ǵ�����'/'���ţ����˻������ַ�
            {
				fseek(fp1, -2L, SEEK_CUR);
				c = fgetc(fp1);
				fputc(c, fp2);
			}			
		}
		else
            fputc(c,fp2);
	} 	 
	fclose(fp1);
	fclose(fp2);
    
    //��ʼ����к�
    FILE *fp3, *fp4; //�ղ���ʱ�洢���ļ� �� ���ļ�����кŲ����
    char str[110]; // �洢ÿһ���ַ�
    fp3 = fopen("d:/test1.c", "r"); //  �򿪸ղ�չ��ʱ�洢���ļ�
    fp4 = fopen("d:/test.c", "w"); // ��д�뷽ʽ����Ҫ�����ĵ��ļ�
    fgets(str, 100, fp3); // ���ļ��ж�ȡһ����Ϣ�����浽str������
    while(!feof(fp3)) 
    {
        fprintf(fp4, "%d %s", lineNum, str); //���н������
        lineNum++; // �кż�һ
        fgets(str, 100, fp3); // ��ȡ��һ��
    }
    fclose(fp3); // �ر��ļ�
    fclose(fp4);
    remove("d:/test1.c");
	printf("��ӳɹ���\n");
	return 0;
} 
