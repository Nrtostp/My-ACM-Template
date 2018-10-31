/* number of continue region sum of xor ==k*/
const int MAX=3e6+5;
int n,m,K,a[MAX],b[MAX],cnt[MAX],block;
struct Q
{
    int l,r,id;
    long long ans;
}q[MAX];
bool cmp1(Q a,Q b)
{
    return a.l/block==b.l/block?a.r<b.r:a.l/block<b.l/block;
}
bool cmp2(Q a,Q b)
{
    return a.id<b.id;
}
int main()
{
    while(~scanf("%d%d%d",&n,&m,&K))
    {
        b[0]=0;memset(cnt,0,sizeof(cnt));a[0]=0;
        for(int i=1;i<=n;++i) {scanf("%d",&a[i]);b[i]=b[i-1]^a[i];}
        for(int i=0;i<m;++i) {scanf("%d%d",&q[i].l,&q[i].r);q[i].id=i;--q[i].l;}
        block=sqrt(n);
        sort(q,q+m,cmp1);
        int L=q[0].l,R=q[0].l-1;long long ans=0;
        for(int i=0;i<m;++i)
        {
            while(R<q[i].r) {++R;ans+=cnt[b[R]^K];++cnt[b[R]];}
            while(R>q[i].r) {--cnt[b[R]];ans-=cnt[b[R]^K];--R;}
            while(L>q[i].l) {--L;ans+=cnt[b[L]^K];++cnt[b[L]];}
            while(L<q[i].l) {--cnt[b[L]];ans-=cnt[b[L]^K];++L;}
            q[i].ans=ans;
        }
        sort(q,q+m,cmp2);
        for(int i=0;i<m;++i) printf("%lld\n",q[i].ans);
    }
    return 0;
}
/* Mo with update:the min number not appear in thr times(of the numbers appear) */
const int MAX=2e5+5;
int n,m,cntq,cntc,cntid,block,a[MAX],now[MAX],vis[MAX],ans[MAX];
map<int,int>id;
struct P
{
    int l,r,t,ans;
    void is(int x1,int x2,int x3){l=x1;r=x2;t=x3;}
}q[MAX];
struct Q
{
    int pos,u,v,t;
    void is(int x1,int x2,int x3,int x4){pos=x1;u=x2;v=x3;t=x4;}
}c[MAX];
inline bool cmp1(P& x1,P& x2)
{
    if(x1.l/block!=x2.l/block) return x1.l<x2.l;
    if(x1.r/block!=x2.r/block) return x1.r<x2.r;
    return x1.t<x2.t;
}
inline bool cmp2(P& x1,P& x2){return x1.t<x2.t;}
inline void add(int x,int d)
{
    if(vis[x]>0)--ans[vis[x]];
    vis[x]+=d;
    if(vis[x]>0)++ans[vis[x]];
}
inline void change(int &x,int l,int r,int val)
{
    if(c[x].v==0) return ;
    if(c[x].pos>=l&&c[x].pos<=r)
    {
        add(a[c[x].pos],-1);
        add(val,1);
    }
    a[c[x].pos]=val;
}
inline int sid(int x)
{
    if(id[x]) return id[x];
    return id[x]=++cntid;
}
int main()
{
    int x,y,z;
    id.clear();cntq=cntid=0;memset(now,0,sizeof(now));memset(c,0,sizeof(c));
    scanf("%d%d",&n,&m);block=pow(n,2.0/3);
    for(int i=1;i<=n;++i) {scanf("%d",&a[i]);now[i]=a[i]=sid(a[i]);}
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&x,&y,&z);
        if(x==1) q[cntq++].is(y,z,i);
        else c[i].is(y,now[y],z=sid(z),i),now[y]=z;
    }
    sort(q,q+cntq,cmp1);
    int l=1,r=0,t=0;
    for(int i=0;i<cntq;++i)
    {
        while(r<q[i].r) add(a[++r],1);
        while(l<q[i].l) add(a[l++],-1);
        while(r>q[i].r) add(a[r--],-1);
        while(l>q[i].l) add(a[--l],1);
        while(t<q[i].t) ++t,change(t,l,r,c[t].v);
        while(t>q[i].t) change(t,l,r,c[t].u),--t;
        int k=1;while(ans[k]) ++k;q[i].ans=k;
    }
    sort(q,q+cntq,cmp2);
    for(int i=0;i<cntq;++i) printf("%d\n",q[i].ans);
    return 0;
}
/* Mo on thee:how many different on the path u to v*/
char buf[1 << 21], *p1 = buf, *p2 = buf;
using namespace std;
const int MAXN = 1e5 + 10;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int N, Q;
int belong[MAXN], block;
struct Query {
    int l, r, ID, lca, ans;
    bool operator < (const Query &rhs) const{
        return belong[l] == belong[rhs.l] ? r < rhs.r : belong[l] < belong[rhs.l];
    }
}q[MAXN];
vector<int>v[MAXN];
int a[MAXN], date[MAXN];
void Discretization() {
    sort(date + 1, date + N + 1);
    int num = unique(date + 1, date + N + 1) - date - 1;
    for(int i = 1; i <= N; i++) a[i] = lower_bound(date + 1, date + num + 1, a[i]) - date;    
}
int deep[MAXN], top[MAXN], fa[MAXN], siz[MAXN], son[MAXN], st[MAXN], ed[MAXN], pot[MAXN], tot;
void dfs1(int x, int _fa) {
    fa[x] = _fa; siz[x] = 1;
    st[x] = ++ tot; pot[tot] = x; 
    for(int i = 0; i < v[x].size(); i++) {
        int to = v[x][i];
        if(deep[to]) continue;
        deep[to] = deep[x] + 1;
        dfs1(to, x);
        siz[x] += siz[to];
        if(siz[to] > siz[son[x]]) son[x] = to;
    }
    ed[x] = ++tot; pot[tot] = x;
}
void dfs2(int x, int topfa) {
    top[x] = topfa;
    if(!son[x]) return ;
    dfs2(son[x], topfa);
    for(int i = 0; i < v[x].size(); i++) {
        int to = v[x][i];
        if(top[to]) continue;
            dfs2(to, to);
    }
}
int GetLca(int x, int y) {
    while(top[x] != top[y]) {
        if(deep[top[x]] < deep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return deep[x] < deep[y] ? x : y;
}
void DealAsk() {
    for(int i = 1; i <= Q; i++) {
        int x = read(), y = read();
        if(st[x] > st[y]) swap(x, y);
        int _lca = GetLca(x, y);
        q[i].ID = i;
        if(_lca == x) q[i].l = st[x], q[i]. r = st[y];
        else q[i].l = ed[x], q[i].r = st[y], q[i].lca = _lca;
    }
}
int Ans, out[MAXN], used[MAXN], happen[MAXN];
void add(int x) {
    if(++happen[x] == 1) Ans++;
}
void delet(int x) {
    if(--happen[x] == 0) Ans--;
}
void Add(int x) {
    used[x] ? delet(a[x]) : add(a[x]); used[x] ^= 1;
}
void Mo() {
    sort(q + 1, q + Q + 1);
    int l = 1, r = 0, fuck = 0;
    for(int i = 1; i <= Q; i++) {
        while(l < q[i].l) Add(pot[l]), l++, fuck++;
        while(l > q[i].l) l--, Add(pot[l]), fuck++;
        while(r < q[i].r) r++, Add(pot[r]), fuck++;
        while(r > q[i].r) Add(pot[r]), r--, fuck++;
        if(q[i].lca) Add(q[i].lca);
        q[i].ans = Ans;
        if(q[i].lca) Add(q[i].lca);
    }
    for(int i = 1; i <= Q; i++) out[q[i].ID] = q[i].ans;
    for(int i = 1; i <= Q; i++)
        printf("%d\n", out[i]);
}
int main() {
    N = read(); Q = read();
    block = sqrt(N);
    for(int i = 1; i <= N; i++) a[i] = date[i] = read();
    for(int i = 1; i <= N * 2; i++) belong[i] = i / block + 1;
    Discretization();
    for(int i = 1; i <= N - 1; i++) {
        int x = read(), y = read();
        v[x].push_back(y); v[y].push_back(x);
    }
    deep[1] = 1; dfs1(1, 0);
    dfs2(1, 1);
    DealAsk();
    Mo();
    return 0;
}
