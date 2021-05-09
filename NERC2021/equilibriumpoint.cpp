using namespace std;

#include <iostream>
#include <math.h>
#include <array>
#include <tuple>
#include <map>

#define MAXN 45
#define MAXK 405

int N;
map<array<short,3>,tuple<short,const array<short,3>*,const array<short,3>*>> seq[MAXN];

double x,y;

string printAns(short curH,tuple<short,const array<short,3>*,const array<short,3>*> t) {
	if(curH == 0) return "";
	if(curH == 2) return "()";
	string le = printAns(get<0>(t),seq[get<0>(t)][*get<1>(t)]);
	string ri = printAns(curH - get<0>(t) - 2,seq[curH - get<0>(t) - 2][*get<2>(t)]);
	return "(" + le + ")" + ri;
}

int main() {
	cin >> N >> x >> y;
	array<short,3> tmp = {0,0,0};
	seq[0][{0,0,0}] = {0,&tmp,&tmp};
	for(int i = 2;i <= N;i += 2) {
		for(int j = 0;j <= i - 2;j += 2) {
			for(auto a = seq[j].begin();a != seq[j].end();++a) {
				for(auto b = seq[i - j - 2].begin();b != seq[i - j - 2].end();++b) {
					short nm = (a -> first)[0] + (b -> first)[0] + j + 1;
					short nxm = (a -> first)[1] + (a -> first)[0] + (b -> first)[1] + (j + 2) * (b -> first)[0] + (j / 2 + 1) * (j + 1);
					short nym = (a -> first)[2] + 3 * (a -> first)[0] + (b -> first)[2] + (j * 3 / 2) + 1;
					if(i != 36) seq[i][{nm,nxm,nym}] = make_tuple(j,&(a -> first),&(b -> first));
					if(i == 36) {
						long double nx = 1.0 * nxm / nm;
						long double ny = 1.0 * nym / nm / 3.0;
						if(abs(x - nx) <= 1e-7 && abs(y - ny) <= 1e-7) {
							cout << printAns(N,make_tuple(j,&(a -> first),&(b -> first))) << endl;
							return 0;
						}
					}
				}
			}
		}
	}
	for(auto itr = seq[N].begin();itr != seq[N].end();++itr) {
		long double nx = 1.0 * (itr -> first)[1] / (itr -> first)[0];
		long double ny = 1.0 * (itr -> first)[2] / (itr -> first)[0] / 3.0;
		if(abs(x - nx) <= 1e-7 && abs(y - ny) <= 1e-7) {
			cout << printAns(N,itr -> second) << endl;
			return 0;
		}
	}
	return 0;
}