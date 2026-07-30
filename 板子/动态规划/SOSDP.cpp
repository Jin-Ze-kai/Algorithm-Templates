
//子集和
vector<int> dp(1<<20);
for(int mask=0;mask<(1<<20);mask++) dp[mask]=a[mask];
for(int i=0;i<20;i++) {
	for(int mask=0;mask<(1<<20);mask++) {
		if (mask&(1<<i)) {
			dp[mask]+=dp[mask^(1<<i)];
		}
	}
}

//超集和
vector<int> dp(1<<20);
for(int mask=0;mask<(1<<20);mask++) dp[mask]=a[mask];
for(int i=0;i<20;i++) {
	for(int mask=0;mask<(1<<20);mask++) {
		if (!(mask&(1<<i))) {
			dp[mask]+=dp[mask|(1<<i)];
		}
	}
}
