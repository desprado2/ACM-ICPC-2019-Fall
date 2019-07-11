#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define dbg() system("pause")
#define N 30
#define M 2000
using namespace std;

typedef long double ld;
typedef long long ll;
const ld eps=5e-7;
const ld pi=acos(-1.0);

int dcmp(ld d){
    if (fabs(d)<eps) return 0;
    return d>0?1:-1;
}
struct Point{
    ld x,y;
    bool operator==(const Point& P)const {return dcmp(x-P.x)==0 && dcmp(y-P.y)==0;}
    Point operator-(const Point& P)const {return {x-P.x , y-P.y};}
    ld operator^(const Point& P)const {return x*P.y - y*P.x;}
    ld operator*(const Point& P)const {return x*P.x + y*P.y;}
};
struct circle{
    ld x,y,r;
};
ld Acos(ld x){
    if (x-1<eps&&x>1) return acos(1.0);
    if (-1-x<eps&&x<-1) return acos(-1.0);
    return acos(x);
}
ld Sqrt(ld x){return x<0?0:sqrt(x);}
ld sqr(ld x){return x*x;}
ld dist(Point a,Point b){return Sqrt((a-b)*(a-b));}

int query(circle a,circle b){//判断两圆关系
    if (a.x==b.x && a.y==b.y && a.r==b.r) return -2;//相等
    ld D=sqr(a.x-b.x)+sqr(a.y-b.y);
    if (D-sqr(a.r+b.r)>0) return 0;//相离,注意这里不要用dcmp()
    if (sqr(a.r-b.r)-D>=0)
        return a.r<b.r?-1:1;//-1: a内含于b;  1: b内含于a
    return 2;//相交或者外切
}

ld cirCross(circle a,circle b){//求两圆交面积
    int t=query(a,b);
    if (t==0) return 0;
    if (t==-1) return pi*sqr(a.r);
    if (t==1) return pi*sqr(b.r);
    ld D=dist({a.x,a.y},{b.x,b.y}) ,r1=a.r, r2=b.r;
    ld ang1=Acos((sqr(r1)+sqr(D)-sqr(r2))/(2.0*r1*D));
    ld ang2=Acos((sqr(r2)+sqr(D)-sqr(r1))/(2.0*r2*D));
    return sqr(r1)*ang1 + sqr(r2)*ang2 - D*r1*sin(ang1);
}

//以下模块用来求一个圆的集合中所有的两两交点
hash<ll> HLL;
struct myhash{
    size_t operator()(const Point& P)const{
        ll x=P.x*1e5, y=P.y*1e5;
        return (HLL(x)<<1)^HLL(y);
    }
};
unordered_map<Point,int,myhash> H;
Point pts[M];//用来存储圆的交点
int cnt;
void add(Point& P){//添加一个点
    if (!H.count(P)) pts[++cnt]=P,H[P]=cnt;
}
void getIntersect(circle C[], int n){
    for (int i=1; i<=n; i++)
        for (int j=i+1; j<=n; j++){
            if (query(C[i],C[j])==0) continue;
            ld D=dist({C[i].x,C[i].y},{C[j].x,C[j].y}) ,r1=C[i].r, r2=C[j].r;
            ld t=Acos((sqr(r1)+sqr(D)-sqr(r2))/(2.0*r1*D));
            ld ang=atan2(C[j].y-C[i].y, C[j].x-C[i].x);
            Point P1={C[i].x+r1*cos(ang+t), C[i].y+r1*sin(ang+t)}, P2={C[i].x+r1*cos(ang-t), C[i].y+r1*sin(ang-t)};
            add(P1), add(P2);
        }
}

struct Line{
    Point s,e;
};
struct seg{ld l,r;};
seg tmp;//这个tmp专门用来记录CIL的结果

ld distL(Point P,Line l){//返回点P到直线l的距离
    ld D=dist(l.e,l.s);
    return D==0?0:fabs((l.e-l.s)^(P-l.s)) / D;
}
ld secant(ld r,ld d,ld l){//求一条起点距圆心为l, 圆心到直线距离d的割线长度
    return Sqrt(sqr(l)-sqr(d)) - Sqrt(sqr(r)-sqr(d));
}
bool CIL(circle c, Line l){
//求圆与线段是否相交，若相交返回线段上两个交点的位置，以距离线段起点的长度计
    Point O={c.x,c.y};
    ld D1=dist(l.s, O), D2=dist(l.e, O), r=c.r;
    if (D1<=r&&D2<=r) {
        tmp.l=0, tmp.r=dist(l.s,l.e);
        return 1;
    }
    if (D1<=r&&D2>r){
        tmp.l=0;
        tmp.r=dist(l.s,l.e) - secant(r,distL(O,l),D2);
        return 1;
    }
    else if (D1>r&&D2<=r){
        tmp.r=dist(l.s,l.e);
        tmp.l=secant(r,distL(O,l),D1);
        return 1;
    }
    else{
        ld c1=(l.e-l.s)*(O-l.s), c2=(l.s-l.e)*(O-l.e), D=distL(O,l);
        if (D<r && c1>0 && c2>0){
            tmp.l=secant(r,D,D1);
            tmp.r=dist(l.s,l.e) - secant(r,D,D2);
            return 1;
        }
        return 0;
    }
}
int main(){}
