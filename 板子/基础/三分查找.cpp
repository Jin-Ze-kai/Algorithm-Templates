
	//查找区间最大值,要求f是严格单峰
	auto f=[&](int x) {
		
	};

	int lo,hi,res; 
    while (hi-lo > 3) {
        int m1=lo+(hi-lo)/3;
        int m2=hi-(hi-lo)/3;
        if (f(m1) < f(m2)) lo=m1+1;
        else hi=m2-1;
    }
    res=f(lo);
    for (int i=lo+1;i<=hi;i++){
        res=max(res,f(i));
    }

	//直线上三分查找点
	auto calc=[&](double t) -> double {
		double x,y;
		if (a == 0) {
			y=-1.0*c/b;
			x=t;
		}
		else if (b == 0) {
			x=-1.0*c/a;
			y=t;
		}
		else {
			x=t;
			y=(-c-a*t)/b;
		}
		double res=0;
		for(auto [x1,y1] : vec) res=max(res,sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1)));
		return res;
	};
	
	double lo=-1e5,hi=1e5,res=-1; 
    while (hi-lo > eps) {
        double m1=lo+(hi-lo)/3;
        double m2=hi-(hi-lo)/3;
        if (calc(m1) < calc(m2)) hi=m2;
        else lo=m1;
    }
    