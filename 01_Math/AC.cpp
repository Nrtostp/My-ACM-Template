/*
AC->build Tire ->build Mat or Dp
*/
const int MAX=1e5+5;
struct Trie
{
    static const int MAXN=26;
    //MAXN will change 
    int nxt[MAX][MAXN],f[MAX],e[MAX];
    int rt,L;
    int newnode()
    {
        for(int i=0;i<MAXN;++i) nxt[L][i]=-1;
        e[L++]=0;
        return L-1;
    }
    void init(){L=0;rt=newnode();}
    void insert(char *buf)
    {
        int len=strlen(buf),now=rt;
        for(int i=0;i<len;++i)
        {
            int x=buf[i]-'a';
            if(nxt[now][x]==-1) nxt[now][x]=newnode();
            now=nxt[now][x];
        }
        ++e[now];
        //e[now]=1;e[now]=id;//e[now]=1<<id;
    }
    void build()
    {
        queue<int>q;
        f[rt]=rt;
        for(int i=0;i<MAXN;++i)
        if(nxt[rt][i]==-1) nxt[rt][i]=rt;
        else
        {
            f[nxt[rt][i]]=rt;
            q.push(nxt[rt][i]);
        }
        while(!q.empty())
        {
            int now=q.front();q.pop();
            for(int i=0;i<MAXN;++i)
            if(nxt[now][i]==-1) nxt[now][i]=nxt[f[now]][i];
            else
            {
                f[nxt[now][i]]=nxt[f[now]][i];
                q.push(nxt[now][i]);
                //e[nxt[now][i]] op e[f[nxt[now][i]]]; | or + or =
            }
        }
    }
    int query(char *buf,other..)
    {
        int len=strlen(buf),now=rt,res=0;
        for(int i=0;i<len;++i)
        {
            now=nxt[now][buf[i]-'a'];
            int tmp=now;
            while(tmp!=rt)
            {
                res+=e[tmp];
                e[tmp]=0;
                tmp=f[tmp];
            }
        }
        return res;
    }
    void get(Mat &a)
    {
        for(int i=0;i<L;++i)if(!e[i])
        for(int j=0;j<MAXN;++j)if(!e[nxt[i][j]])
        a.m[i][nxt[i][j]]=(a.m[i][nxt[i][j]]+1)%MOD;
    }
    void spfa(int k)//need dis[] and g[][] and pos[cnt++]
    {
        queue<int>q;
        memset(dis,-1,sizeof(dis));
        dis[pos[k]]=0;
        q.push(pos[k]);
        while(!q.empty())
        {
            int now=q.front();q.pop();
            for(int i=0;i<2;++i)
            {
                int tmp=nxt[now][i];
                if(dis[tmp]<0&&e[tmp]>=0)
                {
                    dis[tmp]=dis[now]+1;
                    q.push(tmp);
                }
            }
        }
        for(int i=0;i<cnt;++i) g[k][i]=dis[pos[i]];
    }
}AC;
int main()
{
    AC.init();
	for(){AC.insert(char []);}
	AC.build();
	/* get g[][] and then dp find a shortest path
	pos[0]=0;cnt=1;
    for(int i=0;i<AC.L;++i)if(AC.e[i]>0) pos[cnt++]=i;
    for(int i=0;i<cnt;++i) AC.spfa(i);
	*/
	/*
	int xi=AC.nxt[i][j],xhash=hash|?;//save the state
	dp[xi][xhash]=max(dp[xi][xhash],dp[i][hash]+AC.e[xi]);
	for(int i=0;i<AC.L;++i) ans=max(ans,dp[i][hash]);
	*/
	/*
	if resort the string and find a special string
	please be careful about the cnt[char] can be max like that
	for(int j=0;j<AC.MAXN;++j)
    {
    	if(j==0&&a==cnt[0]) continue;
	}
	*/
	/*less val and less string
	strcpy(str[0][0],"");strcpy(ans,"");
        int max_=0;
        for(int i=0;i<n;++i)
        for(int j=0;j<AC.L;++j)if(dp[i][j]>=0)
        {
            strcpy(tmp,str[i][j]);
            int len=strlen(tmp);
            for(int k=0;k<AC.MAXN;++k)
            {
                int xi=i+1,xj=AC.nxt[j][k],t=dp[i][j];
                tmp[len]='a'+k;
                tmp[len+1]='\0';
                if(AC.e[xj]) t+=val[AC.e[xj]];
                if(dp[xi][xj]<t||(dp[xi][xj]==t&&cmp(tmp,str[xi][xj])))
                {
                    dp[xi][xj]=t;
                    strcpy(str[xi][xj],tmp);
                    if(max_<t||(max_==t&&cmp(tmp,ans)))
                    {
                        max_=t;
                        strcpy(ans,tmp);
                    }
                }
            }
        }
	*/
}
/* if need shortest minimum order string */
bool cmp(char *a,char *b)
{
    int al=strlen(a),bl=strlen(b);
    return al==bl?strcmp(a,b)<0:al<bl;
}
