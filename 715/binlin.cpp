using namespace std;

#include <iostream>
#include <cstring>
#include <vector>

#define MAXN 200005

int N,cnt[3],tmp[MAXN];
string str[3];

string combine(int a,int b) {
	for(int i = 0;i < 2 * N;++i) {
		tmp[i] = 0;
	}
	if(cnt[a] <= N && cnt[b] <= N) {
		int c = 0;
		int ptr = 0;
		int mc = 0;
		for(int i = 0;i < 2 * N;++i) {
			if(str[a][i] == '0') {
				tmp[ptr] = max(tmp[ptr],c);
				ptr++;
				c = 0;
			}else{
				c++;
			}
		}
		mc = max(mc,c);
		c = ptr = 0;
		for(int i = 0;i < 2 * N;++i) {
			if(str[b][i] == '0') {
				tmp[ptr] = max(tmp[ptr],c);
				ptr++;
				c = 0;
			}else{
				c++;
			}
		}
		mc = max(mc,c);
		string res = "";
		for(int i = 0;i < max(2 * N - cnt[a],2 * N - cnt[b]);++i) {
			for(int j = 0;j < max(0,tmp[i]);++j) {
				res += '1';
			}
			res += '0';
		}
		res += string(mc,'1');
		return res;
	}else if(cnt[a] >= N && cnt[b] >= N) {
		int c = 0;
		int ptr = 0;
		int mc = 0;
		for(int i = 0;i < 2 * N;++i) {
			if(str[a][i] == '1') {
				tmp[ptr] = max(tmp[ptr],c);
				c = 0;
				ptr++;
			}else{
				c++;
			}
		}
		mc = max(mc,c);
		c = ptr = 0;
		for(int i = 0;i < 2 * N;++i) {
			if(str[b][i] == '1') {
				tmp[ptr] = max(tmp[ptr],c);
				c = 0;
				ptr++;
			}else{
				c++;
			}
		}
		mc = max(mc,c);
		string res = "";
		for(int i = 0;i < max(cnt[a],cnt[b]);++i) {
			for(int j = 0;j < max(0,tmp[i]);++j) {
				res += '0';
			}
			res += '1';
		}
		res += string(mc,'0');
		return res;
	}
	return ".";
}

void solve() {
	cin >> N >> str[0] >> str[1] >> str[2];
	cnt[0] = cnt[1] = cnt[2] = 0;
	for(int i = 0;i < 2 * N;++i) {
		if(str[0][i] == '1') cnt[0]++;
		if(str[1][i] == '1') cnt[1]++;
		if(str[2][i] == '1') cnt[2]++;
	}
	string res = combine(0,1);
	if(res != "." && res.size() <= 3 * N) {
		cout << res << endl;
		return;
	}
	res = combine(0,2);
	if(res != "." && res.size() <= 3 * N) {
		cout << res << endl;
		return;
	}
	cout << combine(1,2) << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}