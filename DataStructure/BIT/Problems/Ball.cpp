#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;
 
typedef int Long;

//https://codeforces.com/contest/12/problem/D
 
const Long MX = 5e5;
const Long EXTRA = 6;
const Long INF = 1e9;
struct BIT{
	Long tree[MX+EXTRA];
	
	void clear(){ //O(n)
		for(Long i = 0; i < MX + EXTRA; i++){
			tree[i] = INF;
		}
	}
	
	Long query(Long x){ //O(log n)
		x += EXTRA;
		Long ans = INF;
		while(x > 0){
			ans = min(ans , tree[x]);
			x -= (x & -x);
		}
		return ans;
	}
	
	void update(Long x , Long add){ //O(log n)
		x += EXTRA;
		while(x < MX + EXTRA){
			tree[x] = min(tree[x] , add);
			x += (x & -x);
		}
	}
		
} ft;
 
struct Triple{
	Long a , b , c;
	Triple(){}
	Triple(Long a , Long b , Long c) : a(a) ,b(b), c(c){}
};
 
bool cmpA(const Triple &T1, const Triple &T2){
	return T1.a < T2.a;
}

bool cmpB(const Triple &T1, const Triple &T2){
	return T1.b < T2.b;
}
bool cmpC(const Triple &T1, const Triple &T2){
	return T1.c < T2.c;
}
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n;
	cin >> n;
	vector<Triple> v(n);
	vector<Long> s;
	ft.clear();
	REP(i , n){
		cin >> v[i].a;
	}
	REP(i , n){
		cin >> v[i].b;
	}
	REP(i , n){
		cin >> v[i].c;
	}
	sort(v.begin(), v.end(), cmpB);
	Long i = 0;
	Long cnt = 0;
	Long maxib = 0;
	while(i < n){
		Long b = v[i].b;
		while(i < n && v[i].b == b){
			v[i].b = cnt;
			i++;
		}
		cnt++;
	}
	
	maxib = cnt;
	
	sort(v.begin(), v.end(), cmpC);
	i = 0;
	cnt = 0;
	Long maxic = 0;
	while(i < n){
		Long c = v[i].c;
		while(i < n && v[i].c == c){
			v[i].c = cnt;
			i++;
		}
		cnt++;
	}
	maxic = cnt;
	
	sort(v.begin(), v.end(), cmpA);
	i = 0;
	cnt = 0;
	Long maxia = 0;
	while(i < n){
		Long a = v[i].a;
		while(i < n && v[i].a == a){
			v[i].a = cnt;
			i++;
		}
		cnt++;
	}
	maxia = cnt;
	
	REP(i , n){
		v[i].a = maxia - v[i].a;
		v[i].b = maxib - v[i].b;
		v[i].c = maxic - v[i].c;
	}
	sort(v.begin(), v.end(), cmpA);
	Long ans = 0;
	i = 0;
	while(i < n){
		vector<pair<Long,Long>> up;
		Long a = v[i].a;
		while(i < n && v[i].a == a){
			
			if(ft.query(v[i].b) < v[i].c){
				ans++;
			}
			up.pb({v[i].b + 1 , v[i].c});
			i++;
		}
		for(pair<Long,Long> p : up){
			ft.update(p.first ,p.second);
		}

	}
	cout << ans << "\n";
	
	return 0;
}
