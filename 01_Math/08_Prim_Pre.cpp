int euler(int n)
{
    int ans=n;
    for(int i=2;i*i<=n;i++)if(n%i==0)
    {
        ans-=ans/i;
        while(n%i==0) n/=i;
    }
    if(n>1) ans-=ans/n;
    return ans;
}
/* phi and prim*/
bool mark[MAX];int phi[MAX],prim[MAX],tot;
void phi_prim(int n)
{
    memset(mark,0,sizeof(mark));
    phi[1]=1;tot=0;
    for(int i=2;i<=n;i++)
    {
        if(!mark[i]){prim[++tot]=i;phi[i]=i-1;}
        for(int j=1;j<=tot;j++)
        {
            int x=prim[j];
            if(i*x>n) break;
            mark[i*x]=1;
            if(i%x==0){phi[i*x]=phi[i]*x;break;}
            else phi[i*x]=phi[i]*phi[x];
        }
    }
}
/* mo and du*/
const int MAX=1e7+5;
bool vis[MAX];int prim[MAX],mu[MAX],fac[MAX],tot,pcnt;
map<long long,long long>dp;
void moblus()
{
    mu[1]=1;tot=0;
    for(int i=2;i<MAX;i++)
    {
        if(!vis[i]) {prim[tot++]=i;mu[i]=-1;}
        for(int j=0;j<tot&&i*prim[j]<MAX;j++)
        {
            vis[i*prim[j]]=1;
            if(i%prim[j]) mu[i*prim[j]]=-mu[i];
            else {mu[i*prim[j]]=0;break;}
        }
    }
    for(int i=2;i<MAX;++i) mu[i]+=mu[i-1];//phi same
}
long long M(long long x)
{
    if(x<MAX) return mu[x];
    if(dp[x]) return dp[x];
    long long sum=1;//sum=0 phi->x*(x+1)/2;
    for(long long l=2,r;l<=x;l=r+1)
    {
        r=x/(x/l);
        sum-=M(x/l)*(r-l+1);
        //sum+=M(x/l)*(r-l+1)
    }
    return dp[x]=sum;//dp[x]=x*(x+1)/2-sum
}
