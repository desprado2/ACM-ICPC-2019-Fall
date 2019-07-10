#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define dbg() system("pause")
#define clr(a,n)\
 for(int i=0; i<n; i++)a[i].clear();
#define N 100005
#define root 1
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

int n,m,q,i,j,k;
vector<int> e[N];

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

vector<int> id,T[N];
bool cmp(int a,int b){return dfn[a]<dfn[b];}

bool imp[N];
int csz[N],ans;
void tra(int u,int p){
    int cnt=0;
    csz[u]=imp[u];
    for (int v:T[u]){
        tra(v,u), csz[u]+=csz[v];
        if (fa[v][0]==u && csz[v]==sz[v]) cnt++;
    }
    if (deg[u]-cnt<2 && imp[u]) ans++;
}
int main()
{
    cin.tie(0), ios::sync_with_stdio(false);
    int cases; cin>>cases;
    for (int tt=1; tt<=cases; tt++){
        cin>>n>>q;
        clr(e,n+5);
        for (i=1; i<n; i++){
            int u,v; cin>>u>>v;
            e[u].pb(v), e[v].pb(u);
        }
        tag=0, dfs(root,root,1), getst();

        cout<<"Case #"<<tt<<":\n";
        while (q--){
            cin>>m;
            //虚树如下
            id.clear();
            for (i=1; i<=m; i++){
                int u; cin>>u;
                id.pb(u), imp[u]=1;
            }
            sort(id.begin(), id.end(), cmp);
            for (i=0, j=id.size(); i+1<j; i++)
                id.pb(lca(id[i],id[i+1]));
            sort(id.begin(), id.end(), cmp);
            auto it=unique(id.begin(), id.end());
            id.erase(it,id.end());

            stack<int> S;
            S.push(id[0]);
            for (i=1; i<id.size(); i++){
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
            //虚树完成
            ans=0, tra(id[0],-1);
            cout<<n-ans<<endl;

            for (int i:id)
                T[i].clear(), csz[i]=0, imp[i]=0;
        }
    }
    return 0;
}
