/*
����Ա����zhangyl
*/
#include<stdio.h>
#include <io.h>

int bookNumber = 1;  //ȫ�ֱ��� ��ʾͼ������
int usersNumber = 1;  //��ʾ���߱��
char enter;  //���ջ��з�

//���ͼ��ĺ���
void addBook(FILE *Book)  
{
    FILE *Book1;  //���ļ����鱾������ʱ��Ҫ�½��ļ���������Ϣ
    int judgeName = 0;  //�жϴ����Ƿ��Ѿ������
    int num = 1, readNum, readNumber;  //�鱾������  ��Ŷ������鱾����  �������鱾���
    char name[20] = {0}, readName[20] = {0};  //���ͼ������  ��ʱ��Ŷ������ַ�����
    printf("������Ҫ��ӵ�ͼ������");
    for(int i = 0; i<20; i++)  //��������ȡ����Ҫ��ӵ��鱾����
    {
        if(i==0)
            scanf("%c%c", &enter,&name[i]);
        else
            scanf("%c",&name[i]);
        if(name[i]==10)  //�����Ļ��з���Ϊ��
        {
            name[i]=0;
            break;
        }
    }  
    if(access("d:/Book.txt",F_OK)==0)  //access�����ж��ļ��Ƿ���ڣ����ڷ���ֵΪ0 ʹ�õ�ͷ�ļ�Ϊio
    {
        judgeName = 1;
        FILE *judge = fopen("d:/Book.txt", "r");  //��ȡ�����ļ��������Ƿ��Ѿ����ڴ���
        while(!feof(judge))
        {
            fscanf(judge, "%d %s %d", &readNumber, readName, &readNum); //����readName�Ѿ���ʾ��ַ������Ҫȡ��ַ��
            fscanf(judge,"\n");  //���뻻�з���׼����һ�еĶ�ȡ
            if(strcmp(name, readName)==0)  //�����Ѿ����ڴ��������ѭ��
            {
                judgeName = 2;  //Ϊ2ʱ��ʾ�Ѿ����ڴ��飬��Ҫ�½�һ���ļ���������Ϣ
                break;
            }
        }
        fclose(judge);  //�ر������ж϶��򿪵��ļ�
        bookNumber = readNumber+1;
        if(judgeName==1)
            Book = fopen("d:/Book.txt", "a");  //�ļ����� �Ҳ�������ͬ����ʱ���׷������
        else if(judgeName==2)
        {
            Book1 = fopen("d:/Book1.txt", "w");  //�½�һ���ļ��ݴ�Book�е���Ϣ������ٷ���Դ�ļ���
            Book = fopen("d:/Book.txt","r");  //ֻ����ԭ�����ļ�
        }
    }
    else
        Book = fopen("d:/Book.txt","w");  //�ļ�������ʱ�½�һ���ļ�
    if (judgeName<2)
    {  
        fprintf(Book, "%d %s %d\n", bookNumber, name, num);  //д����� ���� �����ͻ��з�
        bookNumber++; 
        fclose(Book);
    }
    else
    {
        while(!feof(Book))
        {
            fscanf(Book, "%d %s %d\n", &readNumber, readName, &readNum);
            if(strcmp(name, readName)==0)
                fprintf(Book1, "%d %s %d\n", readNumber, readName, readNum+1);  //д����� ���� ����+1�ͻ��з�
            else
                fprintf(Book1, "%d %s %d\n", readNumber, readName, readNum);  //д����� ���� �����ͻ��з�            
        }
        bookNumber++;
        fclose(Book);  //�ر��ļ�
        fclose(Book1);

        Book1 = fopen("d:/Book1.txt", "r");
        Book = fopen("d:/Book.txt", "w+");   //ˢ��ԭ�ļ����ٴ�д����ȷ����
        while(!feof(Book1))
        {
            fscanf(Book1, "%d %s %d\n", &readNumber, readName, &readNum);
            fprintf(Book, "%d %s %d\n", readNumber, readName, readNum);
        }
        fclose(Book);
        fclose(Book1);
        remove("d:/Book1.txt");  //ɾ��ԭ�ļ�              
        //rename("d:/Book1.txt", "d:/Book.txt");  //�����ĺ���ļ�����Ϊԭ�����ļ�
    }
    printf("��ӳɹ���\n");
}

//�޸�ͼ����Ϣ����
void changeBook(FILE *Book)  
{
    while(1)
    {
        char name[20] = {0}, readName[20] = {0};
        printf("           Edit Book Information            \n");
        printf("[------------------------------------------]\n");
        printf("\t��ѡ����Ҫ�޸ĵ���Ϣ��\n  1.�޸�ͼ������\n  2.�޸�ͼ������\n  3.�������˵�\n");
        printf("[------------------------------------------]\n");
        int function, readNumber, readNum, find = 0;  //����ѡ�� ��ȡ������� ��ȡ�������� �Ƿ��ҵ�����
        
        //�ж��޸ĺ�������Ƿ��ԭ�е��ظ�
        Book = fopen("d:/Book.txt","r");  //ֻ����ԭ�ļ�
        int ifNumber, ifNum;
        char ifName[20] = {0};
        FILE *ifUserExisted = fopen("d:/Users1.txt","w");
        while(!feof(Book))
        {
            fscanf(Book, "%d %s %d\n", &ifNumber, ifName, &ifNum);
            fprintf(ifUserExisted, "%d %s %d\n", &ifNumber, ifName, ifNum);  
        }
        fclose(ifUserExisted);
        fclose(Book);
   
        scanf("%d",&function);
        if(function == 3)
        {
            remove("d:/Book1.txt");  //��ʱ����ഴ�����ļ�����Ҫɾ�� 
            return;
        }
        Book = fopen("d:/Book.txt","r");  //ֻ����ԭ�ļ�
        FILE *Book1 = fopen("d:/Book1.txt", "w");  //���½�һ���ļ��洢���ĺ����Ϣ
        printf("��������Ҫ���ĵ�ͼ������");
        for(int i = 0; i<20; i++)  //��������ȡ����Ҫ��ӵ��鱾����
        {
            if(i==0)
                scanf("%c%c", &enter,&name[i]);
            else
                scanf("%c",&name[i]);
            if(name[i]==10)  //�����Ļ��з���Ϊ��
            {
                name[i]=0;
                break;
            }
        }
        if(function==1)
        {
            while(!feof(Book))
            {
                fscanf(Book, "%d %s %d\n", &readNumber, readName, &readNum);
                if(strcmp(name, readName)==0)
                {  
                    find = 1;  //�ҵ��˴���
                    printf("��Ҫ������%s����Ϊ��", name);
                    char changeName[20] = {0};
                    for(int i = 0; i<20; i++)  //��������ȡ����Ҫ���ĵ��鱾����
                    {
                        if(i==0)
                            scanf("%c",&changeName[i]);
                        else
                            scanf("%c",&changeName[i]);
                        if(changeName[i]==10)  //�����Ļ��з���Ϊ��
                        {
                            changeName[i]=0;
                            break;
                        }
                    }
                    
                    ifUserExisted = fopen("d:/Users1.txt","r");   //�жϸ��ĺ�������Ƿ����Ѵ��ڵ�������ͻ
                    while(!feof(ifUserExisted))
                    {
                        fscanf(ifUserExisted, "%d %s %d\n", &ifNumber, ifName, &ifNum);
                        if (strcmp(changeName, ifName)==0)
                        {
                            printf("����ʧ�ܣ��Ѵ�������Ϊ%s��ͼ��\n", changeName);
                            fclose(ifUserExisted);
                            fclose(Book);  //�ر��ļ�
                            fclose(Book1);
                            return;
                        }
                    }

                    fprintf(Book1, "%d %s %d\n", readNumber, changeName, readNum);  //д����� ���ĺ������ �����ͻ��з�
                }
                else
                    fprintf(Book1, "%d %s %d\n", readNumber, readName, readNum);  //д����� ���� �����ͻ��з�            
            }
            if(find==0)  //��û�ҵ�����
            {
                printf("û���ҵ����飡����������\n");
                break;
            }
            fclose(Book);  //�ر��ļ�
            fclose(Book1);

            Book1 = fopen("d:/Book1.txt", "r");
            Book = fopen("d:/Book.txt", "w+");   //ˢ��ԭ�ļ����ٴ�д����ȷ����
            while(!feof(Book1))
            {
                fscanf(Book1, "%d %s %d\n", &readNumber, readName, &readNum);
                fprintf(Book, "%d %s %d\n", readNumber, readName, readNum);
            }
            fclose(Book);
            fclose(Book1);

            remove("d:/Book1.txt");  //ɾ��ԭ�ļ�              
            //rename("d:/Book1.txt", "d:/Book.txt");  //�����ĺ���ļ�����Ϊԭ�����ļ�  �˷����ɹ��ʵͣ�����
            printf("���ĳɹ�!\n");
        }
        else if(function == 2)
        {
            while(!feof(Book))
            {
                fscanf(Book, "%d %s %d\n", &readNumber, readName, &readNum);
                if(strcmp(name, readName)==0)
                {  
                    find = 1;  //�ҵ��˴���
                    printf("��Ҫ������%d����Ϊ��", readNum);
                    int newNum = 0;
                    scanf("%d",&newNum);
                    fprintf(Book1, "%d %s %d\n", readNumber, readName, newNum);  //д����� ���� ���ĺ�������ͻ��з�
                }
                else
                    fprintf(Book1, "%d %s %d\n", readNumber, readName, readNum);  //д����� ���� �����ͻ��з�            
            }
            if(find==0)  //��û�ҵ�����
            {
                printf("û���ҵ����飡����������");
                break;
            }
            fclose(Book);  //�ر��ļ�
            fclose(Book1);

            Book1 = fopen("d:/Book1.txt", "r");
            Book = fopen("d:/Book.txt", "w+");   //ˢ��ԭ�ļ����ٴ�д����ȷ����
            while(!feof(Book1))
            {
                fscanf(Book1, "%d %s %d\n", &readNumber, readName, &readNum);
                fprintf(Book, "%d %s %d\n", readNumber, readName, readNum);
            }
            fclose(Book);
            fclose(Book1);

            remove("d:/Book1.txt");  //ɾ��ԭ�ļ�              
            //rename("d:/Book1.txt", "d:/Book.txt");  //�����ĺ���ļ�����Ϊԭ�����ļ�  �˷����׳������⣡����
            printf("���ĳɹ�!\n");
        }
        else
        {
            printf("�����ʽ�������������룡");
            break;
        }
    }
}

//ɾ���鼮�ĺ���
void delBook(FILE *Book)
{
    while(1)
    {
        printf("����������ɾ����ͼ������(����\"-r\"������һ��)");
        char delName[20] = {0};
        for(int i = 0; i<20; i++)  //��������ȡ����Ҫɾ�����鱾����
        {
            //if(i==0)
              //  scanf("%c%c", &enter,&delName[i]);
            //else
                scanf("%c",&delName[i]);
            if(delName[i]==10)  //�����Ļ��з���Ϊ��
            {
                delName[i]=0;
                break;
            }
        }
        if(strcmp(delName, "-r")==0)  //���뷵����һ����ָʾ�󷵻�
            return;
        int readNumber, readNum, find = 0;
        char readName[20] = {0};
        Book = fopen("d:/Book.txt","r");
        FILE *Book1 = fopen("d:/Book1.txt","w");
        while (!feof(Book))
        {
            fscanf(Book, "%d %s %d\n", &readNumber, readName, &readNum);
            if(strcmp(delName, readName)==0)
            {  
                find = 1;  //�ҵ��˴���
                //��ΪҪɾ��������Ϣ�����Բ��������ļ��������
            }
            else
            {
                if(find==1)
                    fprintf(Book1, "%d %s %d\n", readNumber-1, readName, readNum);  //����ɾ�����д��-1����� ���� �����ͻ��з�            
                else
                    fprintf(Book1, "%d %s %d\n", readNumber, readName, readNum);  //ɾ��ǰ��д������ ���� �����ͻ��з�            
            }            
        }
        if(find==0)  //��û�ҵ�����
        {
            printf("û���ҵ����飡����������\n");
            continue;
        }
        fclose(Book);
        fclose(Book1);

        Book1 = fopen("d:/Book1.txt", "r");
        Book = fopen("d:/Book.txt", "w+");   //ˢ��ԭ�ļ����ٴ�д����ȷ����
        while(!feof(Book1))
        {
            fscanf(Book1, "%d %s %d\n", &readNumber, readName, &readNum);
            fprintf(Book, "%d %s %d\n", readNumber, readName, readNum);
        }
        fclose(Book);
        fclose(Book1);

        remove("d:/Book1.txt");  //ɾ��ԭ�ļ�              
        printf("ɾ���ɹ�!\n");
    }
}

//չʾȫ��ͼ��ĺ���
void showBook(FILE *Book)
{
    printf("                  Library                   \n");
    printf("[------------------------------------------]\n");
    printf("\t���\t����\t\t����\n");
    char readName[20] = {0};
    int readNumber, readNum;
    Book = fopen("d:/Book.txt", "r");
    while(!feof(Book))
    {
        fscanf(Book, "%d %s %d\n", &readNumber, readName, &readNum);
        printf("\t%d\t%s\t\t%d\n",readNumber, readName, readNum);           
    }
    fclose(Book);
    printf("[------------------------------------------]\n");
}

//�����Աչʾȫ���û��ĺ���
void showUsers(FILE *Users)
{
    printf("                   Users                    \n");
    printf("[------------------------------------------]\n");
    printf("\t���\t����\t������ͼ��\n");
    char readName[20] = {0}, borrowBook[20] = {0};
    int readNumber;
    Users = fopen("d:/Users.txt", "r");
    while(!feof(Users))
    {
        fscanf(Users, "%d %s %s\n", &readNumber, readName, borrowBook);
        printf("\t%d\t%s\t%s\n",readNumber, readName, borrowBook);           
    }
    fclose(Users);
    printf("[------------------------------------------]\n");
}

//����û�����   
void addUsers(FILE *Users)
{
    FILE *Users1;  //���ļ����û�������ʱ��Ҫ�½��ļ���������Ϣ
    int judgeName = 0;  //�жϴ��û��Ƿ��Ѿ�����
    int num = 1, readNumber;  //  ��Ŷ������鱾����  �������û����
    char name[20] = {0}, readName[20] = {0}, borrowBook[20] = {"None"},readBorrowBook[20] = {"None"};  //����û�����  ��ʱ��Ŷ������ַ�����
    printf("������Ҫ��ӵ��û�����");
    for(int i = 0; i<20; i++)  //��������ȡ����Ҫ��ӵ��û���
    {
        if(i==0)
            scanf("%c%c", &enter,&name[i]);
        else
            scanf("%c",&name[i]);
        if(name[i]==10)  //�����Ļ��з���Ϊ��
        {
            name[i]=0;
            break;
        }
    }  
    if(access("d:/Users.txt",F_OK)==0)  //access�����ж��ļ��Ƿ���ڣ����ڷ���ֵΪ0 ʹ�õ�ͷ�ļ�Ϊio
    { 
        judgeName = 1;
        FILE *judge = fopen("d:/Users.txt", "r");  //��ȡ�����ļ��������Ƿ��Ѿ����ڴ��û�
        while(!feof(judge))
        {
            fscanf(judge, "%d %s %s", &readNumber, readName, readBorrowBook); //����readName�Ѿ���ʾ��ַ������Ҫȡ��ַ��
            fscanf(judge,"\n");  //���뻻�з���׼����һ�еĶ�ȡ
            if(strcmp(name, readName)==0)  //�����Ѿ����ڴ��û�������ѭ��
            {
                printf("�Ѿ����ڴ��û����޷���ӡ�");  //�Ѿ����ڴ��û�������
                return;
            }
        }
        fclose(judge);  //�ر������ж϶��򿪵��ļ�
        usersNumber = readNumber+1;
        if(judgeName==1)
            Users = fopen("d:/Users.txt", "a");  //�ļ����� �Ҳ�������ͬ�û�ʱ���׷������
    }
    else
        Users = fopen("d:/Users.txt","w");  //�ļ�������ʱ�½�һ���ļ�
    fprintf(Users, "%d %s %s\n", usersNumber, name, borrowBook);  //д����� �û��� ������ͻ��з�
    usersNumber++; 
    fclose(Users);
    printf("��ӳɹ���\n");
}

//�޸Ķ�����Ϣ����
void changeUsers(FILE *Users)  
{
    while(1)
    {
        char name[20] = {0}, readName[20] = {0}, borrowBook[20] = {"None"};
        printf("              Edit Reader Name              \n");
        printf("[------------------------------------------]\n");
        printf("\t��ѡ����Ҫ�޸ĵ���Ϣ��\n  1.�޸Ķ�������\n  2.�������˵�\n");
        printf("[------------------------------------------]\n");
        int function, readNumber, find = 0;  //����ѡ�� ��ȡ�������  �Ƿ��ҵ�����
        Users = fopen("d:/Users.txt","r");  //ֻ����ԭ�ļ�  
        
        //�˴�����ifUserExisted��һ�����ڲ����Ƿ������ͬ������
        int ifNumber;
        char ifName[20] = {0}, ifBorrow[20] = {0};
        FILE *ifUserExisted = fopen("d:/Book1.txt","w");
        while(!feof(Users))
        {
            fscanf(Users, "%d %s %s\n", &ifNumber, ifName, ifBorrow);
            fprintf(ifUserExisted, "%d %s %s\n", &ifNumber, ifName, ifBorrow);  
        }
        fclose(ifUserExisted);
        fclose(Users);
         
        Users = fopen("d:/Users.txt","r");  //ֻ����ԭ�ļ�
        scanf("%d",&function);
        if(function == 2)
        {
            remove("d:/Users1.txt");  //��ʱ����ഴ�����ļ�����Ҫɾ�� 
            return;
        }
        FILE *Users1 = fopen("d:/Users1.txt", "w");  //���½�һ���ļ��洢���ĺ����Ϣ
        printf("��������Ҫ���ĵ��û�����");
        for(int i = 0; i<20; i++)  //��������ȡ����Ҫ���ĵĶ�������
        {
            if(i==0)
                scanf("%c%c", &enter,&name[i]);
            else
                scanf("%c",&name[i]);
            if(name[i]==10)  //�����Ļ��з���Ϊ��
            {
                name[i]=0;
                break;
            }
        }
        if(function==1)
        {
            while(!feof(Users))
            {
                fscanf(Users, "%d %s %s\n", &readNumber, readName, borrowBook);
                if(strcmp(name, readName)==0)
                {  
                    find = 1;  //�ҵ��˴˶���
                    printf("��Ҫ��������\"%s\"����Ϊ��", name);
                    char changeName[20] = {0};
                    for(int i = 0; i<20; i++)  //��������ȡ����Ҫ���ĵ��û�����
                    {
                        if(i==0)
                            scanf("%c",&changeName[i]);
                        else
                            scanf("%c",&changeName[i]);
                        if(changeName[i]==10)  //�����Ļ��з���Ϊ��
                        {
                            changeName[i]=0;
                            break;
                        }
                    }
                    ifUserExisted = fopen("d:/Book1.txt","r");   //�жϸ��ĺ�������Ƿ��ʹ��ڵ��û�����ͻ
                    while(!feof(ifUserExisted))
                    {
                        fscanf(ifUserExisted, "%d %s %s\n", &ifNumber, ifName, ifBorrow);
                        if (strcmp(changeName, ifName)==0)
                        {
                            printf("����ʧ�ܣ��Ѵ�������Ϊ%s�Ķ���\n", changeName);
                            fclose(ifUserExisted);
                            fclose(Users);  //�ر��ļ�
                            fclose(Users1);
                            return;
                        }
                    }

                    fprintf(Users1, "%d %s %s\n", readNumber, changeName, borrowBook);  //д����� ���ĺ�Ķ����� �����鼮�ͻ��з�
                }
                else
                    fprintf(Users1, "%d %s %s\n", readNumber, readName, borrowBook);  //д����� ���� �����ͻ��з�            
            }
            if(find==0)  //��û�ҵ��˶���
            {
                printf("û���ҵ��˶��ߣ�����������\n");
                break;
            }
            fclose(Users);  //�ر��ļ�
            fclose(Users1);

            Users1 = fopen("d:/Users1.txt", "r");
            Users = fopen("d:/Users.txt", "w+");   //ˢ��ԭ�ļ����ٴ�д����ȷ����
            while(!feof(Users1))
            {
                fscanf(Users1, "%d %s %s\n", &readNumber, readName, borrowBook);
                fprintf(Users, "%d %s %s\n", readNumber, readName, borrowBook);
            }
            fclose(Users);
            fclose(Users1);

            remove("d:/Users1.txt");  //ɾ��ԭ�ļ�              
            //rename("d:/Book1.txt", "d:/Book.txt");  //�����ĺ���ļ�����Ϊԭ�����ļ�  �˷����ɹ��ʵͣ�����
            printf("���ĳɹ�!\n");
        }
        else
        {
            printf("�����ʽ�������������룡\n");
            break;
        }
    }
}

//ɾ���û��ĺ���
void delUsers(FILE *Users)
{
    while(1)
    {
        printf("����������ɾ���Ķ�������(����\"-r\"������һ��)");
        char delName[20] = {0};
        for(int i = 0; i<20; i++)  //��������ȡ����Ҫɾ�����û�����
        {
            //if(i==0)
              //  scanf("%c%c", &enter,&delName[i]);
            //else
                scanf("%c",&delName[i]);
            if(delName[i]==10)  //�����Ļ��з���Ϊ��
            {
                delName[i]=0;
                break;
            }
        }
        if(strcmp(delName, "-r")==0)  //���뷵����һ����ָʾ�󷵻�
            return;
        int readNumber, find = 0;
        char readName[20] = {0}, borrowBook[20] = {"None"};
        Users = fopen("d:/Users.txt","r");
        FILE *Users1 = fopen("d:/Users1.txt","w");
        while (!feof(Users))
        {
            fscanf(Users, "%d %s %s\n", &readNumber, readName, borrowBook);
            if(strcmp(delName, readName)==0)
            {  
                find = 1;  //�ҵ��˴˶���
                //��ΪҪɾ��������Ϣ�����Բ��������ļ��������
            }
            else
            {
                if(find==1)
                    fprintf(Users1, "%d %s %s\n", readNumber-1, readName, borrowBook);  //����ɾ�����д��-1����� ������ ������ͻ��з�            
                else
                    fprintf(Users1, "%d %s %s\n", readNumber, readName, borrowBook);  //ɾ��ǰ��д������ ������ ������ͻ��з�            
            }            
        }
        if(find==0)  //��û�ҵ��˶���
        {
            printf("û���ҵ��˶��ߣ�����������\n");
            continue;
        }
        fclose(Users1);
        fclose(Users);

        Users1 = fopen("d:/Users1.txt", "r");
        Users = fopen("d:/Users.txt", "w+");   //ˢ��ԭ�ļ����ٴ�д����ȷ����
        while(!feof(Users1))
        {
            fscanf(Users1, "%d %s %s\n", &readNumber, readName, borrowBook);
            fprintf(Users, "%d %s %s\n", readNumber, readName, borrowBook);
        }
        fclose(Users1);
        fclose(Users);

        remove("d:/Users1.txt");  //ɾ��ԭ�ļ�              
        printf("ɾ���ɹ�!\n");
    }
}

//���ĺ���
void borrowBooking(char readerName[])
{
    printf("������������ĵ�ͼ������");
    char name[20] = {0};
    for(int i = 0; i<20; i++)  //��������ȡ��ͼ����
    {
        if(i==0)
            scanf("%c%c", &enter,&name[i]);
        else
            scanf("%c",&name[i]);
        if(name[i]==10)  //�����Ļ��з���Ϊ��
        {
            name[i]=0;
            break;
        }
    }
    char readName[20] = {0};
    int readNumber, readNum, find = 0;
    //���ı����ĵ�ͼ�����Ϣ
    FILE *Book = fopen("d:/Book.txt", "r");
    FILE *Book1 = fopen("d:/Book1.txt", "w");
    while (!feof(Book))
    {
        fscanf(Book, "%d %s %d\n", &readNumber, readName, &readNum);
        if(strcmp(name, readName)==0)
        {  
            find = 1;
            if(readNum<1)
            {
                printf("����ʧ��:��ʣ��ɽ��ĵ�%s��\n", readName);
                return;
            }
            fprintf(Book1, "%d %s %d\n", readNumber, readName, readNum-1); //���ҵ���Ҫ���ĵ�ͼ�飬���ڴ��������ϼ�1 
        } 
        else
            fprintf(Book1, "%d %s %d\n", readNumber, readName, readNum);  //ɾ��ǰ��д������ ������ ������ͻ��з� 
    }
    if(find==0)  //��û�ҵ�����
    {
        printf("����ʧ��:û���ҵ����飡\n");
        return;
    }
    fclose(Book);
    fclose(Book1);
    Book1 = fopen("d:/Book1.txt", "r");
    Book = fopen("d:/Book.txt", "w+");   //ˢ��ԭ�ļ����ٴ�д����ȷ����
    while(!feof(Book1))
    {
        fscanf(Book1, "%d %s %d\n", &readNumber, readName, &readNum);
        fprintf(Book, "%d %s %d\n", readNumber, readName, readNum);
    }
    fclose(Book1);
    fclose(Book);
    remove("d:/Book1.txt");  //ɾ��ԭ�ļ� 
    //���Ķ��ߵ���Ϣ
    FILE *Users = fopen("d:/Users.txt", "r");
    FILE *Users1 = fopen("d:/Users1.txt", "w");
    char borrowBook[20] = {"None"};
    while (!feof(Users))
    {
        fscanf(Users, "%d %s %s\n", &readNumber, readName, borrowBook);
        if(strcmp(readerName, readName)==0)
            fprintf(Users1, "%d %s %s\n", readNumber, readName, name); //�ڶ��ߵĽ���ͼ����д�������ĵ�ͼ���� 
        else
            fprintf(Users1, "%d %s %s\n", readNumber, readName, borrowBook); 
    }
    fclose(Users1);
    fclose(Users);
    Users1 = fopen("d:/Users1.txt", "r");
    Users = fopen("d:/Users.txt", "w+");   //ˢ��ԭ�ļ����ٴ�д����ȷ����
    while(!feof(Users1))
    {
        fscanf(Users1, "%d %s %s\n", &readNumber, readName, borrowBook);
        fprintf(Users, "%d %s %s\n", readNumber, readName, borrowBook);
    }
    fclose(Users1);
    fclose(Users);
    remove("d:/Users1.txt");  //ɾ��ԭ�ļ�  ��ʱ����ɾ����
    printf("���ĳɹ���\n"); 
}

//���麯��
void returnBooking(char readerName[], char borrowBook[])
{
    char readName[20] = {0};
    int readNumber, readNum, find = 0;
    //���ı����ص�ͼ�����Ϣ
    FILE *Book = fopen("d:/Book.txt", "r");
    FILE *Book1 = fopen("d:/Book1.txt", "w");
    while (!feof(Book))
    {
        fscanf(Book, "%d %s %d\n", &readNumber, readName, &readNum);
        if(strcmp(borrowBook, readName)==0)
        {
            fprintf(Book1, "%d %s %d\n", readNumber, readName, readNum+1); //���ҵ�������ͼ�飬���ڴ��������ϼ�1  
            find = 1;
        }
        else
            fprintf(Book1, "%d %s %d\n", readNumber, readName, readNum); //���ǻ��ص��� 
    }
    fclose(Book);
    fclose(Book1);
    Book1 = fopen("d:/Book1.txt", "r");
    Book = fopen("d:/Book.txt", "w+");   //ˢ��ԭ�ļ����ٴ�д����ȷ����
    while(!feof(Book1))
    {
        fscanf(Book1, "%d %s %d\n", &readNumber, readName, &readNum);
        fprintf(Book, "%d %s %d\n", readNumber, readName, readNum);
    }
    bookNumber = readNumber+1;
    fclose(Book1);
    fclose(Book);
    remove("d:/Book1.txt");  //ɾ��ԭ�ļ�
    if(find==0)  //����ʱû�������û�д��飬ֱ�����һ��
    {
        FILE *Book;
        Book = fopen("d:/Book.txt", "a");  
        fprintf(Book, "%d %s 1\n", bookNumber, borrowBook);  //д����� ���� �����ͻ��з�
        bookNumber++; 
        fclose(Book);
    }
    //���Ķ��ߵ���Ϣ
    FILE *Users = fopen("d:/Users.txt", "r");
    FILE *Users1 = fopen("d:/Users1.txt", "w");
    char rborrowBook[20] = {"None"};
    while (!feof(Users))
    {
        fscanf(Users, "%d %s %s\n", &readNumber, readName, rborrowBook);
        if(strcmp(readerName, readName)==0)
            fprintf(Users1, "%d %s %s\n", readNumber, readName, "None"); //�������������ͼ���Ϊ"None" 
        else
            fprintf(Users1, "%d %s %s\n", readNumber, readName, rborrowBook); 
    }
    fclose(Users1);
    fclose(Users);
    Users1 = fopen("d:/Users1.txt", "r");
    Users = fopen("d:/Users.txt", "w+");   //ˢ��ԭ�ļ����ٴ�д����ȷ����
    while(!feof(Users1))
    {
        fscanf(Users1, "%d %s %s\n", &readNumber, readName, rborrowBook);
        fprintf(Users, "%d %s %s\n", readNumber, readName, rborrowBook);
    }
    fclose(Users1);
    fclose(Users);
    remove("d:/Users1.txt");  //ɾ��ԭ�ļ�  ��ʱ����ɾ����
    printf("�ɹ�����%s\n", borrowBook);
}

//������ѯ���ܣ����ݱ�Ż�������ѯ�鱻��Щ�˽���
void searchBook()
{
    while (1)
    {
        int function = 0;
        FILE *Book = fopen("d:/Book.txt", "r");
        FILE *Users = fopen("d:/Users.txt", "r");
        char readerName[20] = {0}, bookName[20] = {0}, borrowBook[20] = {0}, name[20] = {0};
        int bookNumber, bookNum, find = 0, readerNumber;
        printf("                   Search                   \n");
        printf("[------------------------------------------]\n");
        printf("\t\t��ѡ���ѯ���ܣ�\n\t1.���ݱ�Ų�ѯ\n\t2.����������ѯ\n\t3.����������\n");
        printf("[------------------------------------------]\n");
        scanf("%d",&function); // ������Ҫ�Ĺ���
        switch (function)
        {
            case 1:
                printf("��Ҫ���ҵ�������ǣ�");
                scanf("%d",&function); // ������Ҫ���ҵ�ͼ����
                while(!feof(Book))
                {
                    fscanf(Book, "%d %s %d\n", &bookNumber, bookName, &bookNum); //����bookName�Ѿ���ʾ��ַ������Ҫȡ��ַ��
                    if(bookNumber==function)  //���ֲ��ҵ��������ѭ��
                    {
                        find = 1;//�ҵ���
                        break;
                    }
                }
                if(find==0)
                {
                    printf("û���ҵ����Ϊ%d��ͼ�顣\n",function);
                    break;
                }
                printf("               Search Result                \n");
                printf("[------------------------------------------]\n");
                find = 0;//��Ҫ�ڲ���˭����ʱ�ٴ�ʹ��
                printf("\t��ţ�\t\t%d\n\t������\t\t%s\n\tʣ��������\t%d\n\t",bookNumber, bookName, bookNum);
                while (!feof(Users))
                {
                    fscanf(Users, "%d %s %s\n", &readerNumber, readerName, borrowBook);//�������߲���˭�������Ȿ��   
                    if (strcmp(borrowBook, bookName)==0)
                    {
                        if(find==0)
                        {
                            find = 1;
                            printf("���Ĵ���Ķ��ߣ�");
                            printf("%s",readerName);
                        }
                        else
                            printf(" ,%s",readerName);
                    }
                }
                if(find==0)
                    printf("��û�ж��߽��Ĵ��顣\n");
                else
                    printf("\n");
                printf("[------------------------------------------]\n");
                printf("����س�����...\n");
                enter = getchar();
                enter = getchar();
                break;
            case 2:
                printf("��Ҫ���ҵ������ǣ�");
                scanf("%s",name); // ������Ҫ���ҵ�ͼ����
                while(!feof(Book))
                {
                    fscanf(Book, "%d %s %d\n", &bookNumber, bookName, &bookNum); //����bookName�Ѿ���ʾ��ַ������Ҫȡ��ַ��
                    if(strcmp(bookName, name)==0)  //���ֲ��ҵ��������ѭ��
                    {
                        find = 1;//�ҵ���
                        break;
                    }
                }
                if(find==0)
                {
                    printf("û���ҵ�����Ϊ%s��ͼ�顣\n",name);
                    break;
                }
                printf("               Search Result                \n");
                printf("[------------------------------------------]\n");
                find = 0;//��Ҫ�ڲ���˭����ʱ�ٴ�ʹ��
                printf("\t��ţ�\t\t%d\n\t������\t\t%s\n\tʣ��������\t%d\n\t",bookNumber, bookName, bookNum);
                while (!feof(Users))
                {
                    fscanf(Users, "%d %s %s\n", &readerNumber, readerName, borrowBook);//�������߲���˭�������Ȿ��   
                    if (strcmp(borrowBook, bookName)==0)
                    {
                        if(find==0)
                        {
                            find = 1;
                            printf("���Ĵ���Ķ��ߣ�");
                            printf("%s",readerName);
                        }
                        else
                            printf(" ,%s",readerName);
                    }
                }
                if(find==0)
                    printf("��û�ж��߽��Ĵ��顣\n");
                else
                    printf("\n");
                printf("[------------------------------------------]\n");
                printf("����س�����...\n");
                enter = getchar();
                enter = getchar();
                break;
            case 3:
                return;
            default:
                printf("������ĸ�ʽ��������������\n");
                break;
        }
        fclose(Book);
        fclose(Users);
    }
}

int main(int argc, char *argv[])  //��Ҫ�������ж������
{
    char identity1[] = "-u";  //�������
    char identity2[] = "-a";  //����Ա���
    FILE *Book, *Users;  //�����ļ��ֱ�洢ͼ����Ϣ�Ͷ�����Ϣ��
	int function1, function2; //����ѡ��
    /*������
    char readerName[20] = {0};
    int test = 0;
    scanf("%d %s",&test, readerName);
    if(test==1)
    */
    if(strcmp(argv[1], identity2)==0)  //����Ա��������
    {
        char Administrator[20] = "Zhang";
        if(strcmp(Administrator, argv[2])==0)
        {    
            while(1)
            {   
                printf("                    menu                    \n");
                printf("[------------------------------------------]\n");
                printf("     ����Ա���ã���ѡ����Ҫʹ�õĹ���:\n  1.�������޸�ͼ����Ϣ\n  2.�������޸Ķ�����Ϣ\n  3.�鿴ȫ���ݲ��鼮\n  4.�鿴ȫ�����߼��������Ϣ\n  5.ͼ�������ѯ\n  6.��������\n");
                printf("[------------------------------------------]\n");
                scanf("%d",&function1);  
                switch (function1)
                {
                    case 1:  //����ͼ����Ϣ
                        printf("                  Books                     \n");
                        printf("[------------------------------------------]\n");
                        printf("\t��ѡ��Ҫ��ͼ����еĲ�����\n  1.���ͼ����Ϣ\n  2.�޸�ͼ����Ϣ\n  3.ɾ��ͼ����Ϣ\n  4.�������˵�\n");
                        printf("[------------------------------------------]\n");
                        scanf("%d",&function2);  //����ڶ�������ָ��
                        switch (function2)
                        {
                            case 1:
                                addBook(Book);  //�������ͼ�麯��
                                
                                break;
                            case 2:
                                changeBook(Book);  //�޸ĺ���
                                break;
                            case 3:
                                scanf("%c",&enter);
                                delBook(Book);  //ɾ������
                                break;
                            case 4:
                                break;
                            default:
                                printf("�����ֵ����������������");
                                break;
                        }
                        break;
                    case 2:  //���Ķ�����Ϣ
                        printf("                  Readers                   \n");
                        printf("[------------------------------------------]\n");
                        printf("\t��ѡ��Ҫ���û����еĲ�����\n  1.����û���Ϣ\n  2.�޸��û���Ϣ\n  3.ɾ���û���Ϣ\n");
                        printf("[------------------------------------------]\n");
                        scanf("%d",&function2);  //����ڶ�������ָ��
                        switch (function2)
                        {
                            case 1:
                                addUsers(Users);  //����û���Ϣ
                                break;
                            case 2:
                                changeUsers(Users);  //�޸��û���Ϣ
                                break;
                            case 3:
                                scanf("%c",&enter);
                                delUsers(Users);  //ɾ���û���Ϣ
                                break;
                            default:
                                printf("�����ֵ����������������");
                                break;
                        }
                        break;
                    case 3:
                        showBook(Book);
                        printf("����س�����...\n");
                        enter = getchar();
                        enter = getchar();
                        break;
                    case 4:
                        showUsers(Users);
                        printf("����س�����...\n");
                        enter = getchar();
                        enter = getchar();
                        break;
                    case 5:
                        searchBook();
                        break;
                    case 6:
                        printf("��л����ʹ�ã��ټ���");
                        return 0;
                    default:
                        printf("�����ʽ��������������!");
                        break;
                }
            }
        }
        else
            printf("����Ա���������������룡");
    }
    /*
    else if(test == 2)
    */                       
    else if (strcmp(argv[1], identity1)==0)  //���ߵĲ�������
    {
        char readName[20] = {0}, borrowBook[20] = {"None"};
        int readNumber,find = 0;
        FILE *Users = fopen("d:/Users.txt","r");  //��Ҫ�ж��Ƿ���ڴ��û�
        while (!feof(Users))
        {
            fscanf(Users, "%d %s %s\n", &readNumber, readName, borrowBook);
            if(strcmp(argv[2], readName)==0)
            {   
                find = 1;
                break;
            }
        }
        fclose(Users);
        if(find==0)
        {
            printf("�������û���Ϊ%s�Ķ��ߣ�", argv[2]);
            return 0;
        }
        while (1)
        {
            FILE *Users = fopen("d:/Users.txt","r");  //ˢ���û��Ľ�����Ϣ
            while (!feof(Users))
            {
                fscanf(Users, "%d %s %s\n", &readNumber, readName, borrowBook);
                if(strcmp(argv[2], readName)==0)
                    break;
            }
            fclose(Users);

            printf("                    menu                    \n");
            printf("[------------------------------------------]\n");
            printf("\t����%s���ã���ѡ����Ҫʹ�õĹ���:\n  1.����ͼ��\n  2.����ͼ��\n  3.�鿴ȫ���ݲ��鼮\n  4.��������\n", argv[2]);
            printf("[------------------------------------------]\n");
            scanf("%d",&function1);  
            switch (function1)
            {
                case 1:  //����ͼ��
                    if(strcmp(borrowBook, "None")==0)
                        borrowBooking(argv[2]);
                    else
                        printf("���Ѿ�����ͼ�飬���Ȼ����ٽ��н��Ĳ�����\n");
                    printf("����س�����...\n");
                    enter = getchar();
                    enter = getchar();
                    break;
                case 2:  //����
                    if(strcmp(borrowBook, "None")!=0)
                        returnBooking(argv[2], borrowBook);
                    else
                        printf("����ǰ��û�н���ͼ�顣\n");
                    printf("����س�����...\n");
                    enter = getchar();
                    enter = getchar();
                    break;
                case 3:
                    showBook(Book);
                    printf("����س�����...\n");
                    enter = getchar();
                    enter = getchar();
                    break;
                case 4:
                    printf("��л����ʹ�ã��ټ���");
                    return 0;
                default:
                    printf("�����ʽ��������������!");
                    break;
            }
        }
    }
    else
        printf("������ĸ�ʽ��������������!");
    return 0;
}
