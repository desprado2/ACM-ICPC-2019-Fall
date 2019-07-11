int Log2[N],st[N][maxlog];//ST表
//log2(1e5)=16.6, log2(1e6)=19.9
void init(){
    for (i=1,k=0; i<=n; i<<=1,k++)
        for (j=i; j<i<<1 && j<=n; j++)
            Log2[j]=k;
    for (i=1; i<=n; i++) st[i][0]=rec[i];
    for (j=1; j<=Log2[n]; j++)
        for (i=1; i<=n; i++)
            if (i+(1<<j-1)<=n) st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
            else st[i][j]=st[i][j-1];
}
int Q(int l,int r){
    int len=r-l+1;
    return max(st[l][Log2[len]] , st[r-(1<<Log2[len])+1][Log2[len]]);
}
