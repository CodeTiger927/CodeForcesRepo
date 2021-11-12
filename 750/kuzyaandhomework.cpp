using namespace std;

#include <iostream>
#include <vector>
#include <stack>

#define MAXN 1000005

int N,a[MAXN];
vector<int> f[MAXN],v[MAXN];
stack<int> s;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> a[i];
	}
	for(int i = 2;i < MAXN;++i) {
		if(f[i].size()) continue;
		for(long long j = i;j < MAXN;j *= i) {
			for(long long k = j;k < MAXN;k += j) {
				f[k].push_back(i);
			}
		}
	}
	long long res = 0;
	for(int i = 0;i < N;++i) {
		char c;
		cin >> c;
		s.push(i);
		for(int j : f[a[i]]) {
			if(c == '*') {
				v[j].push_back(i);
			}else{
				while(!s.empty() && (v[j].empty() || s.top() > v[j].back())) {
					s.pop();
				}
				if(!v[j].empty()) v[j].pop_back();
			}
		}
		res += s.size();
	}
	cout << res << endl;
	return 0;
}