using namespace std;

#include <iostream>
#include <vector>

#define MAXN 100005

int N,Q;
long long arr[MAXN];

int main() {
	cin >> N >> Q;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	for(int i = 0;i < N;++i) {
		int cur;
		cin >> cur;
		arr[i] -= cur;
	}
	for(int i = 0;i < Q;++i) {
		int l,r;
		cin >> l >> r;
		l--;r--;
		vector<long long > v;
		long long ans = 0;
		long long sum = 0;
		for(int j = l;j <= r;++j) {
			sum += arr[j];
			if(sum > 0) {
				cout << -1 << endl;
				// cout << -1 << " " << l << " " << j << " " << arr[j] << endl;
				break;
			}
			if(arr[j] == 0) continue;
			if(v.size() == 0) {
				v.push_back(arr[j]);
				ans = max(ans,abs(arr[j]));
			}else{
				long long last = v.back();
				if(1ll * last * arr[j] > 0) {
					v.pop_back();
					v.push_back(last + arr[j]);
				}else{
					v.push_back(arr[j]);
				}
				ans = max(ans,abs(v.back()));
			}
		}
		if(sum == 0) {
			cout << ans << endl;
		}else if(sum < 0) {
			cout << -1 << endl;
		}
	}
	return 0;
}