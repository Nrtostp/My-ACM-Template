/the k-max number of region */
int root[MAX],a[MAX],n,m,cnt;
struct P{int l,r,v;}b[MAX*25];
vector<int >v;
int id(int x){return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
void update(int l,int r,int &x,int y,int pos)
{
    b[++cnt]=b[y];++b[cnt].v;x=cnt;
    if(l==r) return ;
    int mid=(l+r)>>1;
    if(pos<=mid) update(l,mid,b[x].l,b[y].l,pos);
    else update(mid+1,r,b[x].r,b[y].r,pos);
}
int query(int l,int r,int x,int y,int k)
{
    if(l==r) return l;
    int mid=(l+r)>>1;
    int sum=b[b[y].l].v-b[b[x].l].v;
    if(sum>=k) return query(l,mid,b[x].l,b[y].l,k);
    else return query(mid+1,r,b[x].r,b[y].r,k-sum);
}
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        cnt=0;v.clear();
        for(int i=1;i<=n;++i) scanf("%d",&a[i]),v.push_back(a[i]);
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        for(int i=1;i<=n;++i) update(1,n,root[i],root[i-1],id(a[i]));
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d%d",&x,&y,&k);
            printf("%d\n",v[query(1,n,root[x-1],root[y],k)-1]);
        }
    }
    return 0;
}
