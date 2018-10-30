const int MAX=1e2+5;
const long long MOD=1e9+7;
long long g[MAX][MAX];
void add(int x,int y)
{
    ++g[x][x];++g[y][y];
    --g[x][y];--g[y][x];
}
long long gauss()
{
    long long ans=1;
    for(int i=1;i<n;++i)
    {
        for(int j=i+1;j<n;++j)
        while(g[j][i])
        {
            long long t=g[i][i]/g[j][i];
            for(int k=i;k<n;++k) g[i][k]=(g[i][k]-t*g[j][k]+MOD)%MOD;
            swap(g[i],g[j]);
            ans=-ans;
        }
        ans=(ans*g[i][i])%MOD;
        if(!ans) return 0;
    }
    return (ans+MOD)%MOD;
}
/*minimum tree*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=101; 
const int M=1001;
ll n,m,p,ans;
vector<int>gra[N];
struct edge{int u,v,w;}e[M];
int cmp(edge a,edge b){return a.w<b.w;}
ll mat[N][N],g[N][N];
ll fa[N],ka[N],vis[N];
ll det(ll c[][N],ll n){
    ll i,j,k,t,ret=1;
    for(i=0;i<n;i++)
    for(j=0;j<n;j++) c[i][j]%=p;
    for(i=0; i<n; i++){
        for(j=i+1; j<n; j++)
            while(c[j][i]){
                t=c[i][i]/c[j][i];
                for(k=i; k<n; k++)
                    c[i][k]=(c[i][k]-c[j][k]*t)%p;
                swap(c[i],c[j]);
                ret=-ret;
            }
        if(c[i][i]==0)
            return 0L;
        ret=ret*c[i][i]%p;
    }
    return (ret+p)%p;
}
ll find(ll a,ll f[]){return f[a]==a?a:find(f[a],f);}
void matrix_tree(){
    for(int i=0;i<n;i++)if(vis[i]){
        gra[find(i,ka)].push_back(i);
        vis[i]=0;
    }
    for(int i=0;i<n;i++)
    if(gra[i].size()>1){
        memset(mat,0,sizeof mat);
        int len=gra[i].size();
        for(int j=0;j<len;j++)
        for(int k=j+1;k<len;k++){
            int u=gra[i][j],v=gra[i][k];
            if(g[u][v]){
                mat[k][j]=(mat[j][k]-=g[u][v]);
                mat[k][k]+=g[u][v];mat[j][j]+=g[u][v];
            }
        }
        ans=ans*det(mat,gra[i].size()-1)%p;
        for(int j=0;j<len;j++)fa[gra[i][j]]=i;//suo dian
    }
    for(int i=0;i<n;i++)
    {
        gra[i].clear();
        ka[i]=fa[i]=find(i,fa);
    }
}
int main(){
    while(scanf("%lld%lld%lld",&n,&m,&p),n){
        for(int i=0;i<m;i++){
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            u--;v--;
            e[i]=(edge){u,v,w};
        }
        sort(e,e+m,cmp);
        memset(g,0,sizeof g);
        ans=1;
        for(ll i=0;i<n;i++)ka[i]=fa[i]=i;
        for(ll i=0;i<=m;i++){
            if(i&&e[i].w!=e[i-1].w||i==m)
                matrix_tree();
            ll u=find(e[i].u,fa),v=find(e[i].v,fa);
            if(u!=v)
            {
                vis[v]=vis[u]=1;
                ka[find(u,ka)]=find(v,ka);
                g[u][v]++,g[v][u]++;
            }
        }
        int flag=1;
        for(int i=1;i<n;i++)if(fa[i]!=fa[i-1])flag=0;
        printf("%lld\n",flag?ans%p:0);
    }
}
