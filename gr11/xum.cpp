using namespace std;

#include <iostream>
#include <vector>

long long N;
vector<pair<pair<long long,long long>,int>> ans;

long long sum(long long a,long long b) {
	if(a != 0 && b != 0) ans.push_back({{a,b},0});
	return a + b;
}

long long xxor(long long a,long long b) {
	ans.push_back({{a,b},1});
	return a ^ b;
}

long long mul(long long a,long long b) {
	long long ret = 0;
	for(;b;b >>= 1) {
		if(b & 1) ret = sum(ret,a);
		a = sum(a,a);
	}
	return ret;
}

long long exgcd(long long a,long long b,long long& x,long long& y) {
	if(!b) {
		x = 1;y = 0;
		return a;
	}
	long long tx,ty;
	long long g = exgcd(b,a % b,tx,ty);
	x = ty;
	y = tx - (a / b) * ty;
	return g;
}

int main() {
	cin >> N;
	long long l = 1;
	while((l << 1) <= N) l <<= 1;
	long long K = mul(N,l);
	long long M = xxor(N,K);
	long long x,y;
	exgcd(N,M,x,y);
	if(x < 0) {
		swap(N,M);
		swap(x,y);
	}
	if((x & 1) == 0) {
		y -= N;
		x += M;
	}
	long long a = mul(N,x);
	long long b = mul(M,-y);

	long long res = xxor(a,b);
	cout << ans.size() << endl;
	for(int i = 0;i < ans.size();++i) {
		if(ans[i].second) {
			cout << ans[i].first.first << " ^ " << ans[i].first.second << endl; 
		}else{
			cout << ans[i].first.first << " + " << ans[i].first.second << endl; 
		}
	}
	return 0;
}