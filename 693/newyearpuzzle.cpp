using namespace std;

#include <iostream>
#include <map>

int N,M;

void solve() {
	cin >> N >> M;
	map<int,int> m;
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		m[b] += (1 << (a - 1));
	}
	bool comp = true;
	int last = 0;
	m[N +  1] = 3;
	for(auto itr = m.begin();itr != m.end();++itr) {
		pair<int,int> cur = *itr;
		if(cur.second == 3) {
			if(!comp) {
				cout << "NO" << endl;
				return;
			}
		}else if(comp) {
			last = (cur.first + cur.second) & 1;
			comp = false;
		}else{
			if(last == ((cur.first + cur.second) & 1)) {
				cout << "NO" << endl;
				return;
			}else{
				comp = true;
			}
		}
	}
	cout << "YES" << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}