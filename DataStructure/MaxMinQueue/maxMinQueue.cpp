#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

struct MaxQueue{
	stack<pair<Long,Long>> s1,s2; // ( valor , maximo)
	
	Long f(Long a, Long b){
		return max(a,b);
	}

	Long get(){
		if(s1.empty() && s2.empty()) return 0;
		if(s1.empty() || s2.empty()){
			return s1.empty() ? s2.top().second : s1.top().second;
		}
		else{
			return f(s1.top().second, s2.top().second);
		}
	}
	
	void add(Long newElement){
		Long aux = s1.empty() ? newElement : f(newElement,s1.top().second);
		s1.push(make_pair(newElement,aux));
	}
	
	void pop(){
		if(s2.empty()){
			//s1 = inverse(s2)
			while(!s1.empty()){
				Long element = s1.top().first;
				s1.pop();
				Long aux = s2.empty() ? element : f(element,s2.top().second);
				s2.push(make_pair(element,aux));
			}
		}
		
		s2.pop();
	}
	
	void clear(){
		while(!s1.empty()){
			s1.pop();
		}
		while(!s2.empty()){
			s2.pop();
		}
	}
}mq;


int main() {
	return 0;
}



