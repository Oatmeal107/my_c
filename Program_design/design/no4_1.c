#include<stdio.h>

int get(int array[], int low, int high)
{
    int key = array[low];  //��׼����
    while(low<high)
    {
        while(low<high && array[high]>=key)//Ĭ�ϻ�׼����߿�ʼ�����ұ߿�ʼ�Ƚ�
            high--;                      //��β��Ԫ�ش��ڵ��ڻ�׼����ʱ����һֱ��ǰŲ��highָ��
    
        if(low < high)  //�ҵ���array[low]С�����󣬾Ͱ�highֵ������
            array[low] = array[high];

        while(low < high && array[low] <= key)//����Ԫ��С�ڵ��ڻ�׼����ʱ����һֱ���Ų��lowָ��
            low++;

        if(low < high)//�ҵ���array[high]�����ʱ���Ͱ�ǰ���array[low]������
            array[high] = array[low];
    }
    //����ѭ��ʱlow��high��ȣ���ʱ��low��high����key����ȷ����λ��
    //�ѻ�׼���ݸ�����ȷλ��
    array[low] = key;
    return high;
}

void sort(int array[], int low, int high) //ʵ�ֵݹ�
{
    if(low < high)
    {
        int standard = get(array, low, high);
        //�ݹ�
        sort(array, low, standard-1);
        sort(array, standard+1, high);
    }
}

int main()
{
    int n[50], i;
    char c;
    printf("����������Ҫ���������:");
    for(i = 0; i < 50; i++)
    {
        scanf("%d%c",&n[i], &c);
        if(c==10)
            break;
    }
    sort(n, 0, i);
    printf("����������Ϊ��");
    for(int l = 0; l <= i; l++)
    {
        printf("%d ",n[l]);
    }
}