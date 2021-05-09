using namespace std;

#include <iostream>
#include <algorithm>
#include <tuple>
#include <math.h>
#include <vector>
#include <iomanip>

// Geo template, points , lines , polygons , intersections

#define MAXN 1000005

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
 
typedef Point<double> P;
double segDist(P& s, P& e, P& p) {
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}
template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	for(int i = 0;i < v.size() - 1;++i) a += v[i].cross(v[i+1]);
	return a;
}
 
 
template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
 
template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = p.size();
	for(int i = 0;i < n;++i) {
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a)) return !strict;
		//or: if (segDist(p[i], q, a) <= eps) return !strict;
		cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}

vector<Point<double>> poly[MAXN];
double H,W;
int N,Q;
 
int main() {
	scanf("%lf %lf %d",&H,&W,&N);
	for(int i = 0;i < N;++i) {
		int k;
		cin >> k;
		for(int j = 0;j < k;++j) {
			double x,y;
			// cin >> x >> y;
			scanf("%lf %lf",&x,&y);
			poly[i].push_back(Point<double>{x,y});
		}
	}
	cout << setprecision(6) << fixed;
	scanf("%d",&Q);
	for(int i = 0;i < Q;++i) {
		double x,y,r;
		scanf("%lf %lf %lf",&x,&y,&r);
		Point<double> cur = Point<double>(x,y);
		vector<int> pts;
		double ans = 0;
		for(int j = 0;j < N;++j) {
			bool included = false;
			for(int k = 0;k < poly[j].size();++k) {
				if(segDist(poly[j][k],poly[j][(k + 1) % poly[j].size()],cur) <= r * (1 + 1e-8)) {
					included = true;
					break;
				}
			}
			included |= inPolygon(poly[j],cur);
			if(included) {
				ans += polygonArea2(poly[j]);
				pts.push_back(j);
			}
		}
		cout << (ans / 2) << " " << pts.size();
		for(int id : pts) cout << " " << id;
		printf("\n");
	}
	return 0;
}