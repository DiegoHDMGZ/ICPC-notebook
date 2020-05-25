#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MXX = 1000;
const Long MXY = 1000;
Long combine(Long x , Long y) {
	return x + y;
}

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

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

/*
2 2
1 8
50 300
Q 0 0 1 1
Q 1 0 1 0
-----------
5 3
5 1 3
2 7 -1
8 2 -2
9 -4 2
0 3 1    

*/
	Long n,m;
	cin >> n >> m;

	vector< vector< Long > > a (n , vector<Long> (m));
	
	REP(i, n){
		REP(j, m){
			cin >> a[i][j];
		}
	}

	st.build(a);

	while (true){
		char c;
		cin >> c;
		if (c == 'Q'){
			Long x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;

			cout << st.query(x1, x2, y1, y2) << endl;
		}
		else{
			Long posX, posY, valor;
			cin >> posX >> posY >> valor;

			st.update(posX, posY, valor);
		}
	}

	return 0;
}
