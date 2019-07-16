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
void HL_init(){
	dfs1(1,-1,1);
	dfs2(1,-1,1);
}//remember to build the segment tree!
