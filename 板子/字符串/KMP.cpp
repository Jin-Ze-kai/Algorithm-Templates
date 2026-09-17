
vector<int> get(string &s) {
    int m=s.size();
    vector<int> pi(m);
    for (int i=1;i<m;i++) {
        int j=pi[i-1];
        while (j > 0 and s[i] != s[j]) j=pi[j-1];
        if (s[i] == s[j]) j++;
        pi[i]=j;
    }
    return pi;
}

vector<int> kmp(string &s,string &p) {
    int n=s.size(),m=p.size();
    vector<int> pi=get(p),pos;
    int j=0;
    for (int i=0;i<n;i++) {
        while (j > 0 and s[i] != p[j]) j=pi[j-1];
        if (s[i] == p[j]) j++;
        if (j == m) {
            pos.push_back(i-m+1);
            j=pi[m-1];
        }
    }
    return pos;
}
