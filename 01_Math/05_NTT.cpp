/* MOD：469762049、998244353、1004535809 ;this problem need pow*/
const int g=3;//in this problem
long long fact[MAX],inv[MAX],bit[MAX],a[MAX<<1],b[MAX<<1],c[MAX],ni;int t,n,L;
void init()
{
    fact[0]=inv[0]=bit[0]=1;
    for(int i=1;i<MAX;i++)
    {
        fact[i]=fact[i-1]*i%MOD;
        inv[i]=inv[i-1]*pow(i,MOD-2,MOD)%MOD;
        bit[i]=bit[i-1]*2%MOD;
    }
}
void rader(long long *f_)
{
    int i,j,k;
    for(i=1,j=L/2;i<L-1;++i)
    {
        if(i<j) swap(f_[i],f_[j]);
        k=L/2;
        while(j>=k){j-=k;k>>=1;}
        if(j<k) j+=k;
    }
}
void ntt(long long *f_,int t)
{
    rader(f_);
    for(int i=2;i<=L;i<<=1)
    {
        long long wn=pow(g,(MOD-1)/i,MOD);
        if(t==-1) wn=pow(wn,MOD-2,MOD);
        for(int j=0;j<L;j+=i)
        {
            long long e=1;
            for(int k=j;k<j+i/2;++k)
            {
                long long u=f_[k];
                long long v=e*f_[k+i/2]%MOD;
                f_[k]=(u+v)%MOD;
                f_[k+i/2]=(u-v+MOD)%MOD;
                e=e*wn%MOD;
            }
        }
    }
    if(t==-1) for(int i=0;i<L;++i) f_[i]=f_[i]*ni%MOD;
}
int main()
{
    init();scanf("%d",&t);
    while(t--)
    {
        memset(a,0,sizeof(a));memset(b,0,sizeof(b));
        scanf("%d",&n);L=1;
        while(L<n<<1) L<<=1;
        ni=pow(L,MOD-2,MOD);
        for(int i=1;i<=n;++i) scanf("%I64d",&c[i]);
        sort(c+1,c+n+1,greater<long long>());
        for(int i=0;i<n;++i)
        {
            a[i]=bit[n-i]*inv[i]%MOD;
            b[i]=c[n-i]*fact[n-i-1]%MOD;
        }
        ntt(a,1);ntt(b,1);
        for(int i=0;i<L;++i) a[i]=a[i]*b[i]%MOD;
        ntt(a,-1);
        long long r=inv[2],ans=0;
        for(int i=1;i<=n;++i)
        {
            ans=(ans+a[n-i]*inv[i-1]%MOD*r%MOD)%MOD;
            r=r*inv[2]%MOD;
            printf("%I64d ",ans);
        }
    }
    return 0;
}
