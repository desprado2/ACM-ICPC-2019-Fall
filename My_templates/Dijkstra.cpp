int dis[N];
bool vis[N];
vector<edge> e[N];
void dij(int st)
{
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
        for (edge it:e[u]){
            v=it.to;
            if (dis[u]+it.len<dis[v])
                dis[v]=dis[u]+it.len, qu.push(make_pair(dis[v],v));
        }
    }
}
