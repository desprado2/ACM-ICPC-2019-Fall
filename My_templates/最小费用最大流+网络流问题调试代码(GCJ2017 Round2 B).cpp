#include<bits/stdc++.h>
#define N 5005
#define M 100005
#define inf 0xffffff
using namespace std;

typedef long long LL;

int n,m,c;
int t,i,j,k,cnt,l[N];
struct edge{int to,next,val,c;} e[M];
void adde(int fr,int to,int val,int c)
{
	e[cnt].next=l[fr],e[cnt].to=to,e[cnt].val=val,e[cnt].c=c; l[fr]=cnt; cnt++;
	e[cnt].next=l[to],e[cnt].to=fr,e[cnt].val=0,e[cnt].c=-c; l[to]=cnt; cnt++; //-c !!!
}

int pre[N],id[N],dis[N];
deque<int> qu;
typedef pair<int,int> Pii;
Pii spfa(int st,int en)
{
	int i,j,p=0,q=1,ret=inf;
	bool vis[N];

	qu.clear(); memset(vis,0,sizeof(vis)); memset(dis,0x3f,sizeof(dis));
	qu.push_front(st); dis[st]=0,pre[st]=-1,id[st]=-1; vis[st]=1;
	while (!qu.empty())
	{
		int u=qu.front(),v;
		qu.pop_front();
		for (i=l[u]; i!=-1; i=e[i].next)
		{
			if (e[i].val==0) continue;
			v=e[i].to;
			if (dis[u]+e[i].c<dis[v])
			{
				dis[v]=dis[u]+e[i].c;
				pre[v]=u,id[v]=i;
				if (!vis[v])
				{//SLF optimization
					if (qu.empty()||dis[v]<dis[qu.front()]) qu.push_front(v);
						else qu.push_back(v);
					vis[v]=1;
				}
			}
		}
		vis[u]=0;
	}
	if (dis[en]>n*c) return make_pair(0,-1);

	i=en;
	do ret=min(ret,e[id[i]].val), i=pre[i];
	while (i!=st);
	i=en;
	do e[id[i]].val-=ret,e[id[i]^1].val+=ret, i=pre[i];
	while(i!=st);

	return make_pair(ret,ret*dis[en]);
}
vector<int> pos[N];
int chk(int x)
{
    const int S=1,T=n*3+c+2;
    int i,j;
    memset(l,-1,sizeof(l)), cnt=0;
    for (i=1; i<=c; i++)
        adde(S,i+1,pos[i].size(),0);
    for (i=1; i<=n; i++){
        adde(c+i+1,c+2*n+i+1,inf,0), adde(c+n+i+1,c+2*n+i+1,inf,1);
        adde(c+2*n+i+1,T,x,0);
        if (i>1) adde(c+n+i+1,c+n+i,inf,0);
    }
    for (i=1; i<=c; i++)
        for (j:pos[i]){
            adde(i+1,c+j+1,1,0);
            if (j>1) adde(i+1,c+n+j,1,0);
        }

    int ret=0,cur=0;
    Pii tmp=spfa(S,T);
    while (tmp.first>0) ret+=tmp.second,cur+=tmp.first,tmp=spfa(S,T);
//    for (i=1; i<=T; i++)
//    {
//        for (j=l[i]; j!=-1; j=e[j].next)
//            if (e[j].val) cout<<i<<','<<e[j].to<<':'<<e[j].val<<' '<<e[j].c<<endl;
//
//    }system("pause");
    return cur==m?ret:-1;
}
int main()
{
    freopen("B-large-practice.in","r",stdin);
    freopen("out.txt","w",stdout);

	cin>>t;
	for (int tt=1; tt<=t; tt++)
    {
        cin>>n>>c>>m;
        for (i=1; i<=c; i++) pos[i].clear();
        for (i=1; i<=m; i++)
        {
            int p,b; cin>>p>>b;
            pos[b].push_back(p);
        }
        int L=0,R=m,mid;
        for (i=1; i<=c; i++)
            if (pos[i].size()>L) L=pos[i].size();
        while (L<R){
            mid=(L+R)/2;
            if (chk(mid)>=0) R=mid;
            else L=mid+1;
        }
        printf("Case #%d: %d %d\n",tt,L,chk(L));
    }
	return 0;
}
