
int randINT(int l, int r) {
    static mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<> distrib(l, r);
    return distrib(gen);
}

int randINT(int l, int r) {
    static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<> distrib(l, r);
    return distrib(gen);
}
