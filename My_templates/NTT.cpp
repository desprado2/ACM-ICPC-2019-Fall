typedef long long ll;
const ll M=998244353;
const ll G=3;

ll qp(ll x,ll y){
    if (!y) return 1;
    ll ret=qp(x,y>>1);
    return (y&1)? ret*ret%M*x%M: ret*ret%M;
}
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
int p2(int x){//找到2^i>=x的最小i
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
