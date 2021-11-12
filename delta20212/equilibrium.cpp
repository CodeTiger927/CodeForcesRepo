using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <set>

#define MAXN 100005
#define MAXQ 100005
// BLOCK_SIZE = N / sqrt(Q) Complexity = O(Nsqrt(Q))
#define BLOCK_SIZE 320

struct query {
	int s,e,id;
};

auto cmp = [](query a,query b) {
	int ln = a.s / BLOCK_SIZE;
	int rn = b.s / BLOCK_SIZE;
	return (ln < rn) || (ln == rn && a.e < b.e);
};


int N,Q;
long long arr[MAXN],ans[MAXQ];
vector<query> queries;

// Count number of distinct elements in a range

int curL = 1;
int curR = 0;
long long moAns = 0;

deque<long long> deq;
multiset<long long> ms;

bool sameSign(long long a,long long b) {
	return !((a > 0) ^ (b > 0));
}

void insertR(long long x) {
	if(x == 0) return;
	if(deq.size() == 0) {
		deq.push_back(x);
		ms.insert(x);
	}else{
		long long l = deq.back();
		if(sameSign(l,x)) {
			ms.erase(ms.find(l));
			deq.pop_back();
			deq.push_back(l + x);
			ms.insert(l + x);
		}else{
			deq.push_back(x);
			ms.insert(x);
		}
	}
	moAns = ms.empty() ? 0 : max(abs(*ms.rbegin()),abs(*ms.begin()));
}

void insertL(long long x) {
	if(x == 0) return;
	if(deq.size() == 0) {
		deq.push_front(x);
		ms.insert(x);
		return;
	}else{
		long long l = deq.front();
		if(sameSign(l,x)) {
			ms.erase(ms.find(l));
			deq.pop_front();
			deq.push_front(l + x);
			ms.insert(l + x);
		}else{
			deq.push_front(x);
			ms.insert(x);
		}
	}
	
	moAns = ms.empty() ? 0 : max(abs(*ms.rbegin()),abs(*ms.begin()));
}

void removeR(long long x) {
	if(x == 0) return;
	long long l = deq.back();
	if(l == x) {
		ms.erase(ms.find(l));
		deq.pop_back();
	}else{
		ms.erase(ms.find(l));
		deq.pop_back();
		deq.push_back(l - x);
		ms.insert(l - x);
	}
	
	moAns = ms.empty() ? 0 : max(abs(*ms.rbegin()),abs(*ms.begin()));
}

void removeL(long long x) {
	if(x == 0) return;
	long long l = deq.front();
	if(l == x) {
		ms.erase(ms.find(l));
		deq.pop_front();
	}else{
		ms.erase(ms.find(l));
		deq.pop_front();
		deq.push_front(l - x);
		ms.insert(l - x);
	}
	
	moAns = ms.empty() ? 0 : max(abs(*ms.rbegin()),abs(*ms.begin()));
}

void mo() {
	for(int i = 0;i < Q;++i) {
		while(curR < queries[i].e) insertR(arr[++curR]);
		while(curL > queries[i].s) insertL(arr[--curL]);
		while(curR > queries[i].e) removeR(arr[curR--]);
		while(curL < queries[i].s) removeL(arr[curL++]);
		ans[queries[i].id] = moAns;
	}
	return;
}

long long st[262144];

void update(int x,long long v,int l,int r,int p) {
	if(l > x || r < x) return;
	if(l == r) {
		st[p] = v;
		return;
	}
	int m = (l + r) / 2;
	update(x,v,l,m,2 * p + 1);
	update(x,v,m + 1,r,2 * p + 2);
	st[p] = max(st[2 * p + 1],st[2 * p + 2]);
	return;
}

void update(int x,long long v) {
	update(x,v,0,MAXN,0);
}

long long getMax(int a,int b,int l,int r,int p) {
	if(l > b || r < a) return -1e18;
	if(l >= a && r <= b) return st[p];
	int m = (l + r) / 2;
	return max(getMax(a,b,l,m,2 * p + 1),getMax(a,b,m + 1,r,2 * p + 2));
}

long long getMax(int a,int b) {
	return getMax(a,b,0,MAXN,0);
}

long long pre[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> Q;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	for(int i = 0;i < N;++i) {
		long long cur;
		cin >> cur;
		arr[i] -= cur;
		pre[i + 1] = pre[i] + arr[i];
		update(i,pre[i + 1]);
	}
	for(int i = 0;i < Q;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		queries.push_back({a,b,i});
	}
	sort(queries.begin(),queries.end(),cmp);
	mo();
	for(int i = 0;i < Q;++i) {
		int l = queries[i].s;
		int r = queries[i].e;
		if(pre[r + 1] - pre[l] != 0 || getMax(l,r) > pre[l]) {
			ans[queries[i].id] = -1;
		}
	}
	for(int i = 0;i < Q;++i) {
		cout << ans[i] << "\n";
	}
	return 0;
}