#include<bits/stdc++.h>
#define N 1005
#define M 100005
#define inf 1e7
using namespace std;

int n,m,x,i,j,k,du[N];

int l[N],cnt;
struct edge{int to,next,val;} e[M];
void adde(int fr,int to,int val,int l[],edge e[])
{
	e[cnt].next=l[fr],e[cnt].to=to,e[cnt].val=val,l[fr]=cnt; cnt++;//必须先连边后cnt++,这是为了保证e[i]与e[i^1]互为反边
	e[cnt].next=l[to],e[cnt].to=fr,e[cnt].val=0,l[to]=cnt; cnt++;
}
int S,T,SS,ST,V,gap[N],dis[N],st,en;
int dfs(int u,int cur)//cur:当前允许最大流量
{
	if (u==en) return cur;
	int i,v,mind=V-1,flow=cur,d;
	for (i=l[u]; i!=-1; i=e[i].next)
	{
		v=e[i].to;
		if (e[i].val>0)
		{
			if (dis[v]+1==dis[u])
			{
				d=dfs(v,min(flow,e[i].val));
				e[i].val-=d,e[i^1].val+=d;
				flow-=d;
				if (dis[st]>=V) return cur-flow;
				if (flow==0) break;
			}
			mind=min(mind,dis[v]);
		}
	}
	if (flow==cur)
	{
		--gap[dis[u]];
		if (gap[dis[u]]==0) dis[st]=V;
		dis[u]=mind+1;
		++gap[dis[u]];
	}
	return cur-flow;
}
int sap(int s,int t,int n)//从s到t，共有n个点
{
	st=s,en=t,V=n;
	memset(dis,0,sizeof(dis)); memset(gap,0,sizeof(gap));//!!!
	gap[1]=V;//!!!
	int ans=0;
	while (dis[st]<V) ans+=dfs(st,INT_MAX);
	return ans;
}
int tmpl[N];
edge tmp[N];
struct tt{int pre,v,eid;} t,qu[N];
void ud(int x)
{
	if (qu[x].v==S) return;
	tmp[qu[x].eid].val--;
	ud(qu[x].pre);
	if (qu[x].v!=T) cout<<qu[x].v<<' ';
}
int main()
{
	while (cin>>n)
	{
		memset(l,-1,sizeof(l)),memset(du,0,sizeof(du)); cnt=0;//l[]=-1!!!初始化!!!
		for (i=1; i<=n; i++)
		{
			cin>>x;
			while (x--) {
                cin>>k; du[k]++,du[i]--;
                adde(i,k,inf-1,l,e);
            }
		}
		S=n+1,T=n+2;
		SS=S+2,ST=T+2;
		for (i=1; i<=n; i++)
            adde(S,i,inf*100,l,e),adde(i,T,inf*100,l,e);//*100!!!!
		for (i=1; i<=n; i++)
			if (du[i]>0) adde(SS,i,du[i],l,e);
			else if (du[i]<0) adde(i,ST,-du[i],l,e);
		sap(SS,ST,n+4);
		adde(T,S,inf*100,l,e);//*100!!!!
		sap(SS,ST,n+4);
		cout<<e[cnt-1].val<<endl;
		//实际上，最小流=S所有出边的流量+S所有出边的下界；此处S出边下界均为0，所以偷懒地直接等于S所有出边的流量，即T->S边的流量

		memset(tmpl,-1,sizeof(tmpl)); cnt=0;
		for (i=1; i<=n; i++)//tmp存储残余网络流量情况，并据此构建新图
			for (j=l[i]; j!=-1; j=e[j].next)
			{
				if (e[j].to==SS||e[j].to==ST) continue;
				if ((j&1)&&e[j].to==S&&e[j].val) adde(e[j].to,i,e[j].val,tmpl,tmp);
				if ((j&1)&&e[j].to!=S) adde(e[j].to,i,e[j].val+1,tmpl,tmp);//下界为1
			}
		for (j=l[T]; j!=-1; j=e[j].next)
			if ((j&1)&&e[j].val>0) adde(e[j].to,T,e[j].val,tmpl,tmp);
		do
		{
			bool fl=0,vis[150];
			int p=0,q=1;
			qu[1].v=S,qu[1].pre=0;
			memset(vis,0,sizeof(vis));
			while (p<q)
			{
				p++;
				t=qu[p];
				for (i=tmpl[t.v]; i!=-1; i=tmp[i].next)
				{
					int v=tmp[i].to;
					if (tmp[i].val&&!vis[v]) {qu[++q].v=v,qu[q].pre=p,qu[q].eid=i; vis[v]=1; if (v==T) {fl=1; break;}}
				}
				if (fl) break;
			}
			if (fl) {ud(q); cout<<endl;}
				else break;
		}while (1);//暴力求增广路
	}
	return 0;
}
