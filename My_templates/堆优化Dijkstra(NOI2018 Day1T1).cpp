#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define N 600005
#define logn 19
#define st 1
using namespace std;

typedef pair<int,int> Pii;
struct tzy{int to,l,a;};
struct edge{
    int u,v,a;
    bool operator<(const edge &x){return a>x.a;}
} E[N];

int n,m,t,i,j,k,l,a,dis[N];
bool vis[N];
vector<tzy> e[N];

int fa[N];
struct above{int fa,a;} parent[N],F[N][logn];
int Find(int u){return u==fa[u]?u:(fa[u]=Find(fa[u]));}
int main()
{
    ios::sync_with_stdio(false);
    cin>>t;
    while (t--){
        cin>>n>>m;
        for (i=1; i<=n; i++) e[i].clear();
        for (i=1; i<=m; i++){
            int x,y;
            cin>>x>>y>>l>>a;
            e[x].push_back({y,l,a}), e[y].push_back({x,l,a});
            E[i]={x,y,a};
        }

        //Dijkstra + Heap
        memset(vis,0,sizeof(vis)), memset(dis,0x3f,sizeof(dis));
        dis[st]=0;
        priority_queue<Pii,vector<Pii>,greater<Pii>> qu;
        qu.push(make_pair(dis[st],st));
        while (!qu.empty())
        {
            int u=qu.top().second,v;
            qu.pop();
            if (vis[u]) continue;

            vis[u]=1;
            for (tzy it:e[u]){
                v=it.to;
                if (dis[u]+it.l<dis[v])
                    dis[v]=dis[u]+it.l, qu.push(make_pair(dis[v],v));
            }
        }

        sort(E+1,E+m+1);
        for (i=1; i<=n; i++) fa[i]=i;
        for (i=1; i<=m; i++)
        {
            int x=Find(E[i].u),y=Find(E[i].v);
            if (dis[x]<dis[y]) fa[y]=x,parent[y]=F[y][0]={x,E[i].a};
            else fa[x]=y,parent[x]=F[x][0]={y,E[i].a};
        }
        parent[st]=F[st][0]={st,0};
        for (j=1; j<logn; j++)
            for (i=1; i<=n; i++)
                F[i][j]=F[F[i][j-1].fa][j-1];

        int Q,K,S,v,p,lstans=0;
        cin>>Q>>K>>S;
        while (Q--){
            cin>>v>>p;
            v=(v+K*lstans-1)%n+1;
            p=(p+K*lstans)%(S+1);
            for (j=logn-1; j>=0; j--)
                if (F[v][j].a>p) v=F[v][j].fa;
            cout<<dis[v]<<endl;
            lstans=dis[v];
        }
    }
	return 0;
}
