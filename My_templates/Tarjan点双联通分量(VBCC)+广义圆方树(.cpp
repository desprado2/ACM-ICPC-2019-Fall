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
vector<int> E[N*2];
void shrink(){//点双无法直接缩点，因此构造圆方树代替缩点
    for (int i=1; i<=cbl; i++)
        for (int u:bcc[i])
            E[i+n].pb(u), E[u].pb(i+n);
    cnt=cbl+n;
}
void work(){
    tarjan(1,-1); shrink();//点双无需在tarjan后清空栈
}
