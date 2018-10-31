const int MAX=55;const double eps=1e-9;int n;
struct P{double x,y,z;}p[MAX];
double dist(P ta,P tb){return sqrt((ta.x-tb.x)*(ta.x-tb.x)+(ta.y-tb.y)*(ta.y-tb.y)+(ta.z-tb.z)*(ta.z-tb.z));}
double getans()
{
    P s=p[0];
    double t=100;//change
    double dt=0.98;//change
    double ans=1e9;
    while(t>eps)
    {
        int k=0;
        for(int i=0;i<n;++i) if(dist(s,p[i])>dist(s,p[k])) k=i;
        double d=dist(s,p[k]);
        ans=min(ans,d);
        s.x+=(p[k].x-s.x)/d*t;
        s.y+=(p[k].y-s.y)/d*t;
        s.z+=(p[k].z-s.z)/d*t;
        t*=dt;
    }
    return ans;
}
int main()
{
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=0;i<n;++i) scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].z);
        printf("%.5f\n",getans());
    }
}
