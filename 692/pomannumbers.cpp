using namespace std;

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

int N;
long long T;
string s;
vector<long long> v;

int main() {
	cin >> N >> T >> s;
	for(int i = 0;i < N;++i) {
		T += 1ll << (s[i] - 'a');
		if(i < N - 2) v.push_back(1ll << (s[i] - 'a'));
	}
	if(T & 1) {
		cout << "No" << endl;
		return 0;
	}
	T >>= 1;
	T -= 1ll << (s[N - 1] - 'a');
	sort(v.begin(),v.end(),[&](long long a,long long b) {return a > b;});
	for(int i = 0;i < N - 2;++i) {
		if(T >= v[i]) {
			T -= v[i];
		}
	}
	if(T) {
		cout << "No" << endl;
	}else{
		cout << "Yes" << endl;
	}
	return 0;
}