
string trans(string s,int n,int m) {
    int val=stoll(s,nullptr,n);
    if (val == 0) return "0";
    string d="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string res;
    while (val > 0) {
        res+=d[val%m];
        val/=m;
    }
    reverse(res.begin(), res.end());
    return res;
}
