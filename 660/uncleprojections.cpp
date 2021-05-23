using namespace std;

#include <iostream>
#include <set>
#include <assert.h>
#include <limits>
#include <iomanip>

#define MAXN 2005

struct Line {
	mutable double k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(double x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const constexpr double inf = LLONG_MAX;
	double div(double a, double b) { // floored division
		return a / b; }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(double k, double m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	double query(double x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

set<pair<double,double>>::iterator addInterval(set<pair<double,double>>& is,double L,double R) {
	auto it = is.lower_bound({L, R}),before = it;
	while(it != is.end() && it -> first < R) {
		R = max(R, it -> second);
		before = it = is.erase(it);
	}
	if(it != is.begin() && (--it) -> second > L) {
		L = min(L, it -> first);
		R = max(R, it -> second);
		is.erase(it);
	}
	return is.insert(before,{L,R});

}

int N;
double L[MAXN],R[MAXN],Y[MAXN],mL,mR;
set<pair<double,double>> s;

double slope(double x1,double y1,double x2,double y2) {
	return (x1 - x2) / (y1 - y2);
}

int main() {
	LineContainer lc,lc2;

	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> L[i] >> R[i] >> Y[i];
		lc.add(-Y[i],L[i]);
		lc.add(-Y[i],R[i]);
		lc2.add(Y[i],-L[i]);
		lc2.add(Y[i],-R[i]);
		mL = min((i == 0 ? L[i] : mL),L[i]);
		mR = max((i == 0 ? R[i] : mR),R[i]);
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < i;++j) {
			if(Y[i] == Y[j]) continue;
			double slope1 = slope(L[i],Y[i],R[j],Y[j]);
			double slope2 = slope(R[i],Y[i],L[j],Y[j]);
			if(slope1 > slope2) swap(slope1,slope2);
			addInterval(s,slope1,slope2);
		}
	}
	if(s.empty()) {
		cout << fixed << setprecision(9) << (mR - mL) << endl;
		return 0;
	}

	double ans = 1e18;
	for(auto p : s) {
		ans = min(ans,lc.query(p.first) + lc2.query(p.first));
		ans = min(ans,lc.query(p.second) + lc2.query(p.second));
	}
	cout << fixed << setprecision(9) << ans << endl;
	return 0;
}