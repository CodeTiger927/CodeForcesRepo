using namespace std;

#include <iostream>
#include <set>
#include <map>

set<pair<int,int>> edges1,edges2;
map<pair<int,int>,int> edges;

int main() {
	int N,M;
	cin >> N >> M;
	for(int i = 0;i < M;++i) {
		int a,b;
		char o,c;
		cin >> o;
		if(o == '+') {
			cin >> a >> b >> c;
			if(edges.find({b,a}) != edges.end()) {
				if(edges[{b,a}] == c) {
					edges1.insert({min(a,b),max(a,b)});
				}else{
					edges2.insert({min(a,b),max(a,b)});
				}
			}
			edges[{a,b}] = c;
		}else if(o == '-') {
			cin >> a >> b;
			if(edges1.find({min(a,b),max(a,b)}) != edges1.end()) {
				edges1.erase({min(a,b),max(a,b)});
			}
			if(edges2.find({min(a,b),max(a,b)}) != edges2.end()) {
				edges2.erase({min(a,b),max(a,b)});
			}
			edges.erase({a,b});
		}else if(o == '?'){
			cin >> a;
			if(a & 1) {
				cout << ((!edges1.empty() || !edges2.empty()) ? "YES" : "NO") << endl;
			}else{
				cout << (!edges1.empty() ? "YES" : "NO") << endl;
			}
		}
	}
	return 0;
}