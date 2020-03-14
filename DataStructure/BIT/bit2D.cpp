#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MX_X = 1000;
const Long MX_Y = 1000;
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
	
	Long query(Long x, Long y){ // O((log n)^2)
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
	
	Long query(Long x1, Long y1,Long x2, Long y2){
		return query(x2 , y2) - query(x2 , y1 - 1) - query(x1 - 1 , y2) + query(x1 - 1 , y1 - 1);
	}
	
	void update(Long x, Long y, Long add){ // O((log n)^2)
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
}ft;

int main() {
	return 0;
}

