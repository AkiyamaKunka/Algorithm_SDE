#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <windows.h>
using namespace std;

//���ֵ�����Ϊ-1�����ֵ�����Ϊ1,û���ӵĵط�Ϊ0
//������δȷ��

int board[7][7]={0};   //��ǰ����
long long value[7][7]={{0,0,0,0,0,0,0},{0,1,2,3,2,1,0},{0,2,4,5,4,2,0},{0,3,5,6,5,3,0},{0,2,4,5,4,2,0},{0,1,2,3,2,1,0},{0,0,0,0,0,0,0}};   //����ÿ��λ�õĳ�ʼȨֵ
long long link[5]={0,2,4,1000,100000000};   //�����ҷ�����1��2��3��4����������ʱ��Ȩֵ��ǰ���Ǹ��У��У��Խ�����û�ез����ӣ�
long long broke[5]={0,2,4,100,100000};   //���ڵз�����1��2��3��4������ʱ����������ƻ���Ȩֵ��ǰ���Ǹ��У��У��Խ���û�м������ӣ�
long long ti;   //����������ٶȲ���


void usetime()
{
    int k=1;
    for(int i=1;i<=ti;i++)
    {
        k=(k+i)%5;
    }
}

void AItime()
{
    cout<<"��ѡ�������������ٶ�(1,2,3,4)"<<endl;
    char w;
    cin>>w;
    if(w=='1') ti=300000000;
    else if(w=='2') ti=200000000;
    else if(w=='3') ti=100000000;
    else if(w=='4') ti=50000000;
    else
    {
		Beep(300,400);Beep(600,400); Beep(600,400); 
        cout<<"������µķɿ죬���������Ū������Ĵ���"<<endl;
        ti=0;
    }
}


long long getValue(int i,int j)   //����ÿ�����Ȩֵ
{
    long long ans=value[i][j];


    int own=0;
    for(int t=1;t<=5;t++)
    {
        if(board[t][j]==-1) own++;
        else if(board[t][j]==1) { own=0; break;}
    }
    ans+=link[own];

    own=0;
    for(int t=1;t<=5;t++)
    {
        if(board[i][t]==-1) own++;
        else if(board[i][t]==1) { own=0; break;}
    }
    ans+=link[own];

    own=0;
    if(i==j)
    {
        for(int t=1;t<=5;t++)
        {
            if(board[t][t]==-1) own++;
            else if(board[t][t]==1) { own=0; break;}
        }
        ans+=link[own];
    }

    own=0;
    if(i==6-j)
    {
        for(int t=1;t<=5;t++)
        {
            if(board[t][6-t]==-1) own++;
            else if(board[t][6-t]==1) { own=0; break;}
        }
        ans+=link[own];
    }


    int rival=0;
    for(int t=1;t<=5;t++)
    {
        if(board[t][j]==1) rival++;
        else if(board[t][j]==-1) { rival=0; break;}
    }
    ans+=broke[rival];

    rival=0;
    for(int t=1;t<=5;t++)
    {
        if(board[i][t]==1) rival++;
        else if(board[i][t]==-1) { rival=0; break;}
    }
    ans+=broke[rival];

    rival=0;
    if(i==j)
    {
        for(int t=1;t<=5;t++)
        {
            if(board[t][t]==1) rival++;
            else if(board[t][t]==-1) { rival=0; break;}
        }
        ans+=broke[rival];
    }

    rival=0;
    if(i==6-j)
    {
        for(int t=1;t<=5;t++)
        {
            if(board[t][6-t]==1) rival++;
            else if(board[t][6-t]==-1) { rival=0; break;}
        }
        ans+=broke[rival];
    }

    return ans;
}

void AI(int k)   //�����˻�
{
    cout<<"�������ӣ�"<<endl;
    usetime();
    int best_i=0,best_j=0;
    long long best=0;
    for(int i=1;i<=5;i++)
        for(int j=1;j<=5;j++)
        {
            if(board[i][j]!=0) continue;
            else
            {
                long long v=getValue(i,j);
                if(v>best)
                {
                    best=v;
                    best_i=i; best_j=j;
                }
            }
        }
    board[best_i][best_j]=k;
}

void zAI(int k)   //��ͨ�˻�
{
    cout<<"�������ӣ�"<<endl;
    usetime();
    int best_i=0,best_j=0;
    long long best=0;
    for(int i=1;i<=5;i++)
        for(int j=1;j<=5;j++)
        {
            if(board[i][j]!=0) continue;
            else
            {
                long long v=getValue(i,j);
                if(v>best)
                {
                    best=v;
                    best_i=i; best_j=j;
                }
            }
        }
    if(best>=100000) board[best_i][best_j]=k;
    else
    {
        srand(time(NULL));
        while(true)
        {
            int i=(rand())%5+1,j=(rand())%5+1;
            if(board[i][j]!=0) continue;
            else { board[i][j]=k; break;}
        }
    }
}

void zzAI(int k)   //���˻�
{
    srand(time(NULL));
    cout<<"�������ӣ�"<<endl;
    usetime();
    while(true)
    {
        int i=(rand())%5+1,j=(rand())%5+1;
        if(board[i][j]!=0) continue;
        else { board[i][j]=k; break;}
    }
}


void work(int k)   //������ӣ��޸����̣�
{
    cout<<"�����ӣ�"<<endl;
    char i,j;
    cin>>i>>j;
    if(i<'1'||i>'5'||j<'1'||j>'5'||board[i-48][j-48]!=0)
    {
		Beep(300,400);Beep(600,400); Beep(600,400); 
        cout<<"��Ҫ��ͼ��ƭ�������������Զ��ѿͻ��������ϣ����������ӣ�"<<endl;
        work(k);
    }
    else
    {
        board[i-48][j-48]=k;
        return;
    }
}


void print()
{
    char p_board[7][7];
    for(int i=1;i<=5;i++)
        for(int j=1;j<=5;j++)
        {
            if(board[i][j]==1) p_board[i][j]='X';
            else if(board[i][j]==-1) p_board[i][j]='O';
            else if(board[i][j]==0) p_board[i][j]=' ';
        }
    printf("+---+---+---+---+---+\n"
           "| %c | %c | %c | %c | %c |\n"
           "+---+---+---+---+---+\n"
           "| %c | %c | %c | %c | %c |\n"
           "+---+---+---+---+---+\n"
           "| %c | %c | %c | %c | %c |\n"
           "+---+---+---+---+---+\n"
           "| %c | %c | %c | %c | %c |\n"
           "+---+---+---+---+---+\n"
           "| %c | %c | %c | %c | %c |\n"
           "+---+---+---+---+---+\n",
           p_board[1][1],p_board[1][2],p_board[1][3],p_board[1][4],p_board[1][5],
           p_board[2][1],p_board[2][2],p_board[2][3],p_board[2][4],p_board[2][5],
           p_board[3][1],p_board[3][2],p_board[3][3],p_board[3][4],p_board[3][5],
           p_board[4][1],p_board[4][2],p_board[4][3],p_board[4][4],p_board[4][5],
           p_board[5][1],p_board[5][2],p_board[5][3],p_board[5][4],p_board[5][5]);
    cout<<endl;
}


int check()
{
    int win=0;
    for(int i=1;i<=5;i++)
    {
        if(board[i][1]==0) continue;
        int j;
        for(j=2;j<=5;j++)
        {
            if(board[i][j]!=board[i][1]) break;
        }
        if(j==6) {win=board[i][1]; return win;}
    }

    for(int j=1;j<=5;j++)
    {
        if(board[1][j]==0) continue;
        int i;
        for(i=2;i<=5;i++)
        {
            if(board[i][j]!=board[1][j]) break;
        }
        if(i==6) {win=board[1][j]; return win;}
    }

    if(board[1][1]!=0)
    {
        int t;
        for(t=2;t<=5;t++)
        {
            if(board[t][t]!=board[1][1]) break;
        }
        if(t==6) {win=board[1][1]; return win;}
    }

    if(board[1][5]!=0)
    {
        int t;
        for(t=2;t<=5;t++)
        {
            if(board[t][6-t]!=board[1][5]) break;
        }
        if(t==6) {win=board[1][5]; return win;}
    }
    int full=1;
    for(int i=1;i<=5;i++)
        for(int j=1;j<=5;j++)
        {
            if(board[i][j]==0) {full=0; goto next;}
        }
    next:;
    if(full==1) return 100;
    return win;
}  //���ʤ�����


int choose1()
{
    char x;
    cin>>x;
    int t=x-48;
    if(x!='0'&&x!='1'&&x!='2')
    {
		Beep(600,400); Beep(600,400); Beep(600,400); 
        cout<<"��Ҫ��ͼ��ƭ�������������Զ��ѿͻ��������ϣ�������ѡ��"<<endl;
        t=choose1();
    }
    return t;
}

int choose2()
{
    char x;
    cin>>x;
    int t=x-48;
    if(x!='0'&&x!='1')
    {
		Beep(600,400); Beep(600,400); Beep(600,400); 
		cout<<"��Ҫ��ͼ��ƭ�������������Զ��ѿͻ��������ϣ�������ѡ��"<<endl;
        t=choose2();
    }
    return t;
}
int main()
{ 
    newgame:;
    memset(board,0,sizeof(board));
    cout<<"��Ϸ��ʾ������ΪX������ΪO�������ʽ��x y�����Գ��Բ���Ҫ�����롾/������"<<endl;
    print();
    AItime();
    cout<<"�˻���սѡ��0�����˶�սѡ��1��������սѡ��2��"<<endl;
    int x=choose1();
    if(x==0)
    {
        cout<<"ѡ����������0��ѡ���������1��"<<endl;
        int choose=choose2();
        cout<<"�Ѷ�ѡ�񣺼�ѡ��0���е�ѡ��1������ѡ��2��"<<endl;
        int y=choose1();
        if(choose==0)
        {
            while(true)
            {
                work(1);
                print();
                if(check()==1) {Beep(300,400);Beep(600,400); Beep(600,400);  cout<<"666̫ǿ��!"<<endl; break;}
                if(check()==100) { Beep(600,400); Beep(600,400); Beep(600,400); cout<<"��ϲ�����˹����ϴ��ƽ��"<<endl; break;}
                if(y==1) zAI(-1);
                else if(y==0) zzAI(-1);
                else if(y==2) AI(-1);
                print();
                if(check()==-1) {Beep(500,400); Beep(500,400); Beep(500,400);  cout<<"�ú÷�˼һ���Լ���������Ϊ"<<endl; break;}
                if(check()==100) {Beep(700,200); Beep(700,200); Beep(700,200); cout<<"��ϲ�����˹����ϴ��ƽ��"<<endl; break;}
            }
        }
        if(choose==1)
        {
            while(true)
            {
                if(y==1) zAI(1);
                else if(y==0) zzAI(1);
                else if(y==2) AI(1);
                print();
                if(check()==1) {Beep(500,400); Beep(500,400); Beep(500,400);  cout<<"�ú÷�˼һ���Լ���������Ϊ"<<endl; break;}
                if(check()==100) {Beep(700,200); Beep(700,200); Beep(700,200); cout<<"��ϲ�����˹����ϴ��ƽ��"<<endl; break;}
                work(-1);
                print();
                if(check()==-1) {Beep(300,400);Beep(600,400); Beep(600,400);  cout<<"dalao tql!"<<endl; break;}
                if(check()==100) { Beep(300,400);Beep(600,400); Beep(600,400); cout<<"��ϲ�����˹����ϴ��ƽ��"<<endl; break;}
            }
        }
    }
    if(x==1)
    {
        while(true)
        {
            work(1);
            print();
            if(check()==1) { cout<<"���ֻ�ʤ"<<endl; break;}
            if(check()==100) { cout<<"��ϲ���Ǵ��ƽ��"<<endl; break;}
            work(-1);
            print();
            if(check()==-1) { cout<<"���ֻ�ʤ"<<endl; break;}
            if(check()==100) { cout<<"��ϲ���Ǵ��ƽ��"<<endl; break;}
        }
    }
    if(x==2)
    {
        cout<<"Ϊʲô�����뿴�����˹����ϴ�ܣ�"<<endl;
        cout<<"ѡ���һ���˹������Ѷȣ���ѡ��0���е�ѡ��1������ѡ��2��"<<endl;
        int x1=choose1();
        cout<<"ѡ��ڶ����˹������Ѷȣ���ѡ��0���е�ѡ��1������ѡ��2��"<<endl;
        int x2=choose1();
        while(true)
        {
            if(x1==1) zAI(1);
            else if(x1==0) zzAI(1);
            else if(x1==2) AI(1);
            print();
            if(check()==1) {Beep(300,400);Beep(600,400); Beep(600,400);  cout<<"��һ���˹����ϻ�ʤ"<<endl; break;}
            if(check()==100) {Beep(300,400);Beep(600,400); Beep(600,400);  cout<<"���ˣ���ƽ�ˣ������˰ɣ�"<<endl; break;}
            if(x2==1) zAI(-1);
            else if(x2==0) zzAI(-1);
            else if(x2==2) AI(-1);
            print();
            if(check()==-1) {Beep(300,400);Beep(600,400); Beep(600,400);  cout<<"�ڶ����˹����ϻ�ʤ"<<endl; break;}
            if(check()==100) { Beep(300,400);Beep(600,400); Beep(600,400); cout<<"���ˣ���ƽ�ˣ������˰ɣ�"<<endl; break;}
        }
    }
    cout<<"�Ƿ�����һ�֣��ǣ�1������0��"<<endl;
    int is_n=choose2();
    if(is_n==1) goto newgame;
    else
    {
        cout<<"��л���Ĳ���"<<endl;
        return 0;
    }
}
