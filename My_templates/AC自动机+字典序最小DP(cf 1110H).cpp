#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define maxv 16005
#define N 2005
#define alphabet 10
using namespace std;

int n,i,j,k,f[N][maxv],pre[N][maxv],alpha[N][maxv];
string l,r,st[maxv];

struct tzy{pair<int,int> p; int pos;};
bool cmp(tzy a,tzy b){return a.p.first<b.p.first || a.p.first==b.p.first&&a.p.second<b.p.second;}

#define root 0
int tr[maxv][alphabet],cnt;//AC Automation
int en[maxv][N];
int fail[maxv];
void ins(int u,int d,const string &s,const int suflen)
{
    if (d==s.size()) {
        for (int i=suflen; i<=n; i++) en[u][i]++;
        return;
    }
    if (!tr[u][s[d]-'0']) tr[u][s[d]-'0']=++cnt,st[cnt]=st[u]+s[d];
    ins(tr[u][s[d]-'0'],d+1,s,suflen);
}
void buildAC()
{
    queue<int> q;
    for (i=0; i<alphabet; i++)
        if (tr[root][i]) q.push(tr[root][i]);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for (i=0; i<alphabet; i++)
            if (tr[u][i]){
                q.push(tr[u][i]);
                fail[tr[u][i]]=tr[fail[u]][i];
            }
            else tr[u][i]=tr[fail[u]][i];
    }
}

bool vis[maxv];
void update(int u)
{
    if (vis[u]||u==root) return;

    vis[u]=1, update(fail[u]);
    for (int i=0; i<=n; i++) en[u][i]+=en[fail[u]][i];
}

string dfs(int u,int d)
{
    if (d==0) return "";
    return dfs(pre[d][u],d-1)+to_string(alpha[d][u]);
}
int main()
{
    cin>>l>>r>>n;
    if (l==r) ins(root,0,l,0);
    else{
        i=j=0;
        string L,R;
        if (l.size()==r.size()){
            for (; l[i]==r[j]; i++,j++)
                L+=l[i],R+=r[j];

            for (k=l[i]-'0'+1; k<r[j]-'0'; k++)
                ins(root,0,L+to_string(k),l.size()-i-1);
            L+=l[i],R+=r[j],i++,j++;
        }
        else {
            for (k=l.size()+1; k<r.size(); k++)
                ins(root,0,"",k);
        }

        for (; i<l.size(); i++){
            for (k=l[i]-'0'+1; k<10; k++)
                ins(root,0,L+to_string(k),l.size()-i-1);
            L+=l[i];
        }
        for (; j<r.size(); j++){
            for (k=1; k<r[j]-'0'; k++)
                ins(root,0,R+to_string(k),r.size()-j-1);
            R+=r[j];
        }
        ins(root,0,L,0),ins(root,0,R,0);
    }
    buildAC();
    for (i=0; i<=cnt; i++) update(i);

    int seq[maxv];
    memset(f,0x80,sizeof(f)), memset(pre,-1,sizeof(pre));
    f[0][root]=en[root][n];

    for (i=0; i<=cnt; i++) seq[i]=i;
    tzy p[maxv];
    bool updated[maxv];//保证字典序最小只需要用一个pair记录各节点答案的更新情况即可
    for (i=1; i<=n; i++)
    {
        memset(updated,0,sizeof(updated));
        for (k=0; k<=cnt; k++)
        {
            int u=seq[k];
            for (j=0; j<alphabet; j++)
            {
                int v=tr[u][j]; updated[v]=1;
                if (f[i-1][u]+en[v][n-i]>f[i][v])
                    f[i][v]=f[i-1][u]+en[v][n-i], pre[i][v]=u, alpha[i][v]=j, p[v].p=make_pair(k,j);
            }
        }

        for (k=0; k<=cnt; k++) p[k].pos=k;
        for (k=0; k<=cnt; k++)
            if (!updated[k]) p[k].p=make_pair(INT_MAX,INT_MAX);
        sort(p,p+cnt+1,cmp);
        for (k=0; k<=cnt; k++) seq[k]=p[k].pos;
    }

    int ans=-INT_MAX;
    string anss;
    for (k=0; k<=cnt; k++)
    {
        int u=seq[k];
        if (f[n][u]>ans)
            ans=f[n][u],anss=dfs(u,n);
    }
    cout<<ans<<endl<<anss;
	return 0;
}
