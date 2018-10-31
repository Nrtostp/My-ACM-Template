/* get the number pair of point which dis<c */
struct P{int to,nxt,v;void is(int x1,int x2,int x3){to=x1;nxt=x2;v=x3;}}e[MAX<<1];
int head[MAX],sz[MAX],dis[MAX],maxp[MAX],rem[MAX],cnt,sum,rt,ans;
bool vis[MAX];
void init()
{
    cnt=ans=rt=0;rem[0]=0;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
}
void adde(int u,int v,int w)
{
    e[cnt].is(v,head[u],w);head[u]=cnt++;
    e[cnt].is(u,head[v],w);head[v]=cnt++;
}
void getrt(int u,int pa)
{
    sz[u]=1; maxp[u]=0;
    for(int i=head[u];i!=-1;i=e[i].nxt)
    {
        int to=e[i].to;
        if(to==pa||vis[to]) continue;
        getrt(to,u);
        sz[u]+=sz[to];//update the number of subnode in root [u],[to] is [u]‘s subnode
        maxp[u]=max(maxp[u],sz[to]);//update the max of root [u],if sz [to] is greater
    }
    maxp[u]=max(maxp[u],sum-sz[u]);//in_ex
    if(maxp[u]<maxp[rt]) rt=u;
}
void getdis(int u,int fa)
{
    rem[++rem[0]]=dis[u];
    for(int i=head[u];i!=-1;i=e[i].nxt)
    {
        int to=e[i].to;
        if(to==fa||vis[to])continue;
        dis[to]=dis[u]+e[i].v;
        getdis(to,u);
    }
}
int cal(int u,int ct)
{
    dis[u]=ct;rem[0]=0;
    getdis(u,0);
    sort(rem+1,rem+rem[0]+1);
    int l=1,r=rem[0],x=0;
    while(l<r) if(rem[l]+rem[r]<=m){x+=r-l;++l;} else --r;
    //=c:for(int l=1;l<r;++l){while(rem[l]+rem[r]==m) ++x;--r;}
    return x;
}
int divide(int u)
{
    vis[u]=1;ans+=cal(u,0);
    for(int i=head[u];i!=-1;i=e[i].nxt)//divide the subtree
    {
        int to=e[i].to;
        if(vis[to])continue;
        ans-=cal(to,e[i].v);
        sum=sz[to];rt=0;
        getrt(to,0); divide(rt);
    }
    return ans;
}
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;init();
        for(int i=1;i<n;++i){scanf("%d%d%d",&x,&y,&z);adde(x,y,z);}
        maxp[rt]=sum=n;getrt(1,0);
        printf("%d\n",divide(rt));
    }
    return 0;
}
