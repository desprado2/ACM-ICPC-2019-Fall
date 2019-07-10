#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define dbg() system("pause")
#define N 200005
using namespace std;

typedef long long LL;
typedef pair<LL,LL> Pii;

int n,m,q,i,j,k,t,a[N],p[N],pos[N];

vector<int> e[N];
int pre(int x){return p[(pos[x]-1+n)%n];}

int rec[N];
vector<int> stk;
void dfs(int u,int dep){
    stk.push_back(u);
    if (dep<n) rec[u]=0;
    else rec[u]=stk[dep-n+1];
    for (int v:e[u])
        dfs(v,dep+1);
    stk.pop_back();
}

int Log2[N],st[N][20];//ST table
int Q(int l,int r){
    int len=r-l+1;
    return max(st[l][Log2[len]] , st[r-(1<<Log2[len])+1][Log2[len]]);
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m>>q;
    for (i=0; i<n; i++) cin>>p[i], pos[p[i]]=i;
    for (i=1; i<=m; i++) cin>>a[i];

    int top[N]={0};
    for (i=1; i<=m; i++){
        e[top[pre(a[i])]].pb(i);
        top[a[i]]=i;
    }

    dfs(0,0);
    //以下为ST表
    for (i=1,k=0; i<=m; i<<=1,k++)
        for (j=i; j<i<<1 && j<=m; j++)
            Log2[j]=k;
    for (i=1; i<=m; i++) st[i][0]=rec[i];
    for (j=1; j<=Log2[m]; j++)
        for (i=1; i<=m; i++)
            if (i+(1<<j-1)<=m)st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
            else st[i][j]=st[i][j-1];

    for (i=1; i<=q; i++){
        int l,r; cin>>l>>r;
        if (Q(l,r)>=l) cout<<1;
        else cout<<0;
    }
	return 0;
}
