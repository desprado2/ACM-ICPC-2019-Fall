#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define N 250005
using namespace std;

int n,i,j,k,cnt,a[N],base[32],top_digit[32];
int top(int x){
    int i,j;
    for (i=1; i<=1e9; i<<=1)
        if (i&x) j=i;
    return j;
}
int main()
{
    cin>>n;
    for (i=1; i<=n; i++) cin>>a[i],a[i]^=a[i-1];
    if (a[n]==0) {cout<<-1; return 0;}

    for (i=1; i<=n; i++)
    {
        int t=a[i];
        for (j=1; j<=cnt; j++)
            if (t&top_digit[j]) t^=base[j];
        if (t!=0) base[++cnt]=t,top_digit[cnt]=top(t);
        for (j=1; j<cnt; j++)
            if (t&top_digit[j]) base[j]^=t;
    }

    cout<<cnt;
	return 0;
}
