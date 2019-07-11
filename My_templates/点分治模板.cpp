int mins,r,sz[N],ans;
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
void traverse(int u);//遍历这个子树,注意一旦vis[v]==true就不能往下搜
void calc();//根据已经有的信息计算以u为lca的路径的贡献，注意小心重复
void div(int u)
{
	vis[u]=1;
	for (int v:e[u]){
		if (vis[v]) continue;
		traverse(v), calc();
	}
	init();
	for (int v:e[u])//divide
	{
		if (vis[v]) continue;
		mins=INT_MAX,r=-1;
		dfs(v,u,sz[v]), div(r);
	}
}
void work(){
	mins=ans=INT_MAX, r=-1;
	dfs(1,-1,n), div(r);
}
