#include<bits/stdc++.h>
#define inf 1000000005
#define N 500005
using namespace std;

int n,m,i,j,k,p,t,ans[N];
int SA[N],rank[N],x[N],SAy[N],tmp[N],sortedx[N],height[N];//tmp:Ͱ
string s;
bool cmp(int *a,int x,int y,int l)
{
	return (a[x]==a[y])&&(a[x+l]==a[y+l])&&y;
}
void getSA()
{
	int i,j,k;
	for (i=0; i<=m; i++) tmp[i]=0;
	for (i=1; i<=n; i++) x[i]=s[i],tmp[x[i]]++;
	for (i='a'; i<='z'; i++) tmp[i]+=tmp[i-1];
	for (i=n; i; i--) SA[tmp[x[i]]--]=i;

	for (j=1; j<n; j<<=1,m=p)
	{
		for (p=0,i=n-j+1; i<=n; i++) SAy[++p]=i;
		for (i=1; i<=n; i++) if (SA[i]>j) SAy[++p]=SA[i]-j;//SAy[i]表示第二关键字排名为i的数，第一关键字的位置
		for (i=1; i<=n; i++) sortedx[i]=x[SAy[i]];

		for (i=0; i<=m; i++) tmp[i]=0;
		for (i=1; i<=n; i++) tmp[sortedx[i]]++;
		for (i=1; i<=m; i++) tmp[i]+=tmp[i-1];
		for (i=n; i; i--) SA[tmp[sortedx[i]]--]=SAy[i];

		memcpy(SAy,x,sizeof(x)), p=0;
		for (i=1; i<=n; i++)
			x[SA[i]]=cmp(SAy,SA[i],SA[i-1],j)?p:++p;
	}

	for (i=1; i<=n; i++) rank[SA[i]]=i;
}
void getheight()
{
	int i,j,k=0;
	for (i=1; i<=n; i++)
	{
		if (rank[i]==1) {height[i]=0; continue;}
		if (k) k--;
		for (j=SA[rank[i]-1]; j+k<=n&&i+k<=n&&s[j+k]==s[i+k]; k++);
		height[rank[i]]=k;
	}
}
int main()
{
	cin>>s;
	n=s.size(),m='z'; s=" "+s;

	getSA();
	getheight();
}
//SA[i]: 排名第i的是几号后缀
//rank[i]: 第i号后缀的排名
//height[i]: suffix(SA[i])和suffix(SA[i-1])的最长公共前缀
//LCP(i,j) = min_{i+1}^{j} {height[rank[k]]}
