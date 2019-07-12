int kmp(const string& s,const string& pat)
{
	int n=s.size(),m=pat.size(),j,k,next[m+5];
	next[0]=0;
	for (j=1,k=0; j<m; j++)
	{
		while (k&&pat[k]!=pat[j]) k=next[k-1];
		if (pat[k]==pat[j]) k++;
		next[j]=k;
	}
	for (j=k=0; j<n; j++)
	{
		while (k&&pat[k]!=s[j]) k=next[k-1];
		if (pat[k]==s[j]) k++;
		if (k==m) return j;
	}
	return INT_MAX;
}
