void exgcd(LL a,LL b,LL &x,LL &y){// 求ax+by=gcd(a,b)的一个特解(x,y)
	if (b==0) {x=1,y=0; return;}
	exgcd(b,a%b,x,y);
	LL t=x; x=y, y=t-(a/b)*y;
}
