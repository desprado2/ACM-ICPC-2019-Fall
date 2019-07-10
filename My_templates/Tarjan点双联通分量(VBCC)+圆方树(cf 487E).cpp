#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define dbg() system("pause")
#define clr(a,n)\
 for(int i=0; i<n; i++)a[i].clear();
#define N 200005
using namespace std;

typedef long long LL;
typedef pair<int,int> Pii;

int n,m,q,i,j,k,w[N];
vector<int> e[N];

int now,cbl,dfn[N],low[N];
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
            if (low[v]>=dfn[u]){
                bcc[++cbl].clear();
                while (stk.top()!=v)
                    bcc[cbl].pb(stk.top()), stk.pop();
                bcc[cbl].pb(stk.top()), stk.pop();
                bcc[cbl].pb(u);//和EBCC区分,重要!
            }
        }
        else low[u]=min(low[u],dfn[v]);
    }
}

int cnt,bl[N];
vector<int> bccid[N*2],rst[N*2];
vector<int> E[N*2];
void shrink(){
    int i;
    for (i=1; i<=cbl; i++)
        for (int u:bcc[i])
            bccid[u].pb(i);
    cnt=cbl;
    for (i=1; i<=n; i++)
        if (bccid[i].size()>1){//这是一个割点
            rst[++cnt].pb(i), bl[i]=cnt;
            for (int j:bccid[i])
                E[j].pb(cnt), E[cnt].pb(j);
        }
        else rst[bccid[i][0]].pb(i), bl[i]=bccid[i][0];
}

multiset<int> M[N*2];
int sz[N*2],hson[N*2],d[N*2],fa[N*2];
void dfs1(int u,int f,int dep)
{
	int maxs=0;
	sz[u]=1; fa[u]=f,d[u]=dep;
	for (int v:E[u]){
		if (v==f) continue;
		dfs1(v,u,dep+1);
		if (sz[v]>maxs) maxs=sz[v],hson[u]=v;
		sz[u]+=sz[v];
	}
}
int pos[N*2],id[N*2],segr[N*2],hfa[N*2];//pos[u]:点u在dfs序中的位置(即dfn); id[i]:dfs序中第i个在树上的比编号;
//segr[u]:点u的子树在dfs序的右端点，即，子树对应了区间[pos[u],segr[u]]
//hfa[u]:u对应的重链的顶点
void dfs2(int u,int f,int hf)
{
	cnt++;
	id[cnt]=u,pos[u]=cnt,hfa[u]=hf;
	if (hson[u]) dfs2(hson[u],u,hf);
	for (int v:E[u]){
		if (v==hson[u]||v==f) continue;
		dfs2(v,u,v);
	}
	segr[u]=cnt;
}

bool issqr(int x){return x<=cbl;}//判断是否是"方点"

struct seg{int l,r,m;} b[N*8];
void upd(int x){
    if (b[x].l==b[x].r) return;
    int lc=x*2, rc=lc+1;
    b[x].m=min(b[lc].m, b[rc].m);
}
void modify(int id,int bf,int af){
    multiset<int>::iterator it=M[id].find(bf);
    M[id].erase(it), M[id].insert(af);
}
void ch(int x,int pos,int bf,int af){
    if (b[x].l==b[x].r) {
        int ID=id[b[x].l];
        modify(ID,bf,af), b[x].m=*M[ID].begin();
        return;
    }
    int lc=x*2, rc=lc+1;
    if (b[lc].r>=pos) ch(lc,pos,bf,af);
    else ch(rc,pos,bf,af);
    upd(x);
}
int Q(int x,int L,int R){
    if (b[x].l>=L&&b[x].r<=R) return b[x].m;
    int lc=x*2, rc=lc+1, ret=INT_MAX;
    if (b[lc].r>=L) ret=min(ret,Q(lc,L,R));
    if (b[rc].l<=R) ret=min(ret,Q(rc,L,R));
    return ret;
}
void btree(int x,int l,int r){
    b[x].l=l, b[x].r=r;
    if (l==r){b[x].m=M[id[l]].empty()?INT_MAX:(*M[id[l]].begin()); return;}
    int lc=x*2, rc=lc+1, mid=(l+r)/2;
    btree(lc,l,mid), btree(rc,mid+1,r);
    upd(x);
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m>>q;
    for (i=1; i<=n; i++) cin>>w[i];
    for (i=1; i<=m; i++){
        int x,y; cin>>x>>y;
        e[x].pb(y), e[y].pb(x);
    }

    now=cbl=0, mem(dfn,0), mem(low,0);
    tarjan(1,-1);

    clr(E,n*2); clr(bccid,n*2); clr(rst,n*2);
    cnt=0, shrink();

    dfs1(1,-1,1);
    cnt=0, dfs2(1,-1,1);
    for (i=1; i<=cnt; i++){
        for (int u:rst[i])
            M[i].insert(w[u]);
        if (!issqr(i) && fa[i]!=-1) M[fa[i]].insert(w[rst[i][0]]);
    }

    btree(1,1,cnt);
    for (i=1; i<=q; i++){
        char c; cin>>c;
        if (c=='C'){
            int x,y; cin>>x>>y;
            ch(1,pos[bl[x]],w[x],y);
            if (!issqr(bl[x]) && fa[bl[x]]!=-1)
                ch(1,pos[fa[bl[x]]],w[x],y);
            w[x]=y;
        }
        else{
            int x,y,ans=INT_MAX; cin>>x>>y;
            if (x==y) {cout<<w[x]<<endl; continue;}
            x=bl[x], y=bl[y];
            while (hfa[x]!=hfa[y]){
                if (d[hfa[x]]>d[hfa[y]]) ans=min(ans,Q(1,pos[hfa[x]],pos[x])), x=fa[hfa[x]];
                else ans=min(ans,Q(1,pos[hfa[y]],pos[y])), y=fa[hfa[y]];
            }
            int lca;
            if (d[x]>d[y]) ans=min(ans,Q(1,pos[y],pos[x])),lca=y;
            else ans=min(ans,Q(1,pos[x],pos[y])),lca=x;
            if (issqr(lca) && fa[lca]!=-1) ans=min(ans,w[rst[fa[lca]][0]]);
            cout<<ans<<endl;
        }
    }
	return 0;
}
