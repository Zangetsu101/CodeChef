#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <stack>

#define endl "\n"
#define si(a) scanf("%d",&a)
#define sii(a,b) scanf("%d %d",&a,&b)
#define siii(a,b,c) scanf("%d %d %d",&a,&b,&c)
#define sl(a) scanf("%lld",&a)
#define sll(a,b) scanf("%lld %lld",&a,&b)
#define pf printf
#define vi vector<int>
#define vii vector<pair<int,int> >
#define pii pair<int,int>
#define all(c) c.begin(),c.end()
#define ms(a,c) memset(a,c,sizeof(a))
#define tr(c,i) for(decltype((c).begin()) i=(c).begin();i!=(c).end();i++)
#define trr(c,i) for(decltype((c).rbegin()) i=(c).rbegin();i!=(c).rend();i++)

using namespace std;

#define N 100001
#define mod 1000000007
#define inf 1e9

typedef long long ll;
typedef unsigned long long ull;

short grundy[21][21][21][21];
bool monster[21][21];
char board[21][21];
short value[22][22][4];
int dx[]={0,-1,0,1};
int dy[]={-1,0,1,0};

int getGrundy(set<int> &s)
{
    int at=0;
    for(set<int>::iterator it=s.begin();it!=s.end();it++)
    {
        if(*it!=at)
            break;
        at++;
    }
    return at;
}

int calGrundy(int x1,int y1,int x2,int y2,int x,int y);

int blockGrundy(int x1,int y1,int x2,int y2)
{
    if(grundy[x1][y1][x2][y2]!=-1)
        return grundy[x1][y1][x2][y2];
    set<int> s;
    for(int i=x1;i<=x2;i++)
    {
        for(int j=y1;j<=y2;j++)
        {
            if(monster[i][j])
                s.insert(calGrundy(x1,y1,x2,y2,i,j));
        }
    }
    return grundy[x1][y1][x2][y2]=getGrundy(s);
}

int calGrundy(int x1,int y1,int x2,int y2,int x,int y)
{
    int v=0;
    v^=blockGrundy(x1,y1,x-1,y-1);
    v^=blockGrundy(x1,y+1,x-1,y2);
    v^=blockGrundy(x+1,y1,x2,y-1);
    v^=blockGrundy(x+1,y+1,x2,y2);
    return v;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("Input.txt","r",stdin);
//    freopen("Output.txt","w",stdout);
    int cases;
    cin>>cases;
    while(cases--)
    {
        ms(grundy,-1);
        ms(value,0);
        ms(monster,false);
        int r,c;
        cin>>r>>c;
        for(int i=1;i<=r;i++)
        {
            for(int j=1;j<=c;j++)
                cin>>board[i][j];
        }
        for(int i=1;i<=r;i++)
        {
            for(int j=1;j<=c;j++)
            {
                if(board[i][j]=='^')
                {
                    value[i][j][0]=value[i][j-1][0]+1;
                    value[i][j][1]=value[i-1][j][1]+1;
                }
            }
        }
        for(int i=r;i>0;i--)
        {
            for(int j=c;j>0;j--)
            {
                if(board[i][j]=='^')
                {
                    value[i][j][2]=value[i][j+1][2]+1;
                    value[i][j][3]=value[i+1][j][3]+1;
                }
            }
        }
        for(int i=1;i<=r;i++)
        {
            for(int j=1;j<=c;j++)
            {
                if(board[i][j]=='#')
                    continue;
                short temp=1000;
                for(int k=0;k<4;k++)
                    temp=min(value[i+dx[k]][j+dy[k]][k],temp);
                if(temp>=2)
                    monster[i][j]=true;
            }
        }
        int v=blockGrundy(1,1,r,c);
        if(v)
            cout<<"Asuna"<<endl;
        else
            cout<<"Kirito"<<endl;
    }
    return 0;
}
