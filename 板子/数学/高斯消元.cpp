
//矩阵A的大小为n * (n + 1)
void gauss(vector<vector<double>>& A, int n) {
	for (int i=0;i<n;++i) {
		int r=i;
		for (int j=i+1;j<n;j++) {
			if (fabs(A[j][i]) > fabs(A[r][i])) r=j;
		}
		if (r != i) {
			for (int j=0;j<=n;j++) {
				swap(A[r][j],A[i][j]);
			}
		}
		for (int k=i+1;k<n;k++) {
			for (int j=n;j>=i;j--) {
				A[k][j]-=A[k][i]/A[i][i]*A[i][j];
			}
		}
				
	}
	for (int i=n-1;i>=0;i--) {
		for (int j=i+1;j<n;j++) {
			A[i][n]-=A[j][n]*A[i][j];
		}
		A[i][n]/=A[i][i];
	}
}
