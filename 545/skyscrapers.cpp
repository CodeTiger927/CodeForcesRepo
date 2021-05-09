using namespace std;

#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>

#define MAXN 1005

int N,M,arr[MAXN][MAXN],ans[MAXN][MAXN],rows2[MAXN][MAXN],cols2[MAXN][MAXN],rows3[MAXN],cols3[MAXN];
vector<pair<int,int>> rows[MAXN],cols[MAXN];

int main() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			cin >> arr[i][j];
			rows[i].push_back({arr[i][j],j});
			cols[j].push_back({arr[i][j],i});
		}
	}
	for(int i = 0;i < N;++i) {
		sort(rows[i].begin(),rows[i].end());
		int counter = 0;
		for(int j = 0;j < M;++j) {
			if(j != 0 && rows[i][j].first != rows[i][j - 1].first) counter++;
			rows2[i][rows[i][j].second] = counter;
		}
		rows3[i] = counter + 1;
	}
	for(int i = 0;i < M;++i) {
		sort(cols[i].begin(),cols[i].end());
		int counter = 0;
		for(int j = 0;j < N;++j) {
			if(j != 0 && cols[i][j].first != cols[i][j - 1].first) counter++;
			cols2[cols[i][j].second][i] = counter;
		}
		cols3[i] = counter + 1;
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			int tmp1 = rows2[i][j];
			int tmp2 = cols2[i][j];

			int ans = max(tmp1,tmp2) + max(rows3[i] - tmp1,cols3[j] - tmp2);
			cout << ans << " ";
		}
		cout << endl;
	}
}