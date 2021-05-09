using namespace std;

#include <iostream>
#include <cstring>
#include <vector>

#define MOD 1000000007
#define MOD2 1000696969
#define MAXN 1000005

string s,t;
int N,Q;
long long pre[26][100005],pw[3 * MAXN],pw2[3 * MAXN];
vector<string> songs;

vector<long long> hsh_pre(string& str,int m) {
	vector<long long> res;
	long long cur = 0;
	for(int i = 0;i < m;++i) {
		res.push_back(cur);
		if(i < str.size()) cur += (str[i] - 'a' + 1) * pw2[i] % MOD2;
		if(cur >= MOD2) cur -= MOD2;
	}
	return res;
}

vector<long long> hsh_suf(string& str,int m) {
	vector<long long> res;
	long long cur = 0;
	for(int i = 0;i < m;++i) {
		res.push_back(cur);
		cur = (cur * 271) % MOD2;
		if(i < str.size()) cur += (str[str.size() - 1 - i] - 'a' + 1);
		if(cur >= MOD2) cur -= MOD2;
	}
	return res;
}

int main() {
	cin >> N >> Q >> s >> t;
	for(int i = 0;i < 26;++i) {
		for(int j = 0;j < N;++j) {
			pre[i][j + 1] = (pre[i][j] * 2ll + ((t[j] - 'a') == i)) % MOD;
		}
	}
	pw[0] = pw2[0] = 1;
	for(int i = 1;i < 3 * MAXN;++i) {
		pw[i] = (pw[i - 1] * 2) % MOD;
		pw2[i] = (pw2[i - 1] * 271) % MOD2;
	}
	songs.push_back(s);
	while(songs.size() <= t.size() && songs.back().size() < MAXN) {
		string n = songs.back() + string(1,t[songs.size() - 1]) + songs.back();
		songs.push_back(n);
	}
	for(int i = 0;i < Q;++i) {
		int gen;
		string w;
		cin >> gen >> w;
		int id = 0;
		vector<int> ff(26,0);
		while(id < songs.size() && songs[id].size() < w.size()) {
			id++;
		}
		if(gen < id || id == songs.size()) {
			cout << 0 << endl;
			continue;
		}
		vector<long long> w_pre = hsh_pre(w,w.size() + 1);
		vector<long long> w_suf = hsh_suf(w,w.size() + 1);

		vector<long long> s_pre = hsh_pre(songs[id],songs[id].size() + 1);
		vector<long long> s_suf = hsh_suf(songs[id],songs[id].size() + 1);

		for(int i = 0;i < w.size();++i) {
			if(s_suf[i] == w_pre[i] && s_pre[w.size() - 1 - i] == w_suf[w.size() - 1 - i]) {
				ff[w[i] - 'a']++;
			}
		}

		long long cnt = 0;
		for(int i = w.size();i <= songs[id].size();++i) {
			long long cur = (s_pre[i] - s_pre[i - w.size()] + MOD2) % MOD2;
			if(cur == (w_pre[w.size()] * pw2[i - w.size()] % MOD2)) cnt++;
		}
		long long ans = (cnt * pw[gen - id]) % MOD;
		for(int i = 0;i < 26;++i) {
			ans += (ff[i] * pre[i][gen]) % MOD;
			if(ans >= MOD) ans -= MOD;
		}
		for(int i = 1;i <= id;++i) {
			ans += ff[t[i - 1] - 'a'] * (MOD - pw[gen - i]) % MOD;
			if(ans >= MOD) ans -= MOD;
		}
		cout << ans << endl;
	}
	return 0;
}