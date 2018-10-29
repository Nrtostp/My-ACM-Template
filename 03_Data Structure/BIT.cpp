/*point update region query*/
void add(int x,int v)
{
    while(x<=n) c[x]+=v,x+=x&(-x);
}
int get(int r)
{
    int sum=0;
    while(r) sum+=c[r],r-=r&(-r);
    return sum;
}
int get(int l, int r)
{
    return get(r)-get(l-1);
}
/*point update region query*/
void add(int r, int v)
{
    while(r<=n) c[r]+=v,r+=r&(-r);
}
void add(int l,int r,int x)
{
    add(l,x),add(r+1,-x);
}
int get(int x)
{
    int sum=0;
    while(x) sum+=c[x],x-=x&(-x);
    return sum;
}
/* region update region query*/
void add(int r,int v)
{
    for(int i=r;i<=n;i+=i&(-i)){c1[i]+=v;c2[i]+=r*v;}
}
void add(int l,int r,int v)
{
    add(l,v);add(r+1,-v);
}
int get(int r)
{
    int sum=0;
    for(int i=r;i>0;i-=i&(-i)) sum+=(r+1)*c1[i]-c2[i];
    return sum;
}
int get(int l,int r)
{
    return get(r)-get(l-1);
}
