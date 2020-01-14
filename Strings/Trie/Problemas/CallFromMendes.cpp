#include <bits/stdc++.h>
#define pb push_back
#define REP(i , n) for(Long i = 0; i < (Long)n; i++)
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

typedef int Long;

const Long MX = 1e6 + 2;
const Long ALPH = 26;
const Long INF = 1e9;

//https://codeforces.com/gym/102448/problem/C

struct Trie{
	Long memo[MX][ALPH];
	pair<Long,Long> opt[MX];
	Long p[MX];
	Long cnt[MX];
	Long cntTerminal[MX];
	
	Long nodos = 1;
	
	void init(){
		REP(i , MX){
			opt[i] = {INF, -1};
		}
	}
	
	void addWord(string &s, Long q){
		int sz = s.size();
		int u = 0;
		for(int i = 0; i < sz; i++){
			Long c = s[i] - 'a';
			if(memo[u][c] == 0){
				memo[u][c] = nodos;
				p[nodos] = u;
				nodos++;
			}
			
			u = memo[u][c];
			cnt[u]++;
		}
		cntTerminal[u]++;
		
		opt[u] = {0, q};
		while(u != 0){
			u = p[u];
			if(u == 0) break;
			for(Long i = 25; i >= 0; i--){
				Long v = memo[u][i];
				if(v != 0){
					if(opt[v].first + 1 <= opt[u].first){
						opt[u].first = opt[v].first + 1;
						opt[u].second = opt[v].second;
					}
				}
			}
		}
	}
	
	void deleteWord(string &s){
		int sz = s.size();
		int u = 0;
		for(int i = 0; i < sz; i++){
			Long c = s[i] - 'a';
			assert(memo[u][c] != 0);
			u = memo[u][c];
		}
		cntTerminal[u]--;
		while(u != 0){
			if(cntTerminal[u] == 0) opt[u] = {INF, -1};
			cnt[u]--;

			for(Long i = 25; i >= 0; i--){
				Long v = memo[u][i];
				if(v != 0){
					if(cnt[v] == 0){
						memo[u][i] = 0;
					} else {
						if(opt[v].first + 1 <= opt[u].first){
							opt[u].first = opt[v].first + 1;
							opt[u].second = opt[v].second;
						}
					}
				}
			}
			u = p[u];
		}
	}
	
	Long getAns(string &s){
		int sz = s.size();
		int u = 0;
		for(int i = 0; i < sz; i++){

			Long c = s[i] - 'a';
			if(memo[u][c] == 0){
				return -1;
			}
			u = memo[u][c];
		}
		return opt[u].second;
	}
}trie;

const Long MX2 = 1e5 + 2;
string queries[MX2];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	trie.init();
	Long Q;
	cin >> Q;
	REP(q , Q){
		Long x;
		cin >> x;
		if(x == 1){
			string s;
			cin >> s;
			trie.addWord(s, q + 1);
			queries[q] = s;
		} else if(x == 2){
			Long i;
			cin >> i;
			i--;
			trie.deleteWord(queries[i]);
		} else {
			string s;
			cin >> s;
			cout << trie.getAns(s) << "\n";	
		}
	}
	
	
	return 0;
}
