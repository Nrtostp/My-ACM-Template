void update(int &x,int l,int r,int p,int v)
{
    x=++cnt;if(l==r){val[x]=v;return;}
    int mid=(l+r)>>1;
    if(p<=mid) update(ls[x],l,mid,p,v);
    else update(rs[x],mid+1,r,p,v);
    val[x]=min(val[ls[x]],val[rs[x]]);
}
int merge_(int u,int v)
{
    if(!u) return v;
    if(!v) return u;
    int x=++cnt;
    ls[x]=merge_(ls[u],ls[v]);
    rs[x]=merge_(rs[u],rs[v]);
    if(ls[x]||rs[x]) val[x]=min(val[ls[x]],val[rs[x]]);
    else val[x]=min(val[u],val[v]);
    return x;
}
int query(int x,int l,int r,int L,int R)
{
    if(!x) return INF;
    if(l==L&&r==R) return val[x];
    int mid=(l+r)>>1;
    if(R<=mid) return query(ls[x],l,mid,L,R);
    if(L>mid) return query(rs[x],mid+1,r,L,R);
    return min(query(ls[x],l,mid,L,mid),query(rs[x],mid+1,r,mid+1,R));
}
void dfs(int u,int fa)
{
    update(rt[u],1,100000,d[u],a[u]);
    for(int i=head[u];~i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==fa) continue;
        d[v]=d[u]+1;
        dfs(v,u);
        rt[u]=merge_(rt[u],rt[v]);
    }
}
