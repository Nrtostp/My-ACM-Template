long long gcd(long long x,long long y)
{
    return y==0?x:gcd(y,x%y);
}
long long lcm(long long x,long long y)
{
    return x/gcd(x,y)*y;
}
