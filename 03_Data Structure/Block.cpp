const int eps=1e-8;
int a[MAX],aa[MAX],b[MAX],c[MAX],cc[MAX][2],block,cnt;
void sort(int x)
{
    int L=cc[x][0],R=cc[x][1];
    for(int k=L;k<=R;k++) aa[k]=a[k];
    sort(aa+L,aa+R+1);
}
void add(int l,int r,int w)
{
    bool bl=l==cc[c[l]][0],br=r==cc[c[r]][1];
    if(c[l]==c[r]){for(int k=l;k<=r;k++) a[k]+=w; sort(c[l]);}
    else
    {
        if(!bl){for(int k=l;k<=cc[c[l]][1];k++) a[k]+=w; sort(c[l]);}
        if(!br){for(int k=cc[c[r]][0];k<=r;k++) a[k]+=w; sort(c[r]);}
        for(int k=c[l]+1-bl;k<c[r]+br;k++) b[k]+=w;
    }
}
int query(int l,int r,int w)
{
    int ans=0;
    bool bl=l==cc[c[l]][0],br=r==cc[c[r]][1];
    if(c[l]==c[r]){for(int k=l,v=w-b[c[l]];k<=r;k++) ans+=a[k]>=v;}
    else
    {
        if(!bl)for(int k=l,v=w-b[c[l]];k<=cc[c[l]][1];k++) ans+=a[k]>=v;
        if(!br)for(int k=cc[c[r]][0],v=w-b[c[r]];k<=r;k++) ans+=a[k]>=v;
        for(int k=c[l]+1-bl;k<c[r]+br;k++)
        {
            int L=cc[k][0],R=cc[k][1],v=w-b[k],mid;
            while(L<=R)
            {
                mid=(L+R)>>1;
                aa[mid]>=v?R=mid-1:L=mid+1;
            }
            ans+=cc[k][1]-L+1;
        }
    }
    return ans;
}
int main()
{
    block=(int)(sqrt(n)+eps),cnt=1;
    for(int k=1;k<=n;k++) c[k]=k%block==0?cnt++:cnt;
    for(int k=1;k<=cnt;k++) {cc[k][0]=k*block-block+1;cc[k][1]=k*block;}cc[cnt][1]=n;
    for(int k=1;k<=cnt;k++) sort(k);
    add(x,y,z);query(x,y,z);
    return 0;
}
