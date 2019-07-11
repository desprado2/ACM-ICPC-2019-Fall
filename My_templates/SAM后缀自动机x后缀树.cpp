#define root 0
struct SAM{
    int e[N*4][26];
    int lst,cur,link[N*4],len[N*4],cnt;
    char lstc[N*4];//lstc仅仅用于后缀树，表示这个后缀树节点的开头字母(也就是反序自动机上的结尾)，用于统计后缀树上的一些信息
    bool isleaf[N*4];

    SAM(){mem(isleaf,0), mem(len,0), cnt=0;}
    void clear(){mem(isleaf,0), mem(len,0), cnt=0; mem(e,0);}
    void build(const string& S){
        len[root]=0, link[root]=-1, cur=root;
        for (char c:S){
            c-='a';
            lst=cur, cur=++cnt;
            len[cur]=len[lst]+1, isleaf[cur]=1, lstc[cur]=c+'a';

            int u=lst, v;
            while(u!=-1 && !e[u][c])
                e[u][c]=cur, u=link[u];
            if (u==-1) {link[cur]=root; continue;}

            v=e[u][c];
            if (len[v]==len[u]+1) {link[cur]=v; continue;}

            int clone=++cnt;
            len[clone]=len[u]+1, link[clone]=link[v], memcpy(e[clone],e[v],sizeof(e[v])), lstc[clone]=lstc[v];
            link[v]=link[cur]=clone;
            for (; u!=-1 && e[u][c]==v; u=link[u])
                e[u][c]=clone;
        }
    }
};
