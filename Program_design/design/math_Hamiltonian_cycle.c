#include<stdio.h>

struct point//��Ÿ����е�����
{
    char name[10];//��������
    int much[9];//�������е��÷�(��������Ϊ����)
    int reach;//�ж��Ƿ��Ѿ�ȥ����
};

int main()
{
    struct point city[9]=//�Ÿ����е�����
    {
        {"����",0,293,423,662,409,483,292,560,339,1},
        {"����",293,0,334,528,203,275,230,290,570,0},
        {"����",423,334,0,435,249,290,205,130,360,0},
        {"�人",662,528,435,0,275,360,650,133,425,0},
        {"����",409,203,249,275,0,198,70,213,300,0},
        {"����",483,275,290,360,198,0,390,349,280,0},
        {"�Ϻ�",292,230,205,650,70,390,0,303,99,0},
        {"֣��",560,290,130,133,213,349,303,0,345,0},
        {"������",339,570,360,425,300,280,99,345,0,0}
    };
    int fee1 = 0,fee2 = 0,fee3 = 0,fee4 = 0,fee5 = 0,fee6 = 0,fee7 = 0,fee8 = 0,fee9 = 0;//��¼��ǰ�ܷ���
    int minFee = 9999;//��ǰ����ܷ���
    int travel[9];//��¼�ó�
    int i,j,k,l,o,p,m,n;
    for(i = 1; i<9; i++)//�ӱ�������
    {
        fee1 = city[0].much[i];//��һ�η��ü��㣬���Ǵӱ���������
        city[i].reach=1;
        for(j = 0; j<9; j++)//���ڶ�������
        {
            if(city[j].reach==1)//���Ѿ���������������ȥ
                continue;
            fee2 = fee1 + city[i].much[j];
            city[j].reach=1;
            for(k = 0; k<9; k++)//����������
            {
                if(city[k].reach==1)//���Ѿ���������������ȥ
                    continue;
                fee3 = fee2 + city[j].much[k];
                city[k].reach=1;
                for(l = 0; l<9; l++)//���ĸ�����
                {
                    if(city[l].reach==1)//���Ѿ���������������ȥ
                        continue;
                    fee4 = fee3 + city[k].much[l];
                    city[l].reach=1;
                    for(o = 0; o<9;o++)//���������
                    {
                        if(city[o].reach==1)//���Ѿ���������������ȥ
                            continue;
                        fee5 = fee4 + city[l].much[o];
                        city[o].reach=1;
                        for(p = 0; p<9; p++)//����������
                        {
                            if(city[p].reach==1)//���Ѿ���������������ȥ
                                continue;
                            fee6 = fee5 + city[o].much[p];
                            city[p].reach=1;
                            for(m = 0; m<9; m++)//���߸�����
                            {
                                if(city[m].reach==1)//���Ѿ���������������ȥ
                                    continue;
                                fee7 = fee6 + city[p].much[m];
                                city[m].reach=1;
                                for(n = 0; n<9; n++)
                                {
                                    if(city[n].reach==1)//���Ѿ���������������ȥ
                                        continue;
                                    fee8 = fee7 + city[m].much[n];
                                    fee9 = fee8 + city[n].much[0];//���ر����ķ���
                                    if(minFee>fee9)//���˴η��ñȼ�¼��·�̷��ø���ʱ���޸����Ž�
                                    {
                                        minFee = fee9;
                                        travel[1] = i;//��¼·��
                                        travel[2] = j;
                                        travel[3] = k;
                                        travel[4] = l;
                                        travel[5] = o;
                                        travel[6] = p;
                                        travel[7] = m;
                                        travel[8] = n;
                                    }
                                    fee8 = 0;
                                    fee9 = 0;
                                }
                                fee7 = 0;
                                city[m].reach=0;//��һ��ѭ��ǰ��׼��
                            }
                            fee6 = 0;
                            city[p].reach=0;
                        }
                        fee5 = 0;
                        city[o].reach=0;
                    }
                    fee4 = 0;
                    city[l].reach=0;   
                }
                fee3 = 0;
                city[k].reach=0;
            }
            fee2 = 0;
            city[j].reach=0;
        }
        fee1 = 0;
        city[i].reach=0;
    }
    printf("����·���ǣ�����");
    for(i = 1; i<9; i++)
    {
        printf("-");
        for(l = 0; l<10; l++)
        {
            if(city[travel[i]].name[l]==0)
                break;
            printf("%c",city[travel[i]].name[l]);

        }
    }
    printf("-����\n");
    printf("�ܻ��ѣ�%d",minFee);
    return 0;
}

