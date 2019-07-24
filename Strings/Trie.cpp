#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 1e5; //Suma de caracteres de todas las palabras + 1 : cantidad maxima de nodos
const Long ALPH = 26; // tamaño del alfabeto

struct Trie{
	Long memo[MAX][ALPH];
	bool term[MAX]; //indica si es nodo terminal
	Long nodos = 1;
	
	void init(Long cnt){
		nodos = 1;
		for(Long i = 0; i < cnt; i++){
			term[i] = 0;
			for(int j = 0; j < ALPH; j++){
				memo[i][j] = 0;
			}
		}
	}
	
	void addWord(string &s){
		int sz = s.size();
		int u = 0;
		
		for(Long i = 0; i < sz; i++){
			Long c = s[i] - 'a';
			if(memo[u][c] == 0){
				memo[u][c] = nodos++;
			}
			u = memo[u][c];
		}
		term[u] = true;
	}
	
	bool isPrefix(string &s){
		Long sz = s.size();
		Long u = 0;
		
		for(Long i = 0; i < sz; i++){
			Long c = s[i] - 'a';
			if(memo[u][c] == 0){
				return false;
			}
			u = memo[u][c];
		}
		return true;
	}
	
	bool isWord(string &s){
		Long sz = s.size();
		Long u = 0;
		
		for(Long i = 0; i < sz; i++){
			Long c = s[i] - 'a';
			if(memo[u][c] == 0){
				return false;
			}
			u = memo[u][c];
		}
		return term[u]; //validar si es nodo terminal
	}
		
}trie;



int main() {
	string A[] = {"pikachu", "mama", "mar","marco", "margarita", "pikachu"};
	int n = 6;
	for(Long i = 0; i < n; i++) trie.addWord(A[i]);
	while(true){
		string s;
		cin >> s;
		cout << "Is Prefix : " << trie.isPrefix(s) << endl;
		cout << "Is Word : " << trie.isWord(s) << endl;
	}
	
	return 0;
}


