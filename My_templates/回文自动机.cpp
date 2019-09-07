struct PAM{
	int next[N][26], fail[N], cnt[N], num[N], len[N];
	//fail:失配后跳到fail指向的节点
	//cnt:统计该节点表示的字符串在原串中出现了几次
	//num:统计这个节点可以表示多少个本质不同的回文子串(其实就是fail树的深度)
	//len:这个串的长度
	int last, n, p, s[N];
	int newnode(int l){
		memset(next[p], 0, sizeof next[p]);
		num[p] = cnt[p] = 0;
		len[p] = l;
		return p++;
	}
	void init(){
		p = 0;
		newnode(0), newnode(-1);
		last = 0;
		n = 0, s[n] = -1;
		fail[0] = 1;
	}
	int get_fail(int x){
		while (s[n - len[x] - 1] != s[n])
			x = fail[x];
		return x;
	}

	void add(int c){
		c -= 'a';
		s[++n] = c;
		int cur = get_fail(last);
		if (!next[cur][c]){
			int now = newnode(len[cur] + 2);
			fail[now] = next[get_fail(fail[cur])][c];
			next[cur][c] = now;
			num[now] = num[fail[now]] + 1;
		}
		last = next[cur][c];
		cnt[last]++;
	}
	void count(){//注意在把所有字符扔进PAM以后要更新一下cnt数组
		for (int i=p-1; i>=0; i--)
			cnt[fail[i]] += cnt[i];
	}
};
