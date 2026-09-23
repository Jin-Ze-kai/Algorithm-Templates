
const double eps = 1e-9;
const double PI = acosl(-1.0);

// 安全的反余弦函数，防止浮点误差导致超出 [-1, 1] 范围触发 NaN
double Acos(double x) {
    if (x < -1) return PI;
    if (x > 1) return 0;
    return acosl(x);
}

// 符号函数：处理浮点数精度问题
// 返回值：-1(负数)，0(零)，1(正数)
int sign(double x) {
    if (fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

// 比较函数：比较两个浮点数大小
// 返回值：-1(x < y)，0(x == y)，1(x > y)
int cmp(double x, double y) {
    if (fabs(x - y) < eps) return 0;
    return x < y ? -1 : 1;
}

// ========================================================================

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    Point operator+(const Point& b) const { return Point(x + b.x, y + b.y); }
    Point operator-(const Point& b) const { return Point(x - b.x, y - b.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    Point operator/(double k) const { return Point(x / k, y / k); }
    
    bool operator==(const Point& b) const { 
        return cmp(x, b.x) == 0 && cmp(y, b.y) == 0; 
    }
    
    // 按 x 坐标升序排列，x 相同则按 y 坐标升序排列
    bool operator<(const Point& b) const {
        int c = cmp(x, b.x);
        if (c != 0) return c == -1; 
        return cmp(y, b.y) == -1;   
    }
};
typedef Point Vector;

struct Circle {
    Point c;
    double r;
    Circle(Point c = Point(0, 0), double r = 0) : c(c), r(r) {}
    
    // 通过圆心角求圆上坐标 (逆时针方向，a 为弧度)
    Point point(double a) const {
        return Point(c.x + cos(a) * r, c.y + sin(a) * r);
    }
};

// ========================================================================

// 点积 (内积)：a·b = |a||b|cosθ
double dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

// 叉积 (外积)：a×b = |a||b|sinθ 
// 几何意义：由 a 和 b 构成的平行四边形的有向面积 (a在底，b在顶)
double cross(Vector a, Vector b) {
    return a.x * b.y - b.x * a.y;
}

// 求向量 a 的逆时针 90 度法向量
Vector normal(Vector a) { 
    return Vector(-a.y, a.x);
}

// 求向量的极角，范围 [-PI, PI]
double p_angle(Vector a) {
    return atan2(a.y, a.x);
}

// 极角排序的比较函数 (以 x 负半轴为起点，逆时针 0 到 360 度排序)
bool p_cmp(const Vector& a, const Vector& b) {
    // 修复了 || 和 && 优先级可能导致的警告
    int ha = (a.y > 0 || (a.y == 0 && a.x > 0));
    int hb = (b.y > 0 || (b.y == 0 && b.x > 0));
    if (ha != hb) return ha < hb;
    return sign(cross(a, b)) > 0;
}

// 获取向量的模长
double get_length(Vector a) {
    return hypot(a.x, a.y); 
}

// 将向量单位化 (长度变为 1)
Vector unit(Vector a) {
    double l = get_length(a);
    if (sign(l) == 0) return a; // 防止除以 0 的情况
    return a / l;
}

// 计算两个非零向量的夹角
// 返回值：弧度制，无方向，范围 [0, PI]
double get_angle_robust(Vector a, Vector b) {
    return fabs(atan2(cross(a, b), dot(a, b))); 
}

// 向量 a 绕原点逆时针旋转 angle 角度 (弧度制)
Vector rotate(Vector a, double angle) {
    double c = cos(angle), s = sin(angle);
    return Vector(a.x * c - a.y * s, a.x * s + a.y * c);
}

// 计算点 a, b, c 构成的平行四边形有向面积 (以 a 为公共顶点)
double area(Point a, Point b, Point c) {
    return cross(b - a, c - a);
}

// ========================================================================

// 判断两直线相交并求交点
// 直线表示形式：起点 + 向量*t (P = p + v*t 和 Q = q + w*t)
// 注意：调用前需保证两直线不平行 (sign(cross(v, w)) != 0)
Point get_line_intersection(Point p, Vector v, Point q, Vector w) {
    assert(sign(cross(v, w)) != 0); // 确保直线不平行或共线
    Vector u = p - q;
    double t = cross(w, u) / cross(v, w);
    return p + v * t;
}

// 求点 p 到直线 ab 的垂线段长度 (距离)
double distance_to_line(Point p, Point a, Point b) {
    Vector v1 = b - a, v2 = p - a; 
    return fabs(cross(v1, v2) / get_length(v1)); 
}

// 求点 p 到线段 ab 的最短距离
double distance_to_segment(Point p, Point a, Point b) {
    if (a == b) return get_length(p - a); // 线段退化为点
    Vector v1 = b - a, v2 = p - a, v3 = p - b;
    // 判断 p 在线段所在直线的投影位置
    if (sign(dot(v1, v2)) < 0) return get_length(v2);   // 投影在端点 a 外侧
    if (sign(dot(v1, v3)) > 0) return get_length(v3);   // 投影在端点 b 外侧
    return distance_to_line(p, a, b);                   // 投影在线段 ab 内部
}

// 求点 p 在直线 ab 上的投影点坐标
Point get_line_projection(Point p, Point a, Point b) {
    Vector v = b - a;
    // 利用点积求出投影长度的比例
    return a + v * (dot(v, p - a) / dot(v, v));
}

// 求点 p 关于直线 ab 的对称点坐标
Point get_line_reflection(Point p, Point a, Point b) {
    Point proj = get_line_projection(p, a, b);
    return p + (proj - p) * 2.0;
}

// 判断点 p 是否在线段 ab 上
// 注意：判定条件为共线且处于两端点之间 (包含端点)
bool on_segment(Point p, Point a, Point b) {
    return sign(cross(p - a, p - b)) == 0 && sign(dot(p - a, p - b)) <= 0;
}

// 判断两线段 a1a2 和 b1b2 是否相交 (包含严格相交和端点相交)
bool segment_intersection(Point a1, Point a2, Point b1, Point b2) {
    // 步骤一：快速排斥实验 (Bounding Box 检查)
    if (min(a1.x, a2.x) > max(b1.x, b2.x) || max(a1.x, a2.x) < min(b1.x, b2.x) ||
        min(a1.y, a2.y) > max(b1.y, b2.y) || max(a1.y, a2.y) < min(b1.y, b2.y)) {
        return false;
    }
    // 步骤二：跨立实验 (利用叉积判断线段是否在彼此的两侧)
    double c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);
    double c3 = cross(b2 - b1, a1 - b1), c4 = cross(b2 - b1, a2 - b1);
    return sign(c1) * sign(c2) <= 0 && sign(c3) * sign(c4) <= 0;
}

// ========================================================================

// 求直线 AB 与圆 C 的交点
// 返回交点个数 (0, 1 或 2)，并将交点存入 out1 和 out2 中
int line_circle_intersection(Point a, Point b, Circle C, Point& out1, Point& out2) {
    Vector D = b - a;
    Vector F = a - C.c;
    
    double a_ = dot(D, D);
    double b_ = 2 * dot(F, D);
    double c_ = dot(F, F) - C.r * C.r;
    
    double delta = b_ * b_ - 4 * a_ * c_;
    int sgn = sign(delta);
    if (sgn < 0) return 0; // 无交点
    
    double sqrt_delta = sqrt(max(0.0, delta));
    double t1 = (-b_ - sqrt_delta) / (2 * a_);
    double t2 = (-b_ + sqrt_delta) / (2 * a_);
    out1 = a + D * t1;
    out2 = a + D * t2;
    return sgn == 0 ? 1 : 2; // delta == 0 时为相切
}

// 计算线段 AB 与圆 C 相交的有效参数 t 区间
// 返回值：是否存在交集。若存在，[t1, t2] 为在圆内的参数区间 (0 <= t1 <= t2 <= 1)
// 此时在圆内的有效线段两端点可以通过 a + (b - a) * t1 和 a + (b - a) * t2 求出
bool segment_circle_intersection_interval(Point a, Point b, Circle C, double& t1, double& t2) {
    Vector D = b - a;
    Vector F = a - C.c;
    double a_ = dot(D, D);
    double b_ = 2 * dot(F, D);
    double c_ = dot(F, F) - C.r * C.r;
    
    // 如果 A 和 B 几乎重合（线段退化为点）
    if (sign(a_) == 0) {
        if (sign(c_) <= 0) { 
            t1 = 0.0; t2 = 1.0; 
            return true; 
        }
        return false;
    }
    
    double delta = b_ * b_ - 4 * a_ * c_;
    if (sign(delta) < 0) return false; 
    
    double sqrt_delta = sqrt(max(0.0, delta));
    t1 = (-b_ - sqrt_delta) / (2 * a_);
    t2 = (-b_ + sqrt_delta) / (2 * a_);
    
    // 截取参数域 [0, 1] 的交集
    t1 = max(0.0, t1);
    t2 = min(1.0, t2);
    if (cmp(t1, t2) > 0) return false; 
    
    return true;
}

// 求解两圆相交的交点
// 返回交点个数：0(相离/内含), 1(相切), 2(相交), -1(无穷多交点即完全重合)
int circle_circle_intersection(Circle c1, Circle c2, Point& out1, Point& out2) {
    double d = get_length(c1.c - c2.c);
    if (sign(d) == 0 && sign(c1.r - c2.r) == 0) return -1; // 重合
    if (sign(d - c1.r - c2.r) > 0 || sign(d - fabs(c1.r - c2.r)) < 0) return 0; // 相离/内含
    
    // 余弦定理求 c1中心 到 c2中心向量 旋转到交点向量的夹角 a
    double a = Acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    Vector v_base = unit(c2.c - c1.c) * c1.r;
    out1 = c1.c + rotate(v_base, a);
    out2 = c1.c + rotate(v_base, -a);
    
    if (out1 == out2) return 1;
    return 2;
}

// 求两圆相交部分的面积
double circle_circle_area(Circle c1, Circle c2) {
    double d = get_length(c1.c - c2.c);
    if (cmp(d, c1.r + c2.r) >= 0) return 0.0; // 相离或外切
    if (cmp(d, fabs(c1.r - c2.r)) <= 0) {     // 内含或内切
        double r = min(c1.r, c2.r);
        return PI * r * r;
    }
    // 余弦定理求两扇形的圆心角
    double a1 = 2 * Acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2.0 * c1.r * d));
    double a2 = 2 * Acos((c2.r * c2.r + d * d - c1.r * c1.r) / (2.0 * c2.r * d));
    // 面积 = 两扇形面积之和 - 两三角形面积之和
    double area1 = 0.5 * c1.r * c1.r * (a1 - sin(a1));
    double area2 = 0.5 * c2.r * c2.r * (a2 - sin(a2));
    return area1 + area2;
}

// 求点 p 到圆 C 的切点
// 返回切点个数：0(点在圆内), 1(点在圆上), 2(点在圆外)
int tangents_point_to_circle(Point p, Circle C, Point& out1, Point& out2) {
    Vector u = C.c - p;
    double dist = get_length(u);
    int sgn = sign(dist - C.r);
    
    if (sgn < 0) return 0; 
    if (sgn == 0) { 
        out1 = out2 = p;
        return 1;
    }
    
    double angle = asin(C.r / dist);
    double tangent_len = sqrt(dist * dist - C.r * C.r); // 勾股定理求切线长
    Vector base = unit(u) * tangent_len;
    out1 = p + rotate(base, angle);
    out2 = p + rotate(base, -angle);
    return 2;
}

// ========================================================================

// 求多边形的面积
// 参数：多边形顶点的 vector，需按顺时针或逆时针顺序给出
double polygon_area(const vector<Point>& p) {
    double res = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        res += cross(p[i], p[(i + 1) % n]); 
    }
    return fabs(res / 2.0);
}

// 判断点 p 与多边形 poly 的位置关系 (基于射线法/环绕数法)
// 返回值：2 表示点在多边形边界上，1 表示在多边形内部，0 表示在外部
int is_point_in_polygon(Point p, const vector<Point>& poly) {
    int n = poly.size();
    int wn = 0; 
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        if (on_segment(p, a, b)) return 2; 
        
        // 射线水平向右，判断交点
        int k = sign(cross(b - a, p - a));
        int d1 = sign(a.y - p.y);
        int d2 = sign(b.y - p.y);
        
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;      // 逆时针方向穿过射线向上
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;      // 顺时针方向穿过射线向下
    }
    return wn != 0 ? 1 : 0;
}
