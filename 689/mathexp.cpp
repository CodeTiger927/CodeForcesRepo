using namespace std;

#include <iostream>
#include <set>
#include <vector>

#define MAXN 100005
#define MAXM 65
#define INF 1e17

int N,arr[MAXN],best[MAXM];
long long dp[MAXM];
char ans[MAXN];
string str;
bool p,s,m;

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	cin >> str;
	set<char> tmp;
	for(int i = 0;i < str.size();++i) {
		tmp.insert(str[i]);
	}
	p = (tmp.find('+') != tmp.end());
	s = (tmp.find('-') != tmp.end());
	m = (tmp.find('*') != tmp.end());
	if(str.size() == 1) {
		cout << arr[0];
		for(int i = 1;i < N;++i) {
			cout << str[0] << arr[i];
		}
		cout << endl;
		return 0;
	}
	if(!m) {
		cout << arr[0];
		for(int i = 1;i < N;++i) {
			cout << '+' << arr[i];
		}
		cout << endl;
		return 0;
	}
	if(!p) {
		cout << arr[0];
		for(int i = 1;i < N;++i) {
			if(arr[i] == 0) {
				cout << '-';
			}else{
				cout << "*";
			}
			cout << arr[i];
		}
		cout << endl;
		return 0;
	}
	for(int i = 0;i < N;++i) {
		ans[i] = '+';
	}
	int ptr = 0;
	while(ptr < N) {
		while(ptr < N && arr[ptr] == 0) ptr++;
		if(ptr == N) break;
		int l = ptr;
		while(ptr < N && arr[ptr]) ptr++;
		int r = ptr - 1;
		while(l <= r && arr[l] == 1) l++;
		while(l <= r && arr[r] == 1) r--;
		if(l > r) continue;
		long long res = 1;
		for(int i = l;i <= r;++i) {
			res = min(res * arr[i],10000000ll);
		}
		if(res == 10000000ll) {
			for(int i = l + 1;i <= r;++i) {
				ans[i] = '*';
			}
			continue;
		}
		vector<pair<long long,pair<int,int>>> st;
		int j = l;
		while(j <= r) {
			int l = j;
			long long res = 1;
			if(arr[l] == 1) {
				while(j <= r && arr[j] == 1) j++;
				res = j - l;
			}else{
				while(j <= r && arr[j] > 1) {
					if(j != l) ans[j] = '*';
					res *= arr[j++];
				}
			}
			st.push_back({res,{l,j - 1}});
		}
		int n = st.size();
		for(int i = 1;i <= n;++i) dp[i] = -INF;
		for(int i = 1;i <= n;++i) {
			if(dp[i] < dp[i - 1] + st[i - 1].first) {
				best[i] = i - 1;
				dp[i] = dp[i - 1] + st[i - 1].first;
			}
			if(i & 1) {
				long long res = 1;
				for(int j = i;j <= n;++j) {
					if((j - i) % 2 == 0) res *= st[j - 1].first;
					if((j - i) % 2 == 0 && dp[j] < res + dp[i - 1]) {
						best[j] = i - 1;
						dp[j] = res + dp[i - 1];
					}
				}
			}
		}
		int cur = n;
		while(cur) {
			int l = best[cur] + 1;
			int r = cur;
			cur = best[cur];
			if(l < r) {
				for(int i = st[l - 1].second.first + 1;i <= st[r - 1].second.second;++i) {
					ans[i] = '*';
				}
			}
		}
	}
	cout << arr[0];
	for(int i = 1;i < N;++i) {
		cout << ans[i] << arr[i];
	}
}