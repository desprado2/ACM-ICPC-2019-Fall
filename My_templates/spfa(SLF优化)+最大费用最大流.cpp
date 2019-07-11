#include<bits/stdc++.h>
#define N 505
#define M 100005
#define inf 1e7
using namespace std;

int n,m,i,j,t,tmp,ans;
struct read{int l,r,w,op;} a[205];

int cnt=0,l[N],k,w,x,y,op,S,SS,T;
struct edge{int to,next,val,c;} e[M];
void adde(int fr,int to,int val,int c)
{
	e[cnt].next=l[fr],e[cnt].to=to,e[cnt].val=val,e[cnt].c=c; l[fr]=cnt; cnt++;
	e[cnt].next=l[to],e[cnt].to=fr,e[cnt].val=0,e[cnt].c=-c; l[to]=cnt; cnt++; //-c !!!
}
int pre[N],id[N],dis[N];
list<int> qu;
int spfa(int st,int en)//spfa增广
{
	int i,j,p=0,q=1,ret=inf;
	bool vis[N];

	qu.clear(); memset(vis,0,sizeof(vis)); memset(dis,-1,sizeof(dis));
	qu.push_front(st); dis[st]=0,pre[st]=-1,id[st]=-1; vis[st]=1;
	while (!qu.empty())
	{
		int u=qu.front(),v;
		qu.pop_front();
		for (i=l[u]; i!=-1; i=e[i].next)
		{
			if (e[i].val==0) continue;
			v=e[i].to;
			if (dis[u]+e[i].c>dis[v])//> !!!!!
			{
				dis[v]=dis[u]+e[i].c;
				pre[v]=u,id[v]=i;
				if (!vis[v])
				{//SLF optimization
					if (qu.empty()||dis[v]>dis[qu.front()]) qu.push_front(v);
					else qu.push_back(v);
					vis[v]=1;
				}
			}
		}
		vis[u]=0;
	}
	if (dis[en]==-1) return -1;

	i=en;
	do
		ret=min(ret,e[id[i]].val), i=pre[i];
	while (i!=st);
	
	i=en;
	do
		e[id[i]].val-=ret, e[id[i]^1].val+=ret, i=pre[i];
	while(i!=st);
	return ret*dis[en];
}
int work(int st,int en){
	int tmp, ret=0;
	while ((tmp=spfa(st,en))>0) ret+=tmp;
	return ret;
}
