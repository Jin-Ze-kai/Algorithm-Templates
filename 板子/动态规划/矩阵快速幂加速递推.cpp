
//(min,+)
const int inf=1e18;
vector<vector<int>> operator * (const vector<vector<int>>& A,const vector<vector<int>>& B) {
	const int n=A.size();
	vector C(n,vector<int>(n,inf));
    for (int i=0;i<n;i++) {
        for (int k=0;k<n;k++) {
        	if (A[i][k] == inf) continue;
            for (int j=0;j<n;j++) {
                C[i][j]=min(C[i][j],A[i][k]+B[k][j]);
            }
        }
    }
    return C;
}

vector<vector<int>> Pow(vector<vector<int>> E,vector<vector<int>> A,int exp) {
	for(;exp;exp>>=1) {
		if (exp&1) E=E*A;
		A=A*A;
	}
	return E;
}


//(+,*)
int read(string& s) {
	int res=0;
	for(auto c : s) {
		res=(res*10+c-'0')%(p-1);
	}
	return res;
}
vector<vector<int>> operator * (const vector<vector<int>>& A,const vector<vector<int>>& B) {
    const int n=A.size();
    vector C(n,vector<int>(n,0));
    for (int i=0;i<n;i++) {
        for (int k=0;k<n;k++) {
            if (A[i][k] == 0) continue;
            for (int j=0;j<n;j++) {
                (C[i][j]+=A[i][k]*B[k][j])%=p;
            }
        }
    }
    return C;
}

vector<vector<int>> Pow(vector<vector<int>> E,vector<vector<int>> A,int exp) {
    for (;exp;exp>>=1) {
        if (exp&1) E=E*A;
        A=A*A;
    }
    return E;
}
