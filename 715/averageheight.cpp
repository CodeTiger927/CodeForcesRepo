using namespace std;

#include <iostream>
#include <vector>

int N,cnt;
vector<int> a,b;

void solve() {
	cin >> N;
	cnt = 0;
	a.clear();b.clear();
	for(int i = 0;i < N;++i) {
		int cur;
		cin >> cur;
		if(cur & 1) {
			a.push_back(cur);
		}else{
			b.push_back(cur);
		}
	}
	for(int i = 0;i < a.size();++i) {
		cout << a[i] << " ";
	}
	for(int i = 0;i < b.size();++i) {
		cout << b[i] << " ";
	}
	cout << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}