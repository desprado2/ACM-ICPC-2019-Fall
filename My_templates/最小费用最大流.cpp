Pii spfa(int st,int en)
{
	int i,j,p=0,q=1,ret=inf;
	bool vis[N];

	qu.clear(); memset(vis,0,sizeof(vis)); memset(dis,0x3f,sizeof(dis));
	qu.push_front(st); dis[st]=0,pre[st]=-1,id[st]=-1; vis[st]=1;
	while (!qu.empty())
	{
		int u=qu.front(),v;
		qu.pop_front();
		for (i=l[u]; i!=-1; i=e[i].next)
		{
			if (e[i].val==0) continue;
			v=e[i].to;
			if (dis[u]+e[i].c<dis[v])
			{
				dis[v]=dis[u]+e[i].c;
				pre[v]=u,id[v]=i;
				if (!vis[v])
				{//SLF optimization
					if (qu.empty()||dis[v]<dis[qu.front()]) qu.push_front(v);
						else qu.push_back(v);
					vis[v]=1;
				}
			}
		}
		vis[u]=0;
	}
	if (dis[en]>n*c) return make_pair(0,-1);

	i=en;
	do ret=min(ret,e[id[i]].val), i=pre[i];
	while (i!=st);
	i=en;
	do e[id[i]].val-=ret,e[id[i]^1].val+=ret, i=pre[i];
	while(i!=st);

	return make_pair(ret,ret*dis[en]);//first是流量,second是费用,注意费用是有可能为0的.
}
