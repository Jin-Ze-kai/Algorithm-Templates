
void solve()
{
	int n,m;
	cin>>n>>m;
	vector<array<int,2>> gra;
	for(int i=1;i<=n;i++) {
		int val,cost,num;
		cin>>val>>cost>>num;
		for(int i=0;num-(1<<i)>=0;i++) {
			int k=(1ll<<i);
			gra.push_back({cost*k,val*k});
			num-=k;
		}
		if (num != 0) gra.push_back({cost*num,val*num});
	}
	
	n=gra.size();
	vector<int> dp(m+1);
	for(int i=0;i<n;i++) {
		for(int j=m;j>=gra[i][0];j--) {
			dp[j]=max(dp[j],dp[j-gra[i][0]]+gra[i][1]);
		}
	}
	cout<<dp[m];
}
