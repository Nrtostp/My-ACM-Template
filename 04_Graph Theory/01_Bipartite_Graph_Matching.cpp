/*one Matching */
const int MAX1=5*1e3+1;
int linker[MAX1],n;
bool used[MAX1];
bool dfs(int u)
{
    for (int i=head[u];i!=-1;i=edge[i].next)
    {
        int v=edge[i].to;
        if(!used[v])
        {
            used[v]=1;
            if(linker[v]==-1||dfs(linker[v]))
            {
                linker[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
int hungary()
{
    int res=0;
    memset(linker,-1,sizeof(linker));
    for(int u=1;u<=n;u++)
    {
        memset(used,0,sizeof(used));
        if(dfs(u)) res++;//return 0;
    }
    return res;//return 1;
}
/* multi Matching */
int lg[MAX1][MAX2],inker[MAX2][MAX1],vlink[MAX2]，num[MAX2];bool used[MAX2];
bool dfs(int u)
{
    for(int v=1;v<=m;v++) if(g[u][v]&&!used[v])
    {
        used[v]=1;
        if(vlink[v]<num[v]) {linker[v][++vlink[v]]=u;return 1;}
        for(int k=1;k<=vlink[v];k++) if(dfs(linker[v][k]))
        {
            linker[v][k]=u;
            return 1;
        }
    }
    return 0;
}
int hungary()
{
    memset(linker,-1,sizeof(linker));
    memset(vlink,0,sizeof(vlink));
    for(int u=1;u<=n;u++)
    {
        memset(used,0,sizeof(used));
        if(!dfs(u)) return 0;
    }
    return 1;
}
/* max val Matching -KM*/
int linker[MAX],lx[MAX],ly[MAX],slack[MAX];
int visx[MAX],visy[MAX],w[MAX][MAX];
int dfs(int x)
{
    visx[x]=1;
    for(int y=1;y<=ny;y++)
    {
        if(visy[y]) continue;
        int tmp=lx[x]+ly[y]-w[x][y];
        if(tmp==0)
        {
            visy[y]=1;
            if(linker[y]==-1||dfs(linker[y])) {linker[y]=x;return 1;}
        }
        else if(slack[y]>tmp) slack[y]=tmp;
    }
    return 0;
}
int km()
{
    int i,j;
    memset(linker,-1,sizeof(linker));
    memset(ly,0,sizeof(ly));
    for(i=1;i<=nx;i++)
    for(j=1,lx[i]=-INF;j<=ny;j++)
        if(w[i][j]>lx[i]) lx[i]=w[i][j];
    for(int x=1;x<=nx;x++)
    {
        for(i=1;i<=ny;i++) slack[i]=INF;
        while(1)
        {
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(x)) break;
            int d=INF;
            for(i=1;i<=ny;i++)
                if(!visy[i] && d>slack[i]) d=slack[i];
            for(i=1;i<=nx;i++)
                if(visx[i]) lx[i]-=d;
            for(i=1;i<=ny;i++)
                if(visy[i]) ly[i]+=d;
                else slack[i]-=d;
        }
    }
    int res=0;
    for(i=1;i<=ny;i++)
        if(linker[i]!=-1) res+=w[linker[i]][i];
    return res;
}
int main()
{
    int n,m;char c;int top1,top2;pair<int,int>a[MAX],b[MAX];
    while(~scanf("%d%d",&n,&m)&&n&&m)
    {
        top1=top2=0;memset(w,0,sizeof(w));
        for(int k=0;k<n;k++)
        {
            c=getchar();
            for(int i=0;i<m;i++)
            {
                c=getchar();
                if(c=='H') a[++top1]=make_pair(k,i);
                else if(c=='m') b[++top2]=make_pair(k,i);
            }
        }
        for(int k=1;k<=top1;k++)
        for(int i=1;i<=top2;i++)
            w[k][i]=-abs(a[k].x-b[i].x)-abs(a[k].y-b[i].y);
        nx=top1;ny=top2;
        printf("%d\n",-km());
    }
    return 0;
}
