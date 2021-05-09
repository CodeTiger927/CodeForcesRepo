using namespace std;

#include <iostream>
#include <set>

int N;
set<long long> ans;

long long gcd(long long a,long long b) {
	if(a == 0) return b;
	if(b == 0) return a;
	if(a == 1 || b == 1) return 1;
	if(a > b) swap(a,b);
	return gcd(b % a,a);
}


int main() {
	cin >> N;
	long long curP = 1;
	for(int i = 1;i <= N;++i) {
		if(gcd(i,N) == 1) {
			curP = (1ll * curP * i) % N;
			ans.insert(i);
		}
	}
	if(curP != 1) {
		ans.erase(curP);
	}
	cout << ans.size() << endl;
	for(auto itr = ans.begin();itr != ans.end();++itr) {
		cout << (*itr) << " ";
	}
	cout << endl;
	return 0;
}