//######################################################################################
//############################# GEOMETRIA COMPUTACIONAL ################################
//######################################################################################
 
#define EPS 1e-8
#define PI acos(-1)
#define Vector Point
 
struct Point
{
    double x, y;
    Point(){}
    Point(double a, double b) { x = a; y = b; }
    double mod2() { return x*x + y*y; }
    double mod()  { return sqrt(x*x + y*y); }
    double arg()  { return atan2(y, x); }
    Point ort()   { return Point(-y, x); }
    Point unit()  { double k = mod(); return Point(x/k, y/k); }
};
 
Point operator +(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
Point operator -(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point operator /(const Point &a, double k) { return Point(a.x/k, a.y/k); }
Point operator *(const Point &a, double k) { return Point(a.x*k, a.y*k); }
 
bool operator ==(const Point &a, const Point &b) {
    return abs(a.x - b.x) < EPS && abs(a.y - b.y) < EPS;
}
bool operator !=(const Point &a, const Point &b) {
    return !(a==b);
}
bool operator <(const Point &a, const Point &b) {
    if(abs(a.x - b.x) > EPS) return a.x < b.x;
    return a.y + EPS < b.y;
}
bool byAngle(const Point &p1, const Point &p2) {
    int sp1 = semiplane(p1), sp2 = semiplane(p2);
    if(sp1 != sp2) return sp1 < sp2;
     
    return cross(p1, p2) > 0;
}
 
//### FUNCIONES BASICAS #############################################################
 
double dist(const Point &A, const Point &B)    { return hypot(A.x - B.x, A.y - B.y); }
double cross(const Vector &A, const Vector &B) { return A.x * B.y - A.y * B.x; }
double dot(const Vector &A, const Vector &B)   { return A.x * B.x + A.y * B.y; }
double area(const Point &A, const Point &B, const Point &C) { return cross(B - A, C - A); }
inline int semiplane(const Point &p) { return p.x >= 0 ? 0 : 1; }
//http://codeforces.com/contest/598/problem/C
 
// Heron triangulo y cuadrilatero ciclico
// http://mathworld.wolfram.com/CyclicQuadrilateral.html
// http://www.spoj.pl/problems/QUADAREA/
 
double areaHeron(double a, double b, double c)
{
    double s = (a + b + c) / 2;
    return sqrt(s * (s-a) * (s-b) * (s-c));
}
 
double circumradius(double a, double b, double c) { return a * b * c / (4 * areaHeron(a, b, c)); }
 
double areaHeron(double a, double b, double c, double d)
{
    double s = (a + b + c + d) / 2;
    return sqrt((s-a) * (s-b) * (s-c) * (s-d));
}
 
double circumradius(double a, double b, double c, double d) { return sqrt((a*b + c*d) * (a*c + b*d) * (a*d + b*c))  / (4 * areaHeron(a, b, c, d)); }
 
//### DETERMINA SI P PERTENECE AL SEGMENTO AB ###########################################
bool between(const Point &A, const Point &B, const Point &P)
{
    return  P.x + EPS >= min(A.x, B.x) && P.x <= max(A.x, B.x) + EPS &&
            P.y + EPS >= min(A.y, B.y) && P.y <= max(A.y, B.y) + EPS;
}
 
bool onSegment(const Point &A, const Point &B, const Point &P)
{
    return abs(area(A, B, P)) < EPS && between(A, B, P);
}
 
//### DETERMINA SI EL SEGMENTO P1Q1 SE INTERSECTA CON EL SEGMENTO P2Q2 #####################
//funciona para cualquiera P1, P2, P3, P4
bool intersects(const Point &P1, const Point &P2, const Point &P3, const Point &P4)
{
    double A1 = area(P3, P4, P1);
    double A2 = area(P3, P4, P2);
    double A3 = area(P1, P2, P3);
    double A4 = area(P1, P2, P4);
     
    if( ((A1 > 0 && A2 < 0) || (A1 < 0 && A2 > 0)) && 
        ((A3 > 0 && A4 < 0) || (A3 < 0 && A4 > 0))) 
            return true;
     
    else if(A1 == 0 && onSegment(P3, P4, P1)) return true;
    else if(A2 == 0 && onSegment(P3, P4, P2)) return true;
    else if(A3 == 0 && onSegment(P1, P2, P3)) return true;
    else if(A4 == 0 && onSegment(P1, P2, P4)) return true;
    else return false;
}
 
//### DETERMINA SI A, B, M, N PERTENECEN A LA MISMA RECTA ##############################
bool sameLine(Point P1, Point P2, Point P3, Point P4)
{
    return area(P1, P2, P3) == 0 && area(P1, P2, P4) == 0;
}
//### SI DOS SEGMENTOS O RECTAS SON PARALELOS ###################################################
bool isParallel(const Point &P1, const Point &P2, const Point &P3, const Point &P4)
{
    return cross(P2 - P1, P4 - P3) == 0;
}
 
//### PUNTO DE INTERSECCION DE DOS RECTAS NO PARALELAS #################################
Point lineIntersection(const Point &A, const Point &B, const Point &C, const Point &D)
{
    return A + (B - A) * (cross(C - A, D - C) / cross(B - A, D - C));
}
 
Point circumcenter(const Point &A, const Point &B, const Point &C)
{
    return (A + B + (A - B).ort() * dot(C - B, A - C) / cross(A - B, A - C)) / 2;
}
 
//### FUNCIONES BASICAS DE POLIGONOS ################################################
bool isConvex(const vector <Point> &P)
{
    int n = P.size(), pos = 0, neg = 0;
    for(int i=0; i<n; i++)
    {
        double A = area(P[i], P[(i+1)%n], P[(i+2)%n]);
        if(A < 0) neg++;
        else if(A > 0) pos++;
    }
    return neg == 0 || pos == 0;
}
 
double area(const vector <Point> &P)
{
    int n = P.size();
    double A = 0;
    for(int i=1; i<=n-2; i++)
        A += area(P[0], P[i], P[i+1]);
    return abs(A/2);
}
 
bool pointInPoly(const vector <Point> &P, const Point &A)
{
    int n = P.size(), cnt = 0;
    for(int i=0; i<n; i++)
    {
        int inf = i, sup = (i+1)%n;
        if(P[inf].y > P[sup].y) swap(inf, sup);
        if(P[inf].y <= A.y && A.y < P[sup].y)
            if(area(A, P[inf], P[sup]) > 0)
                cnt++;
    }
    return (cnt % 2) == 1;
}
 
 //### DETERMINA SI P ESTA EN EL INTERIOR DEL POLIGONO CONVEXO A ########################
 
// O (log n)
bool isInConvex(vector <Point> &A, const Point &P)
{
    int n = A.size(), lo = 1, hi = A.size() - 1;
     
    if(area(A[0], A[1], P) <= 0) return 0;
    if(area(A[n-1], A[0], P) <= 0) return 0;
     
    while(hi - lo > 1)
    {
        int mid = (lo + hi) / 2;
         
        if(area(A[0], A[mid], P) > 0) lo = mid;
        else hi = mid;
    }
     
    return area(A[lo], A[hi], P) > 0;
}
 
// O(n)
Point norm(const Point &A, const Point &O)
{
    Vector V = A - O;
    V = V * 10000000000.0 / V.mod();
    return O + V;
}
 
bool isInConvex(vector <Point> &A, vector <Point> &B)
{
    if(!isInConvex(A, B[0])) return 0;
    else
    {
        int n = A.size(), p = 0;
         
        for(int i=1; i<B.size(); i++)
        {
            while(!intersects(A[p], A[(p+1)%n], norm(B[i], B[0]), B[0])) p = (p+1)%n;
             
            if(area(A[p], A[(p+1)%n], B[i]) <= 0) return 0;
        }
         
        return 1;
    }
}

// INTERSECCION DE CIRCULOS
vector <Point> circleCircleIntersection(Point O1, double r1, Point O2, double r2)
{
    vector <Point> X;
     
    double d = dist(O1, O2);
 
    if(d > r1 + r2 || d < max(r2, r1) - min(r2, r1)) return X;
    else
    {
        double a = (r1*r1 - r2*r2 + d*d) / (2.0*d);
        double b = d - a;
        double c = sqrt(abs(r1*r1 - a*a));
 
        Vector V = (O2-O1).unit();
        Point H = O1 + V * a;
 
        X.push_back(H + V.ort() * c);
         
        if(c > EPS) X.push_back(H - V.ort() * c);
    }
     
    return X;
}
