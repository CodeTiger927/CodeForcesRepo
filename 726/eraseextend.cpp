using namespace std;

#include <iostream>
#include <cstring>

bool smaller(string a,string b) {
	for(int i = 0;i < a.size();++i) {
		if(a[i] < b[i]) return true;
		if(a[i] > b[i]) return false;
	}
	return false;
}

int main() {
	int N,K;
	string str;
	cin >> N >> K >> str;
	string fin = string(K,'z');
	for(int i = 0;i < N;++i) {
		string all = "";
		for(int j = 0;j <= i;++j) {
			all += str[j];
		}
		string ans = "";
		while(ans.size() < K) {
			ans += all;
		}
		while(ans.size() > K) ans.pop_back();
		if(smaller(ans,fin)) fin = ans;
	}
	cout << fin << endl;
	return 0;
}