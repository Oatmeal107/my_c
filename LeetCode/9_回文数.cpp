#include<iostream>
using namespace std;

int main(){            //��ʵ����ֻ��תһ�����֣�ȫ����ת������Խ��
    int x;
    cin>> x;

    if(x<0)
        cout<<"���ǻ�����"<<endl;
    else if(x==0)
        cout<<"�ǻ�����"<<endl;
    else{
        int i,copy;
        copy = x;
        for( i=1; i>0; i++){
            copy = copy/10;
            if(copy==0)
                break;
        }
        long long y=0;
        copy=x;
        for(int j=0;j<i;j++){
            y = y*10;
            y = y+(copy%10);
            copy=copy/10;
        }
        if(x==y)
            cout<<"�ǻ�����"<<endl;
        else
            cout<<"���ǻ�����"<<endl; 
    }
    return 0;
}