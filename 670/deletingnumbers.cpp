using namespace std;

#include <iostream>
#include <vector>
#include <set>

#define MAXN 100005
#define SQRT 98

long long qryA(long long x) {
	long long res;
	cout << "A " << x << endl;
	cin >> res;
	return res;
}

long long qryB(long long x) {
	long long res;
	cout << "B " << x << endl;
	cin >> res;
	return res;
}

void qryC(long long x) {
	cout << "C " << x << endl;
	return;
}

long long N,spf[MAXN];
vector<long long> ps,pos;
set<long long> s;
bool vis[MAXN];

void sieve() {
	spf[1] = 1;
	for(long long i = 2;i <= N;++i) {
		if(spf[i]) continue;
		spf[i] = i;
		ps.push_back(i);
		if(1ll * i * i > N) continue;
		for(long long j = i * i;j <= N;j += i) {
			if(!spf[j]) spf[j] = i;
		}
	}
	return;
}


int main() {
	cin >> N;
	for(long long i = 1;i <= N;++i) {
		s.insert(i);
	}
	sieve();
	long long ans = 1;
	long long last = 0;
	bool flag = false;
	for(long long i = 0;i < ps.size();++i) {
		long long cnt = 0;
		for(long long j = ps[i];j <= N;j += ps[i]) {
			cnt += (s.find(j) != s.end());
			s.erase(j);
		}
		if(qryB(ps[i]) != cnt) {
			for(long long j = ps[i];ans * ps[i] <= N;j *= ps[i]) {
				if(qryA(j)) {
					ans *= ps[i];
				}else{
					break;
				}
			}
		}
		if(flag) continue;
		if(i % SQRT == (ps.size() - 1) % SQRT) {
			if(qryA(1) != s.size()) {
				flag = true;
				for(long long j = last;j <= i;++j) {
					if(qryA(ps[j])) {
						for(long long k = ps[j];ans * ps[j] <= N;k *= ps[j]) {
							if(qryA(k)) {
								ans *= ps[j];
							}else{
								break;
							}
						}
						break;
					}
				}
			}
			last = i + 1;
		}
	}
	qryC(ans);
	return 0;
}