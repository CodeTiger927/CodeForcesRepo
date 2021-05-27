using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 1005

int N,arr[MAXN],pos[MAXN];
vector<pair<int,int>> ans;

int main() {
	cin >> N;
	vector<pair<int,int>> v;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		v.push_back({arr[i],i});
	}
	sort(v.begin(),v.end());
	for(int i = 0;i < N;++i) {
		arr[v[i].second] = i + 1;
		pos[i + 1] = v[i].second;
	}
	for(int i = N - 1;i >= 0;--i) {
		int n = arr[i];
		for(int j = n + 1;j <= i + 1;++j) {
			ans.push_back({pos[j],i});
			int tmp = arr[i];
			swap(arr[pos[j]],arr[i]);
			swap(pos[j],pos[tmp]);
		}
	}
	cout << ans.size() << endl;
	for(auto p : ans) {
		cout << p.first + 1 << " " << p.second + 1 << endl;
	}
	return 0;
}