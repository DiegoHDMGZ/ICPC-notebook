#include <bits/stdc++.h>

typedef long long Long;
// Binary Indexed Tree
// tree[i] = f[i - 2^r + 1] + ... + f[i]
//ultimo bit encendido = x & -x;

using namespace std;

const Long MX = 100000;
const Long EXTRA = 6;
struct FenwickTree{
	Long tree[MX+EXTRA];
	
	void clear(Long n){ //O(n)
		for(Long i = 0; i < n + EXTRA; i++){
			tree[i] = 0;
		}
	}
	
	Long query(Long i){ //O(log n)
		i += EXTRA;
		Long sum = 0;
		while(i > 0){
			sum += tree[i];
			i -= (i & -i);
		}
		return sum;
	}
	
	void update(Long i , Long delta){ //O(log MX)
		i += EXTRA;
		while(i < MX + EXTRA){
			tree[i] += delta;
			i += (i & -i);
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

