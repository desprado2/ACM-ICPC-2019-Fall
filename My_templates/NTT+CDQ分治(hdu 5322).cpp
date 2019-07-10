#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define dbg() system("pause")
#define clr(a,n)\
 for(int i=0; i<n; i++)a[i].clear();
#define N 100005
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
const ll M=998244353;
const ll G=3;

ll qp(ll x,ll y){
    if (!y) return 1;
    ll ret=qp(x,y>>1);
    return (y&1)?ret*ret%M*x%M:ret*ret%M;
}
int n,i,j,k;
ll f[N<<1],g[N<<1],fac[N<<1],ifac[N<<1];

void NTT(ll* a,ll* p,int n,bool INV)
{
    int i,j,k,rev;
    const ll ig=qp(G,M-2),in=qp(n,M-2);
    for (i=0; i<n; i++){
        rev=0,k=1;
        while (k<n) rev=(rev<<1)+((i&k)>0),k<<=1;
        p[rev]=a[i];
    }

    for (k=1; k<n; k<<=1)
    {
        ll unit=INV?qp(ig,(M-1)/(k*2)):qp(G,(M-1)/(k*2));
        for (i=0; i<n; i+=k*2)
        {
            ll omega=1;
            for (j=i; j<i+k; j++,omega=omega*unit%M){
                ll x=p[j],y=p[j+k]*omega%M;
                p[j]=(x+y)%M, p[j+k]=(x-y+M)%M;
            }
        }
    }

    if (INV)
        for (i=0; i<n; i++) p[i]=p[i]*in%M;
}
int p2(int x){
    for (int i=1; ; i<<=1)
        if (i>=x) return i;
}
ll pA[N<<1], pB[N<<1], A[N<<1], B[N<<1];
void mul(ll* A,ll* B,int bit)//A <- A*B
{
    NTT(A,pA,bit,false), NTT(B,pB,bit,false);
    for (int i=0; i<bit; i++) pA[i]=pA[i]*pB[i]%M;
    NTT(pA,A,bit,true);
}
void calc(int l,int r){
    int i,j,k,mid=(l+r)/2;
    if (l==r) return;
    calc(l,mid);

    int len=p2(r-l+1);
    for (i=0; i<len; i++) A[i]=B[i]=0;
    for (i=l; i<=mid; i++) A[i-l]=f[i]*ifac[i]%M;
    for (i=0; i<len; i++) B[i]=1ll*i*i%M;
    mul(A,B,len);
    for (i=mid+1; i<=r; i++)
        (f[i]+=A[i-l]*fac[i-1]%M) %=M;

    calc(mid+1,r);
}
int main()
{
    ios::sync_with_stdio(false);
    for (i=1,fac[0]=ifac[0]=1; i<=N-5; i++)
        fac[i]=fac[i-1]*i%M, ifac[i]=qp(fac[i],M-2);
    for (i=1; i<=N-5; i++)
        g[i]=1ll*i*i%M*ifac[i-1]%M;//dbg();
    f[0]=1, calc(0,N-5);
    int n;
    while (cin>>n) cout<<f[n]<<endl;
}
