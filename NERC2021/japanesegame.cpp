using namespace std;

#include <iostream>
#include <cstring>
#include <vector>
#include <cstring>

#define MAXN 100005

string str;
int N,dp[MAXN];
vector<pair<int,int>> v;

int main() {
	cin >> str;
	N = str.length();

	v.push_back({-2,-2});
	for(int i = 0;i < N;++i) {
		if(str[i] == '#') {
			if(i && str[i - 1] == '#') {
				v.back().second++;
			}else{
				v.push_back({i,i});
			}
		}
	}
	v.push_back({N + 1,N + 1});

	for(int i = 0;i <= 3;++i) {
		bool works = true;
		for(int j = 1;j <= N + 2;++j) {
			dp[j] = -1;
			for(int k = 1;k <= min(i,j - 1);++k) if(dp[j - k - 1] != -1) dp[j] = k;
		}
		vector<int> ans;
		for(int j = 1;j < v.size();++j) {
			int gap = v[j].first - v[j - 1].second - 2 - i;
			if(gap >= 0 && dp[gap] != -1) {
				while(gap) {
					ans.push_back(dp[gap]);
					gap -= dp[gap] + 1;
				}
				ans.push_back(v[j].second - v[j].first + 1 + i);
			}else{
				works = false;
				break;
			}
		}

		if(works) {
			cout << ans.size() - 1 << endl;
			for(int i = 0;i < ans.size() - 1;++i) cout << ans[i] << " ";
			cout << endl;
			return 0;
		}
	}
	cout << -1 << endl;
	return 0;
}