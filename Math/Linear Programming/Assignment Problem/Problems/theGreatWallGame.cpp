#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1277

typedef vector<vector<Long>> Matrix;
const Long INF = 1e18;
const Long MX = 1e3;
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n;
	Long cnt = 1;
	bool first = true;
	while(cin >> n){
		if(n == 0) break;
		if(first) first = false;
		else cout << "\n";
		vector<pair<Long,Long>> v(n);
		REP(i , n){
			cin >> v[i].first >> v[i].second;
			v[i].first--;
			v[i].second--;
		}
		Long ans = INF;
		
		Matrix A(n , vector<Long>(n));
		for(Long row = 0; row < n; row++){
			REP(i , n){
				REP(j , n){
					A[i][j] = abs(v[i].first - row) + abs(v[i].second - j);
				}
			}
			ans = min(ans , hg.assign(A));
		}
		
		for(Long col = 0; col < n; col++){
			REP(i , n){
				REP(j , n){
					A[i][j] = abs(v[i].first - j) + abs(v[i].second - col);
				}
			}
			ans = min(ans , hg.assign(A));
		}
		
		for(Long diag = 0; diag < n; diag++){
			REP(i , n){
				A[i][diag] = abs(v[i].first - diag) + abs(v[i].second - diag);
			}
			ans = min(ans , hg.assign(A));
			REP(i , n){
				A[i][diag] = abs(v[i].first - diag) + abs(v[i].second - (n - diag - 1));
			}
			ans = min(ans , hg.assign(A));
		}
		cout << "Board " << cnt << ": " << ans << " moves required.\n"; 
		cnt++;
	}

	return 0;
}
