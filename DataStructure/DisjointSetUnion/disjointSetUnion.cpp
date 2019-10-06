#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
const Long MX = 100000;

struct DSU{
	Long parent[MX];
	Long size[MX];
	
	void make_set(Long v){ //O(1)
		parent[v] = v;
		size[v] = 1;
	}
	
	Long find(Long v){ //O(1) amortized
		if(v==parent[v]){
			return v;
		}
		
		return parent[v] = find(parent[v]);
	}
	
	void join(Long a, Long b){ //O(1) amortized
		a = find(a);
		b = find(b);
		
		if(a != b){
			if(size[a] < size[b]){
				swap(a,b);
			}
			parent[b] = a;
			size[a] += size[b];
		}
	}
} dsu;

int main() {
	return 0;
}


