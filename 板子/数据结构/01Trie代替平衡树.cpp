
const int N=2e5*32;
int tree[N][2];
int pass[N];
int len=1;
const int p=1e7;

void insert(int x) {
	x+=p;
    int cur=0;
    pass[cur]++;
    for(int i=30;i>=0;i--) {
        int b=(x>>i)&1;
        if (tree[cur][b] == 0) {
            tree[len][0]=tree[len][1]=0;
            pass[len]=0;
            tree[cur][b]=len++;
        }
        cur=tree[cur][b];
        pass[cur]++;
    }
}

void erase(int x) {
	x+=p;
    int cur=0;
    pass[cur]--;
    for (int i=30;i>=0;i--) {
		int b=(x>>i)&1;
		cur=tree[cur][b];
    	pass[cur]--;
    }
}

int get_rank(int x) {
	x+=p;
	int cur=0;
	int rank=0;
	for(int i=30;i>=0;i--) {
		int b=(x>>i)&1;
		if (b) {
			int l=tree[cur][0];
			if (l) rank+=pass[l];
		}
		cur=tree[cur][b];
		if (cur == 0 or pass[cur] == 0) break;
	}
	return rank+1;
}

int get_val(int k) {
	int cur=0;
	int ans=0;
	for(int i=30;i>=0;i--) {
		int l=tree[cur][0];
		if (l and pass[l] >= k) cur=l;
		else {
			if (l) k-=pass[l];
			ans|=1<<i;
			cur=tree[cur][1];
		}
	}
	return ans-p;
}
