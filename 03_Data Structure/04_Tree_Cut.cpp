struct P{int to,nxt;}e[MAX<<1];
struct Px{int l,r,v;Px(){l=r=-1;v=0;}void is(int a1,int a2,int a3){l=a1;r=a2;v=a3;}}b[MAX<<2];
int head[MAX],top[MAX],fa[MAX],deep[MAX],num[MAX],p[MAX],fp[MAX],son[MAX],tot,pos,n,m,a[MAX],lz[MAX<<2];
void init()
{
    tot=0;pos=1;
    memset(head,-1,sizeof(head));
    memset(son,-1,sizeof(son));
    memset(lz,-1,sizeof(lz));
}
void adde(int u,int v)
{
    e[tot].to=v;e[tot].nxt=head[u];head[u]=tot++;
    e[tot].to=u;e[tot].nxt=head[v];head[v]=tot++;
}
void dfs(int u,int pre,int d)
{
    deep[u]=d;fa[u]=pre;num[u]=1;
    for(int i=head[u];i!=-1;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v!=pre)
        {
            dfs(v,u,d+1);
            num[u]+=num[v];
            if(son[u]==-1||num[v]>num[son[u]]) son[u]=v;
        }
    }
}
void getpos(int u,int sp)
{
    top[u]=sp;p[u]=pos++;fp[p[u]]=u;
    if(son[u]==-1) return ;
    getpos(son[u],sp);
    for(int i=head[u];i!=-1;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v!=son[u]&&v!=fa[u]) getpos(v,v);
    }
}
inline Px merge_(const Px &x,const Px &y)//may not need
{
    if(x.v==0) return y;
    if(y.v==0) return x;
    Px t;
    t.is(x.l,y.r,x.v+y.v);
    if(x.r==y.l) --t.v;
    return t;
}
inline void pushup(int rt)
{
    b[rt].is(b[rt<<1].l,b[rt<<1|1].r,b[rt<<1].v+b[rt<<1|1].v);
    if(b[rt<<1].r==b[rt<<1|1].l) --b[rt].v;
}
inline void pushdown(int rt)
{
    b[rt<<1].is(lz[rt],lz[rt],1);
    b[rt<<1|1].is(lz[rt],lz[rt],1);
    lz[rt<<1]=lz[rt<<1|1]=lz[rt];
    lz[rt]=-1;
}
void build(int rt,int l,int r)
{
    if(l==r) {b[rt].is(a[fp[r]],a[fp[r]],1);return ;}
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}
void update(int rt,int l,int r,int L,int R,int v)
{
    if(L<=l&&R>=r) {b[rt].is(v,v,1);lz[rt]=v;return ;}
    if(lz[rt]!=-1) pushdown(rt);
    int mid=(l+r)>>1;
    if(L<=mid) update(rt<<1,l,mid,L,R,v);
    if(R>mid) update(rt<<1|1,mid+1,r,L,R,v);
    pushup(rt);
}
Px query(int rt,int l,int r,int L,int R)
{
    if(L<=l&&R>=r) return b[rt];
    if(lz[rt]!=-1) pushdown(rt);
    int mid=(l+r)>>1;Px t;
    if(L<=mid) t=query(rt<<1,l,mid,L,R);
    if(R>mid) t=merge_(t,query(rt<<1|1,mid+1,r,L,R));
    return t;
}
void update(int l,int r,int v)
{
    while(top[l]!=top[r])
    {
        if(deep[top[l]]<deep[top[r]]) swap(l,r);
        update(1,1,n,p[top[l]],p[l],v);
        l=fa[top[l]];
    }
    if(deep[l]>deep[r]) swap(l,r);
    update(1,1,n,p[l],p[r],v);
}
int query(int l,int r)
{
    Px L,R;//*
    while(top[l]!=top[r])
    {
        if(deep[top[l]]<deep[top[r]]) {swap(l,r);swap(L,R);}
        L=merge_(query(1,1,n,p[top[l]],p[l]),L);//*
        l=fa[top[l]];
    }
    if(deep[l]>deep[r]) {swap(l,r);swap(L,R);}
    R=merge_(query(1,1,n,p[l],p[r]),R);//*
    return L.v+R.v-(L.l==R.l?1:0);
}
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        init();
        dfs(1,0,0);getpos(1,1);
        build(1,1,n);
    }
    return 0;
}
