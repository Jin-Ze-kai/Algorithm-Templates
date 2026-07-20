
struct DSU {
    vector<int> f,siz;
    int cnt;

    DSU(int n) {init(n);}

    void init(int n) {
        f.resize(n);
        iota(f.begin(),f.end(),0);
        siz.assign(n,1);
        cnt=n;
    }

    int find(int x) {
    	if (x == f[x]) return x;
    	int r=find(f[x]);
        return f[x]=r;
    }

    bool merge(int x,int y) {
        int fx=find(x);
        int fy=find(y);
        if (fx == fy) return 0;
        siz[fx]+=siz[fy];
        f[fy]=fx;
        cnt--;
        return 1;
    }
};
