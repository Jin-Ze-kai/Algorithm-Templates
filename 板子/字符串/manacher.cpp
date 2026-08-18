
vector<int> manacher(string s) {
    string t="#";
    for (auto c : s) {
        t+=c;
        t+='#';
    }
    int n=t.size();
    vector<int> r(n);
    for (int i=0,j=0;i<n;i++) {
        if (2*j-i >= 0 and i < j+r[j]) r[i]=min(r[2*j-i],j+r[j]-i);
        while (i-r[i] >= 0 and i+r[i] < n and t[i-r[i]] == t[i+r[i]]) r[i]+=1;
        if (i+r[i] > j+r[j]) j=i;
    }
    return r;
}
