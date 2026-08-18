
//找到同区块前提下的最长段，同区块指完全相同的某一组区间覆盖的区块
//暴力,n较小时
mt19937_64 rng {chrono::steady_clock::now().time_since_epoch().count()};
void solve()
{
	int n,m;
	cin>>n>>m;
	vector<u64> f(n);
	for(int i=0;i<m;i++) {
		int n1,n2;
		cin>>n1>>n2;
		n1--,n2--;
		u64 x=rng();
		f[n1]^=x;
		f[n2]^=x;
	}
	for(int i=1;i<n;i++) f[i]^=f[i-1];
	
	map<u64,int> cnt;
	for(int i=0;i<n;i++) cnt[f[i]]++;//同区块的线段长度
	
	int ans=0;
	for(auto [e1,e2] : cnt) ans=max(ans,e2);
		
	cout<<n-ans<<"\n";
}

//n较大时，离散化
	int n,m;
	cin>>n>>m;
	map<int,u64> f;
	f[n]=0;
	for(int i=0;i<m;i++) {
		int n1,n2;
		cin>>n1>>n2;
		u64 x=rng();
		f[n1]^=x;
		f[n2]^=x;
	}
	
	map<u64,int> cnt;
	int p=-1;
	u64 val=0;
	for(auto& [id,x] : f) {
		cnt[val]+=id-p-1;
		val^=x;
		p=id;
	}
	