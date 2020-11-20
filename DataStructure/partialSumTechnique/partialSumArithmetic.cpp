#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const Long MX = 2001;

struct PartialSum{
	Long A[MX];
	Long difConst[MX + 1];
	Long difArith[MX + 1];
	
	void clear(Long n) {
		for (int i = 0; i < n; i++) {
			difConst[i] = 0;
			difArith[i] = 0;
			A[i] = 0;
		}
	}
	
	void build(vector<Long> &v) {
		difConst[0] = 0;
		difArith[0] = 0;
		for (Long i = 0; i < v.size(); i++) {
			difConst[i + 1] = 0;
			difArith[i + 1] = 0;
			updateConstant(i , i, v[i]);
		}
	}
	
	void updateConstant(Long l, Long r, Long delta) { //O(1)
		//a[i] += delta
		difConst[l] += delta;
		difConst[r + 1] -= delta;
	}
	
	void updateIncreasing(Long l, Long r, Long delta, Long c = 0) { //O(1)
		//a[i] += delta * (i - l + 1) + c
		difArith[l] += delta;
		difArith[r + 1] -= delta;
		updateConstant(l , r, c);
		difConst[r + 1] -= delta * (r - l + 1);
	}
	
	void updateDecreasing(Long l, Long r, Long delta, Long c = 0) { //O(1)
		//a[i] += delta * (r - i + 1) + c
		updateConstant(l, r, delta * (r - l + 2));
		updateIncreasing(l , r , -delta); 
		updateConstant(l , r, c);
	}

	void update(Long n) { //O(n)
		//last update before answering queries
		Long acumConst = 0;
		Long cntArith = 0;
		Long acumArith = 0;
		for (Long i = 0; i < n; i++) {
			acumConst += difConst[i];
			cntArith += difArith[i];
			acumArith += cntArith;
			A[i] = acumConst + acumArith;
		}
	}
	
	Long query(Long pos) { //O(1)
		return A[pos];
	}
}ps;

struct Brute{
	Long A[MX];
	
	void clear(Long n) {
		for (int i = 0; i < n; i++) {
			A[i] = 0;
		}
	}
	
	void updateConstant(Long l, Long r, Long delta) { //O(1)
		//a[i] += delta
		for (int i = l; i <= r; i++) {
			A[i] += delta;
		}
	}
	
	void updateIncreasing(Long l, Long r, Long delta, Long c = 0) { //O(1)
		//a[i] += delta * (i - l + 1) + c
		for (int i = l; i <= r; i++) {
			A[i] += delta * (i - l + 1) + c;
		}
	}
	
	void updateDecreasing(Long l, Long r, Long delta, Long c = 0, bool doDebug = false) { //O(1)
		//a[i] += delta * (r - i + 1) + c
		for (int i = l; i <= r; i++) {
			A[i] += delta * (r - i + 1) + c;
		}
	}
	
	Long query(Long pos) { //O(1)
		return A[pos];
	}
}brute;

mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T = 1005;
	REP(t, T) {
		Long n = random(1, 300);
		Long Q = random(1 , 200);
		brute.clear(n);
		ps.clear(n);
		REP(q, Q) {
			Long type = random(0, 2);
			if (type == 0) {
				Long l, r, c;
				l = random(0, n - 1);
				r = random(l, n - 1);
				c = random(-200, 200);
				brute.updateConstant(l ,r , c);
				ps.updateConstant(l ,r , c);
			} else if (type == 1) {
				Long l, r, delta, c;
				l = random(0, n - 1);
				r = random(l, n - 1);
				delta = random(-200, 200);
				c = random(-20, 20
				0);
				brute.updateIncreasing(l ,r , delta, c);
				ps.updateIncreasing(l ,r , delta, c);
			} else {
				Long l, r, delta, c;
				l = random(0, n - 1);
				r = random(l, n - 1);
				delta = random(-20, 20);
				c = random(-20, 20);
				brute.updateIncreasing(l ,r , delta, c);
				ps.updateIncreasing(l ,r , delta, c);
			}
		}
		ps.update(n);
		REP(i, n) {
			assert(brute.query(i) == ps.query(i));
		}
	}

	return 0;
}
