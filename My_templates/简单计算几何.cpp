#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
const double eps=1e-6;
using namespace std;

typedef long double ld;

struct Point{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
    Point operator-(const Point& P){return {x-P.x, y-P.y};}
};
struct Line{//�߶�
    Point s,e;
    ld k,b;
    void calc(){(e.x!=s.x)?(k=ld(e.y-s.y)/ld(e.x-s.x), b=s.y-k*s.x):(k=1e18,b=s.x);}
};
bool eq(double a,double b){return fabs(a-b)<eps;}//��������Χ�����
double dist(Point a,Point b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
double cross(Point vec1,Point vec2){return vec1.x*vec2.y-vec1.y*vec2.x;}//���������Ĳ��

bool chkIntersect(Point a,Point b,Point c,Point d) //�����߶�AB��CD�Ƿ��ཻ
{
	double u,v,w,z;
	u=cross(c-a,b-a), v=cross(d-a,b-a);
	w=cross(a-c,d-c) ,z=cross(b-c,d-c);
	return (u*v<=0&&w*z<=0 && (u==0)+(v==0)+(w==0)+(z==0)<4);
}

Point intersect(Point a,Point b,Point c,Point d)//��ֱ��AB��ֱ��CD�Ľ���
{
    double a1=a.y-b.y, b1=b.x-a.x, c1=-cross(a,b);
    double a2=c.y-d.y, b2=d.x-c.x, c2=-cross(c,d);
    return Point((c1*b2-c2*b1)/(a1*b2-a2*b1) , (a1*c2-a2*c1)/(a1*b2-a2*b1));
}
double Lambda(Line a, Line b){//��a.s + lambda*(a.t+a.s) ��ʾ�߶�a��b�Ľ���,����������������
    return cross(a.s-b.s,b.s-b.e)/cross(a.s-a.e,b.s-b.e);
}
bool coline(Point a,Point b,Point c) //��C�Ƿ����߶�AB��
{
	return (eq(cross(a-c,b-c) , 0)
          &&(c.y-a.y)*(c.y-b.y)<=0 && (c.x-a.x)*(c.x-b.x)<=0);
}

int inside(Point u,vector<Point> &poly)//��һ�����Ƿ��ڶ�����ڲ�
{
	int i,n=poly.size(),cnt=0;
	Point v(u.x+5001,u.y+1);
	//���N,M��С��5000,�򶨡�����㡱������5001,����һ��ֱ�߱ز������ڲ���
	for (i=0; i<n; i++)
	{
		if (coline(poly[i],poly[(i+1)%n],u))return 2;
		if (chkIntersect(u,v,poly[i],poly[(i+1)%n])) cnt++;
	}
	if (cnt%2!=0) return 1; else return 0;
}

vector<Point> cp;//�洢͹��
Point O;//��������С��
bool cmp(Point a,Point b){//0~pi ��������
    double A=cross(a-O,b-O);
    return A>=eps || eq(A,0)&&dist(O,a)<dist(O,b);
}
void convex_hull(vector<Point>& poly)//͹��
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
        while (cp.size()>=2 && cross(*(cp.end()-1) - *(cp.end()-2) , poly[i] - *(cp.end()-2))<=0)
            cp.pop_back();
        cp.pb(poly[i]);
    }
}

double area(vector<Point>& poly)//����������
{
    int n=poly.size(), i;
    double ret=0;
    for (i=0; i<n; i++)
        ret+=cross(poly[i], poly[(i+1)%n])/2.0;
    return ret;
}

bool operator<(Point a,Point b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
bool operator==(Point a,Point b){return a.x==b.x&&a.y==b.y;}
bool cmpL(Line a,Line b){return a.k>b.k || a.k==b.k&&a.b>b.b || a.k==b.k&&a.b==b.b&&a.s<b.s || a.k==b.k&&a.b==b.b&&a.s==b.s&&a.e<b.e;}
vector<Line> rd;
void combineCollinear(vector<Line>& l)//�ϲ��������ཻ���߶�
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
int main(){}
