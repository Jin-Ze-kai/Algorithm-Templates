
// 求<=x的所有数字的数位和之和
int work(int x) {
	if (x == 0) return 0;
	vector<int> a;
	while (x) {
		a.push_back(x%10);
		x/=10;
	}
	
	vector dp(20,vector<int>(200,-1));
	auto dfs=[&](auto&& self,int pos,int sum,bool limit) -> int {
		if (pos == -1) return sum;
		if (limit == 0 and dp[pos][sum] != -1) return dp[pos][sum];
		
		int res=0;
		int up=limit ? a[pos] : 9;
		for(int i=0;i<=up;i++) {
			(res+=self(self,pos-1,sum+i,limit and (i == up)))%=p;
		}
		if (limit == 0) dp[pos][sum]=res;
		return res;
	};
	return dfs(dfs,a.size()-1,0,1);
}
