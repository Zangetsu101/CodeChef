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

#define N 101
#define mod 1000000009
#define inf 1e9

typedef long long ll;
typedef unsigned long long ull;

int data[100001];
int temp[N];
ll dp[2][N];
ll transition[N][N];
ll fact[100001];
ll inv[100001];

ll modPower(ll a,int b)
{
    ll res=1;
    while(b)
    {
        if(b&1)
            res*=a,res%=mod;
        a*=a,a%=mod;
        b>>=1;
    }
    return res;
}

ll modInverse(int a)
{
    return modPower(a,mod-2);
}

ll nCr(int a,int b)
{
    ll res=fact[a]*inv[b];
    res%=mod;
    res*=inv[a-b];
    res%=mod;
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("Input.txt","r",stdin);
//    freopen("Output.txt","w",stdout);
    fact[0]=inv[0]=1;
    for(int i=1;i<100001;i++)
        fact[i]=(fact[i-1]*i)%mod,inv[i]=modInverse(fact[i]);
    int cases;
    cin>>cases;
    while(cases--)
    {
        int n,q;
        cin>>n>>q;
        for(int i=0;i<n;i++)
            cin>>data[i];
        for(int k=0;k<q;k++)
        {
            ms(temp,0);
            ms(dp,0);
            ms(transition,0);
            int m;
            cin>>m;
            for(int i=0;i<n;i++)
            {
                int t=data[i];
                temp[((t%m)+m)%m]++;
            }
            for(int i=0;i<m;i++)
            {
                for(int j=1;j<=temp[i];j++)
                    transition[i][(i*j)%m]+=nCr(temp[i],j),transition[i][(i*j)%m]%=mod;
            }
            int v;
            dp[1][0]=1;
            for(int i=0;i<m;i++)
            {
                v=i&1;
                for(int j=0;j<m;j++)
                    dp[v][j]=dp[v^1][j];
                for(int j=0;j<m;j++)
                {
                    for(int l=0;l<m;l++)
                        dp[v][j]+=transition[i][l]*dp[v^1][(j-l+m)%m],dp[v][j]%=mod;
                }
            }
            cout<<dp[v][0]<<endl;
        }
    }
    return 0;
}
