#include<bits/stdc++.h>
#define N 100005
using namespace std;

struct Q{int l,r,tim,id;} q[N];//query
struct C{int pos,t;} c[N];//change
int n,m,i,j,k,p,col[N],init[N],bl[N];
int unit,cnt[N*10],ans[N],now;
bool cmp(Q a,Q b)
{
	return (bl[a.l]<bl[b.l])||(bl[a.l]==bl[b.l]&&bl[a.r]<bl[b.r])||(bl[a.l]==bl[b.l]&&bl[a.r]==bl[b.r]&&a.tim<b.tim);
}
void chk(int x,char op){if (x==0&&op=='M') now--; if (x==1&&op=='P') now++;}
int main()
{
	cin>>n>>m;
	unit=int(pow(n,0.666));
	for (i=1; i<=n; i++) cin>>col[i], init[i]=col[i];
	for (i=1; i<=n; i++) bl[i]=(i-1)/unit+1;

	char ch;
	int x,y,cnt1=0,cnt2=0;
	for (i=1; i<=m; i++)
	{
		cin>>ch>>x>>y;
		if (ch=='Q') cnt2++,q[cnt2].l=x,q[cnt2].r=y,q[cnt2].tim=cnt1,q[cnt2].id=cnt2;
		else cnt1++,c[cnt1].pos=x,c[cnt1].t=y;
	}
	sort(q+1,q+cnt2+1,cmp);

	int L=1,R=0,T=0;
	for (i=1; i<=cnt2; i++)
	{
		while (T>q[i].tim) {
			p=c[T].pos;
			if (p>=L&&p<=R) chk(--cnt[col[p]],'M');
			col[p]=init[p];
			if (p>=L&&p<=R) chk(++cnt[col[p]],'P');
			T--;
		}
		while (T<q[i].tim) {
			T++;
			p=c[T].pos;
			if (p>=L&&p<=R) chk(--cnt[col[p]],'M');
			col[p]=c[T].t;
			if (p>=L&&p<=R) chk(++cnt[col[p]],'P');
		}

		while (L<q[i].l) {chk(--cnt[col[L]],'M'); L++;}
		while (L>q[i].l) {L--; chk(++cnt[col[L]],'P');}
		while (R<q[i].r) {R++; chk(++cnt[col[R]],'P');}
		while (R>q[i].r) {chk(--cnt[col[R]],'M'); R--;}
		ans[q[i].id]=now;
	}
	for (i=1; i<=cnt2; i++) cout<<ans[i]<<endl;
	return 0;
}
