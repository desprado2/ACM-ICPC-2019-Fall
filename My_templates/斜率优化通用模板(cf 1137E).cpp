#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define dbg() system("pause")
#define N 500005
using namespace std;

typedef long long LL;
typedef pair<LL,LL> Pii;

int m,i,j,k,cnt;
LL n,id[N];

struct fun{bool sign,cat;} F;//F: z=arg_(x,y) min/max{y + k*x};
//{0,0}: k<0,min;  {0,1}: k<0,max;  {1,0}: k>0,min;  {1,1}: k>0,max
struct rec{LL x,y;} a[N];
int p=0,q=0,qu[N];//monotonous queue
void add(LL x,LL y,LL ID,const fun &F)
{
    a[++cnt]={x,y}, id[cnt]=ID;
    if (F.cat)
        while (q>p && (long double)(a[qu[q]].x-a[qu[q-1]].x)*(y-a[qu[q]].y) >= (long double)(a[qu[q]].y-a[qu[q-1]].y)*(x-a[qu[q]].x)) q--;
    else//一定要小心，这里会爆long long
        while (q>p && (long double)(a[qu[q]].x-a[qu[q-1]].x)*(y-a[qu[q]].y) <= (long double)(a[qu[q]].y-a[qu[q-1]].y)*(x-a[qu[q]].x)) q--;
    qu[++q]=cnt;
}
int opt(LL k,const fun &F)//查询，得到最优点的编号
{
    if (F.cat)
        while (q>p && a[qu[q-1]].y+k*a[qu[q-1]].x >= a[qu[q]].y+k*a[qu[q]].x) q--;
    else
        while (q>p && a[qu[q-1]].y+k*a[qu[q-1]].x <= a[qu[q]].y+k*a[qu[q]].x) q--;
    return qu[q];
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m, F={false,true};// k<0, max

    LL pre=0,suf=n, head=0, S=0;
    a[0]={0,0};
    p=q=0, qu[0]=0;
    for (i=1; i<=m; i++){
        LL pat,x,y; cin>>pat;
        if (pat==1){
            cin>>x;
            pre+=x, head=S=0, q=p;
            cout<<"1 0"<<endl;
        }
        else if (pat==2){
            cin>>x;
            add(pre+suf, head+(pre+suf)*S, suf, F);
            j=opt(-S,F);
            cout<<(j==0?1:pre+id[j]+1)<<' '<<head-(a[j].y - S*a[j].x)<<endl;
            suf+=x;
        }
        else {
            cin>>x>>y;
            S+=y, head+=x;
            j=opt(-S,F);
            cout<<(j==0?1:pre+id[j]+1)<<' '<<head-(a[j].y - S*a[j].x)<<endl;
        }
    }
	return 0;
}
