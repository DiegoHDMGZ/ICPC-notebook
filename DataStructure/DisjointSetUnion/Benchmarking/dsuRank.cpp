# include <bits/stdc++.h>
 
using namespace std;
 

// Useful constants
 
//int some_primes[10] = {24443, 100271, 500179, 1000003, 1000333, 2000321, 5000321, 98765431, 1000000123};
#define INF         1011111111
#define LLINF       1000111000111000111LL
#define EPS         (double)1e-10
#define mod         1000000007
#define PI          3.14159265358979323
#define link        asaxlajrewqwe
#define rank        wahayawehasdakw
//*************************************************************************************
 
const int maxn = 10000000;
int p[maxn + 1000];
int size[maxn +1000];
int getp_calls = 0;
int getp(int x) {
    ++getp_calls;
    if (p[x] != x) {
        p[x] = getp(p[x]);
    }
    return p[x];
}
std::mt19937 gen(123);
 
void join( int a, int b ) {
	a = getp(a);
	b = getp(b);
	
	if(a != b){
		/*if(size[a] < size[b]){
			swap(a,b);
		}*/
		p[a] = b;
		//size[a] += size[b];
	}
}
 
double solve(int n) {
    getp_calls = 0;
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
    }
    for (int i = 2; i <= n; ++i) {
        join(uniform_int_distribution<>(1, 1 + i / sqrt(5.0))(gen), i);
    }
    return getp_calls * 1.0 / n;
}
 
int main() {
    for (int n : {1e2, 1e3, 1e4, 1e5, 1e6, 1e7}) {
		cout << " n = " << n << " , solve(n) = " << solve(n) << endl;
    }
    return 0;
}
 
 
 
 
 
 
