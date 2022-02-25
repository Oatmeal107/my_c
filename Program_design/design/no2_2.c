#include<stdio.h>
#include<stdlib.h>

struct Student  //���ڴ������ݹ�����̬����Ľṹ��
{
    long num;
    float score;
    struct Student*next;
};

int n=0;//nΪȫ�ֱ���¼���ѧ��������������������ʹ��
char enter;//���ջس�����������Ĳ�����

struct Student * creat(void)//���庯�����˺�������һ��ָ������ͷ��ָ��
{
    struct Student *head;
    struct Student *p1,*p2;
    n= 0;                                      //malloc����*voidδȷ�����͵�ָ�룬���Ա�ǿ��ת��Ϊ��������ָ��
    p1=p2=(struct Student*)malloc(sizeof(struct Student));//���ٵ�һ���µ�Ԫ malloc:���䳤��Ϊ�����ֽڵ��ڴ��
    scanf("%ld,%f",&p1->num,&p1->score);//�����һ��ѧ����ѧ�źͳɼ�
    head = NULL;
    while(p1->num!=0)
    {
        n++;
        if(n==1)   //ȷ��ͷ��ָ��
            head=p1;
        else
            p2->next=p1;  //�������
        p2=p1;
        p1=(struct Student *)malloc(sizeof(struct Student));
        scanf("%ld,%f%c",&p1->num,&p1->score,&enter);//��������ѧ����ѧ�źͳɼ�
    }
    p2->next=NULL;
    return(head);
}

//����print����
void print(struct Student * head)
{
    struct Student *p;
    
    p=head;
    if(head!=NULL&&n>0)
    {
        printf("\n¼��� %d ��ͬѧ��ѧ�źͷ�����:\n",n);
        do
        {
            printf("%ld %5.1f\n",p->num,p->score);
            p=p->next;
        } 
        while (p!=NULL);
    }
    else
    {
        printf("û�����ݣ����Ƚ������ݱ�\n");
    }
    
}

void ui()
{
    printf("��ѡ��������еĲ�����\n1.����ѧ��ѧ�ųɼ���\n2.ɾ��ѧ���ɼ�\n3.�鿴ѧ���ɼ���\n4.��������\n");
}

//ɾ������
struct Student * Delete(struct Student * head)
{
    struct Student *p,*q;
    long num;

    if(head==NULL||n<1)
    {
        printf("����Ϊ�ա�\n");
        return (head);
    }
    int boo = 0;//�ж��Ƿ��һλ��ɾ��
    printf("������Ҫɾ����ѧ����ѧ�ţ�");
    scanf("%ld%c",&num,&enter);
    for(p=head->next,q=head;p!=NULL;p=p->next,q=q->next)
    {
        if(q==head)
        {
            if(q->num==num)
            {
                head = q->next;
                boo = 1;
            }
        }
        if(p->num==num)
        {
            q->next=p->next;
            boo = 1;   
        }
    }
    if(q==NULL||boo==0)
        printf("Ҫɾ����ѧ�������ڡ�\n");
    else
    {
        printf("ɾ���ɹ���\n");
        n--;
    }
    free(p);
    return (head);
}

int main()
{
    struct Student *head = NULL;
    while(1)
    {
        ui();
        char menu;
        scanf("%c%c",&menu,&enter);
        switch (menu)
        {
        case '1':
            printf("�밴�˸�ʽ���룺ѧ��,����(��0��0��������)\n");
            head = creat();//�������������һ�����ĵ�ַ
            break;
        case '2':
            head = Delete(head);
            break;
        case '3'://�鿴�ɼ�
            print(head);
            break;
        case '4':
            printf("��л����ʹ�ã��ټ���");
            return 0;
        default:
            printf("������ĸ�ʽ��������������!\n");
            break;
        }
    }
} 

