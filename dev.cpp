#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define bug(a) cout<<#a<<": "<<a<<endl
#define N 510
/*��Ҫ������
dis[] ��ʼ�㵽������
edges[][] �ڽӾ���
pre[]  ǰһ����
look[] �������û�б����ʹ�
�����������
*/

int dis[N],edges[N][N] ,fire[N],rootCnt[N], pre[N],  fireSum[N];
int look[N];
int n,m,s,d;

void dijkstra(int s, int d){
    memset(dis, 0x3f, sizeof(dis));//�������Ĵ�Сʵ������510*4(intΪ4)���ֽ�
    dis[s] = 0;
    fireSum[s] = fire[s];
    rootCnt[s] = 1;
    for(int i=0;i<n;i++){
        int k = -1;
        for(int j=0; j<n;j++){
        	bug(dis[j]);
        	bug(dis[k]);
            if(!look[j] && (k == -1 || dis[j]<dis[k]))
                k = j;
        }
        look[k] = true;//һ��ѡ��,���dis[k]���ǵ�k����С����
        for(int j=0;j<n;j++){
            if(dis[j] == dis[k]+edges[k][j]){
                rootCnt[j]+=rootCnt[k];
                if(fireSum[j] < fireSum[k] + fire[j]){
                    pre[j] = k;
                    fireSum[j] = fireSum[k]+fire[j];
                }
            }
            else if(dis[j] > dis[k]+edges[k][j]){
                pre[j] = k;
                dis[j] = dis[k]+edges[k][j];
                rootCnt[j] = rootCnt[k];
                fireSum[j] = fireSum[k] + fire[j];
            }
        }
    }
}
int main(){
    int t;
    cin>>n>>m>>s>>d;
    for(int i=0;i<n;i++) scanf("%d", &fire[i]);
    memset(edges, 0x3f, sizeof edges);//�����������д��������,0x3f�������ֵ
    for(int i=0;i<m;i++){
        int a,b;
        scanf("%d %d %d",&a,&b,&t);
        edges[a][b] = t;
        edges[b][a] = t;
    }
    //init
   
    
    dijkstra(s,d);
    
    cout<<rootCnt[d]<<" "<<fireSum[d]<<endl;
    stack<int> path;
    t = d;
    while(t != s){//��·�����������
        path.push(t);
        t = pre[t];
    }
   path.push(t);
    while(path.size()>1){
        cout<<path.top()<<" ";
        path.pop();
    }
    cout<<d;
    return 0;
}
