/* dp[i][j]=min(dp[i][j],dp[k][j-1]+add[k+1][i]) */
int a[MAX1],dp[MAX1][MAX2],add[MAX1][MAX1],s[MAX1][MAX2];
void init (int n,int m)
{
    for (int k=1;k<=n;k++) read(a[k]);
    for (int i=1;i<n;i++)
    for (int j=i+1;j<=n;j++)
        add[i][j]=add[i][j-1]+a[j]-a[(i+j)>>1];
    for (int k=1;k<=n;k++)
    {
        dp[k][1]=add[1][k];
        s[k][1]=1;
    }
}
int main ()
{
    int n,m;read(n);read(m);init(n,m);
    for (int i=2;i<=m;i++)
    {
        s[n+1][i]=n;
        for (int j=n;j>i;j--)
        {
            dp[j][i]=INF;
            for (int k=s[j][i-1];k<=s[j+1][i];k++) if(dp[j][i]>dp[k][i-1]+add[k+1][j])
            {
                dp[j][i]=dp[k][i-1]+add[k+1][j];
                s[j][i]=k;
            }
        }
    }
    printf ("%d\n",dp[n][m]);
    return 0;
}
