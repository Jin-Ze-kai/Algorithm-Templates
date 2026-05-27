
struct Info {
    int sum=0;
    int Max=-2e18;
};

struct SegTree {
    int n;
    vector<Info> tree;
	
    SegTree(int _) {
        n=_;
        tree.resize(n*4);
    }
	
    void push_up(int p) {
        tree[p].sum=tree[p*2].sum+tree[p*2+1].sum;
        tree[p].Max=max(tree[p*2].Max,tree[p*2+1].Max);
    }
	
    void build(int p,int l,int r,vector<int>& a) {
        if (l == r) {
            tree[p].sum=tree[p].Max=a[l];
            return;
        }
        int m=l+r>>1;
        build(p*2,l,m,a);
        build(p*2+1,m+1,r,a);
    	push_up(p);
    }

    void update(int p,int l,int r,int id,int val) {
        if (l == r) {
            tree[p].sum=tree[p].Max=val;
            return;
        }
        int m=l+r>>1;
        if (id <= m) update(p*2,l,m,id,val);
        else update(p*2+1,m+1,r,id,val);
        push_up(p);
    }

    Info query(int p,int l,int r,int ql,int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int m=l+r>>1;
        if (qr <= m) return query(p*2,l,m,ql,qr);
        if (ql > m) return query(p*2+1,m+1,r,ql,qr);
        
        Info res;
        Info resl=query(p*2,l,m,ql,qr);
        Info resr=query(p*2+1,m+1,r,ql,qr);
        res.sum=resl.sum+resr.sum;
        res.Max=max(resl.Max,resr.Max);
        return res;
    }
};
