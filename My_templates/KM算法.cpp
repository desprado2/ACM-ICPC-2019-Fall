int c[eff*maxF];
vector<int> id[1<<maxF];//id是边表
//本题中,边的代价只与右部有关,存储在数组c中,如果与左部也有关,那么可以也存进一个vector里
vector<int> X,Y;
bool visx[maxN], visy[maxM];
int matchx[maxN],topmarkx[maxN],matchy[maxM],topmarky[maxM], minz;
bool aug(int u)//KM增广,这里求的是最小化匹配
{
    if (!visx[u]) visx[u]=1, X.pb(u);
    for (int v:id[u]){
        if (visy[v]) continue;
        ll t=c[v]-(topmarkx[u]+topmarky[v]);
        if (t==0)
        {
            visy[v]=1, Y.pb(v);
            if (!matchy[v] || aug(matchy[v]))
            {
                matchx[u]=v,matchy[v]=u;
                return 1;
            }
        }
        else minz=min(minz,t);//t>0
    }
    return 0;
}
int KM()//这个模板可以解决点编号是离散以及多次求匹配的情况
{
    int i;
    for (i=0; i<n; i++)
    {
        if (id[i].empty()) return;
        topmarkx[i]=c[id[i][0]];
    }//topmarky默认是0
    for (i=0; i<n; i++)
        while(1){
            minz=LLONG_MAX;
            for (int x:X) visx[x]=0;
            for (int y:Y) visy[y]=0;
            X.clear(), Y.clear();
		
            if (aug(i)) break;//一次增广成功
            if (minz==LLONG_MAX) return;//匹配失败
            for (int x:X) topmarkx[x]+=minz;
            for (int y:Y) topmarky[y]-=minz;
        }

    int ret=0;
    for (i=0; i<dep; i++) tmp+=c[matchx[i]];
    return ret;
}
