bool fl[N];
int pr[N],phi[N],mu[N],d[N],sigma[N],cnt=0;
void sieve(){
    int i,j,e[N],sum[N];
    fl[1]=true, phi[1]=mu[1]=d[1]=sigma[1]=1;
    for (i=2; i<=N-5; i++){
        if (!fl[i]){
            cnt++,pr[cnt]=i;
            phi[i]=i-1, mu[i]=-1, d[i]=2, sigma[i]=i+1;
            e[i]=1, sum[i]=i+1;
        }
        for (j=1; i*pr[j]<=N-5&&j<=cnt; j++){
            fl[i*pr[j]]=1;
            if (i%pr[j]==0){
                mu[i*pr[j]]=0, phi[i*pr[j]]=phi[i]*pr[j], d[i*pr[j]]=d[i]/(e[i]+1)*(e[i]+2), sigma[i*pr[j]]=sigma[i]/sum[i]*(sum[i]*pr[j]+1);
                e[i*pr[j]]=e[i]+1, sum[i*pr[j]]=sum[i]*pr[j]+1;
                break;
            }
            else{
                mu[i*pr[j]]=-mu[i], phi[i*pr[j]]=phi[i]*(pr[j]-1), d[i*pr[j]]=d[i]*2, sigma[i*pr[j]]=sigma[i]*(1+pr[j]);
                e[i*pr[j]]=1, sum[i*pr[j]]=1+pr[j];
            }
        }
    }
}

bool millerrabin(ll p)
{
    if (p==2) return 1;
    if (p<2 || p%2==0 || p == 46856248255981ll) return 0;

    ll t = p-1, s = 0;
    while (t%2==0)
        s++ , t >>= 1;
    int prime[]={2,3,7,61,24251};
	for (int i=0; i<5 && prime[i]<p; i++){
        ll a = prime[i], b = powmod(a , t , p);
        for (int j=1; j<=s; j++){
            ll k = b * b % p;
            if (k==1 && b!=1 && b!=p-1) return 0;
            b = k;
        }
        if (b!=1) return 0;
    }
    return 1;
}
