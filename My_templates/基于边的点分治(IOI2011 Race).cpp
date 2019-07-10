#include<bits/stdc++.h>
#define N 200005
#define K 1000000
typedef long long LL;
using namespace std;

int n,m,x,y,p,i,j,k,ans;
bool vis[N];
vector<int> e[N],w[N];

int mins,r,sz[N];
int dfs(int u,int fa,int subV)
{
	int i,v,edis,maxs=0;
	sz[u]=1;
	for (i=0; i<e[u].size(); i++)
	{
		v=e[u][i],edis=w[u][i];
		if (vis[v]||v==fa) continue;
		int tmp=dfs(v,u,subV);
		maxs=max(maxs,tmp); sz[u]+=tmp;
	}
	maxs=max(maxs,subV-sz[u]);
	if (maxs<mins) mins=maxs,r=u;
	return sz[u];
}
int tmp[K+5],cnt,s[N];
void tra(int u,int fa,int dis,int d)
{
	int i,v,edis;
	if (dis>m) return;
	ans=min(ans,d+tmp[m-dis]);
	for (i=0; i<e[u].size(); i++)
	{
		v=e[u][i],edis=w[u][i];
		if (vis[v]||v==fa) continue;
		tra(v,u,dis+edis,d+1);
	}
}
void ud(int u,int fa,int dis,int d)
{
	int i,v,edis;
	if (dis>m) return;
	tmp[dis]=min(tmp[dis],d);
	s[++cnt]=dis;
	for (i=0; i<e[u].size(); i++)
	{
		v=e[u][i],edis=w[u][i];
		if (vis[v]||v==fa) continue;
		ud(v,u,dis+edis,d+1);
	}
}
void div(int u)//divide and calculate
{
	int i,j,v,edis;
	vis[u]=1;
	for (i=0; i<e[u].size(); i++)
	{
		v=e[u][i],edis=w[u][i];
		if (vis[v]) continue;
		tra(v,u,edis,1); ud(v,u,edis,1);
	}
	for (i=1; i<=cnt; i++) tmp[s[i]]=N;
	cnt=0;//initialize

	for (i=0; i<e[u].size(); i++)
	{
		v=e[u][i],edis=w[u][i];
		if (vis[v]) continue;
		mins=INT_MAX,r=-1;
		dfs(v,u,sz[v]);//×¢ÒâÊÇsz[v]
		div(r);
	}
}
int main()
{
	memset(vis,0,sizeof(vis));
	for (i=1; i<=K; i++) tmp[i]=N;
	cin>>n>>m;
	for (i=1; i<n; i++)
	{
		cin>>x>>y>>k; x++,y++;
		e[x].push_back(y),e[y].push_back(x);
		w[x].push_back(k),w[y].push_back(k);
	}
	mins=ans=INT_MAX,r=-1;
	dfs(1,-1,n);
	div(r);
	if (ans<=n) cout<<ans;
		else cout<<-1;
}
