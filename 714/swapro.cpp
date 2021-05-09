using namespace std;

#include <iostream>
#include <map>

#define MAXN 200005

int N,a[MAXN],b[MAXN];
map<int,int> setA,setB;
long long ans;

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) cin >> a[i];
	for(int i = 0;i < N;++i) cin >> b[i];
	for(int i = 0;i < N;++i) {
		if(a[i] <= b[i]) {
			setA[a[i]] = max(setA[a[i]],b[i]);
		}else{
			setB[b[i]] = max(setB[b[i]],a[i]);
		}
		ans += abs(a[i] - b[i]);
	}
	int m = 0;
	for(auto &x : setA) {
		x.second = m = max(m,x.second);
	}
	m = 0;
	for(auto &x : setB) {
		x.second = m = max(m,x.second);
	}
	int maxOverlap = 0;
	for(int i = 0;i < N;++i) {
		if(a[i] <= b[i]) {
			auto itr = setB.upper_bound(a[i]);
			if(itr == setB.begin()) continue;
			maxOverlap = max(maxOverlap,min((--itr) -> second,b[i]) - a[i]);
		}else{
			auto itr = setA.upper_bound(b[i]);
			if(itr == setA.begin()) continue;
			maxOverlap = max(maxOverlap,min((--itr) -> second,a[i]) - b[i]);
		}
	}
	ans -= 2 * maxOverlap;
	cout << ans << endl;
	return 0;
}