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

#define N 55
#define mod 1000000007
#define inf 1e9

typedef long long ll;
typedef unsigned long long ull;

ll dp[N][N][N][N][2];
int data[N][N];
ll sum[N][N];
int m,n;

ll getRow(int xl,int yl,int xr,int yr,int r)
{
    return sum[r][yr]-sum[r][yl-1]-sum[r-1][yr]+sum[r-1][yl-1];
}

ll getCol(int xl,int yl,int xr,int yr,int c)
{
    return sum[xr][c]-sum[xl-1][c]-sum[xr][c-1]+sum[xl-1][c-1];
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
        ms(dp,0);
        cin>>m>>n;
        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=n;j++)
            {
                cin>>data[i][j];
                sum[i][j]=sum[i-1][j]+sum[i][j-1]+data[i][j]-sum[i-1][j-1];
            }
        }
        for(int w=0;w<m;w++)
        {
            for(int x=1;x+w<=m;x++)
            {
                for(int h=0;h<n;h++)
                {
                    for(int y=1;y+h<=n;y++)
                    {
                        dp[x][y][x+w][y+h][0]=max(dp[x][y][x+w][y+h][0],getRow(x,y,x+w,y+h,x)+dp[x+1][y][x+w][y+h][1]);
                        dp[x][y][x+w][y+h][0]=max(dp[x][y][x+w][y+h][0],getRow(x,y,x+w,y+h,x+w)+dp[x][y][x+w-1][y+h][1]);
                        dp[x][y][x+w][y+h][0]=max(dp[x][y][x+w][y+h][0],getCol(x,y,x+w,y+h,y)+dp[x][y+1][x+w][y+h][1]);
                        dp[x][y][x+w][y+h][0]=max(dp[x][y][x+w][y+h][0],getCol(x,y,x+w,y+h,y+h)+dp[x][y][x+w][y+h-1][1]);
                        int mr=getRow(x,y,x+w,y+h,x)<=getRow(x,y,x+w,y+h,x+w)?x:x+w;
                        int mc=getCol(x,y,x+w,y+h,y)<=getCol(x,y,x+w,y+h,y+h)?y:y+h;
                        if(getRow(x,y,x+w,y+h,mr)<=getCol(x,y,x+w,y+h,mc))
                        {
                            if(getRow(x,y,x+w,y+h,x)<=getRow(x,y,x+w,y+h,x+w))
                                dp[x][y][x+w][y+h][1]=dp[x+1][y][x+w][y+h][0];
                            else
                                dp[x][y][x+w][y+h][1]=dp[x][y][x+w-1][y+h][0];
                        }
                        else
                        {
                            if(getCol(x,y,x+w,y+h,y)<=getCol(x,y,x+w,y+h,y+h))
                                dp[x][y][x+w][y+h][1]=dp[x][y+1][x+w][y+h][0];
                            else
                                dp[x][y][x+w][y+h][1]=dp[x][y][x+w][y+h-1][0];
                        }
                    }
                }
            }
        }
        if(sum[m][n]-dp[1][1][m][n][1]==dp[1][1][m][n][1])
            cout<<sum[m][n]<<endl;
        else
            cout<<max(dp[1][1][m][n][1],sum[m][n]-dp[1][1][m][n][1])<<endl;
    }
    return 0;
}
