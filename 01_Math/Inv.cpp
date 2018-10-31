long long ex_gcd(long long a,long long b,long long &x,long long &y)
{
    if(a==0&&b==0) return -1;
    if(b==0){x=1;y=0;return a;}
    long long d=ex_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
long long inv(long long a,long long n)
{
    long long x,y;
    long long d=ex_gcd(a,n,x,y);
    if(d==1) return (x%n+n)%n;
    else return -1;
}
long long inv_(long long a,long long m)
{
    if(a==1) return 1;
    return inv_(m%a,m)*(m-m/a)%m;
}
long long inv_(long long a,long long mod)
{
    return pow(a,mod-2,mod);
}
void inv_()
{
    inv[0]=inv[1]=1;
    for(int i=2;i<MAX;++i) inv[i]=((MOD-MOD/i)*inv[MOD%i])%MOD;
}
