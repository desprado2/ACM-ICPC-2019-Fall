#include<bits/stdc++.h>
#define N 205
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;

typedef long long LL;
typedef pair<int,int> Pii;

int t,n,m,i,j,k,cntS,cntT;
char c[N][N];
struct node{int x,y;} S[N],T[N];
bool vis[N][N];
vector<int> e[N],reach[N][N];

const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};
bool can(int x,int y){return x&&x<=n&&y&&y<=m&&c[x][y]!='#'&&!vis[x][y];}
unordered_set<int> H[N];
void bfs(int x,int y,int id)
{
    struct rec{int x,y,d;};
    queue<rec> q;
    q.push({x,y,0}), vis[x][y]=1;
    while (!q.empty())
    {
        int tx=q.front().x, ty=q.front().y, td=q.front().d; q.pop();
        for (int i:reach[tx][ty])
            if (H[id].find(i)==H[id].cend()) H[id].insert(i), e[id].push_back(i);
        if (td==k) continue;
        for (int i=0; i<4; i++)
            if (can(tx+dx[i],ty+dy[i]))
                vis[tx+dx[i]][ty+dy[i]]=1, q.push({tx+dx[i],ty+dy[i],td+1});
    }
}

int my[N],mx[N];
bool visy[N];
bool hungary(int u)
{
    for (int v:e[u])
        if (!visy[v]){
            visy[v]=1;
            if (my[v]==-1 || hungary(my[v])){
                mx[u]=v, my[v]=u;
                return 1;
            }
        }
    return 0;
}

bool dyed[N];
void topo(int u,int *in,const vector<int> *e,vector<Pii> &ans)
{
    ans.push_back(make_pair(u,mx[u])), dyed[u]=1;
    for (int v:e[u])
        if (--in[v]==0) topo(v,in,e,ans);
}
int main()
{
    freopen("D-large-practice.in","r",stdin);
    freopen("out3.txt","w",stdout);

	cin>>t;
	for (int tt=1; tt<=t; tt++)
    {
        cin>>m>>n>>k; cntS=cntT=0;
        for (i=1; i<=n; i++)
            for (j=1; j<=m; j++){
                reach[i][j].clear();
                cin>>c[i][j];
                if (c[i][j]=='S') S[++cntS]={i,j};
                if (c[i][j]=='T') T[++cntT]={i,j};
            }
        for (i=1; i<=cntT; i++)
        {
            for (j=T[i].x+1; j<=n; j++)
                if (c[j][T[i].y]!='#') reach[j][T[i].y].push_back(i); else break;
            for (j=T[i].x-1; j; j--)
                if (c[j][T[i].y]!='#') reach[j][T[i].y].push_back(i); else break;
            for (j=T[i].y+1; j<=m; j++)
                if (c[T[i].x][j]!='#') reach[T[i].x][j].push_back(i); else break;
            for (j=T[i].y-1; j; j--)
                if (c[T[i].x][j]!='#') reach[T[i].x][j].push_back(i); else break;
        }
        for (i=1; i<=cntS; i++)
            H[i].clear(), e[i].clear(), mem(vis,0), bfs(S[i].x,S[i].y,i);
        //Hungary Algorithm
        mem(mx,0), mem(my,-1);
        for (i=1; i<=cntS; i++)
            if (!mx[i]) mem(visy,0), hungary(i);

        int in[N]={0};
        vector<int> pre[N];
        for (i=1; i<=cntS; i++)
            if (mx[i])
                for (j:e[i]){
                    if (j==mx[i]) break;
                    pre[my[j]].push_back(i), in[i]++;
                }
        vector<Pii> ans;
        for (mem(dyed,0),i=1; i<=cntS; i++)
            if (mx[i]&&!in[i]&&!dyed[i]) topo(i,in,pre,ans);

        printf("Case #%d: %d\n",tt,ans.size());
        for (Pii i:ans) cout<<i.first<<' '<<i.second<<endl;
    }
	return 0;
}
