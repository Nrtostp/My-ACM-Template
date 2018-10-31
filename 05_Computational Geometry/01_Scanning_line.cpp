/* Overlap area */
const int MAX=2*1e3+1e2;
const double eps=1e-10;
struct node{double l,r,y;int v;}edge[MAX<<1];
double hash_[MAX<<1],one[MAX<<2],two[MAX<<2];int mark[MAX<<2],cnt,n;
inline bool cmp(const node &a,const node &b){return a.y-b.y<-eps;}
inline int find_(const double &x)
{
    int l=1,r=cnt,mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(hash_[mid]-x<-eps) l=mid+1;
        else if(hash_[mid]-x>eps) r=mid-1;
        else break;
    }
    return mid;
}
void pushup(int rt,int l,int r)
{
	  if(mark[rt]==0)
    {
        one[rt]=one[rt<<1]+one[rt<<1|1];
        two[rt]=two[rt<<1]+two[rt<<1|1];
    }
    else if(mark[rt]==1)
    {
        one[rt]=hash_[r+1]-hash_[l];
        two[rt]=one[rt<<1]+one[rt<<1|1];
    }
    else if(mark[rt]>=2)
    {
        one[rt]=two[rt]=hash_[r+1]-hash_[l];
    }
    /* Union
    if(mark[rt]) sum[rt]=hash[r+1]-hash[l];
  	else if(l==r) sum[rt]=0;
	  else sum[rt]=sum[rt<<1]+sum[rt<<1|1];*/
}
void update(int rt,int l,int r,int L,int R,int v)
{
	  if(L<=l&&R>=r)
	  {
	      mark[rt]+=v;
	      pushup(rt,l,r);
	      return;
    }
    int mid=(l+r)>>1;
    if(L<=mid) update(rt<<1,l,mid,L,R,v);
    if(R>mid) update(rt<<1|1,mid+1,r,L,R,v);
    pushup(rt,l,r);
}
int main()
{
    int t;double a,b,c,d;
    scanf("%d",&t);
    while(t--)
    {
        double ans=0;
        memset(one,0,sizeof(one));memset(two,0,sizeof(two));memset(mark,0,sizeof(mark));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
            edge[i*2-1].l=edge[i*2].l=a;
            edge[i*2-1].r=edge[i*2].r=c;
            edge[i*2-1].y=b;edge[i*2].y=d;
            edge[i*2-1].v=1;edge[i*2].v=-1;
            hash_[i*2-1]=a;hash_[i*2]=c;
        }
        sort(hash_+1,hash_+n*2+1);
        cnt=unique(hash_+1,hash_+n*2+1)-hash_-1;
        sort(edge+1,edge+n*2+1,cmp);
        for(int i=1;i<n*2;i++)
        {
            int L=find_(edge[i].l),R=find_(edge[i].r)-1;
            update(1,1,cnt,L,R,edge[i].v);
            ans+=two[1]*(edge[i+1].y-edge[i].y);
        }
        printf("%.2f\n",ans);
    }
    return 0;
}
