using namespace std;

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define MAXN 3005

vector<long long> parties[MAXN];
multiset<long long> all;
long long arr[MAXN];

int main() {
	int N,M;
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		long long a,b;
		cin >> a >> b;
		arr[i] = b;
		parties[a].push_back(b);
	}
	for(int i = 1;i <= M;++i) {
		sort(parties[i].begin(),parties[i].end());
	}
	long long ans = 1e18;
	for(int i = max(parties[1].size(),(size_t)1);i <= N;++i) {
		all.clear();
		for(int j = 0;j < N;++j) {
			all.insert(arr[j]);
		}
		for(int j = 0;j < parties[1].size();++j) {
			all.erase(all.find(parties[1][j]));
		}
		int curNeed = i - parties[1].size();
		long long curAns = 0;

		for(int j = 2;j <= M;++j) {
			if(parties[j].size() >= i) {
				for(int k = 0;k < parties[j].size() - i + 1;++k) {
					curAns += parties[j][k];
					all.erase(all.find(parties[j][k]));
					curNeed--;
				}
			}
		}

		auto itr = all.begin();
		for(int j = 0;j < curNeed;++j) {
			if(itr == all.end()) {
				curAns += 1e15;
				break;
			}
			curAns += *itr;
			itr++;
		}
		ans = min(ans,curAns);
	}
	cout << ans << endl;
	return 0;
}