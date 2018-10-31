/* get n! divide :need pow.cpp prim.cpp */
int fac[MAX];
void factor(int a,int b)
{
    memset(fac,0,sizeof(fac));int i;
    for(i=1;i<=prim[0]&&prim[i]<=a;i++)
    {
        int tmp=a;
        while(tmp){fac[i]+=tmp/prim[i];tmp/=prim[i];}
    }
    fac[0]=i;
    for(i=1;i<=prim[0]&&prim[i]<=b;i++)
    {
        int tmp=b;
        while(tmp){fac[i]-=tmp/prim[i];tmp/=prim[i];}
    }
    for(i=1;i<=prim[0]&&prim[i]<=a-b;i++)
    {
        int tmp=a-b;
        while(tmp){fac[i]-=tmp/prim[i];tmp/=prim[i];}
    }
}
long long C(int a,int b)
{
    factor(a,b);long long c=1;
    for(int i=1;i<fac[0];i++) if(fac[i]) c=c*pow(prim[i],fac[i],MOD)%MOD;
    return c;
}
/* get n divide */
int fac[MAX][2],facnt;
int factor(long long x)
{
    memset(fac,0,sizeof(fac));facnt=0;
    long long tmp=x;
    for(int i=1;prim[i]<=tmp/prim[i];i++)
    {
        fac[facnt][1]=0;
        if(tmp%prim[i]==0)
        {
            fac[facnt][0]=prim[i];
            while(tmp%prim[i]==0){fac[facnt][1]++;tmp/=prim[i];}
            facnt++;
        }
    }
    if(tmp!=1){fac[facnt][0]=tmp;fac[facnt++][1]=1;}
    return facnt;
}
