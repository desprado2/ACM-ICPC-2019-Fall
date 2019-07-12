vector<int> G[N], pre[N];//G:正向边; pre:反向边
int now,dfn[N],id[N],fa[N],semi[N],idom[N];
vector<int> bucket[N];

struct DS{int fa,eval;} S[N];//带权并查集，其中eval相当于权值
DS Find(int x){
    if (S[x].fa==x) return {x,0};
    DS ret=Find(S[x].fa);
    if (!ret.eval || dfn[semi[S[x].eval]] < dfn[semi[ret.eval]])
        ret.eval=S[x].eval;
    S[x]=ret;
    return ret;
}

void dfs(int u,int parent){//构造dfs树
    dfn[u]=++now, id[now]=u;
    fa[u]=parent;
    for (int v:G[u])
        if (!dfn[v]) dfs(v,u);
}
vector<int> son[N];//son[]:支配树的儿子; 对应于idom[]:支配树的父亲
void upd(int u,int v){dfn[semi[v]]<dfn[semi[u]]? semi[u]=semi[v] : 0;}
void build(){//构造支配树
    for (int i=now; i>1; i--){
        int u=id[i];
        for (int v:pre[u]){
            if (!dfn[v]) continue;
            if (dfn[v]<dfn[u]) upd(u,v);
            else {
                DS tmp=Find(v);
                upd(u, tmp.eval);
            }
        }
        bucket[semi[u]].pb(u);
        S[u].fa=fa[u];
        for (int v:bucket[fa[u]]){
            DS tmp=Find(v);
            idom[v]= semi[tmp.eval]<semi[v]? tmp.eval : semi[v];
        }
    }
    for (int i=2; i<=now; i++){
        int u=id[i];
        if (idom[u]!=semi[u]) idom[u]=idom[idom[u]];
        son[idom[u]].pb(u);
    }
}
void init(int n){
    for (int i=1; i<=n; i++)
        dfn[i]=0, S[i].fa=S[i].eval=semi[i]=i,
        bucket[i].clear(), son[i].clear();
    now=0;
}
void work(int n,int R){//以R为根构造支配树
    init(n);
    dfs(R,-1), build();
    tra(R);
}
