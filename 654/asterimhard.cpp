using namespace std;

#include <iostream>
#include <algorithm>

#define MAXN 100005

int N,K,arr[MAXN];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> N >> K;
	
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	sort(arr,arr + N);
	
	int a = 0;
	int b = 2e9;
	for(int i = 0; i < N; i++){
		a = max(a,arr[i] - i);
		if(i >= K - 1) b = min(b,arr[i] - i + K - 1);
	}
	
	cout << max(0,b - a) << endl;
	for(int i = a;i < b;++i) {
		cout << i << " ";
	}
	cout << endl;
}	