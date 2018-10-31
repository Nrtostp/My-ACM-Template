/*Longest Palindrome string*/
const long long P=131;
long long power[MAX],ha1[MAX],ha2[MAX];
bool check(int l1,int r1,int l2,int r2)
{
    long long tmp1=ha1[r1]-ha1[l1-1]*power[r1-l1+1];
    long long tmp2=ha2[r2]-ha2[l2+1]*power[l2+1-r2];
    return tmp1==tmp2;
}
int main()
{
    power[0]=1;for(int i=1;i<MAX-1;++i) power[i]=power[i-1]*P;
 	L=strlen(s+1);
    ha1[0]=ha2[L+1]=0;
    for(int i=1;i<=L;++i) ha1[i]=ha1[i-1]*P+s[i]-'a';
    for(int i=L;i>=1;--i) ha2[i]=ha2[i+1]*P+s[i]-'a';
	while(l<=r){mid;if(check(i-mid,i-1,i+mid,i+1));else;}// fen ji&ou
}
/*multi hash */
const int HASH=10;
int AC[HASH]={131,137,139,149,151,157,163,167,173,179};
int ACC[HASH]={200003,200009,200017,200023,200029,200033,200041,200063,200087,200117};
long long bas[MAX][HASH],sum1[MAX][HASH];
bool check(int index,int x,int len)
{
    long long ha1=((sum1[x+len-1][index]-sum1[x-1][index]*bas[len][index]%ACC[index])%ACC[index]+ACC[index])%ACC[index];
    long long ha2=((sum1[n-x+1][index]-sum1[n-x-len+1][index]*bas[len][index]%ACC[index])%ACC[index]+ACC[index])%ACC[index];
    if(ha1==ha2) return true;
    else return false;
}
bool check(int x,int len)
{
    for(int i=0;i<HASH;i++)
        if(!check(i,x,len)) return false;
    return true;
}
int main()
{
    for (int i=0;i<HASH;i++)
    {
        bas[0][i]=1;
        for(int j=1;j<=n;j++) bas[j][i]=bas[j-1][i]*AC[i]%ACC[i];
        for(int j=1;j<=n;j++) sum1[j][i]=(sum1[j-1][i]*AC[i]%ACC[i]+s[j]-'a'+1)%ACC[i];
    }
    return 0;
}
