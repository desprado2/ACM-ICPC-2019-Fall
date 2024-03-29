int n,m,i,j,k,fa[N],match[N],pre[N];//fa:disjoint set
int cnt=0,last[N];
struct edg{int to,next;} e[N*N*5];
void adde(int a,int b)
{
	e[cnt].to=b,e[cnt].next=last[a],last[a]=cnt; cnt++;
	e[cnt].to=a,e[cnt].next=last[b],last[b]=cnt; cnt++;
}

int find(int x){return (x==fa[x])?x:(fa[x]=find(fa[x]));}
int V,tag=0,bl[N];//bl[]:belong to which cycle.
int lca(int x,int y)
{
	tag++;
	while (bl[x]!=tag)
	{
		if (x)
		{
			x=find(x);
			if (bl[x]==tag) return x;
			bl[x]=tag;
			if (match[x]) x=find(pre[match[x]]);
			else x=0;//先到了以后就不用再走了
		}
		swap(x,y);
	}
	return x;
}
int state[N];
list<int> qu;
void shrink(int x,int lastx,int torus){
	int temp;
	while (find(x)!=torus){
		pre[x]=lastx;
		temp=match[x];
		if (state[temp]==1) state[temp]=0,qu.push_back(temp);
		if (find(temp)==temp) fa[temp]=torus;
		if (find(x)==x) fa[x]=torus;
		lastx=temp, x=pre[lastx];
	}
}
bool bfs(int x)
{
	int i,u,v;
	memset(state,-1,sizeof(state));//state=-1:unvisited,0:even(state S),1:odd(state T);
	for (i=1; i<=V; i++) fa[i]=i;

	qu.clear(), qu.push_back(x);
	state[x]=0;
	while (!qu.empty())
	{
		u=qu.front(), qu.pop_front();
		for (i=last[u]; i!=-1; i=e[i].next)
		{
			v=e[i].to;
			if (state[v]==-1)
			{
				pre[v]=u,state[v]=1;
				if (!match[v])
				{
					int temp,now=v;
					while (now!=0)
					{
						temp=pre[now];
						int next=match[temp];
						match[temp]=now, match[now]=temp;
						now=next;
					}
					return 1;
				}
				state[match[v]]=0; qu.push_back(match[v]);
			}
			else if (state[v]==0){//重新访问到已有的点，必然是奇环
				int torus=lca(u,v);
				shrink(u,v,torus), shrink(v,u,torus);//缩点
			}
		}
	}
	return 0;
}
int bst()//记得赋值总点数V
{
	memset(match,0,sizeof(match)),memset(pre,0,sizeof(pre));
	memset(bl,0,sizeof(bl)),tag=0;
	int ret=0;
	for (int i=1; i<=V; i++)
		if (!match[i]) ret+=bfs(i);
	return ret;
}
