#pragma GCC target ("avx2")
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")

using namespace std;

#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

char cs[4] = {'A','N','T','O'};
bool leftRight[4];
string str,ans;
map<char,int> rev;
int N,cnt[4];
vector<int> preCalc[4][4];

long long CountSteps(string s2) {
	long long res = 0;
	for(int i = 0;i < 4;++i) {
		for(int j = 0;j < i;++j) {
			vector<int> v2;
			v2.reserve(cnt[i] + 1);
			int cnt = 0;
			for(int k = 0;k < s2.size();++k) {
				if(rev[s2[k]] == i) {
					v2.push_back(cnt);
					cnt = 0;
				}else if(rev[s2[k]] == j){
					++cnt;
				}
			}
			v2.push_back(cnt);
			for(int k = 0;k < v2.size() - 1;++k) {
				res += 1ll * abs(v2[k] - preCalc[i][j][k]);
				v2[k + 1] += v2[k] - preCalc[i][j][k];
			}
		}
	}
    return res;
}

void solve() {
	cin >> str;
	memset(cnt,0,sizeof(cnt));
	N = str.size();
	for(int i = 0;i < N;++i) {
		cnt[rev[str[i]]]++;
	}
	for(int i = 0;i < 4;++i) {
		for(int j = 0;j < i;++j) {
			preCalc[i][j].clear();
		}
	}
	vector<int> v = {0,1,2,3};

	for(int i = 0;i < 4;++i) {
		for(int j = 0;j < i;++j) {
			int cnter = 0;
			for(int k = 0;k < str.size();++k) {
				if(rev[str[k]] == i) {
					preCalc[i][j].push_back(cnter);
					cnter = 0;
				}else if(rev[str[k]] == j){
					++cnter;
				}
			}
			preCalc[i][j].push_back(cnter);
		}
	}

	string best = "";
	long long record = -1;
	do {
		string cur = "";
		for(int i = 0;i < 4;++i) {
			if(cnt[v[i]]) cur += string(cnt[v[i]],cs[v[i]]);
		}
		long long res = CountSteps(cur);
		if(res > record) {
			record = res;
			best = cur;
		}
	}while(next_permutation(v.begin(),v.end()));

	cout << best << "\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	rev['A'] = 0;
	rev['N'] = 1;
	rev['T'] = 2;
	rev['O'] = 3;
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}