#include<bits/stdc++.h>
using namespace std;
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
