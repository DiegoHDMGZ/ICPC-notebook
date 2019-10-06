#include <bits/stdc++.h>
#define debug(x) cout << "#x" << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

//grundy(A + B) = grundy(A) xor grundy(B)
//Cualquier estado "v" en el juego, el cual puede alcanzar varios estados "vi"
//es equivalente al juego del nim con una pila de tamaño igual al mex del conjunto de todos los vi

//Una posicion es ganadora si y solo si grundy(pos) > 0, caso contrario es perdedora

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
	for(todas las transaciones de estado){
		Long g = 0;
		for(todos la suma de juegos de ese estado){
			g = g xor grundy(juego);
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
