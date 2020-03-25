#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
#define Mat(a, b) Matrix(a , vector<Long>(b))
using namespace std;

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1829

typedef long long Long;
typedef vector<vector<Long>> Matrix;
typedef string string;

const Long INF = 1e18;
const Long MX = 1603;
const Long dummy = INF / 2; 

/*if the objective function is max , change dummy for -INF
and multiply the matrix by -1*/

struct Hungarian{
	Long matchRow[MX];
	Long matchCol[MX];
	
	void makeSquare(Matrix &A){
		Long n = A.size();
		Long m = A[0].size();
		for(Long i = 0; i < n; i++){
			for(Long j = 0; j < n - m; j++){
				A[i].push_back(dummy);
			}
		}
	}
	
	Long assign(Matrix A){ //O(n^3)
		Long n = A.size();
		Long m = A[0].size();
		if(n > m){
			makeSquare(A);
			m = n;
		}

		vector<Long> colAdd(m, 0);
		vector<Long> rowAdd(n , 0);
		fill(matchRow, matchRow + n, -1); //match for i-th row
		fill(matchCol, matchCol + m , -1);//match for i-th col
		
		for(Long i = 0; i < n; i++){
			vector<bool> forbidden(m, false); //forbidden column
			vector<Long> parent(n, -1); //parent in conflict tree
			vector<Long> minVal(m, INF); //minVal in column
			vector<Long> minPos(m, -1); // row where the min value is achieved
			Long cur = i;
			while(true){
				Long minCol = -1;
				//update minVal and minPos and find minCol
				for(Long j = 0; j < m; j++){
					if(!forbidden[j]){
						Long val = A[cur][j] + rowAdd[cur] + colAdd[j];
						if(val < minVal[j]){
							minVal[j] = val;
							minPos[j] = cur;
						}
						if(minCol == -1 || minVal[j] < minVal[minCol]){
							minCol = j;
						}
					}
				}
				//decrease every considered row
				//increase every forbidden col
				Long x = minVal[minCol];
				for(Long j = 0; j < m; j++){
					if(forbidden[j]){
						colAdd[j] += x;
						rowAdd[matchCol[j]] -= x;
					} else {
						minVal[j] -= x;
					}
				}
				rowAdd[i] -= x;
				if(matchCol[minCol] == -1){
					//solve conflicts
					Long curRow = minPos[minCol];
					Long oldMatch = matchRow[curRow];
					matchCol[minCol] = curRow;
					matchRow[curRow] = minCol;

					while(curRow != i){
						curRow = parent[curRow];
						Long assigned = oldMatch;
						oldMatch = matchRow[curRow];
						matchCol[assigned]	= curRow;
						matchRow[curRow] = assigned;
					}
					break;
				} else {
					forbidden[minCol] = true;
					cur = matchCol[minCol]; //transition
					parent[cur] = minPos[minCol]; //create conflict
				}
			}
		}
		
		Long ans = 0;
		for(Long i = 0; i < n; i++){
			Long j = matchRow[i];
			if(j != -1 && A[i][j] < dummy / 2 ){
				ans += A[i][j];
			}
		}
		return ans;
	}	
}hg;

struct Graph{
	vector<Long> adj[MX];
	vector<Long> d;
	
	void clear(Long n){
		REP(i , n){
			adj[i].clear();
		}
	}
	
	void addEdge(Long u , Long v){
		adj[u].pb(v);
	}
	
	void bfs(Long s , Long n){
		d = vector<Long>(n, INF);
		queue<Long> q;
		q.push(s);
		d[s] = 0;
		
		while(!q.empty()){
			Long u = q.front();
			q.pop();
			for(Long v : adj[u]){
				if(d[v] == INF){
					d[v] = d[u] + 1;
					q.push(v);
				}
			}
		}
	}
}G;

Long n , m;

Long conv(Long i , Long j){
	return i * m + j;
}

bool valid(Long i , Long j){
	return i >= 0 && j >= 0 && i < n && j < m;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	
	REP(t, T){
		cin >> n >> m;
		G.clear(n * m);
		vector<string> A(n);
		REP(i , n){
			cin >> A[i];
		}
		vector<Long> box;
		vector<Long> target;
		REP(i , n){
			REP(j , m){
				if(A[i][j] != '#'){
					for(Long a = -1; a <= 1; a++){
						for(Long b = -1; b <= 1; b++){
							if(abs(a) + abs(b) == 1 && valid(i + a , j + b)){
								if(A[i + a][j + b] != '#'){
									G.addEdge(conv(i , j), conv(i +a , j + b));
								}
							}
						}
					}
					
					if(A[i][j] == 'B'){
						box.pb(conv(i, j ));
					}
					if(A[i][j] == 'X'){
						target.pb(conv(i, j ));
					}
				}
			}
		}
		Matrix C = Mat(box.size(), target.size());
		
		for(Long i = 0; i < box.size(); i++){
			G.bfs(box[i] , n * m);
			for(Long j = 0; j < target.size(); j++){
				C[i][j] = G.d[target[j]];
			}
		}
		
		cout << hg.assign(C) << "\n";
		
	}

	return 0;
}
