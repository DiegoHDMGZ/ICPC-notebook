#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 1e5;

struct SegmentTree{
	Long t[4 * MAX];
	Long maxN;
	
	void setN(Long x) {
		maxN = x;
	}
	
	void clear() {
		for(Long i = 0; i < 4 * MAX; i++) {
			t[i] = 0;
		}
		maxN = 0;
	}
	
	void build(vector<Long> &a, Long v = 1, Long tl = 0, Long tr = MAX - 1){ //O(n)
		if(tl == tr){
			t[v] = a[tl];
		}
		else{
			Long tm = (tl + tr) / 2;
			build(a , 2 * v , tl , tm);
			build(a , 2 * v + 1 , tm + 1 , tr);
			t[v] = t[2 * v] + t[2 * v + 1];
		}
	}
	
	void build(vector<Long> &a) {
		maxN = a.size();
		assert(maxN > 0);
		build(a , 1 , 0 , maxN - 1);
	}
	
	Long findInd(Long suma, Long v , Long tl, Long tr ){ //O(logn)
		//minimo indice donde la suma acumulada es >= suma. Solo funciona si el arreglo es de numeros no negativos
		if(suma > t[v]){
			return -1;
		}
		if(tl == tr){
			return tl;
		}
		Long tm= (tl + tr) / 2;
		if(t[2 * v] >= suma){
			return findInd(suma , 2 * v , tl , tm);
		}
		else{
			return findInd(suma - t[2 * v] , 2 * v + 1, tm + 1 ,tr);
		}
	}
	
	Long findInd(Long suma) {
		assert(maxN > 0);
		return findInd(suma , 1 , 0 , maxN - 1);
	}
	
	void update(Long pos, Long valor, Long v , Long tl , Long tr ){ //O(logn)
		if(tl == tr){
			t[v] = valor;
		}
		else{
			Long tm = (tl + tr) / 2;
			if(pos <= tm){
				update(pos, valor ,2 * v, tl, tm);
			}
			else{
				update(pos, valor, 2 * v + 1 , tm + 1, tr);
			}
			t[v] = t[2 * v] + t[2 * v + 1];
		}
	}
	
	void update(Long pos, Long valor) {
		assert(maxN > 0);
		update(pos , valor, 1 , 0 , maxN - 1);
	}
} st;

int main() {
	return 0;
}
