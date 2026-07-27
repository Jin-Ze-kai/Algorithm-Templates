
const int p=1e9+7;
const int N=1e6;
int jc[N+1];
int inv[N+1];

int Pow(int base,int exp) {
	int res=1;
	base%=p;
	for(;exp;exp>>=1) {
		if (exp&1) res*=base,res%=p;
		base*=base,base%=p;
	}
	return res;
}

int Inv(int num) {
	return Pow(num,p-2);
}

int C(int m,int n)
{
	if (m < n) return 0;
	return jc[m]*inv[m-n]%p*inv[n]%p;
}

int Lucas(int m,int n)
{
	if (m == 0) return 1;
	return C(m%p,n%p)*Lucas(m/p,n/p)%p;
}

	jc[0]=1;
	for(int i=1;i<=N;i++) jc[i]=jc[i-1]*i%p;
	
	//连续数字逆元的线性递推
	inv[1]=1;
	for(int i=2;i<=N;i++) inv[i]=p-inv[p%i]*(p/i)%p;

	//连续阶乘逆元的线性递推
	inv[N]=Pow(jc[N],p-2);
	for(int i=N-1;i>=0;i--) inv[i]=(i+1)*inv[i+1]%p;
