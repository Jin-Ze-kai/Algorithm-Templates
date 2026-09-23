
int sign(int x) {
    if (x == 0) return 0;
    return x < 0 ? -1 : 1;
}

// ========================================================================

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    Point operator+(const Point& b) const { return Point(x + b.x, y + b.y); }
    Point operator-(const Point& b) const { return Point(x - b.x, y - b.y); }
    Point operator*(int k) const { return Point(x * k, y * k); }
    
    bool operator==(const Point& b) const { 
        return x == b.x && y == b.y; 
    }
    
    // 按 x 升序，x 相同按 y 升序 (用于凸包和扫描线)
    bool operator<(const Point& b) const {
        if (x != b.x) return x < b.x; 
        return y < b.y;   
    }
};
using Vector = Point;

// ========================================================================

// 点积 (内积)
int dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

// 叉积 (外积)：表示平行四边形的有向面积
int cross(Vector a, Vector b) {
    return a.x * b.y - b.x * a.y;
}

// 极角排序 (完全依赖叉积和象限，绝对无浮点误差)
// 排序后起点位于 x 轴正半轴，逆时针扫一圈
bool p_cmp(const Vector& a, const Vector& b) {
    int ha = (a.y > 0 || (a.y == 0 && a.x > 0));
    int hb = (b.y > 0 || (b.y == 0 && b.x > 0));
    if (ha != hb) return ha < hb; // 位于上半平面的排在前面
    return cross(a, b) > 0;       // 同半平面内，靠左(逆时针)的排在前面
}

// 获取向量模长的平方 (替代原始的距离比较，完全避免开方和浮点数)
int get_length_sq(Vector a) {
    return dot(a, a);
}

// 两点间的距离平方
int dist_sq(Point a, Point b) {
    return get_length_sq(a - b);
}

// ========================================================================

// 判断点 p 是否在线段 ab 上
bool on_segment(Point p, Point a, Point b) {
    // 叉积为0说明共线，点积<=0说明在两端点之间或端点上
    return cross(p - a, p - b) == 0 && dot(p - a, p - b) <= 0;
}

// 判断两线段 a1a2 和 b1b2 是否相交（包含严格相交或端点相交）
bool segment_intersection(Point a1, Point a2, Point b1, Point b2) {
    // 步骤一：快速排斥实验 (Bounding Box 检查)
    if (min(a1.x, a2.x) > max(b1.x, b2.x) || max(a1.x, a2.x) < min(b1.x, b2.x) ||
        min(a1.y, a2.y) > max(b1.y, b2.y) || max(a1.y, a2.y) < min(b1.y, b2.y)) {
        return false;
    }
    
    // 步骤二：跨立实验
    int c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);
    int c3 = cross(b2 - b1, a1 - b1), c4 = cross(b2 - b1, a2 - b1);
    return sign(c1) * sign(c2) <= 0 && sign(c3) * sign(c4) <= 0;
}

// 求线段 ab 上的整点(格点)数量
// 依赖 <numeric> 库中的 std::gcd (C++17) 或自己实现 gcd
int lattice_points_on_segment(Point a, Point b) {
    return std::gcd(abs(a.x - b.x), abs(a.y - b.y)) + 1;
}

// ========================================================================

// 求多边形有向面积的两倍
// 多边形顶点的坐标全是整数时，其面积的两倍必定是整数。
int polygon_area_2(const vector<Point>& p) {
    int res = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        res += cross(p[i], p[(i + 1) % n]);
    }
    return abs(res); 
}

// 判断点 p 与多边形 poly 的位置关系 (射线法/环绕数法)
// 返回值：2 表示点在多边形边界上，1 表示在多边形内部，0 表示在外部
int is_point_in_polygon(Point p, const vector<Point>& poly) {
    int n = poly.size();
    int wn = 0; 
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        
        if (on_segment(p, a, b)) return 2; 
        
        int k = cross(b - a, p - a);
        int d1 = a.y - p.y;
        int d2 = b.y - p.y;
        
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;      
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;      
    }
    return wn != 0 ? 1 : 0;
}


// 皮克定理 (Pick's Theorem): 2S = 2I + B - 2
// S 为面积，I 为内部格点数，B 为边界格点数
// 此函数用于计算给定整型多边形 内部 和 边界 上一共有多少个整数格点
void picks_theorem(const vector<Point>& p, int& boundary_pts, int& internal_pts) {
    int area2 = polygon_area_2(p);
    boundary_pts = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        // 每条边上的格点数等于端点间 gcd，由于端点会被重复计算，这里每条边算 gcd 即可
        Point a = p[i], b = p[(i + 1) % n];
        boundary_pts += std::gcd(abs(a.x - b.x), abs(a.y - b.y));
    }
    // 根据皮克定理公式推导内部格点数 I = (2S - B + 2) / 2
    internal_pts = (area2 - boundary_pts + 2) / 2;
}
