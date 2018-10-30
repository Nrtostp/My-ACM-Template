const int MAX=1e2+5;
const long long MOD=1e9+7;
long long g[MAX][MAX];
void add(int x,int y)
{
    ++g[x][x];++g[y][y];
    --g[x][y];--g[y][x];
}
long long gauss()
{
    long long ans=1;
    for(int i=1;i<n;++i)
    {
        for(int j=i+1;j<n;++j)
        while(g[j][i])
        {
            long long t=g[i][i]/g[j][i];
            for(int k=i;k<n;++k) g[i][k]=(g[i][k]-t*g[j][k]+MOD)%MOD;
            swap(g[i],g[j]);
            ans=-ans;
        }
        ans=(ans*g[i][i])%MOD;
        if(!ans) return 0;
    }
    return (ans+MOD)%MOD;
}
