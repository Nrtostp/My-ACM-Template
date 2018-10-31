/* rotate */
for(i=1;i*i<n;++i)
{
    if(n%i) continue;
    ans+=euler(n/i)%p*pow(n%p,i-1,p)%p+euler(i)%p*pow(n%p,n/i-1,p)%p;
}
if(i*i==n) ans+=euler(i)%p*pow(n%p,i-1,p)%p;
/* rotate+Symmetric */
for(i=1;i*i<n;++i)
{
    if(n%i) continue;
    ans+=euler(n/i)*pow_(3,i)+euler(i)*pow_(3,n/i);
}
if(i*i==n) ans+=euler(i)*pow_(3,i);
ans/=n;
ans+=(pow_(3,(n+1)/2)+pow_(3,n/2+1))/2;
