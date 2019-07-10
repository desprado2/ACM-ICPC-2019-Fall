#include<bits/stdc++.h>
#define N 400005
void mem(int a[],int len){for(int i=0;i<=len;i++)a[i]=0;}
using namespace std;

int n,m,t,i,j,k,l[N],r[N];
struct tzy{int x,y,c,id;} read[N],a[N];
bool cmpx(tzy a,tzy b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
bool cmpy(tzy a,tzy b){return a.y<b.y||a.y==b.y&&a.x<b.x;}
bool cmpc(tzy a,tzy b){return a.c<b.c;}
struct ord{int x,y;};
bool cmppos(int x,int y){return a[x].y<a[y].y||a[x].y==a[y].y&&a[x].x<a[y].x;}

int tree[N*2];
void ch(int x,int t)
{
	for (int i=x; i<=n; i+=i&(-i)) tree[i]+=t;
}
int Q(int x)
{
	int i,ret;
	for (i=x,ret=0; i; i-=i&(-i)) ret+=tree[i];
	return ret;
}
int query(int L,int R)
{
	if (R<L) return 0;
	return Q(R)-Q(L-1);
}
int ans,pos[N],pre[N],sum[N];
stack<ord> st[N];
int main()
{
	cin>>t;
	while (t--)
	{
		cin>>n>>m;
		mem(tree,n);
		for (i=1; i<=n; i++) {cin>>read[i].x>>read[i].y>>read[i].c; read[i].id=i;}
		int cntc,cntx,cnty;
		sort(read+1,read+n+1,cmpc);
		for (i=1,cntc=0; i<=n; i++)
			if (read[i].c!=read[i-1].c) a[read[i].id].c=++cntc;
				else a[read[i].id].c=cntc;
		sort(read+1,read+n+1,cmpy);
		for (i=1,cnty=0; i<=n; i++)
			if (read[i].y!=read[i-1].y) a[read[i].id].y=++cnty;
				else a[read[i].id].y=cnty;
		sort(read+1,read+n+1,cmpx);
		for (i=1,cntx=0; i<=n; i++)
			if (read[i].x!=read[i-1].x) a[read[i].id].x=++cntx;
				else a[read[i].id].x=cntx;
		sort(a+1,a+n+1,cmpx);
		ord tmp;
		mem(l,n); mem(r,n);
		for (i=1; i<=cntc; i++) {while(!st[i].empty())st[i].pop(); tmp.x=tmp.y=0,st[i].push(tmp);}
		for (i=1; i<=n; i++)
		{
			while (st[a[i].c].top().y>=a[i].y) st[a[i].c].pop();
			l[i]=(st[a[i].c].top()).x;
			tmp.x=a[i].x,tmp.y=a[i].y; st[a[i].c].push(tmp);
		}
		for (i=1; i<=cntc; i++) {while(!st[i].empty())st[i].pop(); tmp.x=cntx+1,tmp.y=0,st[i].push(tmp);}
		for (i=n; i; i--)
		{
			while (st[a[i].c].top().y>=a[i].y) st[a[i].c].pop();
			r[i]=(st[a[i].c].top()).x;
			tmp.x=a[i].x,tmp.y=a[i].y; st[a[i].c].push(tmp);
		}
		for (i=1; i<=n; i++)
			if (l[i]==a[i].x) r[i]=l[i];

		ans=0;
		for (i=1; i<=n; i++) pos[i]=i;
		sort(pos+1,pos+n+1,cmppos);
		for (i=1; i<=n; i=j+1)
		{
			for (j=i; j<n&&a[pos[j+1]].y==a[pos[j]].y; j++);
			for (k=i; k<=j; k++)
				ans=max(ans,query(l[pos[k]]+1,r[pos[k]]-1));
			for (k=i; k<=j; k++)
				ch(a[pos[k]].x,1);
		}
		mem(sum,n),mem(pre,n);
		for (i=1; i<=n; i++) sum[a[i].x]++;
		for (i=1; i<=cntx; i++) sum[i]=sum[i-1]+sum[i];
		for (i=1; i<=n; i++)
		{
			ans=max(ans,sum[a[i].x-1]-sum[pre[a[i].c]]);
			pre[a[i].c]=a[i].x;
		}
		for (i=1; i<=cntc; i++)
			ans=max(ans,n-sum[pre[i]]);
		cout<<ans<<endl;
	}
	return 0;
}
