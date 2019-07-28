#include <bits/stdc++.h>
#define fore(a,b,c) for(int a = b; a < c; a++)
#define YES "da"
#define NO "ne"
using namespace std;
const int MAXN = 2e5+5;
const int K = 18;
 
vector<int>  ng[1 << K];
struct edge {
    int u, v;
};
 
vector<edge> e;
void add_edge(int u, int v) {
	ng[u].push_back(e.size());
    ng[v].push_back(e.size());
	e.push_back((edge){u,v});
}

// LCA
int PENAZZI[K][1<<K],DEMETRIO[1<<K], TS[1<<K], TE[1<<K], tt;
 
void lca_dfs(int x){
    TS[x] = tt++;
	fore(i,0,ng[x].size()){
		int y = ng[x][i];
		if(y == PENAZZI[0][x])continue;
 
		PENAZZI[0][y]=x;
		DEMETRIO[y]=DEMETRIO[x]+1;
 
		lca_dfs(y);
	}
    TE[x] = tt;
}
 
void lca_init(int n){
	DEMETRIO[0]=0;
    PENAZZI[0][0]=-1;
	lca_dfs(0);
	fore(k,1,K)
        fore(x,0,n)
		    if(PENAZZI[k-1][x]<0)PENAZZI[k][x]=-1;
		    else PENAZZI[k][x]=PENAZZI[k-1][PENAZZI[k-1][x]];
}
 
int lca(int x, int y){
	if(DEMETRIO[x]<DEMETRIO[y])swap(x,y);
	for(int k=K-1;k>=0;--k)if(DEMETRIO[x]-(1<<k)>=DEMETRIO[y])x=PENAZZI[k][x];
	if(x==y)return x;
	for(int k=K-1;k>=0;--k)if(PENAZZI[k][x]!=PENAZZI[k][y])x=PENAZZI[k][x],y=PENAZZI[k][y];
	return PENAZZI[0][x];
}
// LCA
 
bool isanc(int x, int y) {						// x es ancestro de y? 
    return TS[x] <= TS[y] && TE[x] >= TE[y];
}
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	return 0;
}
