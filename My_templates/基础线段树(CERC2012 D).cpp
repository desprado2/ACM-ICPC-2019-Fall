#include<bits/stdc++.h>
#define mem(a) memset(a,0,sizeof(a))
#define N 200005
#define inf 1e9+10
using namespace std;

int n,m,t,i,j,l,r,cnt,pre[N];
struct tzy{int id,n;} a[N];
bool cmp(tzy a,tzy b){return a.n<b.n||a.n==b.n&&a.id<b.id;}

struct seg{int min,l,r,tag;} b[N*20];
void btree(int x,int l,int r)
{
	b[x].l=l,b[x].r=r;
	if (l==r) {b[x].min=b[x].tag=0; return;}//lazy标记一定要清0!!!!!
	int mid=(l+r)/2,lc=x*2,rc=x*2+1;
	btree(lc,l,mid); btree(rc,mid+1,r);
	b[x].min=min(b[lc].min,b[rc].min);b[x].tag=0;
}
void update(int x)
{
	if (b[x].l==b[x].r) {b[x].min-=b[x].tag; b[x].tag=0; return;}
	int lc=x*2,rc=x*2+1;
	b[x].min=min(b[lc].min,b[rc].min)-b[x].tag;
}
void down(int x)
{
	int lc=x*2,rc=x*2+1;
	b[lc].tag+=b[x].tag,b[rc].tag+=b[x].tag;
	update(lc),update(rc);
	b[x].tag=0;//标记必须消掉!!!!!
}
void ch(int L,int R,int t,int x)
{
	if (b[x].l>=L&&b[x].r<=R) {b[x].tag+=t; update(x); return;}//更新了就滚出去,千万不要pushdown免得push了叶子节点
	int lc=x*2,rc=x*2+1;
	down(x);
	if (b[lc].r>=L) ch(L,R,t,lc);
	if (b[rc].l<=R) ch(L,R,t,rc);
	update(x);//先pushdown，再递归，最后更新.
}
int query(int x,int L,int R)
{
	if (b[x].l>=L&&b[x].r<=R) return b[x].min;
	int lc=x*2,rc=x*2+1,ret=inf;
	down(x);
	if (b[lc].r>=L) ret=min(ret,query(lc,L,R));
	if (b[rc].l<=R) ret=min(ret,query(rc,L,R));
	update(x);
	return ret;
}
int main()
{
	std::ios::sync_with_stdio(false);
	cin>>t;
	while (t--)
	{
		cin>>n;
		for (i=1; i<=n; i++) {cin>>a[i].n; a[i].id=i;}
		a[0].n=-1;
		sort(a+1,a+n+1,cmp);
		for (i=1; i<=n; i++)
			if (a[i].n!=a[i-1].n) pre[a[i].id]=0;
			else pre[a[i].id]=a[i-1].id;
		bool fl=1;
		btree(1,1,n);
		for (i=1; i<=n; i++)
		{
			ch(pre[i]+1,i,-1,1);
			if (pre[i]) ch(pre[pre[i]]+1,pre[i],1,1);
			if (query(1,1,i)==0) {fl=0; break;}
		}
		if (fl) cout<<"non-boring\n";
			else cout<<"boring\n";
	}
	return 0;
}
