
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
vector<vector<int>> operator * (const vector<vector<int>>& A,const vector<vector<int>>& B) {
    int n=A.size();
    int l=A[0].size();
    int m=B[0].size();
    vector C(n,vector<int>(m));
    for (int i=0;i<n;i++) {
        for (int k=0;k<l;k++) {
            if (A[i][k] == 0) continue;
            for (int j=0;j<m;j++) {
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
