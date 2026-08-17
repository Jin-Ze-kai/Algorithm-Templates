
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
                (C[i][j]+=A[i][k]*B[k][j]%p)%=p;
            }
        }
    }
    return C;
}

vector<vector<int>> Pow(vector<vector<int>> A,int exp) {
	int n=A.size();
	vector E(n,vector<int>(n));
	for(int i=0;i<n;i++) E[i][i]=1;
	for(;exp;exp>>=1) {
		if (exp&1) E=E*A;
		A=A*A;
	}
	return E;
}

vector<vector<int>> Pow10(vector<vector<int>> A,string exp) {
    int n=A.size();
    vector<vector<int>> E(n,vector<int>(n,0));
    for (int i=0;i<n;i++) E[i][i]=1;
    vector<vector<vector<int>>> tmp(10);
    tmp[0]=E;
    for (int i=1;i<=9;i++) tmp[i]=tmp[i-1]*A;
    for (char c : exp) {
    	E=Pow(E,10)*tmp[c-'0'];
    }
    return E;
}
