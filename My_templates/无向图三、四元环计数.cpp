int n, m, deg[N];//deg[]:度数
vector<int> G[N], e[N];//G:原图; e:新图G'
bool ecmp(int x,int y){return deg[x]>deg[y] || deg[x]==deg[y]&&x>y;}
void build_new_graph(){//构造新图G'
    for (int u=1; u<=n; u++)
        for (int v : G[u])
            if (ecmp(u,v)) e[u].pb(v);
}

long long c3[N], c4[N];//统计每一个点出发的三/四元环数量
long long cnt3(){//三元环计数
    int vis[N] = {0};
    for (int u=1; u<=n; u++){
        for (int v : e[u]) vis[v]++;
        for (int v : e[u])
            for (int w : e[v])
                c3[u]+=vis[w], c3[v]+=vis[w], c3[w]+=vis[w];
        for (int v : e[u]) vis[v]=0;
    }
    long long ret = 0;
    for (int u=1; u<=n; u++) ret+=c3[u];
    return ret/3;
}
long long cnt4(){//四元环计数
    int cnt[N] = {0};
    for (int u=1; u<=n; u++){
        for (int v : e[u])
            for (int w : G[v])
                if (ecmp(u,w)){
                    c4[u]+=cnt[w], c4[v]+=cnt[w], c4[w]+=cnt[w];
                    cnt[w]++;
                }
        for (int v : e[u])
            for (int w : G[v])
                if (ecmp(u,w))
                    c4[v]+=(--cnt[w]);
    }
    long long ret = 0;
    for (int u=1; u<=n; u++) ret+=c4[u];
    return ret/4;
}
