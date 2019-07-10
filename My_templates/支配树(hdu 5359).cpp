#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define pb push_back
#define mp make_pair
#define mem(a,b) memset(a,b,sizeof(a))
#define dbg system("pause")
#define N 400005
using namespace std;

typedef pair<int,int> Pii;
typedef long long ll;

int n,m,i,j,k;
struct edge{int to,id;};
vector<edge> e[N];
//以下是tarjan SCC预处理
vector<int> scc[N];
stack<int, vector<int>> stk;
int _now,_dfn[N],low[N],instack[N];
int bl[N],cbl;
void tarjan(int u)
{
    low[u]=_dfn[u]=++_now;
    instack[u]=1;
    stk.push(u);
    for (edge it:e[u])
    {
        int v=it.to;
        if (!_dfn[v]) tarjan(v), low[u]=min(low[u],low[v]);
        else if (instack[v]) low[u]=min(low[u],_dfn[v]);
    }
    if (_dfn[u]==low[u]){
        cbl++, scc[cbl].clear();
        while (stk.top()!=u){
            int t=stk.top();
            scc[cbl].pb(t), bl[t]=cbl, instack[t]=0;
            stk.pop();
        }
        scc[cbl].pb(u), bl[u]=cbl, instack[u]=0, stk.pop();
    }
}

int Eid[N];
bool ans[N];
//-------------------------以下是支配树模板---------------------
vector<int> G[N], pre[N];
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
vector<int> son[N];
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
bool tra(int u){//在支配树上dp
    bool ret=0;
    for (int v:son[u])
        ret|= tra(v);
    if (Eid[u]) ans[Eid[u]] |= ret;
    else ret=1;
    return ret;
}

void init(int n){
    for (int i=1; i<=n; i++)
        dfn[i]=0, S[i].fa=S[i].eval=semi[i]=i,
        bucket[i].clear(), son[i].clear();
    now=0;
}
void work(int n,int R){//以R为根
    init(n);
    dfs(R,-1), build();
    tra(R);
}
//--------------------------------------------------------------
void Clear(int n){
    for (int i=1; i<=n; i++)
        G[i].clear(), pre[i].clear(), Eid[i]=0;
}
int main(){
    cin.tie(0), ios::sync_with_stdio(false);
    int tt; cin>>tt;
    while (tt--){
        cin>>n>>m;
        for (i=1; i<=n; i++) e[i].clear();
        memset(ans, 0, m+1);
        for (i=1; i<=m; i++){
            int u,v; cin>>u>>v;
            e[u].pb({v,i});
        }
        memset(_dfn, 0, n+1<<2); cbl=_now=0;
        for (i=1; i<=n; i++)
            if (!_dfn[i]) tarjan(i);

        int H[n+5];
        for (i=1; i<=cbl; i++){
            for (j=0; j<scc[i].size(); j++)
                H[scc[i][j]]=j+1;

            int C=scc[i].size();
            for (int u:scc[i]){
                for (edge it:e[u]){
                    int v=it.to;
                    if (bl[v]==bl[u]){
                        ++C;
                        G[H[u]].pb(C), G[C].pb(H[v]);
                        pre[H[v]].pb(C), pre[C].pb(H[u]);
                        Eid[C]=it.id;
                    }
                }
            }
            work(C,H[scc[i][0]]);
            Clear(C);

            C=scc[i].size();
            for (int u:scc[i]){
                for (edge it:e[u]){
                    int v=it.to;
                    if (bl[v]==bl[u]){
                        ++C;
                        G[C].pb(H[u]), G[H[v]].pb(C);
                        pre[C].pb(H[v]), pre[H[u]].pb(C);
                        Eid[C]=it.id;
                    }
                }
            }
            work(C,H[scc[i][0]]);
            Clear(C);
        }

        for (i=1; i<=m; i++) cout<<ans[i];
        cout<<endl;
    }
    return 0;
}
