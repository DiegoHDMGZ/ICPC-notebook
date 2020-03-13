#include <bits/stdc++.h>

typedef long long Long;
// Binary Indexed Tree
// tree[i] = f[i - 2^r + 1] + ... + f[i]
//last significant bit = x & -x;

using namespace std;

const Long MX = 1e5;
const Long EXTRA = 6;
struct FenwickTree{
	Long tree[MX+EXTRA];
	
	void clear(Long n){ //O(n)
		for(Long i = 0; i < n + EXTRA; i++){
			tree[i] = 0;
		}
	}
	
	Long query(Long x){ //O(log n)
		x += EXTRA;
		Long sum = 0;
		while(x > 0){
			sum += tree[x];
			x -= (x & -x);
		}
		return sum;
	}
	
	void update(Long x , Long delta){ //O(log MX)
		x += EXTRA;
		while(x < MX + EXTRA){
			tree[x] += delta;
			x += (x & -x);
		}
	}
	
	void update(Long l , Long r, Long delta){
		update(l , delta);
		update(r + 1 , -delta);
	}		
} ft;

int main() {
	return 0;
}

