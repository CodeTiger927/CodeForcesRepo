using namespace std;

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <set>
#include <algorithm>

#define MAXN 1000005
#define INF 1e18

long long N,K;
unordered_map<long long,int> rev,id;
vector<long long> primes,groups,numbers[MAXN],numberss[MAXN]; // primes <= 1e6
bool isp[MAXN];
long long arr[MAXN];

void sieve() {
	isp[1] = false;
	for(int i = 2;i < MAXN;++i) {
		if(isp[i]) continue;
		primes.push_back(i);
		if(1ll * i * i >= MAXN) continue;
		for(int j = i * i;j < MAXN;j += i) {
			isp[j] = true;
		}
	}
}

int main() {
	sieve();
	cin >> N >> K;
	if(K == 1) {
		cout << 0 << endl;
		return 0;
	}
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		id[arr[i]] = i + 1;
	}
	long long sum = 0;
	for(int i = 0;i < primes.size();++i) {
		// prime groups with p^q where q >= 3
		long long cur = 1;
		vector<int> pos;
		while(cur <= INF / primes[i]) {
			cur *= primes[i];
			if(id[cur]) {
				pos.push_back(id[cur]);
			}
		}
		if(pos.size() >= 2) {
			rev[primes[i]] = groups.size();
			groups.push_back(primes[i]);
			sum += pos.size();
			for(int j = 0;j < pos.size();++j) {
				numberss[rev[primes[i]]].push_back(pos[j] - 1);
			}
		}
	}
	for(int i = 0;i < N;++i) {
		bool isPrime = true;
		if(arr[i] < MAXN || arr[i] > 1e9) continue;
		for(int j = 2;j <= sqrt(arr[i]);++j) {
			if(arr[i] % j == 0) {
				isPrime = false;
				break;
			}
		}
		if(isPrime) {
			for(int j = 0;j < N;++j) {
				if(arr[j] == arr[i] * arr[i]) {
					rev[arr[i]] = groups.size();
					groups.push_back(arr[i]);
					numberss[rev[arr[i]]] = {i,j};
					sum += 2;
				}
			}
		}
	}
	sort(groups.begin(),groups.end(),[&](int a,int b) {return numberss[rev[a]].size() > numberss[rev[b]].size();});
	for(int i = 0;i < groups.size();++i) {
		for(int j = 0;j < numberss[rev[groups[i]]].size();++j) {
			numbers[i].push_back(numberss[rev[groups[i]]][j]);
		}
	}
	vector<long long> ans;
	if(sum >= K) {
		bool all2 = true;
		int big3 = -1;
		for(int i = 0;i < groups.size();++i) {
			all2 &= (numbers[i].size() == 2);
			if(numbers[i].size() > 2) big3 = i;
		}
		if(K % 2 == 0) {
			vector<int> tmp;
			// just output all of them
			for(int i = 0;i < groups.size();++i) {
				if(numbers[i].size() % 2) tmp.push_back(i);
				for(int j = 0;j < min((size_t)K,numbers[i].size()) >> 1 << 1;++j) {
					ans.push_back(numbers[i][j]);
				}
				K -= min((size_t)K,numbers[i].size()) >> 1 << 1;
			}
			for(int j = 0;j < K;++j) {
				ans.push_back(numbers[tmp[j]].back());
			}
			K = 0;
		}else{
			if(all2) {
				int record = N + 1;
				int r = -1;
				for(int i = 0;i < N;++i) {
					int counter = 0;
					long long cur = arr[i];
					for(int j = 0;j < groups.size();++j) {
						if(arr[i] % groups[j] == 0) counter++;
						while(cur % groups[j] == 0) cur /= groups[j];
					}
					if(counter != 1 && counter < record && cur == 1) {
						record = counter;
						r = i;
					}
				}
				if(r == -1 || record > ((K - 1) / 2)) {
					cout << 0 << endl;
					return 0;
				}
				K--;
				set<int> duplicates;
				for(int i = 0;i < groups.size();++i) {
					if(arr[r] % groups[i] != 0) continue;
					duplicates.insert(i);
					for(int j = 0;j < min((size_t)K,numbers[i].size());++j) {
						ans.push_back(numbers[i][j]);
					}
					K -= min((size_t)K,numbers[i].size());
				}

				for(int i = 0;i < groups.size();++i) {
					if(duplicates.find(i) != duplicates.end()) continue;
					for(int j = 0;j < min((size_t)K,numbers[i].size());++j) {
						ans.push_back(numbers[i][j]);
					}
					K -= min((size_t)K,numbers[i].size());
				}
				ans.push_back(r);
			}else{
				// just output all of them
				for(int i = 0;i < groups.size();++i) {
					if(K == 1) break;
					for(int j = 0;j < min((size_t)K,numbers[i].size());++j) {
						ans.push_back(numbers[i][j]);
					}
					K -= min((size_t)K,numbers[i].size());
				}
				if(K == 1) {
					ans.erase(ans.begin());
					for(int j = 0;j < 2;++j) {
						ans.push_back(numbers[groups.size() - 1][numbers[groups.size() - 1].size() - 1 - j]);
					}
				}
				K = 0;
			}
		}
	}else{
		for(int i = 0;i < groups.size();++i) {
			for(int j = 0;j < min((size_t)K,numbers[i].size());++j) {
				ans.push_back(numbers[i][j]);
			}
			K -= min((size_t)K,numbers[i].size());
		}
		for(int i = 0;i < N;++i) {
			int counter = 0;
			long long cur = arr[i];
			for(int j = 0;j < groups.size();++j) {
				if(arr[i] % groups[j] == 0) counter++;
				while(cur % groups[j] == 0) cur /= groups[j];
			}
			if(counter != 1 && counter >= 2 && cur == 1) {
				ans.push_back(i);
				K--;
			}
			if(!K) break;
		}
	}
	if(K) {
		cout << 0 << endl;
	}else{
		for(int i = 0;i < ans.size();++i) {
			cout << arr[ans[i]] << " ";
		}
		cout << endl;
	}
	return 0;
}