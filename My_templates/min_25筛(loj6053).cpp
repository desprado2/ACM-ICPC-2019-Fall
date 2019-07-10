#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define dbg() system("pause")
#define clr(a,n)\
 for(int i=0; i<n; i++)a[i].clear();
#define N 200005
using namespace std;

typedef long long ll;
const ll M=1e9+7;

ll n;
int i,j,k,cnt,pr[N/10];
bool fl[N];
void sieve(){
    fl[1]=1;
    for (i=2; i<=sqrt(n); i++){
        if (!fl[i]) pr[++cnt]=i;
        for (j=1; j<=cnt&&pr[j]*i<=sqrt(n); j++){
            fl[i*pr[j]]=1;
            if (i%pr[j]==0) break;
        }
    }
}

ll num[N],c;
ll sum1[N],sum2[N],g1[N],g2[N],g[N];
int id1[N],id2[N];
int H(ll x){return x<N?id1[x]:id2[n/x];}

ll f(ll p,int e){return p^e;}
ll S(int x,int j){
    ll ret=(g[x] - (sum2[j-1]-sum1[j-1]+(j>1?2:0)) +M)%M;
    for (int k=j; 1ll*pr[k]*pr[k]<=num[x]&&k<=cnt; k++){
        ll pke=pr[k];//pke: Pk*e
        for (int e=1; pke*pr[k]<=num[x]; e++,pke*=pr[k])
            (ret+=S(H(num[x]/pke),k+1)*f(pr[k],e)%M + f(pr[k],e+1)) %=M;
    }
    return ret;
}
int min_25(){
    ll i,j;
    for (i=1; i<=n; i=n/(n/i)+1)
        num[++c]=n/i, n/i<N?id1[n/i]=c:id2[n/(n/i)]=c;//id1,id2ÓÃÓÚ¹þÏ£
    for (i=1; i<=cnt; i++)
        sum1[i]=sum1[i-1]+1, sum2[i]=(sum2[i-1]+pr[i])%M;
    for (i=1; i<=c; i++)//g1(x)=1, g2(x)=x
        g1[i]=num[i]-1,
        g2[i]=(num[i]&1)? (num[i]-1)/2%M*((num[i]+2)%M)%M : (num[i]+2)/2%M*((num[i]-1)%M)%M;
    for (j=1; j<=cnt; j++)
        for (i=1; 1ll*pr[j]*pr[j]<=num[i]&&i<=c; i++)
            g1[i]=(g1[i] - g1[H(num[i]/pr[j])] + sum1[j-1] +M)%M,
            g2[i]=(g2[i] - pr[j]*g2[H(num[i]/pr[j])]%M + pr[j]*sum2[j-1]%M +M)%M;
    for (i=1; i<=c; i++)
        g[i]=(g2[i]-g1[i]+(num[i]>=2?2:0) +M)%M;//f(p)=p-1, exception:f(2)=3
    return S(1,1)+1;
}
int main()
{
    cin.tie(0), ios::sync_with_stdio(false);

    cin>>n, sieve();
    cout<<min_25();
    return 0;
}
