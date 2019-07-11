vector<int> e[N];

int now,cbl,dfn[N],low[N],bl[N];
vector<int> bcc[N];
stack<int, vector<int>> stk;
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

void work(){
    tarjan(1,-1);
    bcc[++cbl].clear();
    while (!stk.empty())
        bcc[cbl].pb(stk.top()), bl[stk.top()]=cbl, stk.pop();//注意边双在tarjan完后要清空栈
}
