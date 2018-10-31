const int MAX=1<<17;
const double PI=acos(-1.0);
typedef complex<double> C;
map<int,int>mp;map<int,int>::iterator p;
C a1[MAX],a2[MAX],a3[MAX],ans[MAX];int n,L,cnt[MAX];
void rader(C *c_)
{
    for(int i=1,j=L/2,k;i<L-1;++i)
    {
        if(i<j) swap(c_[i],c_[j]);
        k=L/2;
        while(j>=k){j-=k;k/=2;}
        if(j<k) j+=k;
    }
}
void fft(C *c_,int v)
{
    rader(c_);
    for(int i=2;i<=L;i<<=1)
    {
        C wn(cos(-2.0*v*PI/i),sin(-2.0*v*PI/i));
        for(int j=0;j<L;j+=i)
        {
            C w(1,0);
            for(int k=j;k<j+i/2;++k)
            {
                C u=c_[k];
                C t=w*c_[k+i/2];
                c_[k]=u+t;
                c_[k+i/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(v==-1) for(int i=0;i<L;++i) c_[i].real(c_[i].real()/L);
}
int main()
{
    int x;scanf("%d",&n);mp.clear();
    for(int i=0;i<n;++i)
    {
        scanf("%d",&x);x+=20000;
        if(mp[x]) ++mp[x];
        else mp[x]=1;
    }
    for(p=mp.begin();p!=mp.end();++p) a1[p->first]=a2[p->first*2]=a3[p->first*3]=C(p->second,0);L=MAX;
    /*L=1;while(L<L1<<1||L<L2<<1) L<<=1;
      L=L1+L2-1;while(ans[L]<=0&&L>0) --L;*/
    fft(a1,1);fft(a2,1);fft(a3,1);
    for(int i=0;i<L;++i) ans[i]=a1[i]*a1[i]*a1[i]-a1[i]*a2[i]*3.0+a3[i]*2.0;
    fft(ans,-1);
    for(int i=0;i<L;++i)
    {
        long long tmp=(long long)(ans[i].real()+0.5)/6;
        if(tmp) printf("%d : %I64d\n",i-60000,tmp);
    }
    return 0;
}
