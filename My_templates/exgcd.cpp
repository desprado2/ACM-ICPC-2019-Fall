#include<bits/stdc++.h>
typedef long long LL;
using namespace std;

void exgcd(LL a,LL b,LL &x,LL &y){
	if (b==0) {x=1,y=0; return;}
	exgcd(b,a%b,x,y);
	LL t=x; x=y, y=t-(a/b)*y;
}
LL inv(LL a){
    LL x,y;
    exgcd(a,M,x,y);
    return (x+M)%M;
}
