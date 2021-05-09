using namespace std;

#include <iostream>
#include <cstring>

#define MOD 1007130781

long long 

long long pow2(long long exp) {
	if(exp == 0) return 1;
	if(exp == 1) return 2;
	long long tmp = pow2(exp / 2);
	if(exp & 1) {
		return (2 * (tmp * tmp) % MOD) % MOD;
	}
	return (tmp * tmp) % MOD;
}

string str,str2;
int cnt0,cnt1;

int main() {
	cin >> str >> str2;
	for(int i = 0;i < str.length();++i) {
		if(str[i] == '0') {
			cnt0++;
		}else{
			cnt1++;
		}
	}
	long long hash1,hash2;
	hash1 = hash2 = 0;
	int optimal = -1;
	for(int i = 0;i < str2.length() - 1;++i) {
		hash1 = (2 * hash1 + (str2[i] - '0')) % MOD;
		if(str2[str2.length() - i - 1] == '1') {
			hash2 += pow2(i);
			if(hash2 >= MOD) hash2 -= MOD;
		}
		if(hash1 == hash2) {
			optimal = i;
		}
	}
	int cnt20 = 0;
	int cnt21 = 0;
	for(int i = 0;i < str2.length();++i) {
		if(str2[i] == '0') {
			cnt20++;
		}else{
			cnt21++;
		}
	}
	if(cnt20 > cnt0 || cnt21 > cnt1) {
		cout << str << endl;
		return 0;
	}
	string ans = str2;
	cnt0 -= cnt20;
	cnt1 -= cnt21;
	int curP = optimal + 1;
	while(cnt0 > 0 && cnt1 > 0) {
		ans += str2[curP];
		if(str2[curP] == '0') {
			cnt0--;
		}else{
			cnt1--;
		}
		curP++;
		if(curP >= str2.length()) curP = optimal + 1;
	}
	for(int i = 0;i < cnt0;++i) {
		ans += '0';
	}
	for(int i = 0;i < cnt1;++i) {
		ans += '1';
	}
	for(int i = 0;i < cnt0;++i) {
		ans += '1';
	}
	cout << ans << endl;
	return 0;
}