/*
PT.L-2:The Number different of Palindromes
num[i]:The Number different of Palindromes in Palindromes String i
cnt[i]:The Number appear of Palindromes String i
*/
struct Trie
{
    static const int MAXN=26;
    int nxt[MAX][MAXN],f[MAX],cnt[MAX],num[MAX],len[MAX],c[MAX],last,n,L;
    int newnode(int x)
    {
        for(int i=0;i<MAXN;++i) nxt[L][i]=0;
        cnt[L]=num[L]=0;len[L]=x;return L++;
    }
    void init()
    {
        L=0;newnode(0);newnode(-1);
        last=0;n=0;c[n]=-1;f[0]=1;
    }
    int getf(int x)
    {
        while(c[n-len[x]-1]!=c[n]) x=f[x];
        return x;
    }
    void add(int x)
    {
        x-='a';c[++n]=x;
        int cur=getf(last);
        if(!nxt[cur][x])
        {
            int now=newnode(len[cur]+2);
            f[now]=nxt[getf(f[cur])][x];
            nxt[cur][x]=now;
            num[now]=num[f[now]]+1;
        }
        ++cnt[last=nxt[cur][x]];
    }
    void count(){for(int i=L-1;i>=2;--i) cnt[f[i]]+=cnt[i];}
}PT;
int main()
{
    PT.init();for(int i=0;i<l;++i) PT.add(char i);PT.count();
    for(int i=2;i<PT.L;++i) //??
    return 0;
}
/*the number of two string' same Palindromes pairs*/
long long dfs(int u,int v)
{
    long long tmp=0;
    for(int i=0;i<26;++i) if(PT1.nxt[u][i]&&PT2.nxt[v][i])
    {
        tmp+=1ll*PT1.cnt[PT1.nxt[u][i]]*PT2.cnt[PT2.nxt[v][i]];
        tmp+=dfs(PT1.nxt[u][i],PT2.nxt[v][i]);
    }
    return tmp;
}
