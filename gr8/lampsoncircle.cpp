using namespace std;

#include <iostream>
#include <vector>

#define MAXN 1005

int N;
bool arr[MAXN],use[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	pair<int,int> rec = {0,0};
	for(int i = 2;i <= N;++i) {
		int cur = N / i * (i - 1) + max(0,N % i - 1) - (i - 1);
		rec = max(rec,{cur,i});
	}
	if(rec.first == 0) {
		cout << 0 << endl;
		return 0;
	}
	for(int i = 0;i < N;++i) {
		use[i] = (i % rec.second != rec.second - 1 && i != N - 1);
	}
	while(true) {
		int cnt = 0;
		vector<int> v;
		for(int i = 0;i < N;++i) {
			if(arr[i]) {
				cnt++;
			}else if(use[i]) {
				v.push_back(i);
			}
		}
		if(cnt >= rec.first) break;
		if(v.size() > rec.second) v.resize(rec.second);
		cout << v.size();
		for(int x : v) {
			cout << " " << x + 1;
			arr[x] = true;
		}
		cout << endl;
		int x;
		cin >> x;
		if(x == -1) return 0;
		x--;
		for(int i = 0;i < rec.second;++i) arr[(x + i) % N] = false;
	}
	cout << 0 << endl;
	return 0;
}