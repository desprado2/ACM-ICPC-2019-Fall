struct fun{bool sign,cat;} F;//F: z=arg_(x,y) min/max{y + k*x};
//{0,0}: k<0,min;  {0,1}: k<0,max;  {1,0}: k>0,min;  {1,1}: k>0,max
struct rec{LL x,y;} a[N];
int p=0,q=0,qu[N];//单调队列
void add(LL x,LL y,LL ID,const fun &F)
{
    a[++cnt]={x,y}, id[cnt]=ID;
    if (F.cat)
        while (q>p && (long double)(a[qu[q]].x-a[qu[q-1]].x)*(y-a[qu[q]].y) >= (long double)(a[qu[q]].y-a[qu[q-1]].y)*(x-a[qu[q]].x)) q--;
    else//一定要小心，这里会爆long long
        while (q>p && (long double)(a[qu[q]].x-a[qu[q-1]].x)*(y-a[qu[q]].y) <= (long double)(a[qu[q]].y-a[qu[q-1]].y)*(x-a[qu[q]].x)) q--;
    qu[++q]=cnt;
}
int query(LL k,const fun &F)//查询，得到最优点的编号
{
    if (F.cat)
        while (q>p && a[qu[q-1]].y+k*a[qu[q-1]].x >= a[qu[q]].y+k*a[qu[q]].x) q--;
    else
        while (q>p && a[qu[q-1]].y+k*a[qu[q-1]].x <= a[qu[q]].y+k*a[qu[q]].x) q--;
    return qu[q];
}
