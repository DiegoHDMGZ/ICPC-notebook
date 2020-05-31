#include <bits/stdc++.h>
#define debug(x) cout << "#x" << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;


//In any impartial game , let define an state "v" in the game that can reach other states "vi"
//this is equivalent to the game of Nim with one pile of size mex(set of vi)
//this number is call grundy

//A position is a winner position iff grundy(pos) > 0

//For sum of games : grundy(A + B) = grundy(A) xor grundy(B)

Long mex(set<Long> &s){
	Long ans = 0;
	for(Long x : s){
		if(ans != x){
			return ans;
		}
		ans++;
	}
	return ans;
}

Long grundy(Long n) { //O(N + M log M)
	set<Long> s;
	for(all transitions){
		Long g = 0;
		for(all splitted games){
			g = g xor grundy(game);
		}
		s.insert(g);
	}
	return mex(s);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	return 0;
}
