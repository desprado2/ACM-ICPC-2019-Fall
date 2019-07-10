#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define N 200005
using namespace std;

int gcd(int a,int b){return b==0?a:gcd(b,a%b);}

int n,m,i,j,k,cnt,pr[N/10],a[N];
bool f[N];
vector<int> fact[N];
void sieve()
{
    for (int i=2; i<=N-5; i++){
        if (!f[i]) pr[++cnt]=i;
        for (int j=1; j<=cnt&&i*pr[j]<=N-5; j++){
            f[i*pr[j]]=1;
            if (i%pr[j]==0) break;
        }
    }
}
void factorization()
{
    for (int i=2; i<=N-5; i++){
        int x=i;
        for (int j=1; j<=cnt&&pr[j]<=x; j++)
            if (x%pr[j]==0){
                fact[i].push_back(pr[j]);
                while (x%pr[j]==0) x/=pr[j];
            }
    }
}

vector<int> e[N];

int ans=0,sz[N],tmps,r;
bool vis[N];
void dfs(int u,int fa,int subV)
{
    int maxs=0;
    sz[u]=1;
    for (int v:e[u]){
        if (vis[v]||v==fa) continue;
        dfs(v,u,subV);
        maxs=max(maxs,sz[v]), sz[u]+=sz[v];
    }
    maxs=max(maxs,subV-sz[u]);
    if (maxs<tmps) tmps=maxs,r=u;
}

vector<int> GCDs,tGCDs;
int dist[N],tdist[N];
void tra(int u,int fa,int GCD,int dep)
{
    int G=gcd(a[u],GCD);
    if (G==1) return;
    for (int F:fact[G])
        if (!tdist[F]) tGCDs.push_back(F),tdist[F]=dep;
        else tdist[F]=max(tdist[F],dep);

    for (int v:e[u]){
        if (vis[v]||v==fa) continue;
        tra(v,u,G,dep+1);
    }
}
void calc()
{
    int i,j;
    for (int F:tGCDs){
        ans=max(ans,tdist[F]+1);
        if (dist[F]) ans=max(ans,dist[F]+tdist[F]+1),dist[F]=max(dist[F],tdist[F]);
        else GCDs.push_back(F),dist[F]=tdist[F];
    }

    for (int F:tGCDs) tdist[F]=0;
    tGCDs.clear();//initialize
}

void div(int u)
{
    vis[u]=1;
    for (int v:e[u]){
        if (vis[v]) continue;
        tra(v,u,a[u],1);
        calc();
    }
    for (int F:GCDs) dist[F]=0;
    GCDs.clear();

    for (int v:e[u]){
        if (vis[v]) continue;
        tmps=INT_MAX, r=-1, dfs(v,u,sz[v]);
        div(r);
    }
}
int main()
{
    sieve(), factorization();
    cin>>n;
    for (i=1; i<=n; i++) {cin>>a[i]; if (a[i]>1)ans=1;}
    for (i=1; i<n; i++){
        int x,y;
        cin>>x>>y;
        e[x].push_back(y), e[y].push_back(x);
    }

    tmps=INT_MAX, r=-1, dfs(1,0,n);
    div(r);
    cout<<ans;
	return 0;
}
