/*
2 string LCA
multi string LCA
*/
struct Tire
{
    static const int MAXN=26;
    int nxt[MAX][MAXN],f[MAX],L[MAX],last,tot;
    void init()
    {
        last=tot=0;
        memset(nxt[0],-1,sizeof(nxt[0]));
        f[0]=-1;L[0]=0;
    }
    void add(int x)
    {
        int p=last,np=++tot;
        L[np]=L[p]+1;
        memset(nxt[np],-1,sizeof(nxt[np]));
        while(~p&&nxt[p][x]==-1) nxt[p][x]=np,p=f[p];
        if(p==-1) f[np]=0;
        else
        {
            int q=nxt[p][x];
            if(L[q]!=L[p]+1)
            {
                int nq=++tot;
                L[nq]=L[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
                f[nq]=f[q];
                f[q]=f[np]=nq;
                while(~p&&nxt[p][x]==q) nxt[p][x]=nq,p=f[p];
            }
            else f[np]=q;
        }
        last=np;
    }
    int find(char *s)
    {
        int len=strlen(s);
        int res=0,tmp=0,u=0;
        for(int i=0;i<len;++i)
        {
            int x=s[i]-'a';
            if(~nxt[u][x]) ++tmp,u=nxt[u][x];
            else
            {
                while(~u&&nxt[u][x]==-1) u=f[u];
                if(~u) tmp=L[u]+1,u=nxt[u][x];
                else tmp=0,u=0;
            }
            res=max(res,tmp);
            //Max[u]=max(Max[u],tmp);//multi string
        }
        //for(int i=tot;i>=1;--i) Max[f[i]]=max(Max[f[i]],Max[i]);//multi string
        //for(int i=0;i<=tot;++i) Min[i]=min(Min[i],Max[i]);//multi string
        return res;
    }
    /*
    int cal()//multi string
    {
        int res=0;
        for(int i=0;i<=tot;++i) res=max(res,Min[i]);
        return res;
    }
    */
    void cal()//topsort
    {
        memset(in,0,sizeof(in));
        for(int i=1;i<=tot;++i) ++in[f[i]];
        queue<int >q;
        for(int i=1;i<=tot;++i) if(!in[i]) q.push(i);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            if(f[u]==-1) continue;
            rt[f[u]]+=rt[u];
            if(--in[f[u]]==0) q.push(f[u]);
        }
        memset(ans,0,sizeof(ans));
        for(int i=1;i<=tot;++i) ans[L[i]]=max(ans[L[i]],rt[i]);//the max number of length L[i] strings
    }
}SAM;
int main()
{
    SAM.init();
    for(int i=0;i<len;++i) SAM.add(s[i]-'a');
    printf("%d\n",SAM.find(s));
    return 0;
}
/*
L[i]-L[f[i]]:number of different substrings
*/
