const double eps=1e-8;
struct point
{
    double x,y;
    point(){}
    point(double a,double b){x=a;y=b;}
    point operator -(const point &a)const{return point(x-a.x,y-a.y);}
    double operator ^(const point &a)const{return x*a.y-y*a.x;}
    double operator *(const point &a)const{return x*a.x+y*a.y;}
}p[MAX],b[MAX];
int top,n;
double cross(point a,point b,point c){return (b-a)^(c-a);}//Triangle'Area*Area
double dis(point a,point b){return (a-b)*(a-b);}//Point Dis
bool cmp(point a,point b)
{
    double tmp=cross(p[0],a,b);
    if(tmp>eps||(fabs(tmp)<eps&&dis(p[0],a)-dis(p[0],b)>eps)) return 1;
    return 0;
}
void graham()
{
    int u=0;top=0;
    for(int k=1;k<n;k++) if(p[u].y-p[k].y>eps||(fabs(p[u].y-p[k].y)<eps&&p[u].x-p[k].x>eps)) u=k;
    swap(p[u],p[0]);
    sort(p+1,p+n,cmp);
    if(n>0) {b[0]=p[0];top++;}
    if(n>1) {b[1]=p[1];top++;}
    if(n<3) return ;
    for(int i=2;i<n;i++)
    {
        while(top>1&&cross(b[top-2],b[top-1],p[i])<eps) top--;
        b[top++]=p[i];
    }
}
/*Zhou Chang*/
int main()
{
    double sum=0; scanf("%d",&n);
    for(int k=0;k<n;k++) scanf("%lf%lf",&p[k].x,&p[k].y);
    graham();b[top]=b[0];
    for(int k=1;k<=top;k++) sum+=sqrt(dis(b[k],b[k-1]));
    printf("%.2f\n",sum);
    return 0;
}
/* Area */
int main()
{
    double sum=0; scanf("%d",&n);
    for(int k=0;k<n;k++) scanf("%lf%lf",&p[k].x,&p[k].y);
    graham();
    for(int k=1;k<top-1;k++) sum+=fabs(cross(b[0],b[k],b[k+1]));//Sum of Triangle Area
    printf("%d\n",(int)(sum/100));
    return 0;
}
/*Farthest point Dis*/
double rotating()
{
    double ans=0; b[top]=b[0];
    for(int k=0,i=1;k<=top;k++)
    {
        while(fabs(cross(b[k],b[i+1],b[k+1]))-fabs(cross(b[k],b[i],b[k+1]))>eps) i=(i+1)%top;
        ans=max(ans,dis(b[i],b[k]));
    }
    return ans;
}
/*Minimum width*/
double rotating()
{
    double ans=0x3f3f3f3f; b[top]=b[0];
    for(int k=0,i=1;k<=top;k++)
    {
        while(fabs(cross(b[k],b[i+1],b[k+1]))-fabs(cross(b[k],b[i],b[k+1]))>eps) i=(i+1)%top;
        ans=min(ans,fabs(cross(b[k],b[k+1],b[i])/sqrt(dis(b[k],b[k+1]))));
    }
    return ans;
}
/* Max Area of Triangle*/
double rotating()
{
    double ans=0;
    for(int k=0;k<top;k++)
    {
        int i=(k+1)%top,j=(i+1)%top;
        while(i!=k&&j!=k)
        {
            ans=max(ans,fabs(cross(b[k],b[i],b[j])));
            while(fabs(cross(b[k],b[i+1],b[j]))-fabs(cross(b[k],b[i],b[j]))>eps) i=(i+1)%top;
            j=(j+1)%top;
        }
    }
    return ans;
}
/* The max/min Dis of two convex hull */
const double eps=1e-8;
const double INF=1e99;
struct point{}p[MAX],b1[MAX],b2[MAX];
int top1,top2;
double min(double a,double b){return a-b<-eps?a:b;}
double cross(point a,point b,point c){return (b-a)^(c-a);}
double multi(point a,point b,point c){return (b-a)*(c-a);}
double dis(point a,point b){return (a-b)*(a-b);}
double dist(point a,point b,point c)//Line Dis
{
    point d;
    double t=multi(b,a,c)/dis(b,c);
    if(t>-eps&&t-1<eps) d=point(b.x+(c.x-b.x)*t,b.y+(c.y-b.y)*t);
    else
    {
        if(dis(a,b)-dis(a,c)<-eps) d=b;
        else d=c;
    }
    return dis(a,d);
}
double distence(point a,point b,point c,point d){return min(min(dist(a,c,d),dist(b,c,d)),min(dist(c,a,b),dist(d,a,b)));}//Two Line
bool cmp(point a,point b)
{
    double tmp=cross(p[0],a,b);
    if(tmp>eps||(fabs(tmp)<eps&&dis(p[0],a)-dis(p[0],b)>eps)) return 1;
    return 0;
}
void graham(point *b,int n,int &top)
{
    int u=0;top=0;
    for(int k=1;k<n;k++) if(p[u].y-p[k].y>eps||(fabs(p[u].y-p[k].y)<eps&&p[u].x-p[k].x>eps)) u=k;
    swap(p[u],p[0]);
    sort(p+1,p+n,cmp);
    if(n>0) {b[0]=p[0];top++;}
    if(n>1) {b[1]=p[1];top++;}
    if(n<3) return ;
    for(int i=2;i<n;i++)
    {
        while(top>1&&cross(b[top-2],b[top-1],p[i])<eps) top--;
        b[top++]=p[i];
    }
}
double rotating(point *a,int n,point *b,int m)
{
    int i1=0,i2=0;
    for(int k=0;k<n;k++) if(a[k].y-a[i1].y<-eps) i1=k;
    for(int k=0;k<m;k++) if(b[k].y-b[i2].y>eps) i2=k;
    a[n]=a[0];b[m]=b[0];
    double tmp,ans=INF;
    for(int k=0;k<n;k++)
    {
        while((tmp=cross(a[i1+1],b[i2+1],a[i1])-cross(a[i1+1],b[i2],a[i1]))>eps) i2=(i2+1)%m;
        if(tmp<-eps) ans=min(ans,dist(b[i2],a[i1],a[i1+1]));
        else ans=min(ans,distence(a[i1],a[i1+1],b[i2],b[i2+1]));
        i1=(i1+1)%n;
    }
    return ans;
}
int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m)&&(n||m))
    {
        for(int k=0;k<n;k++) scanf("%lf%lf",&p[k].x,&p[k].y);
        graham(b1,n,top1);
        for(int k=0;k<m;k++) scanf("%lf%lf",&p[k].x,&p[k].y);
        graham(b2,m,top2);
        printf("%0.5f\n",sqrt(min(rotating(b1,top1,b2,top2),rotating(b2,top2,b1,top1))));
    }
    return 0;
}
/* Minest rectangle contain convex hull*/
const double eps=1e-8;
const double INF=1e99;
struct point{}p[MAX],b[MAX];
int top,n;
double min(double a,double b){return a-b<-eps?a:b;}
double cross(point a,point b,point c){return (b-a)^(c-a);}
double multi(point a,point b,point c){return (b-a)*(c-a);}
double dis(point a,point b){return (a-b)*(a-b);}
bool cmp(point a,point b)
{
    double tmp=cross(p[0],a,b);
    if(tmp>eps||(fabs(tmp)<eps&&dis(p[0],a)-dis(p[0],b)>eps)) return 1;
    return 0;
}
void graham()
{
    int u=0;top=0;
    for(int k=1;k<n;k++) if(p[u].y-p[k].y>eps||(fabs(p[u].y-p[k].y)<eps&&p[u].x-p[k].x>eps)) u=k;
    swap(p[u],p[0]);
    sort(p+1,p+n,cmp);
    if(n>0) {b[0]=p[0];top++;}
    if(n>1) {b[1]=p[1];top++;}
    if(n<3) return ;
    for(int i=2;i<n;i++)
    {
        while(top>1&&cross(b[top-2],b[top-1],p[i])<eps) top--;
        b[top++]=p[i];
    }
}
double rotating()
{
    int r=1,u=1,l;
    double ans=INF;
    b[top]=b[0];
    for(int k=0;k<top;k++)
    {
        while(cross(b[k],b[k+1],b[u+1])-cross(b[k],b[k+1],b[u])>-eps) u=(u+1)%top;
        while(multi(b[k],b[k+1],b[r+1])-multi(b[k],b[k+1],b[r])>eps) r=(r+1)%top;
        l=k==0?r:l;
        while(multi(b[k],b[k+1],b[l+1])-multi(b[k],b[k+1],b[l])<eps) l=(l+1)%top;
        ans=min(ans,fabs(cross(b[k],b[k+1],b[u]))*fabs(multi(b[k],b[k+1],b[r])-multi(b[k],b[k+1],b[l]))/dis(b[k],b[k+1]));
    }
    return ans;
}
int main()
{
    int t;scanf("%d",&t);
    for(int tc=1;tc<=t;tc++)
    {
        scanf("%d",&n);n*=4;
        for(int k=0;k<n;k++) scanf("%lf%lf",&p[k].x,&p[k].y);
        graham();
        printf("Case #%d:\n%d\n",tc,(int)(rotating()+0.5));
    }
    return 0;
}
