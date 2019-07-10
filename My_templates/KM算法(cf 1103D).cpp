#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define N 1000005
#define eff 12005
#define maxF 12
using namespace std;

typedef long long LL;

int n,i,j,k,cnt,tot;
struct tzy{
    LL a,e;
    bool operator <(const tzy &x){return e<x.e;}
} b[N];

LL gcd(LL a,LL b){return b==0?a:gcd(b,a%b);}
LL G,ans=1ll<<60,pr[maxF];

hash<LL> HLL;
struct MyHash{
    size_t operator ()(const vector<LL> &a)const
    {
        size_t ret=0;
        for (LL i:a) ret=(ret^(HLL(i)<<1))>>1;
        return ret;
    }
};
struct MyCmp{
    bool operator ()(const vector<LL> &a,const vector<LL> &b)const
    {
        if (a.size()!=b.size()) return 0;
        for (int i=0; i<a.size(); i++)
            if (a[i]!=b[i]) return 0;
        return 1;
    }
};
unordered_map<vector<LL>,vector<int>,MyHash,MyCmp> H;
void HashClear(unordered_set<int> &a){while(!a.empty()) a.erase(a.begin());}

int c[eff*maxF],id[eff][maxF];
//本题中,边的代价只与右部有关,存储在数组c中
//id是边表,相当于一个vector
unordered_set<int> X,Y,visitedY;
LL matchx[1<<maxF],topmarkx[1<<maxF],matchy[eff*maxF],topmarky[eff*maxF],minz;
bool aug(int u)//KM增广
{
    X.insert(u);
    for (int i=1,v; i<=cnt&&id[u][i]; i++)
    {
        v=id[u][i];
        if (Y.find(v)!=Y.cend()) continue;
        LL t=c[v]-(topmarkx[u]+topmarky[v]);
        if (t==0)
        {
            Y.insert(v);
            if (!matchy[v] || aug(matchy[v]))
            {
                matchx[u]=v,matchy[v]=u;
                return 1;
            }
        }
        else minz=min(minz,t);//t>0
    }
    return 0;
}
void dfs(int dep,int S,vector<int> pick)
{
    int i;
    if (S==0){
        for (i=0; i<dep; i++)
        {
            if (id[pick[i]][1]==0) return;
            topmarkx[pick[i]]=c[id[pick[i]][1]];
            //因为边表id已经排序，所以不需要再找一次最小值
        }//topmarky默认是0
        for (i=0; i<dep; i++)
            while(1){
                minz=INT_MAX;
                HashClear(X),HashClear(Y);
                if (aug(pick[i])) break;
                if (minz>=INT_MAX) return;

                for (int j:X) topmarkx[j]+=minz;
                for (int j:Y) topmarky[j]-=minz;
            }

        LL tmp=0;
        for (i=0; i<dep; i++) tmp+=c[matchx[pick[i]]];
        ans=min(ans,tmp*dep);
        //Initialization
        for (i=0; i<dep; i++){
            topmarkx[pick[i]]=matchx[pick[i]]=0;
            for (int j=1; j<=cnt&&id[i][j]; j++) topmarky[id[i][j]]=matchy[id[i][j]]=0;
        }
        return;
    }

    for (i=S; i>S/2; i=(i-1)&S)//枚举集合划分
    {
        pick.push_back(i);
        dfs(dep+1,S^i,pick);
        pick.pop_back();
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for (i=1; i<=n; i++) cin>>b[i].a,G=gcd(b[i].a,G);
    if (G==1) {cout<<0; return 0;}
    for (i=1; i<=n; i++) cin>>b[i].e;
    sort(b+1,b+n+1);

    for (i=2; i*i<=G; i++)
        if (G%i==0)
        {
            pr[cnt++]=i;
            LL tmp=1;
            while (G%i==0) G/=i,tmp*=i;
        }
    if (G>1) pr[cnt++]=G;

    for (i=1; i<=n; i++)
    {
        vector<LL> tmp(cnt);
        for (LL re=b[i].a,j=0; j<cnt; j++)
        {
            tmp[j]=1;
            while (re%pr[j]==0) tmp[j]*=pr[j],re/=pr[j];
        }
        if (H.find(tmp)==H.cend()) c[++tot]=b[i].e,H.insert(make_pair(tmp,vector<int>(1,tot)));
        else if (H[tmp].size()<cnt) c[++tot]=b[i].e,H[tmp].push_back(tot);
    }

    c[0]=INT_MAX;
    H.reserve(eff);
    for (auto it:H)
    {
        vector<LL> num=it.first;
        for (j=1; j<(1<<cnt); j++)
        {
            LL tmp=1;
            for (int bit=0; (1<<bit)<=j; bit++)
                if ((1<<bit)&j) tmp*=num[bit];
            if (tmp<=k){
                for (int l:it.second)
                {
                    if (c[l]>=c[id[j][cnt]]) continue;
                    int top;
                    for (top=cnt; top>1&&c[id[j][top-1]]>c[l]; top--)
                        id[j][top]=id[j][top-1];
                    id[j][top]=l;
                }
            }
        }
    }


    dfs(0,(1<<cnt)-1,vector<int>(0));
    if (ans>=1ll<<60) cout<<-1;
    else cout<<ans;
	return 0;
}
