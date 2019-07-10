#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define dbg() system("pause")
using namespace std;

typedef long double LD;
const LD eps=1e-12;

struct Point{
    LD x,y;
    Point(LD x=0,LD y=0):x(x),y(y){}
};
struct Line{//线段
    Point s,e;
    LD a;
    Line(){}
    Line(Point _s,Point _e){
        s=_s, e=_e, a=atan2(e.y-s.y,e.x-s.x);
    }
};
bool eq(LD a,LD b){return fabs(a-b)<eps;}//精度允许范围内相等
LD dist(Point a,Point b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
LD cross(Point a1,Point a2,Point b1,Point b2)//向量a和b的叉积,使用起点终点表示
{
    Point a(a2.x-a1.x,a2.y-a1.y), b(b2.x-b1.x,b2.y-b1.y);
    return a.x*b.y - a.y*b.x;
}
LD det(Point vec1,Point vec2){return vec1.x*vec2.y-vec1.y*vec2.x;}//两个向量的叉积

Point intersect(Point a,Point b,Point c,Point d)//求直线AB和直线CD的交点
{
    LD a1=a.y-b.y, b1=b.x-a.x, c1=-det(a,b);
    LD a2=c.y-d.y, b2=d.x-c.x, c2=-det(c,d);
    return Point((c1*b2-c2*b1)/(a1*b2-a2*b1) , (a1*c2-a2*c1)/(a1*b2-a2*b1));
}
bool chk(Line a,Line b,Line c)//判断直线b和直线c交点是否在a右侧(即不在半平面内)
{
    Point P=intersect(b.s,b.e, c.s,c.e);
    return cross(P,a.s,P,a.e)<0;
}
bool cmp(const Line &a,const Line &b){return a.a<b.a || a.a==b.a&&cross(a.s,a.e,a.s,b.e)<0;}
deque<Line> S;//存储有意义的直线
vector<Point> core;
bool HPI(vector<Line> &L)//半平面交
{
    S.clear(), core.clear();
    sort(L.begin(), L.end(), cmp);
    vector<Line> vec;
    for (int i=0; i<L.size(); i++)
        if (!i || L[i].a!=L[i-1].a) vec.pb(L[i]);
    for (int i=0; i<vec.size(); i++){
        while (S.size()>=2 && chk(vec[i], *(S.end()-1), *(S.end()-2))) S.pop_back();
        while (S.size()>=2 && chk(vec[i], *S.begin(), *(S.begin()+1))) S.pop_front();
        S.pb(vec[i]);
    }
    while (S.size()>=2 && chk(*S.begin(), *(S.end()-1), *(S.end()-2))) S.pop_back();
    while (S.size()>=2 && chk(*(S.end()-1), *S.begin(), *(S.begin()+1))) S.pop_front();

    if (S.size()<3) return false;
    for (int i=0,n=S.size(); i<n; i++)
        core.pb(intersect(S[i].s,S[i].e, S[(i-1+n)%n].s,S[(i-1+n)%n].e));
    return true;
}
LD area(vector<Point>& poly)//多边形求面积
{
    int n=poly.size(), i;
    LD ret=0;
    for (i=0; i<n; i++)
        ret+=det(poly[i], poly[(i+1)%n])/2.0;
    return ret;
}

struct tri{
    Point A,B,C;
};
list<tri> T;

Point mid(Point &a,Point &b){return {(a.x+b.x)/2.0, (a.y+b.y)/2.0};}
LD calc(Point *r,bool del=false){
    LD ret=0;
    for (list<tri>::iterator it=T.begin(),tmp; it!=T.end(); )
    {
        vector<Line> L;
        for (int i=0; i<4; i++)
            L.pb(Line(r[i],r[(i+1)%4]));
        L.pb(Line(it->A,it->B)), L.pb(Line(it->B,it->C)), L.pb(Line(it->C,it->A));
        LD A;
        if (!HPI(L) || (A=area(core))<eps){
            if (del){
                tmp=it, tmp++;
                T.erase(it), it=tmp;
            } else it++;
        }
        else ret+=A, it++;
    }
    return ret;
}

int n,w,h,i,j,k;
int main(){
    srand(time(NULL));
    cin.tie(0), ios::sync_with_stdio(false);

    cin>>n>>w>>h;
    for (i=1; i<=n; i++){
        int x1,y1,x2,y2,x3,y3;
        cin>>x1>>y1>>x2>>y2>>x3>>y3;
        Point P(x1,y1), Q(x2,y2), R(x3,y3);
        if (cross(P,Q,P,R)>0) T.push_back({P,Q,R});
        else T.push_back({P,R,Q});
    }

    Point R[4]={Point(0,0), Point(w,0), Point(w,h), Point(0,h)};
    while (1){
        LD now=(R[2].x-R[0].x)*(R[2].y-R[0].y) - calc(R,true);
        if (T.empty()) break;
        for (i=0; i<3; i++){
            Point tmp[4];
            for (j=0; j<4; j++)
                tmp[j]= j!=i?mid(R[j],R[i]):R[j];
            LD A=calc(tmp);
            if ((tmp[2].x-tmp[0].x)*(tmp[2].y-tmp[0].y) - A >= now/4.0 + eps) break;
        }
        for (j=0; j<4; j++)
            R[j]= j!=i?mid(R[j],R[i]):R[j];
    }
    Point ans=mid(R[0],R[2]);
    cout<<setiosflags(ios::fixed)<<setprecision(8)<<ans.x<<' '<<ans.y;
    return 0;
}
