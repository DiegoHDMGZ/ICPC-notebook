#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MXX = 1000;
const Long MXY = 1000;
//Long a[MXX][MXY];

struct SegmentTree{
	Long t[4 * MXX][4 * MXY];
	Long maxN, maxM;
	
	void build_y(vector< vector < Long > > &a , Long vx, Long lx, Long rx, Long vy , Long ly, Long ry ) {

		if (ly == ry){
			if (lx == rx){
				t[vx][vy] = a[lx][ly];
			}
			else{
				t[vx][vy] = t[2 * vx][vy] + t[2 * vx + 1][vy];
			}
		}
		else{
			Long my = (ly + ry) / 2;
			build_y(a , vx, lx, rx, 2 * vy, ly, my);
			build_y(a, vx, lx, rx, 2 * vy + 1, my + 1, ry);
			t[vx][vy] = t[vx][2 * vy] + t[vx][2 * vy + 1];
		}
	}

	void build(vector< vector < Long > > &a , Long vx , Long lx , Long rx , Long ry) { //O(mn)
		if (lx != rx){
			Long mx = (lx + rx) / 2;
			build(a , 2 * vx, lx, mx , ry);
			build(a, 2 * vx + 1, mx + 1, rx, ry);
		}
		build_y(a, vx, lx, rx , 1 , 0 , ry);
	}
	
	void build(vector< vector < Long > > &a) {
		maxN = a.size();
		maxM = a[0].size();
		build(a, 1 , 0 , maxN - 1 , maxM - 1);
	}

	Long sum_y(Long vx, Long ly, Long ry, Long vy , Long tly , Long try_ ) {
		if (ly > ry) {
			return 0;	
		}

		if (ly == tly && try_ == ry) {
			return t[vx][vy];
		}

		Long tmy = (tly + try_) / 2;

		return sum_y(vx, ly, min(ry, tmy), 2 * vy, tly, tmy) + sum_y(vx, max(ly, tmy + 1), ry, 2 * vy + 1, tmy + 1, try_);
	}

	Long sum(Long lx, Long rx, Long ly, Long ry, Long vx , Long tlx , Long trx , Long try_) { //O(log n log m)
		if (lx > rx) {
			return 0;
		}

		if (lx == tlx && rx == trx) {
			return sum_y(vx, ly, ry , 1 , 0 , try_);
		}

		Long tmx = (tlx + trx) / 2;

		return sum(lx, min(rx, tmx), ly, ry, 2 * vx, tlx, tmx , try_) + sum(max(lx, tmx + 1), rx, ly, ry, 2 * vx + 1, tmx + 1, trx , try_);
	}
	
	Long sum(Long lx ,Long rx, Long ly, Long ry) {
		return sum(lx , rx , ly, ry , 1 , 0 , maxN - 1 , maxM - 1);
	}

	void update_y(Long posX, Long posY, Long valor, Long vx, Long tlx, Long trx, Long vy, Long tly , Long try_) {
		if (tly == try_) {
			if (tlx == trx) {
				t[vx][vy] = valor;
			}
			else {
				t[vx][vy] = t[2 * vx][vy] + t[2 * vx + 1][vy];
			}
		}
		else {
			Long tmy = (tly + try_) / 2;
			if (posY <= tmy) {
				update_y(posX, posY, valor, vx, tlx, trx, 2 * vy, tly, tmy);
			}
			else {
				update_y(posX, posY, valor, vx, tlx, trx, 2 * vy + 1, tmy + 1, try_);
			}
			t[vx][vy] = t[vx][2 * vy] + t[vx][2 * vy + 1];
		}
	}

	void update(Long posX, Long posY, Long valor, Long vx , Long tlx , Long trx  , Long try_) {
		if (tlx != trx) {
			Long tmx = (tlx + trx) / 2;
			if (posX <= tmx) {
				update(posX, posY, valor, 2 * vx, tlx, tmx , try_);
			}
			else{
				update(posX, posY, valor, 2 * vx + 1, tmx + 1, trx, try_);
			}
		}

		update_y(posX, posY, valor, vx, tlx, trx , 1 , 0 , try_);
	}
	
	void update(Long posX, Long posY, Long valor) {
		update(posX, posY, valor , 1 , 0 , maxN - 1 , maxM - 1);
	}
} st;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

/*
2 2
1 8
50 300
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

			cout << st.sum(x1, x2, y1, y2) << endl;
		}
		else{
			Long posX, posY, valor;
			cin >> posX >> posY >> valor;

			st.update(posX, posY, valor);
		}
	}

	return 0;
}
