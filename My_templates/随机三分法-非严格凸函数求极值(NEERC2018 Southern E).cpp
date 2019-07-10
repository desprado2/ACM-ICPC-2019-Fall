#include<bits/stdc++.h>
#define N 200005
typedef long long LL; 
using namespace std;

LL n,m,x,i,j,k,t,tmp,ans,a[N],b[N];
LL calc(LL u)
{
	LL i,j,t,cnt,ret=0;
	for (i=1,t=cnt=j=0; i<=n; i++)
		if (a[i]<=u)
		{
			if (j+a[i]>k) break;
			j+=a[i],cnt+=a[i],ret++,t++;
			if (t==m) j+=cnt,cnt=t=0;
			if (j>=k) break;
		}
	return ret;
}
LL ra(){return rand()%2+1;}
int main()
{
	srand((int)time(NULL));
	cin>>t;
	while (t--)
	{
		cin>>n>>m>>k;
		for (i=1; i<=n; i++) {cin>>a[i]; b[i]=a[i];}
		sort(b+1,b+n+1);
		long L=1,R=n;
		while (b[R]>k) R--;//避免峰值出现在左端点附近而其它区域全为0 
		while (R-L>=50)
		{
			LL lm=(2*L+R)/3,rm=(L+2*R)/3,lc=calc(b[lm]),rc=calc(b[rm]);
			if (lc>rc) R=rm;
			else if (lc<rc) L=lm;
			else{
				LL quat=(lm-L)/5+ra(); bool fl=0;
				for (i=lm-quat; i>L; i-=quat)
				{
					tmp=calc(b[i]);
					if (tmp>rc) {R=rm,fl=1; break;}
					if (tmp<rc) {L=i,fl=1; break;}
				}
				if (fl) continue;
				quat=(R-rm)/5+ra();
				for (i=rm+quat; i<R; i+=quat)
				{
					tmp=calc(b[i]);
					if (tmp>lc) {L=lm,fl=1; break;}
					if (tmp<lc) {R=i,fl=1; break;}
				}
				if (fl) continue;
				quat=(rm-lm)/5+ra();
				for (i=quat+lm; i<rm; i+=quat)
				{
					tmp=calc(b[i]);
					if (tmp>lc) {L=lm,fl=1; break;}
					if (tmp<lc) {R=i,fl=1; break;}
				}
				if (!fl) L=lm+quat*2,R=lm+quat*3;
			}
		}
		j=k;
		for (i=L,ans=0; i<=R; i++)
		{
			x=calc(b[i]);
			if (ans<x) ans=x,j=b[i];
		}
		cout<<ans<<' '<<j<<endl;
	}
	return 0;
}
