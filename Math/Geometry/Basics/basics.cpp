#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long double Double;
typedef long long Long;
const Double EPS = 1e-10;
const Double INF = 1e17;

struct Point{
	Double x,y,z;
	
	Point(){
		x = 0;
		y = 0;
		z = 0;
	}
	Point(Double x, Double y, Double z = 0):
		x(x), y(y), z(z){}

	Point operator += (const Point &t){
		x += t.x;
		y += t.y;
		z += t.z;
		return *this;
	}
	Point operator -= (const Point &t){
		x -= t.x;
		y -= t.y;
		z -= t.z;
		return *this;
	}
	Point operator *= (Double t){
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}
	Point operator +(const Point &t) const {
		return Point(*this) += t;
	}
	Point operator - (const Point &t) const{
		return Point(*this) -= t;
	}
	Point operator *(Double t) const{
		return Point(*this) *= t;
	}
	
	Point operator /(Double t) const{
		return Point(*this) *= 1.0/t;
	}
	
	bool operator == (const Point &P) const{
		return fabs(x-P.x) < EPS && fabs(y-P.y) < EPS;
	}
	
	Double norm(){
		return x * x + y * y + z * z;
	}
	
	Double abs(){
		return sqrt(norm());
	}
	
	Point ort(){
		return Point(-y,x);
	}
	
	Double cross(const Point &P) const {
		return x * P.y - y * P.x;
	}
	
	Double cross(const Point &a , const Point &b) const {
		return (a - *this).cross(b - *this);
	}
	
	bool inTriangle(Point A, Point B , Point C) {
		//compare areas
		Point P = Point(*this);
		Double a1 = fabs(A.cross(B , C));
		Double a2 = fabs(P.cross(A , B)) + fabs(P.cross(A , C)) + fabs(P.cross(B , C));
		return fabs(a1 - a2) < EPS;
	}
	
	bool inSegment(Point A, Point B) {
		Point target = Point(*this);
		if(fabs(A.cross(B , target)) < EPS) {
			if(target.x >= min(A.x , B.x) && target.x <= max(A.x , B.x) && target.y >= min(A.y , B.y) && target.y <= max(A.y , B.y )) {
				return true;
			} 
		}
		return false;
	}
	
	void debugPoint(string nombre){
		cout << nombre << " = ( " << fixed << setprecision(2) <<  x << " , " << y << " , " << z << " ) " << endl; 
	}
};

Long quad(Point P) {
	if(P.x >= 0 && P.y > 0) {
		return 1;
	}
	if(P.x < 0 && P.y >= 0) {
		return 2;
	}
	if(P.x <= 0 && P.y < 0) {
		return 3;
	}
	return 4;
} 

bool counterClockwise(const Point &A, const Point &B , Point center) {
	if(quad(A - center) != quad(B - center)) {
		return quad(A - center) < quad(B - center);
	}
	
	return center.cross(A, B) > 0;
}

Point operator *(Double a, Point b) {
	return b * a;
}

Point operator/(Double a , Point b){
	return b / a;
}

double abs(Point A){
	return sqrt(A.norm());
}

Double dot(Point A, Point B){
	return A.x * B.x + A.y * B.y + A.z * B.z;
}

Point proj(Point A, Point B){
	if(B.abs() < EPS){
		return Point(INF,INF);
	}
	return  B* (dot(A,B)/B.abs() );
}

Point midPoint(Point A, Point B) {
	return Point((A + B) / 2.0);
}

Double angle(Point A, Point B){
	if(A.abs()*B.abs() < EPS){
		return INF;
	}
	return acos(dot(A,B) / (A.abs()*B.abs()) );
}

Point cross(Point A, Point B){
	return Point(A.y*B.z - A.z * B.y , 
				 A.z*B.x - A.x * B.z ,
				 A.x*B.y - A.y * B.x);
}

Double triple(Point A, Point B, Point C){
	return dot(A,cross(B,C));
}

Double dist(Point A, Point B){
	return sqrt( (A.x-B.x)*(A.x-B.x) + (B.y-A.y)*(B.y-A.y) );
}


Point intersectPlanes(Point a1, Point n1, Point a2, Point n2, Point a3, Point n3){
	Point x(n1.x, n2.x, n3.x);
	Point y(n1.y, n2.y, n3.y);
	Point z(n1.z, n2.z, n3.z); 
	Point d(dot(a1, n1), dot(a2, n2), dot(a3, n3));
	return Point(triple(d, y, z), 
				triple(x, d, z), 
				triple(x, y, d)) / triple(n1, n2, n3);
}

Double areaDet(Point P1, Point P2, Point P3 ){
	return (P2.x-P1.x)*(P3.y - P2.y) - (P3.x-P2.x)*(P2.y-P1.y);
}

long double area(Point P1, Point P2, Point P3 ){
	return fabs(areaDet(P1,P2,P3))/2.0;
}


struct Line{
	Double A , B ,C;
	//AX + BY + C = 0
	
	Line(){	}
	Line(Double a , Double b, Double c){
		A = a;
		B = b;
		C = c;
	}
	
	Line(Point P1, Point P2){
		A = P1.y - P2.y;
		B = P2.x - P1.x;
		C = -A*P1.x  - B*P1.y;	
	}
	
	void debugLine(string nombre){
		cout << nombre << " : " << fixed << setprecision(2) << A << "x + " << B << "y + " << C << " = 0" << endl;
	}
};

Double dist(Line L, Point P){
	//distancia minima de un punto a una recta
	return fabs(L.A*P.x + L.B * P.y + L.C)/ sqrt(L.A*L.A + L.B * L.B);
}

Double det(Double a, Double b, Double c, Double d){
	//determinante
	return a*d-b*c;
}

struct Circle{
	Double r;
	Point center;
	Circle(){}
	Circle(Double rad, Point c){
		r =rad;
		center = c;
	}
	
	Circle(Point c, Double rad){
		r = rad;
		center = c;
	}
	
	void debugCircle(string nombre){
		cout << nombre << " : " << "R = " << r << " , ";
		center.debugPoint("Centro");
	}
	
};

Long sgn(Double x) {
	if(x == 0) {
		return 0;
	}
	if(x > 0) return 1;
	return -1;
}

bool intersectAxis(Double a, Double b , Double c, Double d) {
	if(a > b) {
		swap(a , b);
	}
	if(c > d) {
		swap(c , d);
	}
	return max(a , c) <= min(b , d);
}

bool intersectSegment(Point A, Point B, Point C, Point D) {
	if(C.cross(A, D) == 0 && C.cross(B, D) == 0) {
		//same line
		return intersectAxis(A.x, B.x, C.x, D.x ) && intersectAxis(A.y ,B.y , C.y , D.y);
	}
	return sgn(A.cross(B, C)) != sgn(A.cross(B , D)) && sgn(C.cross(D, A)) != sgn(C.cross(D, B));
}

bool intersect(Point P1, Point d1, Point P2, Point d2, Point &resp ){
	
	//Cuando expresamos la recta como R: P = P0 + t a vectorial
	
	if(cross(d1,d2).abs() == 0){
		return false;	
	}
	resp = P1 + (cross(P2-P1,d2).abs() / cross(d1,d2).abs() ) * d1;
	return true;
}

int intersect(Line L1, Line L2, Point &resp){
	//0 -> Paralelas
	//1 -> Un punto intersección
	//2 -> Rectas iguales
	Double zn = det(L1.A,L1.B, L2.A, L2.B);
	
	if(fabs(zn) < EPS){
		if(fabs(det(L1.C, L1.B , L2.C , L2.B)) < EPS && fabs(det(L1.A, L1.C , L2.A , L2.C)) < EPS){
			return 2;
		}
		else{
			return 0;
		}
	}
	
	resp.x = -det(L1.C, L1.B , L2.C , L2.B)/zn;
	resp.y = -det(L1.A, L1.C , L2.A , L2.C)/zn;
	

	return 1;
}

int intersect(Line L, Circle C, Point &resp1, Point &resp2){
/*
	0 = no hay interseccion
	1 = 1 punto
	2 = 2 puntos
*/

//translación de coordenadas hacia C.centro como origen
	Double plus = C.center.x*L.A + C.center.y*L.B;
	L.C += plus;
	
	Double x0 = -L.A*L.C/(L.A*L.A + L.B * L.B);
	Double y0 = -L.B * L.C / (L.A * L.A + L.B * L.B);
	
	if(L.C * L.C - C.r*C.r*(L.A*L.A+L.B*L.B) > EPS){
		//si la distancia minima de la recta al origen es mayor que r, entonces no hay interseccion
		return 0;
	}
	
	if(fabs(L.C * L.C - C.r*C.r*(L.A*L.A+L.B*L.B)) < EPS){
		//la distancia minima es casi igual al radio
		resp1 = Point(x0 , y0 );
		resp1 += C.center; //translación
		resp2 = Point(INF,INF);
		return 1;
	}
	
	Double d = C.r*C.r - L.C*L.C / (L.A*L.A + L.B*L.B);
	Double mult = sqrt(d/ (L.A * L.A + L.B * L.B));
	
	resp1 = Point(x0 + L.B*mult , y0 - L.A * mult);
	resp2 = Point(x0 - L.B*mult , y0 + L.A * mult);
	
	resp1 += C.center; //translación
	resp2 += C.center; //translación
	
	return 2;
}

int intersect(Circle C, Line L, Point &resp1 , Point &resp2){
	return intersect(L,C,resp1,resp2);
}

int intersect(Circle C1, Circle C2, Point &resp1, Point &resp2){
	//0 no hay interseccion
	//1 una sola
	//2 hay 2
	//3 infintas
	C2.center -= C1.center; //translacion
	
	Point origen = C1.center;
	C1.center -= C1.center;
	
	//x² + y² = r1²
	//(x-x2)² + (y-y2)² = r2²
	// =>  x (-2x2) + y (-2y2) + (x2²+y2² + r1² - r2² ) =0
	
	Double d = dist(C1.center,C2.center);
	if(d > C1.r + C2.r) return 0;
	if(d < fabs(C1.r-C2.r)) return 0;
	
	Line L(-2*C2.center.x, -2*C2.center.y , C2.center.x * C2.center.x + C2.center.y * C2.center.y + C1.r * C1.r - C2.r * C2.r);
	
	if(C1.center == C2.center){
		if(C1.r == C2.r) return 3;
		else return 0;
	}
	
	int x = intersect(C1,L,resp1,resp2);
	
	resp1 += origen;
	resp2 += origen;
	
	return x;
}

Circle circuncenter(Point A, Point B , Point C) {
	Point M = midPoint(A , B);
	Point N = midPoint(A , C);
	Point Mx = M + (B - A).ort();
	Point Nx = N + (C - A).ort();
	
	Line L1(M , Mx);
	Line L2(N , Nx);
	
	Circle ans;
	intersect(L1 , L2, ans.center);
	
	ans.r = dist(ans.center , A);
	return ans;
}

Circle incenter(Point A , Point B, Point C) {
	Double a = dist(B , C);
	Double b = dist(A , C);
	Double c = dist(A , B);
	
	Circle ans;
	ans.center.x = (a * A.x + b * B.x + c * C.x ) / (a + b + c);
	ans.center.y = (a * A.y + b * B.y + c * C.y ) / (a + b + c);
	
	Double p = (a + b + c) / 2.0;
	
	ans.r = sqrt(p * (p - a ) * (p - b) * (p - c)) / p;
	return ans;
}

Double area(vector<Point> &v) {
	Double ans = 0;
	Long sz = v.size();
	for(Long i = 0; i < sz; i++) {
		Point P = v[(i - 1 + sz) % sz ];
		Point Q = v[i];
		ans += (P.x - Q.x) * (P.y + Q.y);
	}
	return fabs(ans) / 2.0;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
/*
5 6
7 -3
2 3
9

20.9 3.5
9 15.3
2 3
9

11.4 3.5
11.4 9
2.4 3.6
9
*/
	Point P1,P2;
	Double r1,r2;
	
	while(cin >> P1.x >> P1.y >> r1 >> P2.x >> P2.y >> r2){
		Circle C1(P1,r1);
		Circle C2(P2,r2);
		
		Point resp1,resp2;
		int x = intersect(C1,C2,resp1,resp2);
		if( x > 0){
			resp1.debugPoint("resp1");
			if(x == 2){
				resp2.debugPoint("resp2");
			}
			else if (x == 3){
				cout << "SUPERPUESTA" << endl;
			}
		}
		else{
			cout << "NO INTERSECTION" << endl;
		}
	}
	return 0;
}
