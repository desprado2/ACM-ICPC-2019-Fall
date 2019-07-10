#include<bits/stdc++.h>
#define N 5005
typedef long long LL;
using namespace std;

int n,m,i,j,k,tmp,x;
double f[N][2],p[N][2],g[N][9][29],gp[N][9][29],ans;
double d81(int x){return double(x)/81.0;}
double d100(int x){return double(x)/100.0;}
int main()
{
	cin>>n;
	if (n==1) {ans=d81(2)*4.0+d81(43)*5.0+d81(15)*2.0+d81(21)*3.0; cout<<setiosflags(ios::fixed)<<setprecision(7)<<ans; return 0;}

	f[1][1]=0.43*3.0+0.02*2.0+0.45; f[1][0]=0.21*2.0+0.34*1.0+0.55;
	p[1][1]=0.45,p[1][0]=0.55;
	for (i=2; i<n; i++)
	{
		f[i][1]=(0.43*3.0+0.02*2.0)*p[i-1][0]+0.45*f[i-1][0]+(0.49*4.0+0.06*3.0)*p[i-1][1]+0.55*f[i-1][1]+0.45*p[i-1][0]+0.55*p[i-1][1];
		f[i][0]=(0.21*2.0+0.34*1.0)*p[i-1][0]+0.55*f[i-1][0]+(0.15*3.0+0.30*2.0)*p[i-1][1]+0.45*f[i-1][1]+0.55*p[i-1][0]+0.45*p[i-1][1];
		p[i][1]=0.45*p[i-1][0]+0.55*p[i-1][1];
		p[i][0]=0.55*p[i-1][0]+0.45*p[i-1][1];
	}
	ans+=f[n-1][0]*d81(45)+(d81(2)*2.0+d81(43)*3.0)*p[n-1][0]+f[n-1][1]*d81(53)+(d81(4)*3.0+d81(49)*4.0)*p[n-1][1];//carry
	ans+=f[n-1][0]*d81(36)+(d81(15)*1.0+d81(21)*2.0)*p[n-1][0]+f[n-1][1]*d81(28)+(d81(13)*2.0+d81(15)*3.0)*p[n-1][1];//not carry
	ans+=p[n-1][0]*d81(45)*2.0+p[n-1][1]*d81(53)*2.0+p[n-1][0]*d81(36)+p[n-1][1]*d81(28); //digits

	gp[1][1][0]=0.08,gp[1][0][1]=0.56,gp[1][0][0]=0.36;
	for (i=2; i<n; i++)
		for (j=0; j<=8; j++)
			for (k=0; k<=28; k++)
			{
				g[i][j][k]=(g[i-1][j][k]+gp[i-1][j][k]*1.0)*d100(j+k*2)+g[i-1][j][k]*d100(36);
				if (j) g[i][j][k]+=g[i-1][j-1][k]*d100(8-(j-1));
				if (k) g[i][j][k]+=g[i-1][j][k-1]*d100(56-2*(k-1));
				gp[i][j][k]=gp[i-1][j][k]*d100(j+k*2+36);
				if (j) gp[i][j][k]+=gp[i-1][j-1][k]*d100(8-(j-1));
				if (k) gp[i][j][k]+=gp[i-1][j][k-1]*d100(56-2*(k-1));
			}
	for (j=0; j<=8; j++)
		for (k=0; k<=28; k++)
		{
			if (!j&&!k) continue;
			g[n][j][k]=(g[n-1][j][k]+gp[n-1][j][k]*1.0)*d81(j+k*2)+g[i-1][j][k]*d81(17);
			if (j) g[n][j][k]+=g[n-1][j-1][k]*d81(8-(j-1));
			if (k) g[n][j][k]+=g[n-1][j][k-1]*d81(56-2*(k-1));
			ans-=g[n][j][k];
		}
//	cout<<g[2][0][1]+g[2][1][0];system("pause");
	cout<<setiosflags(ios::fixed)<<setprecision(7)<<ans;
	return 0;
}
