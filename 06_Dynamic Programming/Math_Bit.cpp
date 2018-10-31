int L,R,a[20];long long dp[20][2];
long long dfs(int pos,int fa,int st,bool limit)
{
    if(pos==-1) return 1;
    if(!limit&&dp[pos][st]!=-1) return dp[pos][st];
    int up=limit?a[pos]:9;
    long long ans=0;
    for(int i=0;i<=up;++i)
    {
        if(i==4) continue;
        else if(fa==6&&i==2) continue;
        ans+=dfs(pos-1,i,i==6,limit&&i==a[pos]);
    }
    if(!limit) dp[pos][st]=ans;
    return ans;
}
long long get(long long x)
{
    int pos=0;
    while(x){a[pos++]=x%10;x/=10;}
    return dfs(pos-1,0,0,1);
}
int main()
{
    while(~scanf("%d%d",&L,&R))
    {
        if(L==0&&R==0) break;
        memset(dp,-1,sizeof(dp));
        printf("%lld\n",get(R)-get(L-1));
    }
    return 0;
}
