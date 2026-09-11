
struct Node {
    int a,b,c;
    int cnt;
    int res;
};

struct BIT {
	int n;
	vector<int> c;
	BIT(int n) : n(n),c(n+1,0) {}

	void add(int x,int y) {
		for (;x<=n;x+=x&-x) c[x]+=y;
	}

	int query(int x) {
		int res=0;
		for (;x;x-=x&-x) res+=c[x];
		return res;
	}
};

bool cmp1(Node& x,Node& y) {
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}

bool cmp2(Node& x,Node& y) {
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}

vector<Node> arr;
void cdq(int l,int r,BIT& bit) {
    if (l == r) return;
    int mid=l+r>>1;
    cdq(l,mid,bit);
    cdq(mid+1,r,bit);
    sort(arr.begin()+l,arr.begin()+mid+1,cmp2);
    sort(arr.begin()+mid+1,arr.begin()+r+1,cmp2);
    int j=l;
    for (int i=mid+1;i<=r;i++) {
        while (j<=mid and arr[j].b<=arr[i].b) {
            bit.add(arr[j].c,arr[j].cnt);
            j++;
        }
        arr[i].res+=bit.query(arr[i].c);
    }
    for (int i=l;i<j;i++) {
        bit.add(arr[i].c,-arr[i].cnt);
    }
}
