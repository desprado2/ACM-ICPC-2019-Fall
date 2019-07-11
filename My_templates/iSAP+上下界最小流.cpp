int du[N];
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
void work()
{
	for (i=1; i<=n; i++)
		if (du[i]>0) adde(SS,i,du[i],l,e);
		else if (du[i]<0) adde(i,ST,-du[i],l,e);
	sap(SS,ST,n+4);
	adde(T,S,inf*100,l,e);//*100!!!!
	sap(SS,ST,n+4);
	cout<<e[cnt-1].val<<endl;
		//实际上，最小流=S所有出边的流量+S所有出边的下界；此处S出边下界均为0，所以偷懒地直接等于S所有出边的流量，即T->S边的流量
}
