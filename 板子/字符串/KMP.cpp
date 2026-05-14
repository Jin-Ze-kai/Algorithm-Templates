
vector<int> Next(string s) {
	int m=s.size();
	vector<int> nxt(m+1);
	nxt[0]=-1;
	nxt[1]=0;
	int i=2,cur=0;
	while (i < m+1) {
		if (s[i-1] == s[cur]) nxt[i++]=++cur;
		else if (cur > 0) cur=nxt[cur];
		else nxt[i++]=0;
	}
	return nxt;
}

int KMP(string s1,string s2) {
	int n=s1.size();
	int m=s2.size();
	auto nxt=Next(s2);
	int x=0,y=0;
	while (x < n and y < m) {
		if (s1[x] == s2[y]) {
			x++;
			y++;
		}
		else if (y == 0) x++;
		else y=nxt[y];
	}
	
	return y;
}
