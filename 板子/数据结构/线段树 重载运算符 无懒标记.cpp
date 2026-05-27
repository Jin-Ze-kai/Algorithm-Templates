
const int inf=1e18;
struct Info {
	int sum,Max,Min,Gcd,Xor;
	Info() : sum(0),Max(-inf),Min(inf),Gcd(0),Xor(0) {};
    Info(int val) : sum(val),Max(val),Min(val),Gcd(val),Xor(val) {};
    Info operator+(const Info &other) const {
    	Info res;
    	res.sum=sum+other.sum;
    	res.Min=min(Min,other.Min);
    	res.Max=max(Max,other.Max);
    	res.Gcd=gcd(Gcd,other.Gcd);
    	res.Xor=(Xor^other.Xor);
    	return res;
    }
};

struct SegTree {
	int n;
	vector<Info> tree;
	SegTree(int _) {
		n=_;
		tree.resize(n*4);
	}
	
	void Set(int p,int l,int r,int id,int val) {
		if (l == r) {tree[p]=Info(val);return;}
		int m=l+r>>1;
		if (id <= m) Set(2*p,l,m,id,val);
		else Set(2*p+1,m+1,r,id,val);
		tree[p]=tree[p*2]+tree[p*2+1];
	}
	
	Info query(int p,int l,int r,int ql,int qr) {
		if (ql > r or qr < l) return Info();
		if (ql <= l and r <= qr) return tree[p];
		int m=l+r>>1;
		return query(2*p,l,m,ql,qr)+query(2*p+1,m+1,r,ql,qr);
	}
	
	int kth(int p,int l,int r,int k) {
    	if (l == r) return l;
    	int m=l+r>>1;
    	int cnt=tree[2*p].sum;
		if (k <= cnt) return kth(2*p,l,m,k);
		else return kth(2*p+1,m+1,r,k-cnt);
	}
};
