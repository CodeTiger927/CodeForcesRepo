using namespace std;

#include <iostream>
#include <vector>
#include <map>

#define MAXN 200005

int N,arr[MAXN];
map<int,int> m;

void solve(int l,int r) {
	if(l > r) return;
	int a,b;
	cout << "? " << l << " " << r << endl;
	cin >> a >> b;
	if(m.count(a)) {
		m[a] -= b;
		while(b--) arr[r--] = a;
	}else{
		m[a] = b;
		for(;m[a] == b;l += b) solve(l,l + b - 1);
		b = m[a];
		while(b--) arr[l++] = a;
		m.erase(a);
	}
	solve(l,r);
}

int main() {
	cin >> N;
	solve(1,N);
	cout << "!";
	for(int i = 1;i <= N;++i) cout << " " << arr[i];
	cout << endl;
	return 0;
}