const int MAX=1e2+5;const long long MOD=1e9+7;
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
/*minimum tree*/
int n,m,p,g[MAX][MAX],vis[MAX],fa[MAX],ka[MAX];
long long ans,mat[MAX][MAX];
vector<int>gra[MAX];
struct P{int u,v,w;}e[MAX];
bool cmp(P ta,P tb){return ta.w<tb.w;}
long long gauss(int n)
{
    long long ans=1;
    for(int i=0;i<n;++i)
    {
        for(int j=i+1;j<n;++j)
        while(mat[j][i])
        {
            long long t=mat[i][i]/mat[j][i];
            for(int k=i;k<n;++k) mat[i][k]=(mat[i][k]-t*mat[j][k]+p)%p;
            swap(mat[i],mat[j]);
            ans=-ans;
        }
        ans=(ans*mat[i][i])%p;
        if(!ans) return 0;
    }
    return (ans+p)%p;
}
int find_(int x,int y[]) {return x==y[x]?x:find_(y[x],y);}
void matrix_tree()
{
    for(int i=0;i<n;++i) if(vis[i]){gra[find_(i,ka)].push_back(i);vis[i]=0;}
    for(int i=0;i<n;++i) if(gra[i].size()>1)
    {
        memset(mat,0,sizeof(mat));
        int len=gra[i].size();
        for(int j=0;j<len;++j)
        for(int k=j+1;k<len;++k)
        {
            int u=gra[i][j],v=gra[i][k];
            if(g[u][v])
            {
                mat[k][j]=(mat[j][k]-=g[u][v]);
                mat[k][k]+=g[u][v];mat[j][j]+=g[u][v];
            }
        }
        ans=ans*gauss(gra[i].size()-1)%p;
        for(int j=0;j<len;++j) fa[gra[i][j]]=i;
    }
    for(int i=0;i<n;++i) {gra[i].clear();ka[i]=fa[i]=find_(i,fa);}
}
int main()
{
    while(~scanf("%d%d%d",&n,&m,&p))
    {
        if(n==0&&m==0&&p==0) break;
        memset(g,0,sizeof(g));ans=1;
        for(int i=0;i<m;++i) {scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);--e[i].u;--e[i].v;}
        sort(e,e+m,cmp);
        for(int i=0;i<n;++i) ka[i]=fa[i]=i;
        for(int i=0;i<=m;++i)
        {
            if((i&&e[i].w!=e[i-1].w)||i==m) matrix_tree();
            long long u=find_(e[i].u,fa),v=find_(e[i].v,fa);
            if(u!=v)
            {
                vis[v]=vis[u]=1;
                ka[find_(u,ka)]=find_(v,ka);
                ++g[u][v],++g[v][u];
            }
        }
        int flag=1;
        for(int i=1;i<n;++i) if(fa[i]!=fa[i-1]) flag=0;
        printf("%lld\n",flag?ans%p:0);
    }
    return 0;
}

