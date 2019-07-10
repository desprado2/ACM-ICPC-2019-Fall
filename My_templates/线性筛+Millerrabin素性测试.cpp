#include<bits/stdc++.h>
#define N 1000005
#define M 998244353
typedef long long LL;
using namespace std;

LL q,l,r,i,j,k,x,tmp,ans;
vector<int> num[N];

bool fl[N];
int pr[N],phi[N],mu[N],d[N],sigma[N],cnt=0;
void getpr()
{
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

void getnum()
{
	int i,j,k,tmp;
	for (i=2; i<=N-5; i++)
	{
		tmp=i;
		for (j=1; j<=cnt&&tmp>=pr[j]; j++)
		{
			k=0;
			while (tmp%pr[j]==0) k++,tmp/=pr[j];
			if (k) num[i].push_back(k);
			if (!fl[tmp]) {num[i].push_back(1); break;}
		}
	}//system("pause");
}

LL powmod(LL a,LL x,LL p) //a^x%p
{
	if (x==1) return a%p;
	LL k=powmod(a,x/2,p);
	if (x&1) return k*k%p*a%p;
    else return k*k%p;
}
bool millerrabin(LL p)
{
	if (p==46856248255981) return 0;
	int i,m[5]={2,3,7,61,24251};
	for (i=0; i<5; i++)
		if (powmod(m[i],p-1,p)!=1) return 0;
	return 1;
}

int main()
{
	getpr(), getnum();
	cin>>q;
	while (q--)
	{
		cin>>l>>r>>k;
		ans=0;
		for (i=l; i<=r; i++)
		{
			LL s,p=1;
			tmp=i;
			for (j=1; j<=cnt&&tmp>=pr[j]; j++)
			{
				if (tmp<=N-5)
				{
					for (LL jj=0; jj<num[tmp].size(); jj++)
						p=p*(num[tmp][jj]*k%M+1)%M;
					tmp=1;
					break;
				}
				s=0;
				while (tmp%pr[j]==0) s++,tmp/=pr[j];
				p=p*(s*k%M+1)%M;
				if (j>500&&tmp!=1&&s==0&&millerrabin(tmp)) break;
			}
			if (tmp!=1) p=p*2%M;
			ans=(ans+p)%M;
		}
		cout<<ans<<endl;
	}
	return 0;
}
