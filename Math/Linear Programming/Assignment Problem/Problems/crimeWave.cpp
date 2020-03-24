#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

//http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1687

typedef long long Long;
typedef long double Double;
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

Long afterPoint(string &s){
	for(Long i = 0; i < s.size(); i++){
		if(s[i] == '.'){
			return (Long)s.size() - i - 1;
		} 
	}
	return 0;
}

Long conv(string &s, Long pot){
	Long cnt = 0;
	Long num = 0;
	for(Long i = 0; i < s.size(); i++){
		if(s[i] == '.'){
			cnt = (Long)s.size() - i - 1;
		} else {
			num = num * 10 + (s[i] - '0');
		}	
	}
	cnt -= pot;
	REP(i , cnt) num *= 10;
	return num;
}
   
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Long n , m;
	//freopen("output.txt", "w", stdout);
	while(true){
		cin >> n >> m;
		if(n == 0 && m == 0) break;
		Matrix M(n, vector<Long>(m));
		vector<vector<string>> A(n , vector<string>(m));
		Long maxPot = 0;
		REP(i , n){
			REP(j , m){
				cin >> A[i][j];
				maxPot = max(maxPot , afterPoint(A[i][j]));
			}
		}
		REP(i , n) {
			REP(j , m){
				M[i][j] = conv(A[i][j] , maxPot);
			}
		}
		Double ans = 1.0 * hg.assign(M) / n;
		REP(i , maxPot) ans /= 10.0;
		ans = floor(ans*100.0+0.5+1e-9)/100.0;
		cout << fixed << setprecision(2) << ans << endl;
	}
	
	return 0;
}
