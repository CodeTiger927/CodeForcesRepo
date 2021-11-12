using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 10005

long long N,K,sum[MAXN];

long long askor(int a,int b) {
	cout << "or " << a << " " << b << endl;
	long long res;
	cin >> res;
	return res;
}

long long askand(int a,int b) {
	cout << "and " << a << " " << b << endl;
	long long res;
	cin >> res;
	return res;
}

long long asksum(int a,int b) {
	return askor(a,b) + askand(a,b);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> K;
	for(int i = 2;i <= N;++i) {
		sum[i] = asksum(1,i);
	}
	sum[0] = asksum(2,3);
	vector<long long> all;
	all.push_back((sum[2] + sum[3] - sum[0]) / 2);
	for(int i = 2;i <= N;++i) {
		all.push_back(sum[i] - all[0]);
	}
	sort(all.begin(),all.end());
	cout << "finish " << all[K - 1] << endl;
	return 0;
}