#include<stdio.h>

void putStack(int stack[16], int head)  //����ÿ�β������������ջ��Ԫ��
{
    if(head==0)
        printf("ջ��û��Ԫ�ء�");
    else
    {
        printf("ջ��Ԫ�أ�");
        for(int i = head-1; i>=0; i--)
            printf("%d ",stack[i]);
    }
    printf("\n");
}

int main()
{
    void putStack(int stack[16], int head);
    int stack[16];//����һ��������Ϊջ
    int head = 0;//��¼ջ��λ��
    char function;//��¼ѡ��Ĺ���
    char receiver;//������������Ļس�
    while(1)
    {
        printf("������������еĲ�����ţ�\n1.������ջ��\n2.���г�ջ��\n3.����ջ��Ԫ�ء�\n4.��������\n");
        scanf("%c%c",&function,&receiver);
        switch (function)
        {
        case '1':
            if(head==16)
            {
                printf("ջ�������޷��������Ԫ�أ�\n");
                break;
            }
            else
            {
                printf("��������ջ��Ԫ��(����)��");
                scanf("%d%c",&stack[head],&receiver);
                head++;
                break;
            }
        case '2':
            if(head==0)
            {
                printf("ջ�ѿգ��޷�����ȡ��Ԫ�أ�\n");
                break;
            }
            else
            {
                printf("ȡ��Ԫ�أ�%d\n",stack[head-1]);
                head--;
                break;
            }
        case '3':
            if(head>0)
            {
                printf("ջ��Ԫ���ǣ�%d\n",stack[head-1]);
                break;
            }
            else
            {
                break;
            }
        case '4':
            printf("�ټ���");
            return 0;
        default:
            printf("�����ʽ�������������룡\n");
            break;
        }
        putStack(stack,head);
    }
}

