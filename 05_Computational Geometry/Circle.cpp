/* Perimeter intersection*/
double cal(point c1,double r1,point c2,double r2)
{
    double d = sqrt(dis(c1,c2));
    if(r1+r2-d<-eps||fabs(r1-r2)-d>eps) return 0;
    double x = (d*d + r1*r1 - r2*r2)/(2*d);
    double t1 = acos(x / r1);
    double t2 = acos((d - x)/r2);
    return (t2*r2-t1*r1)*2;
}
/* Area intersection*/
double areaover(point c1,double r1,point c2,double r2)
{
    double d=sqrt(dis(c1,c2));
    if(r1+r2-d<-eps) return 0;
    if(fabs(r1-r2)-d>eps)
    {
        double r=min(r1,r2);
        return PI*r*r;
    }
    double x=(d*d+r1*r1-r2*r2)/(2*d);
    double t1=acos(x/r1);
    double t2=acos((d-x)/r2);
    return r1*r1*t1+r2*r2*t2-d*r1*sin(t1);
}
/ Triangle Outcenter */
point outcenter(point a,point b,point c)
{
    double a1=b.x-a.x,b1=b.y-a.y,c1=(a1*a1+b1*b1)/2;
    double a2=c.x-a.x,b2=c.y-a.y,c2=(a2*a2+b2*b2)/2;
    double d=a1*b2-a2*b1;
    return point(a.x+(c1*b2-c2*b1)/d,a.y+(a1*c2-a2*c1)/d);
}
