#define root 0
int tr[maxv][alphabet],cnt;//AC Automation
int en[maxv][N], fail[maxv];//en[u][i]指的是匹配到第i位,在自动机的节点u处可以成功匹配多少个模式串
string st[maxv];//st存储对应节点的字符串
void ins(int u,int d,const string &s,const int suflen)//suflen在这个程序中指的是这一个模式串后面通配符长度
{
    if (d==s.size()) {
        for (int i=suflen; i<=n; i++) en[u][i]++;
        return;
    }
    if (!tr[u][s[d]-'0']) tr[u][s[d]-'0']=++cnt,st[cnt]=st[u]+s[d];
    ins(tr[u][s[d]-'0'],d+1,s,suflen);
}
void buildAC()
{
    queue<int> q;
    for (i=0; i<alphabet; i++)
        if (tr[root][i]) q.push(tr[root][i]);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for (i=0; i<alphabet; i++)
            if (tr[u][i]){
                q.push(tr[u][i]);
                fail[tr[u][i]]=tr[fail[u]][i];
            }
            else tr[u][i]=tr[fail[u]][i];
    }
}
bool vis[maxv];
void update(int u)//这一段一般来说必不可少，因为走到"abcd"的节点上实际上也匹配了"cd"模式串
{
    if (vis[u] || u==root) return;
    vis[u]=1, update(fail[u]);
    for (int i=0; i<=n; i++) en[u][i]+=en[fail[u]][i];
}
void work(){//构建一个普通AC自动机
    doInsert();
    buildAC();
    for (int i=1; i<=cnt; i++) update(i);
}
/*以下是一段AC自动机上求字典序最小的dp实例
    f[i][v]:待匹配串长度为i,走到v节点总共匹配模式串次数的最大值
    pre[i][v], match[i][v]:记录转移路径,便于输出答案
    struct rec{pair<int,int> p; int pos;}是一个更新状态转移优先顺序的记录
    
    int seq[maxv];//按照seq的顺序更新状态,排在前面的点字典序小
    memset(f,128,sizeof(f)), memset(pre,-1,sizeof(pre));
    f[0][root]=en[root][n];
    for (i=0; i<=cnt; i++) seq[i]=i;//因为一开始只有root处有dp值,也就是说其他点根本没有用,因此“初始字典序”可以是任意的
    rec p[maxv];
    for (i=1; i<=n; i++)
    {
        for (k=0; k<=cnt; k++)//因为保证了seq的字典序顺序,所以转移的时候只需要考虑>的情况
        {
            int u=seq[k];
            for (j=0; j<alphabet; j++)
            {
                int v=tr[u][j];
                if (f[i-1][u]+en[v][n-i]>f[i][v])
                    f[i][v]=f[i-1][u]+en[v][n-i], pre[i][v]=u, alpha[i][v]=j, p[v].p=make_pair(k,j);
		    //k是当前字典序,j是新加进来字符的字典序
            }
        }
        for (k=0; k<=cnt; k++) p[k].pos=k;
        sort(p,p+cnt+1,cmp);
        for (k=0; k<=cnt; k++) seq[k]=p[k].pos;//更新字典序顺序
    }
*/

