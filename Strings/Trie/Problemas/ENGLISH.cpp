#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://www.codechef.com/JAN20A/problems/ENGLISH

const Long MX = 1e5 + 2; //Suma de caracteres de todas las palabras + 1 : cantidad maxima de nodos
const Long ALPH = 26 * 26; // tamaño del alfabeto

struct Trie{
	Long memo[MX][ALPH];
	Long cnt[MX];
	Long h[MX];
	Long p[MX];
	Long nodos = 1;
	Long outdegree[MX];
	Long acum[MX];
	
	void init(){
		
		for(Long i = 0; i < nodos; i++){
			cnt[i] = 0;
			p[i] = -1;
			h[i] = 0;
			acum[i] = 0;
			outdegree[i] = 0;
			for(int j = 0; j < ALPH; j++){
				memo[i][j] = 0;
			}
		}
		nodos = 1;
		h[0] = 0;
	}
	
	void addWord(string &s){
		int sz = s.size();
		int u = 0;
		cnt[u]++;
		for(Long i = 0; i < sz; i++){
			Long c1 = s[i] - 'a';
			Long c2 = s[sz - i - 1] - 'a';
			Long c = 26 * c1 + c2;
			if(memo[u][c] == 0){
				memo[u][c] = nodos++;
				outdegree[u]++;
			}
			p[memo[u][c]] = u;
			h[memo[u][c]] = h[u] + 1;
			u = memo[u][c];
			cnt[u]++;
		}
	}

		
}trie;

void solve(){
	trie.init();
	Long n;
	cin >> n;
	REP( i , n){
		string s;
		cin >> s;
		trie.addWord(s);
	}
	deque<Long> q;
	REP(i , trie.nodos){
		if(trie.outdegree[i] == 0){
			q.pb(i);
		}
	}
	
	Long ans = 0;
	while(!q.empty()){
		
		Long u = q.front();
		q.pop_front();
		
		if(trie.cnt[u] == 0) continue;
		
		trie.cnt[u] -= trie.acum[u];
	
		ans += (trie.cnt[u] / 2) * trie.h[u] * trie.h[u];
		
		Long v = trie.p[u];
		
		if(v != -1){
			trie.acum[v] += trie.cnt[u] - (trie.cnt[u] % 2);
			trie.acum[v] += trie.acum[u];
			trie.outdegree[v]--;
			if(trie.outdegree[v] == 0){
				q.pb(v);
			}
		} 
		trie.cnt[u] = 0;
	}
	cout << ans << "\n";
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	REP(t, T){
		solve();
	}

	return 0;
}
