using namespace std;

#include <iostream>
#include <map>

#define MAXN 1000005

int N,arr[MAXN],sum,ans;
map<int,int> f[2][21];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < 20;++i) f[0][i][0] = 0;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i];
		sum ^= arr[i];
		for(int j = 0;j < 20;++j) {
			if(!f[i & 1][j].count(sum >> j)) f[i & 1][j][sum >> j] = i;
			if((arr[i] >> j) & 1) {
				ans = max(ans,i - f[i & 1][j][sum >> j]);
			}else{
				f[0][j].clear();
				f[1][j].clear();
				f[i & 1][j][sum >> j] = i;
			}
		}
	}
	cout << ans << endl;
	return 0;
}