using namespace std;

#include <iostream>

#define MAXN 200005

int N,Q,arr[MAXN];

struct tree {
	int l, r, add, lv, rv;
	long long sum;
}tr[MAXN << 2];
 
void Add(int rt, int x) {
	tr[rt].lv = tr[rt].rv = tr[rt].add = x;
	tr[rt].sum = 1ll * (tr[rt].r - tr[rt].l + 1) * x;
}
void Pushdown(int rt) {
	if(tr[rt].add) {
		Add(rt << 1, tr[rt].add);
		Add(rt << 1 | 1, tr[rt].add);
		tr[rt].add = 0;
	}
}
void Pushup(int rt) {
	tr[rt].lv = tr[rt << 1].lv;
	tr[rt].rv = tr[rt << 1 | 1].rv;
	tr[rt].sum = tr[rt << 1].sum + tr[rt << 1 | 1].sum;
}
void Build(int rt, int l, int r) {
	tr[rt].l = l, tr[rt].r = r;
	if(l == r) {
		tr[rt].sum = tr[rt].lv = tr[rt].rv = arr[l];
		tr[rt].add = 0;
		return;
	}
	int mid = (l + r) >> 1;
	Build(rt << 1, l, mid), Build(rt << 1 | 1, mid + 1, r);
	Pushup(rt);
}
void Modify(int rt, int x, int y) {
	if(tr[rt].l > x) return;
	if(tr[rt].rv >= y) return;
	if(tr[rt].lv <= y && tr[rt].r <= x)
		return Add(rt, y);
	Pushdown(rt);
	Modify(rt << 1, x, y), Modify(rt << 1 | 1, x, y);
	Pushup(rt);
}
int Ask(int rt, int x, int &y) {
	if(y < tr[rt].rv || tr[rt].r < x) return 0;
	int ret = 0;
	if(tr[rt].l >= x && tr[rt].sum <= y)
		return y -= tr[rt].sum, x = tr[rt].r + 1, tr[rt].r - tr[rt].l + 1;
	if(tr[rt].l == tr[rt].r) return 0;
	Pushdown(rt);
	ret += Ask(rt << 1, x, y);
	ret += Ask(rt << 1 | 1, x, y);
	return ret;
}
int main() {
	scanf("%d %d",&N,&Q);
	for(int i = 1;i <= N;++i) {
		scanf("%d",&arr[i]);
	}
	Build(1,1,N);
	while(Q--) {
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		if(a == 1) {
			Modify(1,b,c);
		}else{
			printf("%d\n",Ask(1,b,c));
		}
	}
	return 0;
}