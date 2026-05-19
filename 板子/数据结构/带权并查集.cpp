
struct DSU {
    vector<int> f,d,siz;
    // x=fx+d[x] 即fx->x
    int cnt,ok;

    DSU(int n) {init(n);}

    void init(int n) {
        f.resize(n);
        iota(f.begin(),f.end(),0);
        siz.assign(n,1);
        d.assign(n,0);
        cnt=n;
        ok=1;
    }

    int find(int x) {
    	if (x == f[x]) return x;
    	int r=find(f[x]);
    	//d[x]^=d[f[x]];
    	d[x]+=d[f[x]];
        return f[x]=r;
    }
	
	//fx->x->y->fy
    bool merge(int x,int y,int w) {
        int fx=find(x);
        int fy=find(y);
        if (fx == fy) {
        	//if ((d[x]^w) != d[y]) ok=0;
        	if (d[x]+w != d[y]) ok=0;
        	return 0;
        }
        siz[fy]+=siz[fx];
        f[fx]=fy;
        //d[fx]=d[y]^d[x]^w;
	    d[fx]=d[y]-d[x]-w;
        cnt--;
        return 1;
    }

    int esize(int x) {
        return siz[find(x)];
    }
};
