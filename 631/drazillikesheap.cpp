using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>

#define MAXN 1048576

int H,G,h[MAXN],v2i[MAXN];
long long arr[2 * MAXN],sum;

void f(int i) {
	int l = 2 * i,r = 2 * i + 1;
	if(arr[l] == 0 && arr[r] == 0) {
		arr[i] = 0;
	}else if(arr[l] > arr[r]) {
		arr[i] = arr[l];
		f(l);
	}else{
		arr[i] = arr[r];
		f(r);
	}
	v2i[arr[i]] = i;
	return;
}

bool test(int i) {
	int l = 2 * i,r = 2 * i + 1;
	if(arr[l] == 0 && arr[r] == 0) {
		// cout << "HELLO " << h[i] << endl;
		return h[i] >= G;
	}else if(arr[l] > arr[r]) {
		return test(l);
	}
	return test(r);
}

void solve() {
	cin >> H >> G;
	vector<int> v;
	sum = 0;
	memset(h,0,sizeof(h[0]) * (1 << H));
	memset(arr,0,sizeof(arr[0]) * (2 << H));

	for(int i = 1;i < (1 << H);++i) {
		cin >> arr[i];
		sum += arr[i];
		v.push_back(arr[i]);
		v2i[arr[i]] = i;
		h[i] = (i > 1 ? h[i >> 1] + 1 : 0);
	}
	for(int i = 1;i < (1 << H);++i) {
		for(int j = 0;j < N;++j) {
			
		}
	}
	sort(v.begin(),v.end(),[&](int a,int b) {return a > b;});
	vector<int> ans;
	for(int i = 0,j = (1 << H) - 1;i < v.size() && j > (1 << G) - 1;++i) {
		// cout << i << " " << j << endl;
		if(test(v2i[v[i]])) {
			sum -= v[i];
			j--;
			ans.push_back(v2i[v[i]]);
			// cout << "Taking " << v[i] << endl;
			f(v2i[v[i]]);
		}
	}
	cout << sum << endl;
	for(int i = 0;i < ans.size();++i) {
		cout << ans[i] << " \n"[i == ans.size() - 1];
	}
	// for(int i = 1;i < (1 << H);++i) {
	// 	cout << arr[i] << " ";
	// }
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
}