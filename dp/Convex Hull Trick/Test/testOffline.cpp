#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

/*
We have "n" linear functions yi = mi x + bi
There are queries for the maximum y for a given x among all the functions. 

For minimum just put the negative of mi and bi.
Or change the comparator sign in cmp, and in check and in same slope case
*/

const Long MX = 2e5;
struct Line{
	Long m , b;
	Line(){}
	Line(Long m , Long b) : m(m), b(b){}
};

bool cmp(const Line &L1, const Line &L2){
	if(L1.m == L2.m){
		return L1.b < L2.b;
	}
	return L1.m < L2.m;
}

struct CHT{
	vector<Line> envelope;
	
	Long f(Long pos , Long x){
		return envelope[pos].m * x + envelope[pos].b;
	}

	bool check( Long med, Long x ){
		return f(med + 1, x) - f(med , x ) <= 0;
	}

	Long search(  Long ini , Long fin, Long x ){ //O(logn)
		// F F F... V V V
		if(!check(fin - 1, x)) return f(fin, x); //todos F
		if(check(ini, x)) return f(ini, x); //todos V
		while(fin - ini > 1){ // hay mas de 2 valores
			Long med= ini + (fin - ini) / 2;
			
			if(check( med , x )){
				fin = med;
			} 
			else {
				ini = med;
			}
		}
		//hay 2 valores ini es F y fin es V
		return f(fin, x);
	}

	bool bad(Line l1, Line l2, Line l3){
		//tells if l2 is bad an can be eliminated by l3
		//intersection of l1 , l3 left of intersection of l1, l2
		return (l3.b - l1.b) *(l1.m - l2.m)  <=  (l2.b - l1.b) * (l1.m - l3.m);
	}

	void addLine(Line l3){
		if(envelope.size() == 0) {
			envelope.push_back(l3);
			return;
		}
		if(envelope.size() == 1) {
			if(l3.m == envelope[0].m){
				if(l3.b > envelope[0].b){
					envelope = {l3};
				}
			} else {
				envelope.push_back(l3);
			}
			return;
		}
		
		Long sz = envelope.size();
		Line l1 = envelope[sz - 2];
		Line l2 = envelope[sz - 1];
		while(bad(l1 , l2 , l3) ) {
			
			envelope.pop_back();
			sz = envelope.size();
			l1 = envelope[sz - 2];
			l2 = envelope[sz - 1];
			if(envelope.size() == 1) {
				break;
			}
		}
		envelope.push_back(l3);
	}

	void build(vector<Line> &lines){ //O(n log n)
		sort(lines.begin(), lines.end() , cmp);
		for(Line l : lines){
			addLine(l);
		}
	}
	
	void debugEnvelope(){
		cout << "envelope = " << endl;
		for(Line l : envelope){
			cout << l.m << " " << l.b << endl;
		}
	}
	
	Long maxY(Long x){ //O(log n)
		assert(!envelope.empty());
		return search(0, (Long)envelope.size() - 1, x);
	}
	
}cht;



mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

Long brute(vector<Line> &L, Long x){
	Long ans = L[0].m * x + L[0].b;
	for(Long i = 1; i < L.size(); i++){
		ans = max(ans , L[i].m * x + L[i].b);
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Long n;
	//cin >> n;
	n = random(141 ,150);
	
	debug(n);
	vector<Line> L(n);
	cout << "L = " << endl;
	REP(i , n){
		//cin >> L[i].m >> L[i].b;
		L[i].m = random(-20,20);
		L[i].b = random(-100,100);
		cout << L[i].m << " " << L[i].b << endl;
	}
	cout << "--------------" << endl;
	cht.build(L);
	cht.debugEnvelope();
	Long q = 100000;
	/*Long q;
	cin >> q;*/
	REP(i , q){
		Long x = random(-100 , 2);
		/*Long x;
		cin >> x;
		debug(brute(L , x));
		debug(cht.minY(x));*/
		if(brute(L , x) != cht.maxY(x)){
			debug(x);
			debug(brute(L , x));
			debug(cht.maxY(x));
			system("pause");
		}
	}
	
	return 0;
}
