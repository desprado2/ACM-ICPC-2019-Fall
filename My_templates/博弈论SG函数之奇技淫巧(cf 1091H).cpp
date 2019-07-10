#include<bits/stdc++.h>
#define N 200000
typedef long long LL;
using namespace std;

int n,c,i,j,k,cnt,pr[N],sg[N];
bool fl[N];

bitset<N> can,s[105],t,zero(0);
int main()
{
    cin>>n>>c;
    fl[1]=1;
    for (i=2; i<N; i++){
        if (!fl[i]) pr[++cnt]=i;
        for (j=1; j<=cnt&&i*pr[j]<N; j++){
            fl[i*pr[j]]=1;
            if (i%pr[j]==0) break;
        }
    }
    for (i=1; i<=cnt; i++)
        for (j=i; j<=cnt&&LL(pr[i])*LL(pr[j])<N; j++)
            fl[pr[i]*pr[j]]=0;
    fl[c]=1;

    for (i=1; i<N; i++)
        if (!fl[i]) can[i]=1;

    sg[0]=sg[1]=0;
    s[0]|=can<<0, s[0]|=can<<1;
    for (i=2; i<N; i++){
        for (j=0; j<=100; j++)
            if (!s[j][i]) break;
        sg[i]=j;
        s[j]|=can<<i;
    }
    int SG=0;
    for (i=1; i<=n; i++){
        int x,y,z;
        cin>>x>>y>>z;
        SG^=sg[y-x-1]^sg[z-y-1];
    }
    cout<<(SG?"Alice\nBob\n":"Bob\nAlice\n");
	return 0;
}
