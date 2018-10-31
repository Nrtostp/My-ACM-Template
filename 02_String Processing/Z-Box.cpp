/*
z[i]:string'sa[i] compare with string the length-LCP
S=P+$+T
z[strlen(P)+1~~strlen(P)+strlen(T)]==length(T)--'s idex -strlen(P)-1:the place P appear in T
S=T+$+P
the number of z[strlen(T)+1~~strlen(T)+strlen(P)]!=0:the number of T'sa[i] is P'prefix 
*/
void z-box()
{
    z[0]=n;
	int j=1,k;
	for (int i=1;i<n;i=k)
	{
		if (j<i) j=i;
		while (j<n&&S[j]==S[j-i]) j++;
		z[i]=j-i;
		k=i+1;
		while (k+z[k-i]<j)
		{
			z[k]=z[k-i];k++;
		}
	}
}
