using namespace std;

#include <iostream>
#include <bitset>
#include <unordered_map>

#define MAXN 1005
#define MAXS 30

typedef bitset<MAXN> bs;

int N,S,D;
bs arr[MAXS],tmp,tmp2;
unordered_map<bs,int> bf;

int main() {
	cin >> N >> S >> D;
	for(int i = 0;i < S;++i) {
		int c;
		cin >> c;
		for(int j = 0;j < c;++j) {
			int cur;
			cin >> cur;
			arr[i][cur - 1] = 1;
		}
	}
	for(int i = 0;i < (1 << 20);++i) {
		tmp.reset();
		for(int j = 0;j < 20;++j) {
			if(i & (1 << j)) tmp ^= arr[j];
		}
		if(bf.find(tmp) == bf.end()) {
			bf[tmp] = __builtin_popcount(i);
		}else{
			bf[tmp] = min(bf[tmp],__builtin_popcount(i));
		}
	}
	for(int i = 0;i < D;++i) {
		tmp.reset();
		int c;
		cin >> c;
		for(int j = 0;j < c;++j) {
			int cur;
			cin >> cur;
			tmp[cur - 1] = 1;
		}
		int ans = 1e9;
		for(int j = 0;j < (1 << 10);++j) {
			tmp2.reset();
			for(int k = 0;k < 10;++k) {
				if(j & (1 << k)) tmp2 ^= arr[20 + k];
			}
			tmp2 ^= tmp;
			if(bf.find(tmp2) != bf.end()) ans = min(ans,bf[tmp2] + __builtin_popcount(j));
		}
		cout << (ans == 1e9 ? -1 : ans) << endl;
	}
	return 0;
}