
const int inf=1e18;
struct Info {
	int sum,Max,Min;
	Info() : sum(0),Max(-inf),Min(inf) {};
    Info(int val) : sum(val),Max(val),Min(val) {};
    Info operator+(const Info &other) const {
    	Info res;
    	res.sum=sum+other.sum;
    	res.Min=min(Min,other.Min);
    	res.Max=max(Max,other.Max);
    	return res;
    }
};

struct SegTree {
	int n;
	vector<Info> tree;
    vector<int> ladd,lset;
    const int f=1e18+7; 

	SegTree(int _) {
		n=_;
		tree.resize(n*4);
        ladd.resize(n*4,0);
        lset.resize(n*4,f);
	}
	
    void applyset(int p,int l,int r,int val) {
        tree[p].sum=(r-l+1)*val;
        tree[p].Min=val;
        tree[p].Max=val;
        lset[p]=val;
        ladd[p]=0;
    }

    void applyadd(int p,int l,int r,int val) {
        tree[p].sum+=(r-l+1)*val;
        tree[p].Min+=val;
        tree[p].Max+=val;
        if (lset[p] != f) {
            lset[p]+=val;
        } else {
            ladd[p]+=val;
        }
    }

    void pushdown(int p,int l,int r) {
        int m=l+r>>1;
        if (lset[p] != f) {
            applyset(p*2,l,m,lset[p]);
            applyset(p*2+1,m+1,r,lset[p]);
            lset[p]=f;
        }
        if (ladd[p] != 0) {
            applyadd(p*2,l,m,ladd[p]);
            applyadd(p*2+1,m+1,r,ladd[p]);
            ladd[p]=0;
        }
    }
	
    void Set(int p,int l,int r,int ql,int qr,int val) {
        if (ql > r or qr < l) return;
        if (ql <= l and r <= qr) {
            applyset(p,l,r,val);
            return;
        }
        pushdown(p,l,r);
        int m=l+r>>1;
        Set(p*2,l,m,ql,qr,val);
        Set(p*2+1,m+1,r,ql,qr,val);
        tree[p]=tree[p*2]+tree[p*2+1];
    }

    void Add(int p,int l,int r,int ql,int qr,int val) {
        if (ql > r or qr < l) return;
        if (ql <= l and r <= qr) {
            applyadd(p,l,r,val);
            return;
        }
        pushdown(p,l,r);
        int m=l+r>>1;
        Add(p*2,l,m,ql,qr,val);
        Add(p*2+1,m+1,r,ql,qr,val);
        tree[p]=tree[p*2]+tree[p*2+1];
    }

	Info query(int p,int l,int r,int ql,int qr) {
		if (ql > r or qr < l) return Info();
		if (ql <= l and r <= qr) return tree[p];
        pushdown(p,l,r);
		int m=l+r>>1;
		return query(2*p,l,m,ql,qr)+query(2*p+1,m+1,r,ql,qr);
	}
};
