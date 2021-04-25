#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

struct hash_pair { 
	template <class T1, class T2> 
	size_t operator()(const pair<T1, T2>& p) const
	{ 
		auto hash1 = hash<T1>{}(p.first); 
		auto hash2 = hash<T2>{}(p.second); 
		return hash1 ^ hash2; 
	} 
};

unordered_map<pair<Long,Long> , Long , hash_pair> m;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	return 0;
}
