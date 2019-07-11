const double eps=1e-8;
typedef long double ld;

struct Point{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
    Point operator-(const Point& P)const{return {x-P.x , y-P.y};}
    double operator^(const Point& P)const{return x*P.y - y*P.x;}
    double operator*(const Point& P)const{return x*P.x + y*P.y;}
};
struct Line{//线段
    Point s,e;
    ld k,b;
    void calc(){(e.x!=s.x)?(k=ld(e.y-s.y)/ld(e.x-s.x), b=s.y-k*s.x):(k=1e18,b=s.x);}
};
bool eq(double a,double b){return fabs(a-b)<eps;}//精度允许范围内相等
double dist(Point a,Point b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}

bool chkIntersect(Point a,Point b,Point c,Point d) //求两线段AB和CD是否相交
{
	double u,v,w,z;
	u=(c-a)^(b-a), v=(d-a)^(b-a);
	w=(a-c)^(d-c) ,z=(b-c)^(d-c);
	return (u*v<=0&&w*z<=0 && (u==0)+(v==0)+(w==0)+(z==0)<4);
}

Point intersect(Point a,Point b,Point c,Point d)//求直线AB和直线CD的交点
{
    double a1=a.y-b.y, b1=b.x-a.x, c1=-(a^b);
    double a2=c.y-d.y, b2=d.x-c.x, c2=-(c^d);
    return Point((c1*b2-c2*b1)/(a1*b2-a2*b1) , (a1*c2-a2*c1)/(a1*b2-a2*b1));
}
double Lambda(Line a, Line b){//用a.s + lambda*(a.t+a.s) 表示线段a和b的交点,有利于整理交点坐标
    return ((a.s-b.s)^(b.s-b.e))/((a.s-a.e)^(b.s-b.e));
}
bool coline(Point a,Point b,Point c) //求C是否在线段AB上
{
	return (eq((a-c)^(b-c) , 0)
          &&(c.y-a.y)*(c.y-b.y)<=0 && (c.x-a.x)*(c.x-b.x)<=0);
}

int inside(Point u,vector<Point> &poly)//求一个点是否在多边形内部
{
	int i,n=poly.size(),cnt=0;
	Point v(u.x+5001,u.y+1);
	//如果N,M均小于5000,则定“界外点”坐标是5001,这样一条直线必不穿过内部点
	for (i=0; i<n; i++)
	{
		if (coline(poly[i],poly[(i+1)%n],u))return 2;
		if (chkIntersect(u,v,poly[i],poly[(i+1)%n])) cnt++;
	}
	if (cnt%2!=0) return 1; else return 0;
}

vector<Point> cp;//存储凸包
Point O;//纵坐标最小点
bool cmp(Point a,Point b){//0~pi 极角排序
    double A=(a-O)^(b-O);
    return A>=eps || eq(A,0)&&dist(O,a)<dist(O,b);
}
void convex_hull(vector<Point>& poly)//凸包
{
    int i,t=0,n=poly.size();
    O.y=1e10;
    for (i=0; i<n; i++)
        if (poly[i].y<O.y || poly[i].y==O.y&&poly[i].x<O.x)
            O=poly[i], t=i;
    swap(poly[0],poly[t]);
    sort(poly.begin()+1, poly.end(), cmp);

    if (n<=2){
        for (i=0; i<n; i++) cp.pb(poly[i]);
        return;
    }
    cp.pb(poly[0]), cp.pb(poly[1]);
    for (i=2; i<n; i++){
        while (cp.size()>=2 && ((*(cp.end()-1) - *(cp.end()-2)) ^ (poly[i] - *(cp.end()-2)))<=0)
            cp.pop_back();
        cp.pb(poly[i]);
    }
}

double area(vector<Point>& poly)//多边形求面积
{
    int n=poly.size(), i;
    double ret=0;
    for (i=0; i<n; i++)
        ret+=(poly[i] ^ poly[(i+1)%n])/2.0;
    return ret;
}

bool operator<(Point a,Point b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
bool operator==(Point a,Point b){return a.x==b.x&&a.y==b.y;}
bool cmpL(Line a,Line b){return a.k>b.k || a.k==b.k&&a.b>b.b || a.k==b.k&&a.b==b.b&&a.s<b.s || a.k==b.k&&a.b==b.b&&a.s==b.s&&a.e<b.e;}
vector<Line> rd;
void combineCollinear(vector<Line>& l)//合并共线且相交的线段
{
    int n=l.size(), i;
    sort(l.begin(), l.end(), cmpL);
    Line tmp;
    tmp.k=tmp.b=-1e18;
    for (i=0; i<n; i++){
        if (l[i].k!=tmp.k || l[i].b!=tmp.b || tmp.e<l[i].s){
            if (i!=1) rd.pb(tmp);
            tmp=l[i];
        }
        if (tmp.e<l[i].e) tmp.e=l[i].e;
    }
    rd.pb(tmp);
}
