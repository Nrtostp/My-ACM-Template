#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+1;
long long n,m,MOD;
long long fact[MAX];
inline long long inv_(long long a)
{
    if(a==1) return 1;
    return inv_(MOD%a)*(MOD-MOD/a)%MOD;
}
inline void init()
{
    fact[0]=1;
    for(int i=1;i<=MOD;i++) fact[i]=(fact[i-1]*i)%MOD;
}
inline long long C(long long a,long long b)
{
    if(b>a) return 0;
    return fact[a]*inv_(fact[a-b]*fact[b]%MOD)%MOD;
}
inline long long lucas(long long a,long long b)
{
    if(a<MOD&&b<MOD) return C(a,b);
    return lucas(a/MOD,b/MOD)*C(a%MOD,b%MOD)%MOD;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%I64d%I64d%I64d",&n,&m,&MOD);
        init();
        printf("%I64d\n",lucas(n+m,m));
    }
    return 0;
}
/* Chinese Left */
#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+5;
long long n,m,k,MOD,ans[MAX],m1[MAX];
long long pow(long long a,int k,long long mod)//快速幂取模
{
    long long b=1;
    while(k)
    {
        if(k&1) b=b*a%mod;
        a=a*a%mod;
        k>>=1;
    }
    return b;
}
inline long long C(long long a,long long b)
{
    if(b>a) return 0;
    long long x=1,y,z;
    for(int i=1;i<=b;++i)
    {
        y=(a+i-b)%MOD;
        z=i%MOD;
        x=x*(y*pow(z,MOD-2,MOD)%MOD)%MOD;
    }
    return x;
}
inline long long lucas(long long a,long long b)
{
    if(a<MOD&&b<MOD) return C(a,b);
    return lucas(a/MOD,b/MOD)*C(a%MOD,b%MOD)%MOD;
}
long long ex_gcd(long long a,long long b,long long &x,long long &y)
{
    if(b==0){x=1;y=0;return a;}
    long long d=ex_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
long long muli(long long a,long long b,long long mod)
{
    a=(a%mod+mod)%mod;
    b=(b%mod+mod)%mod;
    long long ret=0;
    while(b)
    {
        if(b&1){ret+=a;if(ret>=mod)ret-=mod;}
        b>>=1;a<<=1;
        if(a>=mod) a-=mod;
    }
    return ret;
}
long long china()
{
    long long M=1,d,y,x=0;
    for(int i=0;i<k;++i) M*=m1[i];
    for(int i=0;i<k;++i)
    {
        long long w=M/m1[i];
        ex_gcd(m1[i],w,d,y);
        x=(x+muli(muli(y,w,M),ans[i],M));
    }
    return (x+M)%M;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%I64d%I64d%I64d",&n,&m,&k);
        for(int i=0;i<k;++i) scanf("%I64d",&m1[i]);
        for(int i=0;i<k;++i) {MOD=m1[i];ans[i]=lucas(n,m);}
        printf("%I64d\n",china());
    }
    return 0;
}
