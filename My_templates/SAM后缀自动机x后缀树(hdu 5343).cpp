#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define pb push_back
#define mp make_pair
#define mem(a,b) memset(a,b,sizeof(a))
#define dbg() system("pause")
#define clr(a,n)\
 for(int i=0; i<n; i++)a[i].clear();
#define N 100005
using namespace std;

typedef unsigned long long LL;
typedef pair<int,int> Pii;

#define root 0
struct SAM{
    int e[N*4][26];
    int lst,cur,link[N*4],len[N*4],cnt;
    char lstc[N*4];//lstc仅仅用于后缀树，表示这个节点的开头字母(在反序自动机上是结尾)
    bool isleaf[N*4];

    SAM(){mem(isleaf,0), mem(len,0), cnt=0;}
    void clear(){mem(isleaf,0), mem(len,0), cnt=0; mem(e,0);}
    void build(const string& S){
        len[root]=0, link[root]=-1, cur=root;
        for (char c:S){
            c-='a';
            lst=cur, cur=++cnt;
            len[cur]=len[lst]+1, isleaf[cur]=1, lstc[cur]=c+'a';

            int u=lst, v;
            while(u!=-1 && !e[u][c])
                e[u][c]=cur, u=link[u];
            if (u==-1) {link[cur]=root; continue;}

            v=e[u][c];
            if (len[v]==len[u]+1) {link[cur]=v; continue;}

            int clone=++cnt;
            len[clone]=len[u]+1, link[clone]=link[v], memcpy(e[clone],e[v],sizeof(e[v])), lstc[clone]=lstc[v];
            link[v]=link[cur]=clone;
            for (; u!=-1 && e[u][c]==v; u=link[u])
                e[u][c]=clone;
        }
    }
};

int cnt[N*4],g[26];
vector<int> son[N*4];
void tra(int u, const SAM& B){
    cnt[u]=B.len[u]-B.len[B.link[u]];
    for (int v:son[u]){
        tra(v,B);
        cnt[u]+=cnt[v];
    }
    if (B.link[u]==root)
        g[B.lstc[u]-'a']=cnt[u];
}
LL f[N*4];
void dfs(int u, const SAM& A){
    if (f[u]) return;
    for (char c='a'; c<='z'; c++)
        if (!A.e[u][c-'a']) f[u]+=g[c-'a'];
        else {
            int v=A.e[u][c-'a'];
            dfs(v,A), f[u]+=f[v];
        }
    f[u]++;
}
SAM A,B;
char aa[N],bb[N];
int main()
{
    cin.tie(0), ios::sync_with_stdio(false);
    int T; cin>>T;
    while (T--){
        string a,b;
        cin>>a>>b;

        A.clear(), B.clear();
        reverse(b.begin(), b.end());
        A.build(a), B.build(b);

        mem(cnt,0); clr(son,B.cnt+5); mem(g,0);
        for (int i=1; i<=B.cnt; i++)
            son[B.link[i]].pb(i);
        tra(root,B);

        mem(f,0);
        dfs(root,A);
        cout<<f[0]<<endl;
    }
	return 0;
}
