#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define dbg() system("pause")
#define N 3005
using namespace std;

typedef long long LL;
typedef pair<LL,LL> Pii;

int n,m,A,B,i,j,k;
vector<int> e[N];

int now,cbl,dfn[N],low[N],bl[N];
vector<int> bcc[N];
stack<int> stk;
void tarjan(int u,int fa)
{
    dfn[u]=low[u]=++now;
    stk.push(u);
    for (int v:e[u]){
        if (v==fa) continue;
        if (!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if (low[v]>dfn[u]){
                bcc[++cbl].clear();
                while (stk.top()!=v)
                    bcc[cbl].pb(stk.top()), bl[stk.top()]=cbl, stk.pop();
                bcc[cbl].pb(stk.top()), bl[stk.top()]=cbl, stk.pop();
            }
        }
        else low[u]=min(low[u],dfn[v]);
    }
}

bool danger[N];
void bfs(int st,int* dis){
    queue<int> q;
    dis[st]=0, q.push(st);
    while (!q.empty()){
        int u=q.front(); q.pop();
        for (int v:e[u])
            if (!dis[v]&&v!=st){
                dis[v]=dis[u]+1;
                q.push(v);
            }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    int T; cin>>T;
    while (T--){
        cin>>n>>m>>A>>B;
        for (i=1; i<=n; i++)
            e[i].clear();
        for (i=1; i<=m; i++){
            int x,y; cin>>x>>y;
            e[x].pb(y), e[y].pb(x);
        }
        //以下是tarjan
        now=cbl=0, mem(dfn,0), mem(low,0);
        tarjan(1,-1);
        bcc[++cbl].clear();
        while (!stk.empty())
            bcc[cbl].pb(stk.top()), bl[stk.top()]=cbl, stk.pop();//不要忘记这句话!!!

        for (i=1; i<=cbl; i++)
            for (int u:bcc[i])
                danger[u]=(bcc[i].size()==1);

        int disA[n+5]={0},disB[n+5]={0}, ans=1;
        bfs(A, disA), bfs(B, disB);
        for (i=1; i<=n; i++)
            if (!danger[i] && disA[i]<disB[i]){ans=-1; break;}
            else if (disA[i]<disB[i]) ans=max(ans,disB[i]);
        if (ans==-1) cout<<"No"<<endl;
        else cout<<ans<<endl;
    }
	return 0;
}
