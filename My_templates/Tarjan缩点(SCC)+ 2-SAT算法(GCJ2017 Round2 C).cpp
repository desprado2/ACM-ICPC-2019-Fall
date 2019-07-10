#include<bits/stdc++.h>
#define N 105
#define M 10005
using namespace std;

typedef long long LL;
typedef pair<int,int> Pii;
struct triple{int a,b;char c;};

int t,n,m,i,j,k,cnt,d[N];
char c[N][N],ans[N][N];
struct node{int x,y;} v[M];
bool vis[N][N];

const int dx[]={0,1,0,-1};
const int dy[]={-1,0,1,0};
const int refl[]={1,0,3,2};
const int refr[]={3,2,1,0};
bool can(int x,int y){return x&&x<=n&&y&&y<=m&&c[x][y]!='#';}
bool dfs(int x,int y,int dir,bool init,vector<node> &a)
{
    if (!init && (c[x][y]=='|' || c[x][y]=='-')) return 0;
    if (c[x][y]=='/') dir=refl[dir];
    if (c[x][y]=='\\') dir=refr[dir];
    if (c[x][y]=='.'&&!vis[x][y]) a.push_back({x,y});
    vis[x][y]=1;
    if (can(x+dx[dir],y+dy[dir])) return dfs(x+dx[dir],y+dy[dir],dir,false,a);
    else return 1;
}

vector<Pii> choose[N][N];
void mark(const vector<node> &a,int id,int dir){
    for (node i:a)
        choose[i.x][i.y].push_back(make_pair(id,dir));
}
//---------------------以下是2-SAT和tarjan的内容--------------------------------
vector<int> e[M];
bool dyed[M],noans;
int def[M];
void dye(int u){//2-SAT前决定一些点的选择
    dyed[u]=1;
    def[u]=1,def[u^1]=-1;
    int x=v[u/2+1].x,y=v[u/2+1].y; char t="-|"[u%2];
    if (ans[x][y]=='\0') ans[x][y]=t;
    else if (ans[x][y]!=t) {noans=1; return;}
    for (int i:e[u])
        if (!dyed[i]) dye(i);
}

vector<int> scc[M];
stack<int, vector<int>> stk;
int now,dfn[M],low[M],instack[M];
int bl[M],cbl;
void tarjan(int u)
{
    low[u]=dfn[u]=++now;
    instack[u]=1;
    stk.push(u);
    for (int v:e[u])
    {
        if (def[v]) continue;//在2-SAT之前已经决定了某些点的选择，那么就不能在tarjan中再访问这些点
        if (!dfn[v]) tarjan(stk,v), low[u]=min(low[u],low[v]);
        else if (instack[v]) low[u]=min(low[u],dfn[v]);
    }
    if (dfn[u]==low[u]){
        cbl++, scc[cbl].clear();
        while (stk.top()!=u){
            int t=stk.top();
            scc[cbl].push_back(t), bl[t]=cbl, instack[t]=0;
            stk.pop();
        }
        scc[cbl].push_back(u), bl[u]=cbl, instack[u]=0, stk.pop();
    }
}
vector<int> reve[M];
int in[M];
void topo(int u)
{
    int i,j;
    vector<triple> tmp;
    for (i:scc[u]){
        int id=i/2+1;
        char c="-|"[i%2];

        if (def[i]) return;//如果之前已经取过这部分的对应的某个二元组，那么这部分以及其"上面"的部分就全部不能取
        else tmp.push_back({v[id].x,v[id].y,c});
    }

    for (i=0; i<tmp.size(); i++)
        ans[tmp[i].a][tmp[i].b]=tmp[i].c;
    for (i:scc[u]) def[i]=1,def[i^1]=-1;
    for (i:reve[u])
        if (--in[i]==0) topo(i);
}

int main()
{
    freopen("C-large-practice.in","r",stdin);
    freopen("out.txt","w",stdout);

	cin>>t;
	for (int tt=1; tt<=t; tt++)
    {
        cin>>n>>m;
        for (i=1; i<=n; i++)
            for (j=1; j<=m; j++)
                cin>>c[i][j],choose[i][j].clear();
        cnt=0;
        for (i=1; i<=n; i++)
            for (j=1; j<=m; j++)
                if (c[i][j]=='|' || c[i][j]=='-') v[++cnt]={i,j},ans[i][j]='\0';
                else ans[i][j]=c[i][j];

        int udc=0,dc=0,start[M]={0};
        noans=0;
        for (i=1; i<=cnt; i++)
        {
            vector<node> tmp1,tmp2;
            memset(vis,0,sizeof(vis));
            bool fl1=dfs(v[i].x,v[i].y,0,true,tmp1) && dfs(v[i].x,v[i].y,2,true,tmp1);
            memset(vis,0,sizeof(vis));
            bool fl2=dfs(v[i].x,v[i].y,1,true,tmp2) && dfs(v[i].x,v[i].y,3,true,tmp2);

            if (!fl1 && !fl2) {noans=1; break;}
            else if (fl1 && !fl2) mark(tmp1,i,0),start[++dc]=(i-1)*2;
            else if (!fl1 && fl2) mark(tmp2,i,1),start[++dc]=(i-1)*2+1;
            else {
                mark(tmp1,i,0), mark(tmp2,i,1);
            }
        }
        for (i=1; !noans&&i<=n; i++)
            for (j=1; !noans&&j<=m; j++)
                if (c[i][j]=='.' && choose[i][j].size()==0) noans=1;
        for (i=1; !noans&&i<=n; i++)
            for (j=1; !noans&&j<=m; j++)
            {
                if (c[i][j]!='.') continue;
                if (choose[i][j].size()==1)
                {
                    Pii id=choose[i][j][0];
                    start[++dc]=(id.first-1)*2+id.second;
                }
            }
        if (noans){printf("Case #%d: IMPOSSIBLE\n",tt); continue;}

        for (i=0; i<cnt*2; i++) e[i].clear();
        for (i=1; i<=n; i++)
            for (j=1; j<=m; j++)
            {
                if (c[i][j]!='.' || choose[i][j].size()<2) continue;
                int u=(choose[i][j][0].first-1)*2+choose[i][j][0].second, v=(choose[i][j][1].first-1)*2+choose[i][j][1].second;
                e[u^1].push_back(v), e[v^1].push_back(u);
            }
        memset(def,0,sizeof(def));
        for (i=1; i<=dc; i++)
            memset(dyed,0,sizeof(dyed)), dye(start[i]);

        //Tarjan
        memset(dfn,0,sizeof(dfn)), cbl=now=0;
        for (i=0; i<cnt*2; i++)
            if (!dfn[i]&&!def[i]) tarjan(i);

        for (i=0; !noans&&i<cnt*2; i+=2)
            if (!def[i]&&bl[i]==bl[i^1]) noans=1;
        if (noans){printf("Case #%d: IMPOSSIBLE\n",tt); continue;}
        //2-SAT
        memset(in,0,sizeof(in));
        for (i=1; i<=cbl; i++) reve[i].clear();
        for (i=0; i<cnt*2; i++){
            if (def[i]) continue;
            for (j:e[i])
                if (!def[j]&&bl[i]!=bl[j]) reve[bl[j]].push_back(bl[i]),in[bl[i]]++;
        }

        for (i=1; i<=cbl; i++)
            if (!in[i]) topo(i);
        printf("Case #%d: POSSIBLE\n",tt);
        for (i=1; i<=n; i++){
            for (j=1; j<=m; j++) cout<<ans[i][j];
            cout<<endl;
        }
    }
	return 0;
}
