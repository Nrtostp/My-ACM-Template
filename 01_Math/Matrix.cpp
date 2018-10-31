struct Mat
{
    long long m[3][3];
    Mat(){memset(m,0,sizeof(m));}
};
Mat multi(const Mat &a,const Mat &b)
{
    Mat c;
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)if(a.m[j][i]!=0)
    for(int k=0;k<3;k++)if(b.m[i][k]!=0)
    c.m[j][k]=(c.m[j][k]+a.m[j][i]*b.m[i][k]%MOD)%MOD;
    return c;
}
Mat pow(Mat &a,int k)
{
    Mat b;
    for(int i=0;i<3;i++) b.m[i][i]=1;
    while(k)
    {
        if(k&1) b=multi(b,a);
        a=multi(a,a);
        k>>=1;
    }
    return b;
}
