#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MAXX = 1000;
const Long MAXY = 1000;

struct FenwickTree2D{
	Long tree[MAXX+1][MAXY+1];
	
	FenwickTree2D(){ //O(MAXX * MAXY)
		for(Long i = 0; i<= MAXX; i++){
			for(Long j = 0; j <= MAXY; j++){
				tree[i][j] = 0;	
			}
		}
	}
	
	void build(){ //O(MAXX * MAXY)
		for(Long i = 0; i<= MAXX; i++){
			for(Long j = 0; j <= MAXY; j++){
				tree[i][j] = 0;	
			}
		}
	}
	
	Long query(Long i, Long j){ // O(log i * log j)
		Long sum = 0;
		while(i > 0){
			Long _j = j;
			while(_j > 0){
				sum += tree[i][_j];
				_j -= (_j & -_j);
			}
			i -= (i & -i);
		}
		return sum;
	}
	
	Long query(Long x1, Long y1,Long x2, Long y2){
		return query(x2 , y2) - query(x2 , y1 - 1) - query(x1 - 1 , y2) + query(x1 - 1 , y1 - 1);
	}
	
	void update(Long i, Long j, Long delta){ //O(log MAXX * log MAXY)
		while(i <= MAXX){
			Long _j = j;
			while(_j <= MAXY){
				tree[i][_j] += delta;
				_j += (_j & -_j);
			}
			i += (i & -i);
		}
	}		
}ft;

int main() {
	return 0;
}

