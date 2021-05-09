using namespace std;

#include <iostream>
#include <vector>

int N;

int ask(int a,int A,int b,int B) {
	cout << "? " << (A - a + 1) << " " << (B - b + 1) << endl;
	for(int i = a;i <= A;++i) {
		cout << i << " ";
	}
	cout << endl;
	for(int i = b;i <= B;++i) {
		cout << i << " ";
	}
	cout << endl;
	int res;
	cin >> res;
	return res;
}

void solve() {
	cin >> N;
	vector<int> ans;
	int mag = -1;
	for(int i = 2;i <= N;++i) {
		int res = ask(1,i - 1,i,i);
		if(res) {
			mag = i;
			break;
		}
	}
	for(int i = mag + 1;i <= N;++i) {
		int res = ask(mag,mag,i,i);
		if(!res) {
			ans.push_back(i);
		}
	}
	int l = 1;
	int r = mag - 1;
	while(l < r) {
		int m = (l + r) >> 1;
		int res = ask(l,m,mag,mag);
		if(res) {
			r = m;
		}else{
			l = m + 1;
		}
	}
	for(int i = 1;i < mag;++i) {
		if(i == l) continue;
		ans.push_back(i);
	}
	cout << "! " << ans.size();
	for(int i = 0;i < ans.size();++i) {
		cout << " " << ans[i];
	}
	cout << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}