
// 矩阵A的大小为 m*(n+1)
// m方程个数,n未知数个数

// 加法:
const double eps=1e-9;
int gauss(vector<vector<double>>& A,int m,int n) {
    int row=0;
    for (int col=0;col<n;col++) {
        int r=row;
        for (int i=row+1;i<m;i++) {
            if (abs(A[i][col]) > abs(A[r][col])) r=i;
        }
        if (abs(A[r][col]) < eps) continue;
        if (r != row) swap(A[r],A[row]);

        for (int k=row+1;k<m;k++) {
            if (abs(A[k][col]) > eps) {
                double factor=A[k][col]/A[row][col];
                for (int j=col;j<=n;j++) {
                    A[k][j]-=factor*A[row][j];
                }
            }
        }
        row++;// 秩++
        if (row == m) break;// 后面几列都是自由变元
    }

    // 无解
    for (int i=row;i<m;i++) {
        if (abs(A[i][n]) > eps) return -1;
    }

    // 多解
    if (row < n) return n-row;// 返回自由变元个数

    // 唯一解
    for (int i=n-1;i>=0;i--) {
        for (int j=i+1;j<n;j++) {
            A[i][n]-=A[i][j]*A[j][n];
        }
        A[i][n]/=A[i][i];
    }
    return 0;
}

// 异或:
int gauss(vector<vector<int>>& A,int m,int n) {
    int row=0;
    for (int col=0;col<n;col++) {
        int r=row;
        while (r < m and A[r][col] == 0) r++;
        if (r == m) continue;// 这列是自由变元
        if (r != row) swap(A[r],A[row]);

        for (int k=row+1;k<m;k++) {
            if (A[k][col] == 1) {
                for (int j=col;j<=n;j++) {
                    A[k][j]^=A[row][j];
                }
            }
        }
        row++;// 秩++
        if (row == m) break;// 后面几列都是自由变元
    }
	
    // 无解
    for (int i=row;i<m;i++) {
        if (A[i][n] != 0) return -1;
    }

    // 多解
    if (row < n) return n-row;// 自由变元个数

    // 回代求解，唯一解
    for (int i=n-1;i>=0;i--) {
        for (int j=i+1;j<n;j++) {
            if (A[i][j]) A[i][n]^=A[j][n];
        }
    }
    return 0;
}
