long long pow(long long a,int k,long long mod)
{
    long long b=1;
    while(k){if(k&1) b=b*a%mod;a=a*a%mod;k>>=1;}
    return b;
}
