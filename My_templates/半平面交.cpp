typedef long double LD;
const LD eps=1e-12;

struct Point{
    LD x,y;
    Point(LD x=0,LD y=0):x(x),y(y){}
    Point operator+(const Point& p)const{return {x+p.x , y+p.y};}
    Point operator-(const Point& p)const{return {x-p.x , y-p.y};}
    LD operator^(const Point& p)const {return x*p.y - y*p.x;}
    LD operator*(const Point& p)const {return x*p.x + y*p.y;}
};
struct Line{//线段
    Point s,e;
    LD a;//a:倾角
    Line(){}
    Line(Point _s,Point _e){
        s=_s, e=_e, a=atan2(e.y-s.y,e.x-s.x);
    }
};
bool eq(LD a,LD b){return fabs(a-b)<eps;}//精度允许范围内相等
LD dist(Point a,Point b){return sqrt((a-b)*(a-b));}

Point intersect(Point a,Point b,Point c,Point d)//求直线AB和直线CD的交点
{
    LD a1=a.y-b.y, b1=b.x-a.x, c1=-(a^b);
    LD a2=c.y-d.y, b2=d.x-c.x, c2=-(c^d);
    return Point((c1*b2-c2*b1)/(a1*b2-a2*b1) , (a1*c2-a2*c1)/(a1*b2-a2*b1));
}
bool chk(Line a,Line b,Line c)//判断直线b和直线c交点是否在a右侧(即不在半平面内)
{
    Point P=intersect(b.s,b.e, c.s,c.e);
    return ((a.s-P)^(a.e-P))<0;
}
bool cmp(const Line &a,const Line &b){return a.a<b.a || a.a==b.a&&((a.s-a.e)^(a.s-b.e))<0;}
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
        ret+=(poly[i]^poly[(i+1)%n]) /2.0;
    return ret;
}
