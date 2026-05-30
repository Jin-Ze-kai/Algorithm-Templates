
const int N=1e5*32;
int tree[N][2];
int pass[N];
int len=1;

void insert(int x) {
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

int query(int x) {
    int cur=0;
    int ans=0;
    for(int i=30;i>=0;i--) {
        int b=(x>>i)&1;
        if (tree[cur][b^1] != 0) {
            ans|=(1<<i);
            cur=tree[cur][b^1];
        }
        else cur=tree[cur][b];
    }
    return ans;
}
