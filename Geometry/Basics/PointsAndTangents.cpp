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
    Point(Double x, Double y, Double z) : x(x), y(y) , z(z){
    }
    Point(Double _x, Double _y){
        x = _x;
        y = _y;
        z = 0;
    }
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
    Point operator /= (Double t) {
        *this *= 1.0/t;
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
        return x*x+y*y+z*z;
    }
    
    double abs(){
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
    
    
    void debugPoint(string nombre){
        cout << nombre << " = ( " << fixed << setprecision(2) <<  x << " , " << y << " , " << z << " ) " << endl; 
    }
};

Long quad(Point P) {
    if(P.x > 0 && P.y >= 0) {
        return 1;
    }
    if(P.x <= 0 && P.y > 0) {
        return 2;
    }
    if(P.x < 0 && P.y <= 0) {
        return 3;
    }
    return 4;
} 

bool antiClockwise(const Point &A, const Point &B , Point center) {
    if(quad(A - center) != quad(B - center)) {
        return quad(A - center) < quad(B - center);
    }
    
    return center.cross(A, B) > 0;
}


Point operator*(Double a, Point b) {
    return b * a;
}

Point operator/(Double a , Point b){
    return b/a;
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

double angle(Point A, Point B){
    if(A.abs()*B.abs() < EPS){
        return INF;
    }

    return acos(dot(A,B) / (A.abs()*B.abs()) );
}

Double dist(Point A, Point B){
    return sqrt( (A.x-B.x)*(A.x-B.x) + (B.y-A.y)*(B.y-A.y) );
}

Long dist2(pair<Long,Long> A, pair<Long,Long> B){
    return (A.first - B.first) * (A.first - B.first) + (B.second - A.second) * (B.second - A.second) ;
}


struct Line{
    Double A , B ,C;
    //AX + BY + C = 0
    
    Line(){    }
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

Point midPoint(Point A, Point B) {
    return Point((A.x + B.x) / 2.0 , (A.y + B.y) / 2.0);
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

void transf(Point &P) {
    /*if(P.x < EPS && P.y < EPS) {
        P.x = fabs(P.x);
        P.y = fabs(P.y);
    }
    else if(P.y < EPS && P.x > -EPS) {
        P.y = -P.y;
        P.x = -P.x;
    }*/
    if(quad(P) > 2 ) {
    	P.x = -P.x;
    	P.y = -P.y;
	}
}

vector<Double> tangentLine(Circle C, Point P) {
    Point ans1, ans2;
    
    Circle aux;
    aux.center = midPoint(C.center, P);
    aux.r = dist(aux.center, P);
    
    Long x =intersect(aux , C, ans1, ans2);
    if(x == 0) {
        return {};
    }
    
    Point A = ans1 - P;
    Point B = ans2 - P;
    transf(A);
    transf(B);

    Double angle1 = angle(A, Point(1 , 0));
    Double angle2 = angle(B, Point(1 , 0));
    return {angle1, angle2};
}

const Double PI = acos(-1);

Point tangentCenter(Point A, Point B, Point inter , Long r) {
    Double ang = angle(A - inter, B - inter);
    Point v = A - inter;
    Point M = inter + r  * (v / v.abs() ) / tan(ang / 2.0);
    
    Long sign = 1;
    
    if(inter.cross(A , B) < 0) {
       sign = -1;
    }
    Point ans = M + sign * r * v.ort() / v.abs();
   return ans;
}

Long circleType(Circle C1, Circle C2) {
    
    if(C1.center == C2.center && fabs(C1.r - C2.r) < EPS) {
        // Circulos iguales 
        return 0;
    }

    if(C1.r + C2.r - dist(C1.center, C2.center) < EPS ) {
        //Circulos disjuntos
       return 1;
    }

    if(fabs(C1.r + C2.r - dist(C1.center, C2.center)) < EPS) {
        return 2; //Tangentes externamente
    }

    if(fabs(C1.r - C2.r) - dist(C1.center, C2.center)< EPS) {
        //se intersecan 
        return 3;
    }
    if(fabs(fabs(C1.r - C2.r) - dist(C1.center, C2.center)) < EPS ) {
        //tangentes internamente
        return 4;
    }

    //Un circulo contiene al otro
    return 5;
}



bool tangents(Circle C1, Circle C2, vector< Line > &ans) {
    Long t = circleType(C1, C2);

    if(t == 0) {
        return false;
    }

    if(t == 5) {
        return true;
    }
   
   //bool cero = false;

   Double vx = C2.center.x - C1.center.x;
   Double vy = C2.center.y - C1.center.y;

   Double r2 = C2.r;
   Double r1 = C1.r;
   

	for(Long i = -1; i <= 1; i+= 2) {
		for(Long j = -1; j <= 1; j+= 2) {
			Double d1 = i * r1;
			Double d2 = j * r2;
			Double sq = vx * vx + vy * vy - (d2 - d1) * (d2 - d1);
			if(sq < EPS) {
				continue;
			}
			/*if(sq == 0) {
				if(cero) {
					continue;
				}
				cero = true;
			} else{
				sq = sqrt(sq);
			}*/
			sq = sqrt(sq);
			Double a = (d2 - d1) * vx + vy * sq;
			a = 1.0 * a / (vx * vx + vy * vy);
			Double b = (d2 - d1) * vy - vx * sq;
			b = 1.0 * b / (vx * vx + vy * vy);
			Double c = d1;
			
			c -= C1.center.x * a + C1.center.y * b;
			
			Line L(a, b ,c);
			
			ans.pb(L);
		}
	}
	
	return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while(cin >> s) {
        if(s[0] == 'C' && s[4] == 'u') {
            Point A,B,C;
            cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
            Circle ans = circuncenter(A , B , C);
            cout << fixed << setprecision(6) << "(" << ans.center.x << "," << ans.center.y << "," << ans.r << ")" << endl;
        }
        else if(s[0] == 'I') {
            Point A,B,C;
            cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
            Circle ans = incenter(A , B , C);
            cout << fixed << setprecision(6) << "(" << ans.center.x << "," << ans.center.y << "," << ans.r << ")" << endl;
        } else if(s[0] == 'T') {
            Long xc, yc, r , x, y;
            cin >> xc >> yc >> r >> x >> y;
            vector<Double> ans;
            if((x - xc) * (x - xc) + (y - yc) * (y - yc) == r * r) {
                Point vec = Point(xc, yc) - Point(x , y);
                vec = vec.ort();
                transf(vec);
                ans.pb(angle(vec, Point(1 , 0)));
            } else if((x - xc) * (x - xc) + (y - yc) * (y - yc) > r * r){
                ans = tangentLine(Circle(Point(xc, yc) , r) , Point(x , y ));
            }
            sort(ans.begin(), ans.end());
            cout <<"[";
            REP( i , ans.size()) {
                cout << fixed << setprecision(6) << ans[i] * 180.0 / PI;
                if(i + 1 != ans.size()) {
                    cout <<",";
                }
            }
            cout <<"]" << endl;
        } else if(s[7] == 'h') {
            Long px,py;
            Long ax, ay, bx,by;
            Long r;
            cin >> px >> py >> ax >> ay >> bx >> by >> r;
            Long a,b,c;
            a = ay - by;
            b = bx - ax;
            c = -a *ax  - b *ay;
            //if dist Point to Line > 2 * r
            vector<pair<Double,Double>> ans;
            Point P(px, py);
            Point A(ax, ay);
            Point B(bx, by);
            if(a * px + b * py + c == 0) {
                Point ortog = (B - A).ort();
                ortog /= ortog.abs();
                ans.pb({(P + r * ortog).x , (P + r * ortog).y});
                ans.pb({(P - r * ortog).x , (P - r * ortog).y});
            } else     if((a * px + b * py + c) * (a * px + b * py + c) <= 4 * r * r * (a * a + b * b)) {
                Long sol = 2;
                if((a * px + b * py + c) * (a * px + b * py + c) == 4 * r * r * (a * a + b * b) ) {
                    sol = 1;
                }
                
                Point ortog = (B - A).ort();
                ortog /= ortog.abs();
                Point Ax = A + r * ortog;
                Point Bx = B + r * ortog;
    
                if(sgn(A.cross(B , Ax) ) != sgn(A.cross(B , P)) ) {
                    Ax = A - r * ortog;
                    Bx = B - r * ortog;
                }
            
                Line L(Ax, Bx);
                Point ans1, ans2;
                intersect(L, Circle(P, r), ans1 , ans2);
                ans.pb({ans1.x, ans1.y});
                if(sol == 2) {
                    ans.pb({ans2.x, ans2.y});
                } 
            }
            
            sort(ans.begin(),ans.end());
            cout <<"[";
            REP(i , ans.size()) {
                cout << "(" << fixed << setprecision(6) << ans[i].first << "," << ans[i].second << ")";
                if(i + 1 != ans.size()) {
                    cout << ",";
                }
            }
            cout <<"]" << endl;
        
        } else if(s[18] == 'L') {
            Point A, B, C , D;
            Double r;
            cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y >> r;
            Line L1(A , B);
            Line L2(C , D);
            Point inter;
            intersect(L1 , L2 , inter);
            
            vector<pair<Double,Double> > ans;
            
            if((A - inter).abs() < EPS) {
               A = inter - B + inter;
            } else  {
               B = inter - A + inter;
            } 
            
            if( (C- inter).abs() < EPS) {
               C = inter - D + inter;
            } else{
               D = inter - C + inter;
            }
            
            
           ans.pb({tangentCenter(A , C , inter , r).x ,tangentCenter(A , C , inter , r).y});
           ans.pb({tangentCenter(A , D , inter , r).x ,tangentCenter(A , D , inter , r).y});
           ans.pb({tangentCenter(B , C , inter , r).x ,tangentCenter(B , C , inter , r).y});
           ans.pb({tangentCenter(B , D , inter , r).x ,tangentCenter(B , D , inter , r).y});
            sort(ans.begin(),ans.end());
            
            cout <<"[";
            REP(i , ans.size()) {
                cout << fixed << setprecision(6) << "(" << ans[i].first << "," << ans[i].second << ")";
                if(i + 1 != ans.size()) {
                    cout << ",";
                }
            }
            cout << "]" << endl;
            
            
        } else{
        	Long x1, y1, r1, x2,y2 , r2 , r;
			cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2 >> r; 
			Long d2 = dist2({x1,y1} , {x2,y2});
			vector<pair<Double,Double > > ans;
			if(d2 <= (2 * r + r1 + r2) * (2 * r + r1 + r2)) {
				if(d2 == (2 * r + r1 + r2) * (2 * r + r1 + r2)) {
					Circle C1, C2;
					C1.center = Point(x1 , y1);
					C1.r = r1;
					C2.center = Point(x2 , y2);
					
					Point ans1 = C1.center + (r1 + r) * (C2.center - C1.center) / (C2.center - C1.center).abs();
					ans.pb({ans1.x, ans1.y});
				} else{
					Circle C1, C2;
					C1.center = Point(x1 , y1);
					C1.r = r1;
					C2.center = Point(x2 , y2);
					C2.r = r2;
					C1.r += r;
					C2.r += r;
		           
		           Point ans1, ans2;
		           Long num = intersect(C1, C2 , ans1 , ans2);
					ans.pb({ans1.x, ans1.y});
					ans.pb({ans2.x, ans2.y});
				}
			} 
			
          
           sort(ans.begin(), ans.end());
           cout <<"[";
            REP(i , ans.size()) {
                cout << fixed << setprecision(6) << "(" << ans[i].first << "," << ans[i].second << ")";
                if(i + 1 != ans.size()) {
                    cout << ",";
                }
            }
            cout << "]" << endl;
        }
    }
/*
TangentLineThroughPoint 0 0 3 -3 3
TangentLineThroughPoint 5 6 5 0 4
TangentLineThroughPoint 5 6 5 2 10
TangentLineThroughPoint 5 6 5 8 10
TangentLineThroughPoint 5 6 5 5 1
TangentLineThroughPoint 5 6 5 5 11
TangentLineThroughPoint 5 6 5 4 8
CircleThroughAPointAndTangentToALineWithRadius 5 7 3 9 8 6 1
CircleThroughAPointAndTangentToALineWithRadius 5 7 3 9 8 6 10
CircleThroughAPointAndTangentToALineWithRadius 3 9 3 9 8 6 0
CircleThroughAPointAndTangentToALineWithRadius -5 -7 3 9 8 6 10
CircleThroughAPointAndTangentToALineWithRadius 8 10 2 6 2 10 3
CircleTangentToTwoDisjointCirclesWithRadius 5 5 5 31 5 5 1
CircleTangentToTwoDisjointCirclesWithRadius 5 5 5 31 5 5 8
CircleTangentToTwoDisjointCirclesWithRadius 5 5 5 31 5 5 9
CircleTangentToTwoDisjointCirclesWithRadius 5 5 5 15 5 5 1 
CircleTangentToTwoLinesWithRadius 5 6 7 8 7 12 7 15 5
*/
    return 0;
}

