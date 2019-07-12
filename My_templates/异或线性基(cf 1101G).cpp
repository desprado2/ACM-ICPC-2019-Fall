int base[32],top_digit[32];
int top(int x){
    for (int i=INT_MAX; i; i>>=1)
        if (i&x) return i;
}
void work(int* a,int n){
    for (i=1; i<=n; i++)
    {
        int t=a[i];
        for (j=1; j<=cnt; j++)
            if (t&top_digit[j]) t^=base[j];
        if (t!=0) base[++cnt]=t,top_digit[cnt]=top(t);
        for (j=1; j<cnt; j++)
            if (t&top_digit[j]) base[j]^=t;
    }
}
