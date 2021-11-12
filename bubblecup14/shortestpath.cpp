using namespace std;

#include <iostream>
#include <math.h>
#include <algorithm>
#include <iomanip>

#define MAXN 200005

int N,M;
pair<long long,long long> arr[MAXN],s;

long double dist(int a,int b) {
	return sqrt((arr[a].first - arr[b].first) * (arr[a].first - arr[b].first) + (arr[a].second - arr[b].second) * (arr[a].second - arr[b].second));
}

bool chk(int a,int b,int c) {
	return ((arr[b].first - arr[a].first) * (arr[c].second - arr[a].second) - (arr[c].first - arr[a].first) * (arr[b].second - arr[a].second)) == 0;
}

int main() {
	cin >> N >> M;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i].first >> arr[i].second;
	}
	s = arr[M];
	if(chk(1,2,3)) {
		for(int i = 4;i <= N;++i) {
			if(!chk(1,2,i)) {
				swap(arr[i],arr[N]);
				break;
			}
		}
	}else if(N > 3) {
		if(chk(1,2,4)) {
			swap(arr[3],arr[N]);
		}else if(chk(1,3,4)) {
			swap(arr[2],arr[N]);
		}else{
			swap(arr[1],arr[N]);
		}
	}
	sort(arr + 1,arr + N);
	for(int i = 1;i <= N;++i) {
		if(arr[i] == s) M = i;
	}
	cout << setprecision(10) << fixed;
	if(M == N) {
		cout << min(dist(1,N),dist(N - 1,N)) + dist(1,N - 1) << endl;
		return 0;
	}
	long double ans = dist(1,N - 1) + min(dist(1,M) + dist(N - 1,N),dist(M,N - 1) + dist(1,N));
	for(int i = 1;i < N - 1;++i) {
		int A = i;
		int B = i + 1;
		int C = 1;
		int D = N - 1;
		if(i < M) {
			swap(A,B);
			swap(C,D);
		}
		ans = min(ans,min(dist(M,A) + dist(A,C) + dist(C,N) + dist(N,B) + dist(B,D),
			dist(M,C) + dist(C,A) + dist(A,N) + dist(N,B) + dist(B,D)));
	}
	cout << ans << endl;
	return 0;
}