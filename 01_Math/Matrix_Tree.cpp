#include<bits/stdc++.h>
using namespace std;
const int MAX=90;
const long long MOD=1e9;
int n,m,tot,a[MAX][MAX];
long long g[MAX][MAX];
char s[MAX][MAX];
void add(int x,int y)
{
    if(x>y) return ;
    ++g[x][x];++g[y][y];
    --g[x][y];--g[y][x];
}
long long gauss()
{
    long long ans=1;
    for(int i=1;i<tot;++i)
    {
        for(int j=i+1;j<tot;++j)
        while(g[j][i])
        {
            long long t=g[i][i]/g[j][i];
            for(int k=i;k<tot;++k) g[i][k]=(g[i][k]-t*g[j][k]+MOD)%MOD;
            swap(g[i],g[j]);
            ans=-ans;
        }
        ans=(ans*g[i][i])%MOD;
    }
    return (ans+MOD)%MOD;
}
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        memset(a,0,sizeof(a));tot=0;
        memset(g,0,sizeof(g));
        for(int i=1;i<=n;++i) scanf("%s",s[i]+1);
        for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j) if(s[i][j]=='.') a[i][j]=++tot;
        for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            int u,v;
            if(!(u=a[i][j])) continue;
            if(v=a[i-1][j]) add(u,v);
            if(v=a[i+1][j]) add(u,v);
            if(v=a[i][j-1]) add(u,v);
            if(v=a[i][j+1]) add(u,v);
        }
        printf("%lld\n",gauss());
    }
    return 0;
}
