#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define N 100005
using namespace std;

typedef long long LL;
const LL M=998244353;
const LL g=3;

void exgcd(LL a,LL b,LL &x,LL &y){
	if (b==0) {x=1,y=0; return;}
	exgcd(b,a%b,x,y);
	LL t=x; x=y, y=t-(a/b)*y;
}
LL inv(LL a){
    LL x,y; exgcd(a,M,x,y);
    return (x+M)%M;
}
LL Qpow(LL x,LL y){//x^y
    if (y==0) return 1;
    LL t=Qpow(x,y/2);
    return (y&1)?t*t%M*x%M:t*t%M;
}

void NTT(vector<LL> &a,vector<LL> &p,LL n,bool INV)
{
    int i,j,k,rev;
    const LL ig=inv(g),in=inv(n);
    for (i=0; i<n; i++){
        rev=0,k=1;
        while (k<n) rev=(rev<<1)+((i&k)>0),k<<=1;
        p[rev]=a[i];
    }

    for (k=1; k<n; k<<=1)
    {
        LL unit=INV?Qpow(ig,(M-1)/(k*2)):Qpow(g,(M-1)/(k*2));
        for (i=0; i<n; i+=k*2)
        {
            LL omega=1;
            for (j=i; j<i+k; j++,omega=omega*unit%M){
                LL x=p[j],y=p[j+k]*omega%M;
                p[j]=(x+y)%M, p[j+k]=(x-y+M)%M;
            }
        }
    }

    if (INV)
        for (i=0; i<n; i++) p[i]=p[i]*in%M;
}

void mul(vector<LL> &A,int dega,vector<LL> B,int degb)//A <- A*B
{
    int bit=1,deg=dega+degb;
    while (bit<deg+1) bit<<=1;

    A.resize(bit,0),B.resize(bit,0);
    vector<LL> pA(bit),pB(bit);
    NTT(A,pA,bit,false), NTT(B,pB,bit,false);
    for (int i=0; i<bit; i++) pA[i]=pA[i]*pB[i]%M;
    NTT(pA,A,bit,true);
}
void polymul(vector<LL> *poly,int *para,int l,int r)//(1+para_1*x)(1+para_2*x)...(1+para_m*x)
{
    if (l>r) return;
    if (l==r) {poly[l].resize(2),poly[l][0]=1,poly[l][1]=para[l]; return;}
    int mid=(l+r)/2;
    polymul(poly,para,l,mid), polymul(poly,para,mid+1,r);
    mul(poly[l],mid-l+1,poly[mid+1],r-mid);
}

int n,m,i,j,k,x,y,sz[N];
vector<int> e[N];
LL sum[N],ans=0;

LL calc(const vector<LL> &poly,int deg){
    if (deg==0) return 1;
    LL tmp=0,permutation=1;
    for (int i=0; i<=k&&i<=deg; i++)
        tmp=(tmp+poly[i]*permutation%M)%M,permutation=permutation*(k-i)%M;
    return tmp;
}
void dfs(int u,int fa)
{
    const int deg=e[u].size();
    vector<LL> poly[deg+5];
    int i,j,para[deg+5]={0},cnt=0;

    sum[u]=0,sz[u]=1;
    for (int v:e[u]){
        if (v==fa) continue;
        dfs(v,u);

        ans=(ans+sum[v]*sum[u])%M;
        para[++cnt]=sz[v];
        sz[u]+=sz[v],sum[u]=(sum[u]+sum[v])%M;
    }
    polymul(poly,para,1,cnt);//poly[1]=answer polynomial
    sum[u]=(sum[u]+calc(poly[1],cnt))%M;

    unordered_map<int,LL> h;
    unordered_map<int,LL>::iterator it;
    for (int v:e[u]){
        if (v==fa) continue;

        it=h.find(sz[v]);
        if (it!=h.cend()){
            ans=(ans+sum[v]*it->second%M)%M;
            continue;
        }
        else{
            vector<LL> t(cnt+1),tmp(poly[1]);
            const LL isz=inv(sz[v]);
            for (i=cnt-1,t[cnt]=0; i>=0; i--)
            {
                t[i]=tmp[i+1]*isz%M;
                tmp[i]=(tmp[i]-t[i]+M)%M;
            }
            for (i=cnt; i; i--)
                t[i]=(t[i]+t[i-1]*(n-sz[u])%M)%M;

            const LL F=calc(t,cnt);
            ans=(ans+sum[v]*F%M)%M, h.insert(make_pair(sz[v],F));
        }
    }
}
int main()
{
    cin>>n>>k;
    if (k==1) {cout<<1ll*n*(n-1)/2%M; return 0;}
    for (i=1; i<n; i++){
        cin>>x>>y;
        e[x].push_back(y), e[y].push_back(x);
    }

    dfs(1,0);
    cout<<ans;
	return 0;
}
