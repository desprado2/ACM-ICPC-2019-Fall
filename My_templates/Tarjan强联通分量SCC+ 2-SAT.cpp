vector<int> e[M];
bool dyed[M],noans=0;
int def[M];
void dye(int u){//2-SAT前决定一些点的选择
    dyed[u]=1;
    def[u]=1,def[u^1]=-1;
    for (int v:e[u])
        if (!dyed[v]) dye(v);
	else if (def[v]==-1) noans=1;
}

vector<int> scc[M];
stack<int, vector<int>> stk;
int now,dfn[M],low[M],instack[M];
int bl[M],cbl;
void tarjan(int u)//求强联通分量
{
    low[u]=dfn[u]=++now;
    instack[u]=1;
    stk.push(u);
    for (int v:e[u])
    {
        if (def[v]) continue;//在2-SAT之前已经决定了某些点的选择，那么就不能在tarjan中再访问这些点
	//正常的SCC tarjan可以直接删掉这条语句
        if (!dfn[v]) tarjan(stk,v), low[u]=min(low[u],low[v]);
        else if (instack[v]) low[u]=min(low[u],dfn[v]);
    }
    if (dfn[u]==low[u]){
        cbl++, scc[cbl].clear();
        while (stk.top()!=u){
            int t=stk.top();
            scc[cbl].push_back(t), bl[t]=cbl, instack[t]=0;
            stk.pop();
        }
        scc[cbl].push_back(u), bl[u]=cbl, instack[u]=0, stk.pop();
    }
}

vector<int> reve[M];
int in[M];
void topo(int u)
{
    for (int i:scc[u])
        if (def[i]) return;//如果之前已经访问过这部分的对应的某个二元组,说明这个二元组一定是-1,则这个部分以及其"上面"的部分就全部不能取
    for (i:scc[u])
	def[i]=1, def[i^1]=-1;
    for (i:reve[u])
        if (--in[i]==0) topo(i);
}
bool work(){
    int i;
    memset(def,0,sizeof(def));
    for (i=1; i<=decided; i++)
        memset(dyed,0,sizeof(dyed)), dye(start[i]);//先对已经确定选择的点染色

    memset(dfn,0,sizeof(dfn)), cbl=now=0;
    for (i=0; i<cnt*2; i++)
         if (!dfn[i]&&!def[i]) tarjan(i);

    for (i=0; i<cnt*2; i+=2)
        if (!def[i] && bl[i]==bl[i^1]) noans=1;//判断是否无解
    if (noans) return 0;
    memset(in,0,sizeof(in));//如果有解,建反向边,按照反向拓扑序得出答案
    for (i=1; i<=cbl; i++) reve[i].clear();
    for (i=0; i<cnt*2; i++){
        if (def[i]) continue;
        for (j:e[i])
            if (!def[j] && bl[i]!=bl[j]) reve[bl[j]].push_back(bl[i]),in[bl[i]]++;
    }
    for (i=1; i<=cbl; i++)
        if (!in[i]) topo(i);
    return 1;
//2-SAT的方案存储在def[]数组里面
}
