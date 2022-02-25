#include<stdio.h>
#include<string.h>

void rleZip(FILE *fp, FILE *rlep)
{
    int len;//�����ظ����ֵĴ���
	char c, equal;//����ÿ�λ�ȡ���ַ������ڱȽϵ��ݴ��
	c=fgetc(fp);   //ȡ���ļ���һ���ַ�
	equal=c;   //����һ���ַ���ֵ��equal
	len=1;   //�ַ��������ִ��������ȳ�ʼ��Ϊ1
	while(!feof(fp))
	{
		c=fgetc(fp);   // ȡ���ļ�����һ���ַ�
		if(c==equal)     // �ļ���һ���ַ��Ƿ��뵱ǰ�ַ����
		    len++;            // ������������ȼ�һ
		else
		{
			fputc(len,rlep);
			fputc(equal,rlep); // ����ȣ�����������ĳ��ȺͶ�Ӧ�ַ�
			equal=c;       // ������ȵĵ�һ���ַ���ֵ��seq����ʼ�´γ��ȼ���
			len=1;              // ���ȹ���һ
		}
	}
}

void unzip(FILE *rlep,FILE *fp)
{
	int len,i;
	char c;
	while(!feof(rlep))		   
	{
		len=fgetc(rlep);//��ȡ�ַ����ֵĴ���
		c=fgetc(rlep);  //��ȡ��Ҫ�ظ����ַ�
		for(i=0;i<len;i++)
			fputc(c,fp);//ѭ�������ǰ�ַ�
	}
}

int main(int argc, char *argv[])
{
    char *func1 = "-c";//ѹ������
    char *func2 = "-d";//��ѹ������
    if(strcmp(argv[2], func1)==0)
    {
        FILE *fp = fopen(argv[1], "rb");//����Ҫѹ�����ļ�
        if (fp == NULL)
        {
            printf("�޷����ļ���");
		    return 0;
        }
        FILE *rlep = fopen(argv[3], "wb");//�½�����ѹ�����ݵ��ļ�
        rleZip(fp, rlep);
        printf("ѹ���ɹ���");
    }
    else if(strcmp(argv[2], func2)==0)
    {
        FILE *rlep = fopen(argv[1], "rb");//����Ҫ��ѹ���ļ�
        if (rlep == NULL)
        {
            printf("�޷����ļ���");
		    return 0;
        }
        FILE *fp = fopen(argv[3], "wb");//�½��ļ��洢��ѹ����ļ�
        unzip(rlep, fp);
        printf("��ѹ�ɹ���");
    }
    else
    {
        printf("������ĸ�ʽ�������������룡");
        return 0;
    }
    return 0;
}

