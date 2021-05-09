using namespace std;

#include <iostream>
#include <vector>

#define MAXN 250000

int N,M,ans[MAXN];
vector<int> arr[MAXN];

bool solve(int x) {
	for(int i = 0;i < N;++i) {
		vector<int> v;
		for(int j = 0;j < M;++j) {
			if(ans[j] != arr[i][j]) {
				v.push_back(j);
			}
		}
		if(x + v.size() > 4) return false;
		if(v.size() > 2) {
			for(int j = 0;j < v.size();++j) {
				int tmp = ans[v[j]];
				ans[v[j]] = arr[i][v[j]];
				if(solve(x + 1)) return true;
				ans[v[j]] = tmp;
			}
			return false;
		}
	}
	return true;
}

int main() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		arr[i].resize(M);
		for(int j = 0;j < M;++j) {
			cin >> arr[i][j];
			if(i == 0) ans[j] = arr[i][j];
		}
	}
	if(solve(0)) {
		cout << "Yes" << endl;
		for(int i = 0;i < M;++i) {
			cout << ans[i] << " ";
		}
		cout << endl;
	}else{
		cout << "No" << endl;
	}
	return 0;
}