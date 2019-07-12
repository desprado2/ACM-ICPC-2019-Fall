
vector<int> e[N];//e是原来的树
int dfn[N],fa[N][17],dep[N],sz[N],deg[N],tag;
void dfs(int u,int p,int d){
    dfn[u]=++tag, dep[u]=d, fa[u][0]=p;
    sz[u]=1, deg[u]=0;
    for (int v:e[u])
        if (v!=p) dfs(v,u,d+1), sz[u]+=sz[v],deg[u]++;
}
void getst(){
    for (j=1; j<17; j++)
        for (i=1; i<=n; i++)
            fa[i][j]=fa[fa[i][j-1]][j-1];
}
int lca(int u,int v){
    if (dep[u]<dep[v]) swap(u,v);
    for (int i=16; i>=0; i--)
        if (dep[fa[u][i]]>=dep[v]) u=fa[u][i];
    if (u==v) return u;
    for (int i=16; i>=0; i--)
        if (fa[u][i]!=fa[v][i])
            u=fa[u][i], v=fa[v][i];
    return fa[u][0];
}

vector<int> id,T[N];//T存储虚树
bool cmp(int a,int b){return dfn[a]<dfn[b];}

void work(){//事实上
    tag=0, dfs(root,root,1), getst();
    while (Q--){
        cin>>m, id.clear();
        for (int i=1; i<=m; i++){
            int u; cin>>u;//u是每次询问的“有效节点”
            id.pb(u);
        }
        sort(id.begin(), id.end(), cmp);
        for (int i=0, j=id.size(); i+1<j; i++)
            id.pb(lca(id[i],id[i+1]));
        sort(id.begin(), id.end(), cmp);
        auto it=unique(id.begin(), id.end());
        id.erase(it,id.end());

        stack<int, vector<int>> S;
        S.push(id[0]);
        for (int i=1; i<id.size(); i++){
            int u=id[i];
            while (!S.empty()){
                int v=S.top();
                if (lca(u,v)==v){
                    T[v].pb(u); break;
                }
                S.pop();
            }
            S.push(u);
        }
        doCalculate();//虚树构建完成，根据题目要求完成计算
        for (int i:id) T[i].clear();//注意清空虚树
    }
}
