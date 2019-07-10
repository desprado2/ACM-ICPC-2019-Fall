#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define dbg() system("pause")
#define N 100005
using namespace std;

typedef pair<bool,int> pbi;
typedef long long ll;

int n,m,q,i,j,k;
pbi a[N];
vector<int> e[N];

int fa[N][17],d[N];
void getst(){
    for (int j=1; j<=16; j++)
        for (int i=1; i<=n; i++)
            fa[i][j]=fa[fa[i][j-1]][j-1];
}
int lca(int x,int y){
    if (d[x]<d[y]) swap(x,y);
    for (int i=16; i>=0; i--)
        if (d[fa[x][i]]>=d[y]) x=fa[x][i];
    if (x==y) return x;
    for (int i=16; i>=0; i--)
        if (fa[x][i]!=fa[y][i])
            x=fa[x][i], y=fa[y][i];
    return fa[x][0];
}

int id[N<<1], st[N],en[N],now;
void dfs(int u,int FA,int dep){
    fa[u][0]=FA, d[u]=dep;
    st[u]=++now, id[now]=u;
    for (int v:e[u])
        if (v!=FA) dfs(v,u,dep+1);
    en[u]=++now, id[now]=u;
}

struct query{int l,r,lca,pos;} Q[N];
int bl[N<<1],Sqrt;
bool cmp(query a,query b){return bl[a.l]<bl[b.l] || bl[a.l]==bl[b.l]&&a.r<b.r;}

unordered_map<int,int> A[2];
ll ans;
void modify(pbi x,bool add){
    if (!add){
        A[x.first][x.second] --;
        ans -= A[!x.first][x.second];
    }
    else {
        A[x.first][x.second] ++;
        ans += A[!x.first][x.second];
    }
}
int main(){
    cin.tie(0), ios::sync_with_stdio(false);
    cin>>n;
    for (i=1; i<=n; i++) cin>>a[i].first;
    for (i=1; i<=n; i++) cin>>a[i].second;
    for (i=1; i<n; i++){
        int u,v; cin>>u>>v;
        e[u].pb(v), e[v].pb(u);
    }
    dfs(1,1,1), getst();

    cin>>q;
    for (i=1; i<=q; i++){
        int x,y; cin>>x>>y;
        if (st[x]>st[y]) swap(x,y);
        if (en[x]>=en[y]){
            Q[i].l=st[x], Q[i].r=st[y];
            Q[i].lca=-1;
        }
        else {
            Q[i].l=en[x], Q[i].r=st[y];
            Q[i].lca=lca(x,y);
        }
        Q[i].pos=i;
    }
    Sqrt=sqrt(now);
    for (i=1; i<=now; i++) bl[i]=(i-1)/Sqrt;
    sort(Q+1,Q+q+1,cmp);

    int L=1, R=0, tot[n+5]={0};
    ll res[q+5];
    A[0].reserve(n+5), A[1].reserve(n+5);
    for (i=1; i<=q; i++){
        while (R<Q[i].r) {R++; tot[id[R]]++, modify(a[id[R]], tot[id[R]]%2==1);}
        while (R>Q[i].r) {tot[id[R]]--, modify(a[id[R]], tot[id[R]]%2==1); R--;}
        while (L>Q[i].l) {L--; tot[id[L]]++, modify(a[id[L]], tot[id[L]]%2==1);}
        while (L<Q[i].l) {tot[id[L]]--, modify(a[id[L]], tot[id[L]]%2==1); L++;}
        res[Q[i].pos]=ans;
        if (Q[i].lca!=-1){
            int id=Q[i].lca;
            res[Q[i].pos]+= A[!a[id].first][a[id].second];
        }
    }
    for (i=1; i<=q; i++) cout<<res[i]<<endl;
    return 0;
}
