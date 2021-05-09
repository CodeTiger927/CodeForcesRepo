using namespace std;

#include <iostream>
#include <set>

int N,X;

void solve() {
	int total = 0;
	set<int> s;
	cin >> N >> X;
	for(int i = 0;i < N;++i) {
		int cur;
		cin >> cur;
		total += cur;
		s.insert(cur);
	}
	if(total == X) {
		cout << "NO" << endl;
		return;
	}
	cout << "YES" << endl;
	int cur = 0;
	while(!s.empty()) {
		auto itr = s.begin();
		if(cur + *itr == X) {
			cout << *next(itr) << " ";
			cur += *next(itr);
			s.erase(next(itr));
			continue;
		}else{
			cout << *itr << " ";
			cur += *itr;
			s.erase(itr);
		}
	}
	cout << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}