using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>

#define MAXN 105
#define MAXM 10005

int N,K,arr[MAXM],cnt[MAXN],pos[MAXN][MAXN];
vector<pair<int,int>> ans;

int main() {
	cin >> N >> K;
	int sz = (N - 1) / (K - 1) + 1;
	vector<int> v;
	for(int i = 1;i <= N;++i) {
		v.push_back(i);
	}
	for(int i = 1;i <= N * K;++i) {
		cin >> arr[i];
		pos[arr[i]][cnt[arr[i]]++] = i;
	}
	for(int i = 1;v.size();++i) {
		sort(v.begin(),v.end(),[&](int a,int b){return pos[a][i] > pos[b][i];});
		for(int j = 0;j < sz && v.size();++j) {
			int cur = v.back();
			v.pop_back();
			ans.push_back({pos[cur][i - 1],pos[cur][i]});
		}
	}
	sort(ans.begin(),ans.end(),[&](pair<int,int> a,pair<int,int> b) {return arr[a.first] < arr[b.first];});
	for(auto [a,b] : ans) {
		cout << a << " " << b << endl;
	}
	return 0;
}