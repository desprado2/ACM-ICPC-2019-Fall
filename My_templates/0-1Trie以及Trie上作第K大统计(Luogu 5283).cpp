#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define dbg() system("pause")
#define N 500005
using namespace std;

typedef unsigned int uint;
typedef long long LL;
int n,m,i,j,k,cnt;
uint a[N];
struct node{
    int s[2],cnt;
    node(){s[0]=s[1]=cnt=0;}
} tr[N*32];

#define root 0
void build(int u,uint x,uint t){//Trie
    tr[u].cnt++;
    if (!t) return;

    bool f=t&x;
    if (!tr[u].s[f])
        tr[u].s[f]=++cnt, build(cnt,x,t>>1);
    else build(tr[u].s[f],x,t>>1);
}

LL ans=0;
vector<int> A,B;
void dfs(int dep,int remain,uint now)
{
    if (dep==32 || remain==0) {ans+=1ll*now*remain; return;}

    LL sum1=0;
    for (int i=0; i<A.size(); i++)
        sum1+=(1ll*tr[tr[A[i]].s[0]].cnt*tr[tr[B[i]].s[1]].cnt + 1ll*tr[tr[A[i]].s[1]].cnt*tr[tr[B[i]].s[0]].cnt)/((A[i]==B[i])?2:1);
        //不要忘了考虑/2的情况,下同

    if (sum1<remain){
        vector<int> tA=A,tB=B;
        A.clear(), B.clear();
        for (int i=0; i<tA.size(); i++)//1
        {
            if (tr[tA[i]].s[0] && tr[tB[i]].s[1])
                A.pb(tr[tA[i]].s[0]), B.pb(tr[tB[i]].s[1]);
            if (tA[i]==tB[i]) continue;// Warning!
            if (tr[tA[i]].s[1] && tr[tB[i]].s[0])
                A.pb(tr[tA[i]].s[1]), B.pb(tr[tB[i]].s[0]);
        }
        dfs(dep+1,sum1,now|(1ll<<31-dep));

        A.clear(), B.clear();
        for (int i=0; i<tA.size(); i++)//0
        {
            if (tr[tA[i]].s[1] && tr[tB[i]].s[1])
                A.pb(tr[tA[i]].s[1]), B.pb(tr[tB[i]].s[1]);
            if (tr[tA[i]].s[0] && tr[tB[i]].s[0])
                A.pb(tr[tA[i]].s[0]), B.pb(tr[tB[i]].s[0]);
        }
        dfs(dep+1,remain-sum1,now);
    }
    else{
        vector<int> tA=A,tB=B;
        A.clear(), B.clear();
        for (int i=0; i<tA.size(); i++)//1
        {
            if (tr[tA[i]].s[0] && tr[tB[i]].s[1])
                A.pb(tr[tA[i]].s[0]), B.pb(tr[tB[i]].s[1]);
            if (tA[i]==tB[i]) continue;// Warning!
            if (tr[tA[i]].s[1] && tr[tB[i]].s[0])
                A.pb(tr[tA[i]].s[1]), B.pb(tr[tB[i]].s[0]);
        }
        dfs(dep+1,remain,now|(1ll<<31-dep));
    }
}
int main()
{
    cin>>n>>k;
    for (i=1; i<=n; i++)
        cin>>a[i], a[i]^=a[i-1];
    for (i=0; i<=n; i++)
        build(root,a[i],1ll<<31);

    tr[0].cnt=0;
    A.pb(0),B.pb(0), dfs(0,k,0);
    cout<<ans;
    return 0;
}
