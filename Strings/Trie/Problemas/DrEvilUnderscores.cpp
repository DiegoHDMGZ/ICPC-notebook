#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://codeforces.com/contest/1285/problem/D

const Long MX = 4e6 + 10; //Suma de caracteres de todas las palabras + 1 : cantidad maxima de nodos
const Long ALPH = 3; // tamaño del alfabeto

const Long INF= 1e18;
const Long BITS = 30;

void turnOn(Long &x, Long i){
	x = x | (1LL << i);
}

struct Trie{
	Long memo[MX][ALPH];
	Long children[MX];
	Long score[MX];
	Long nodos = 1;
	
	
	void dfs(Long u = 0, Long h = 0){
		bool first = true;
		for(Long i = 0; i < 2; i++){
			if(memo[u][i] != 0){
				dfs(memo[u][i], h + 1);
				if(first){
					first = false;
					score[u] = score[memo[u][i]];
				} else {
					score[u] = min(score[u] , score[memo[u][i]]);
				}
				
			}
			
		}
		if(children[u] == 2 ) turnOn(score[u], BITS - h );
	}
	
	void addWord(deque<Long> &s){
		int sz = s.size();
		int u = 0;
		
		for(Long i = 0; i < sz; i++){
			Long c = s[i];
			if(memo[u][c] == 0){
				memo[u][c] = nodos;
				children[u]++;
				nodos++;
			}
			u = memo[u][c];
		}
	}
	
	Long getAns(){
		Long u = 0;
		Long ans = 0;
		while(children[u] > 0){
			//debug(u);
			if(children[u] == 1){
				ans = ans * 2;
				if(memo[u][0] != 0) u = memo[u][0];
				else u = memo[u][1];
			} else {
				ans = ans * 2 + 1;
				if(score[memo[u][0]] < score[memo[u][1]]){
					u = memo[u][0];
				} else {
					u = memo[u][1];
				}
			}
		}
		return ans;
	}

		
}trie;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n;
	cin >> n;
	vector<Long> v;
	REP(i , n){
		Long x;
		cin >> x;
		v.pb(x);
		deque<Long> binary;
		REP(b , BITS){
			binary.push_front(x % 2);
			x /= 2;
		}
		trie.addWord(binary);
	}
	trie.dfs(0);
	cout << trie.getAns() << endl;

	return 0;
}
