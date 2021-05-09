using namespace std;

#include <iostream>
#include <vector>

#define MAXN 5005

int N;
long long x[MAXN],y[MAXN];
vector<int> per;

long long cross(int a,int b,int c) {
	return (x[a] - x[b]) * (x[b] - x[c]) + (y[a] - y[b]) * (y[b] - y[c]);
}

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> x[i] >> y[i];
	}
	for(int i = 0;i < N;++i) {
		per.push_back(i);
		for(int j = per.size() - 1;j > 1;--j) {
			if(cross(per[j],per[j - 1],per[j - 2]) >= 0) {
				swap(per[j],per[j - 1]);
			}else{
				break;
			}
		}
	}
	for(int i = 0;i < per.size();++i) {
		cout << per[i] + 1 << " ";
	}
	cout << endl;
}