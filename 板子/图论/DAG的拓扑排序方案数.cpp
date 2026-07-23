
	vector<int> pre(n);
	for(auto e : edge) {
		auto [u,v]=e;
		pre[v]|=1<<u;
	}
	vector<int> dp(1<<n);
	dp[0]=1;
	for(int i=0;i<(1<<n);i++) {
		if (dp[i] == 0) continue;
		for(int u=0;u<n;u++) {
			if ((i&(1<<u)) == 0 and (pre[u]&i) == pre[u]) {
				dp[i|(1<<u)]+=dp[i];
			}
		}
	}
