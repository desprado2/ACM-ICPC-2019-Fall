
int my[N],mx[N];
bool visy[N];
bool hungary(int u)
{
    for (int v:e[u])
        if (!visy[v]){
            visy[v]=1;
            if (my[v]==-1 || hungary(my[v])){
                mx[u]=v, my[v]=u;
                return 1;
            }
        }
    return 0;
}
void work(){
    memset(mx,0,sizeof mx), mem(my,-1,sizeof my);
    for (int i=1; i<=cntS; i++)
        if (!mx[i]) mem(visy,0), hungary(i);
}
