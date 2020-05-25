#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
#define getMatrix(n , m) vector<vector<Long>>(n , vector<Long>(m, 0))
using namespace std;

typedef long long Long;
typedef vector<vector<Long>> Matrix;

const Long MXX = 5000;
const Long MXY = 5000;
Long combine(Long x , Long y) {
	return x + y;
}

Long cntUpdate;
Long cntQuery1;
Long cntQuery2;
struct SegmentTree{
	Long t[2 * MXX][2 * MXY];
	Long maxN, maxM;
	
	void clear(Long n , Long m){
		for(Long i = 0 ; i < 2 * n; i++){
			for(Long j = 0; j < 2 * m; j++){
				t[i][j] = 0;
			}
		}
		maxN = n;
		maxM = m;
	}
	
	void buildY(vector< vector < Long > > &a , Long idX, Long tlX, Long trX, Long idY , Long tlY, Long trY ) {
		if (tlY == trY){
			if(tlX == trX){
				t[idX][idY] = a[tlX][tlY];
			} else{
				Long tmX = (tlX + trX) / 2;
				Long leftX = idX + 1;
				Long rightX = idX + 2 * (tmX - tlX + 1) ;
				t[idX][idY] = combine(t[leftX][idY], t[rightX][idY]);
			}
			
		}else{
			Long tmY = (tlY + trY) / 2;
			Long leftY = idY + 1;
			Long rightY = idY + 2 * (tmY - tlY + 1) ;
			buildY(a , idX, tlX , trX, leftY, tlY, tmY);
			buildY(a, idX, tlX, trX, rightY, tmY + 1 , trY);
			t[idX][idY] = combine(t[idX][leftY] , t[idX][rightY]);
		}
	}

	void build(vector< vector < Long > > &a , Long idX, Long tlX , Long trX, Long trY) { //O(mn)
		if (tlX != trX){
			Long tmX = (tlX + trX) / 2;
			Long leftX = idX + 1;
			Long rightX = idX + 2 * (tmX - tlX + 1) ;
			build(a , leftX, tlX, tmX , trY);
			build(a, rightX, tmX + 1, trX, trY);
		}
		buildY(a, idX, tlX , trX, 1 , 0 , trY);
	}
	
	void build(vector< vector < Long > > &a) {
		maxN = a.size();
		maxM = a[0].size();
		build(a, 1 , 0 , maxN - 1 , maxM - 1);
	}

	Long queryY(Long idX, Long lY, Long rY, Long idY , Long tlY , Long trY ) {
		cntQuery1++;
		if (lY <= tlY && trY <= rY) {
			return t[idX][idY];
		}

		Long tmY = (tlY + trY) / 2;
		Long leftY = idY + 1;
		Long rightY = idY + 2 * (tmY - tlY + 1) ;
		if(rY < tmY + 1){
			//only left child
			return queryY(idX , lY , rY , leftY , tlY , tmY);
		}else if(tmY < lY){
			//only right child
			return queryY(idX , lY , rY, rightY , tmY + 1 , trY); 
		} else{
			//both children
			return combine(queryY(idX , lY, rY, leftY, tlY, tmY) , queryY(idX, lY, rY, rightY, tmY + 1, trY));
		}
	}

	Long query(Long lX, Long rX, Long lY, Long rY, Long idX , Long tlX , Long trX , Long trY) { //O(log n log m)
		if (lX <= tlX && trX <= rX) {
			return queryY(idX, lY, rY, 1 , 0 , trY);
		}
		cntQuery2++;
		Long tmX = (tlX + trX) / 2;
		Long leftX = idX + 1;
		Long rightX = idX + 2 * (tmX - tlX + 1) ;
		if(rX < tmX + 1){
			//only left child
			return query(lX , rX , lY, rY, leftX , tlX , tmX, trY);
		}else if(tmX < lX){
			//only right child
			return query(lX , rX, lY, rY , rightX , tmX + 1 , trX , trY); 
		} else{
			//both children
			return combine(query(lX , rX , lY, rY, leftX , tlX , tmX, trY) , query(lX , rX, lY, rY , rightX , tmX + 1 , trX , trY));
		}
	}
	
	Long query(Long lX ,Long rX, Long lY, Long rY) {
		return query(lX , rX , lY, rY , 1 , 0 , maxN - 1 , maxM - 1);
	}

	void updateY(Long posX, Long posY, Long val, Long idX, Long tlX, Long trX ,Long idY, Long tlY , Long trY) {
		cntUpdate++;
		if (tlY == trY) {
			if(tlX == trX){
				t[idX][idY] = val;
			} else{
				Long tmX = (tlX + trX) / 2;
				Long leftX = idX + 1;
				Long rightX = idX + 2 * (tmX - tlX + 1) ;
				t[idX][idY] = combine(t[leftX][idY], t[rightX][idY]);
			}
			
		}else {
			Long tmY = (tlY + trY) / 2;
			Long leftY = idY + 1;
			Long rightY = idY + 2 * (tmY - tlY + 1) ;
			if (posY <= tmY) {
				updateY(posX, posY, val, idX, tlX, trX, leftY, tlY, tmY);
			}else {
				updateY(posX, posY, val, idX, tlX, trX , rightY, tmY + 1, trY);
			}
			t[idX][idY] = combine(t[idX][leftY] , t[idX][rightY]);
		}
	}

	void update(Long posX, Long posY, Long val, Long idX , Long tlX , Long trX  , Long trY) {
		if(tlX != trX){
			Long tmX = (tlX + trX) / 2;
			Long leftX = idX + 1;
			Long rightX = idX + 2 * (tmX - tlX + 1) ;
			if (posX <= tmX) {
				update(posX, posY, val, leftX, tlX, tmX , trY);
			}else{
				update(posX, posY, val, rightX, tmX + 1, trX, trY);
			}
		}
		updateY(posX, posY, val, idX , tlX, trX , 1 , 0 , trY);
	}
	
	void update(Long posX, Long posY, Long val) {
		update(posX, posY, val , 1 , 0 , maxN - 1 , maxM - 1);
	}
} st;

const Long MX_X = 5000;
const Long MX_Y = 5000;
const Long EXTRA = 6;

struct BIT2D{
	Long tree[MX_X + EXTRA][MX_Y + EXTRA];
	
	void clear(Long n, Long m){ //O(n * m)
		for(Long i = 0; i< n + EXTRA; i++){
			for(Long j = 0; j < m + EXTRA; j++){
				tree[i][j] = 0;	
			}
		}
	}
	
	Long query(Long x, Long y){ // O(log n log m)
		x += EXTRA;
		y += EXTRA;
		Long sum = 0;
		while(x > 0){
			Long j = y;
			while(j > 0){
				sum += tree[x][j];
				j -= (j & -j);
			}
			x -= (x & -x);
		}
		return sum;
	}
	
	void update(Long x, Long y, Long add){ // O(log n log m)
		x += EXTRA;
		y += EXTRA;
		while(x < MX_X + EXTRA){
			Long j = y;
			while(j < MX_Y + EXTRA){
				tree[x][j] += add;
				j += (j & -j);
			}
			x += (x & -x);
		}
	}
	
	//you can only use one of this range implementations
	Long query(Long x1, Long y1,Long x2, Long y2){
		return query(x2 , y2) - query(x2 , y1 - 1) - query(x1 - 1 , y2) + query(x1 - 1 , y1 - 1);
	}
	
	void update(Long x1, Long y1, Long x2 , Long y2, Long add){
		update(x1 , y1 , add);
		update(x2 + 1 , y1, -add);
		update(x1, y2 + 1 , -add);
		update(x2 + 1 , y2 + 1 , add);
	}	
}ft;

mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

long double getTime(){
	return chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
}

void solve(){
	Long n = 4096;
	Long m = 4096;
	Matrix A = getMatrix(n , m);

	ft.clear(n , m);
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j < m; j++){
			A[i][j] = random(-10, 10);
			ft.update(i , j , A[i][j]);
		}
	}
	st.build(A);
	
	Long q = 1;
	long double updateTimeFT = 0;
	long double updateTimeST = 0;
	long double queryTimeFT = 0;
	long double queryTimeST = 0;
	
	REP(i , q){
		Long posX, posY , val;
		posX = random(0 , n - 1);
		posY = random(0 , m - 1);
		val = random(-100, 100);
		cntUpdate = 0;
		long double low = getTime();
		st.update(posX, posY, val);
		long double  high = getTime();
		
		assert(cntUpdate <= (ceil(log2(n) + 1) * ceil(log2(m) + 1)));
		updateTimeST += high - low;
		
		
		Long cur = ft.query(posX, posY, posX, posY);
		low = getTime();
		ft.update(posX, posY, val - cur);
		high = getTime();
		updateTimeFT += high - low;
		
		Long x1, y1 , x2 , y2;
		/*x1 = random(0, n - 1);
		x2 = random(x1 , n - 1);
		y1 = random(0 , m - 1);
		y2 = random(y1 , m - 1);*/
		x1 = 1;
		x2 = n - 2;
		y1 = 1;
		y2 = m - 2;
		
		low = getTime();
		Long ftQuery = ft.query(x1 , y1 , x2 , y2);
		high = getTime();
		queryTimeFT += high - low;
		
		cntQuery1 = cntQuery2 = 0;
		low = getTime();
		Long stQuery = st.query(x1, x2, y1 , y2);
		high = getTime();
		debug(cntQuery1);
		debug(cntQuery2);
		Long cntQuery = cntQuery1 + cntQuery2;
		assert(cntQuery <= 7 * (ceil(log2(n) ) * ceil(log2(m) )));
		
		queryTimeST += high - low;
		assert( ftQuery == stQuery);
		
	}
	updateTimeFT /= q;
	updateTimeST /= q;
	queryTimeFT /= q;
	queryTimeST /= q;

	/*debug(updateTimeFT);
	debug(updateTimeST);
	debug(queryTimeFT);
	debug(queryTimeST);*/
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T = 1;
	REP(t , T) solve();

	return 0;
}
