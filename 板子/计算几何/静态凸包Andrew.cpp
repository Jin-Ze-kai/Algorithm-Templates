
// 若用于斜率优化，a 取 {y轴截距, 斜率} 存入 Point 的 {x, y}
vector<Point> andrew(vector<Point>& a) {
    sort(a.begin(), a.end());
    vector<Point> l, h;
    for(const auto& p : a) {
        // sign <= 0 表示 p 在前进方向的右侧或共线，维护下凸壳（左转）
        while (l.size() > 1 && sign(area(l[l.size() - 2], l.back(), p)) <= 0) {
            l.pop_back();
        }
        // sign >= 0 表示 p 在前进方向的左侧或共线，维护上凸壳（右转）
        while (h.size() > 1 && sign(area(h[h.size() - 2], h.back(), p)) >= 0) {
            h.pop_back();
        }
        l.push_back(p);
        h.push_back(p);
    }
    
    // reverse(h.begin(), h.end());
    // h.insert(h.end(), l.begin() + 1, l.end() - 1); //完整凸包
    return h;
}
