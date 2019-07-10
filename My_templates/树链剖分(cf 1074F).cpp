#include<bits/stdc++.h>
#define N 200005
typedef long long LL;
using namespace std;

int n,q,t,i,j,k;
vector<int> e[N];

int sz[N],hson[N],fa[N],d[N];
void dfs1(int u,int f,int dep)
{
	int i,v,maxs=0;
	sz[u]=1; fa[u]=f,d[u]=dep;
	for (i=0; i<e[u].size(); i++)
	{
		v=e[u][i];
		if (v==f) continue;
		dfs1(v,u,dep+1);
		if (sz[v]>maxs) maxs=sz[v],hson[u]=v;
		sz[u]+=sz[v];
	}
}
int cnt=0,pos[N],id[N],segr[N],hfa[N];//pos[u]:点u在dfs序中的位置(即dfn); id[i]:dfs序中第i个在树上的比编号;
//segr[u]:点u的子树在dfs序的右端点，即，子树对应了区间[pos[u],segr[u]]
//hfa[u]:u对应的重链的顶点
void dfs2(int u,int f,int hf)
{
	int i,v;
	cnt++;
	id[cnt]=u,pos[u]=cnt,hfa[u]=hf;
	if (hson[u]) dfs2(hson[u],u,hf);
	for (i=0; i<e[u].size(); i++)
	{
		v=e[u][i];
		if (v==hson[u]||v==f) continue;
		dfs2(v,u,v);
	}
	segr[u]=cnt;
}
struct seg{int l,r,min,mnum,tag;} b[N*4];
void ud(int x)
{
	if (b[x].l==b[x].r){b[x].min+=b[x].tag,b[x].tag=0; return;}
	int lc=x*2,rc=lc+1;
	if (b[lc].min<b[rc].min) b[x].min=b[lc].min+b[x].tag,b[x].mnum=b[lc].mnum;
	else if (b[lc].min>b[rc].min) b[x].min=b[rc].min+b[x].tag,b[x].mnum=b[rc].mnum;
	else b[x].min=b[lc].min+b[x].tag,b[x].mnum=b[lc].mnum+b[rc].mnum;
}
void pd(int x)
{
	int lc=x*2,rc=lc+1;
	b[lc].tag+=b[x].tag,b[rc].tag+=b[x].tag;
	b[x].tag=0;
	ud(lc),ud(rc);
}
void ch(int x,int L,int R,int del)//+delta
{
	if (L<=b[x].l&&b[x].r<=R) {b[x].tag+=del; ud(x); return;}
	int lc=x*2,rc=lc+1;
	pd(x);
	if (b[lc].r>=L) ch(lc,L,R,del);
	if (b[rc].l<=R) ch(rc,L,R,del);
	ud(x);
}
void btree(int x,int l,int r)
{
	int lc=x*2,rc=x*2+1,mid=(l+r)/2;
	b[x].l=l,b[x].r=r,b[x].tag=0;
	if (l==r) {b[x].min=0; b[x].mnum=1; return;}
	btree(lc,l,mid); btree(rc,mid+1,r);
	ud(x);
}
//no query.
int main()
{
	cin>>n>>q;
	int x,y;
	for (i=1; i<n; i++)
	{
		cin>>x>>y;
		e[x].push_back(y),e[y].push_back(x);
	}
	dfs1(1,-1,1);
	dfs2(1,-1,1);
	btree(1,1,n);

	unordered_set<LL> H;
	LL ha;
	for (i=1; i<=q; i++)
	{
		cin>>x>>y;
		if (d[x]>d[y]||d[x]==d[y]&&x>y) swap(x,y);
		int tx=x,ty=y;
		while (hfa[tx]!=hfa[ty])
		{
			if (d[hfa[tx]]>d[hfa[ty]]) tx=fa[hfa[tx]];
				else ty=fa[hfa[ty]];
		}
		int lca=(d[tx]<d[ty])?tx:ty,del;
		ha=LL(x-1)*LL(n)+LL(y-1);
		if (H.find(ha)==H.end()) del=1,H.insert(ha);
		else del=-1,H.erase(ha);

		if (lca==x)
		{
			ty=y;
			while (1)
			{
				if (hfa[ty]==hfa[x]) {ty=hson[x]; break;}
				if (fa[hfa[ty]]==x) {ty=hfa[ty]; break;}
				ty=fa[hfa[ty]];
			}
			ch(1,pos[ty],segr[ty],del);
			ch(1,pos[y],segr[y],-del);
		}
		else
		{
			ch(1,pos[1],segr[1],del);
			ch(1,pos[x],segr[x],-del);
			ch(1,pos[y],segr[y],-del);
		}
		if (b[1].min==0) cout<<b[1].mnum<<endl;
			else cout<<"0\n";
	}
	return 0;
}
