for(int i=0;i<100;++i)//1e-6
{
    midl=l+(r-l)/3.0;midr=r-(r-l)/3.0;
    lr=getr(midl),rr=getr(midr);
    if(lr-rr>eps) l=midl;
    else r=midr;
}
