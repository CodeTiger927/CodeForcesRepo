using namespace std;

#include <iostream>
#include <iomanip>
#include <math.h>

#define MAXN 100005

int N;
long double x[MAXN],y[MAXN];

long double area(long double x1,long double y1,long double x2,long double y2,long double x3,long double y3) {
	return abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
}

long double dist(long double x1,long double y1,long double x2,long double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

long double dist(long double x1,long double y1,long double x2,long double y2,long double x3,long double y3) {
	return area(x1,y1,x2,y2,x3,y3) / dist(x2,y2,x3,y3);
}

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> x[i] >> y[i];
	}
	x[N] = x[0];
	x[N + 1] = x[1];
	y[N] = y[0];
	y[N + 1] = y[1];
	long double ans = 1e18;
	for(int i = 0;i < N;++i) {
		ans = min(ans,dist(x[i],y[i],x[i + 1],y[i + 1]));
		ans = min(ans,dist(x[i + 1],y[i + 1],x[i],y[i],x[i + 2],y[i + 2]));
	}
	cout << setprecision(10) << fixed << (ans / 2) << endl;
	return 0;
}