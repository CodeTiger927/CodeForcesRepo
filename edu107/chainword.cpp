using namespace std;

#include <iostream>
#include <map>
#include <cstring>
#include <queue>

#define MAXN 45
#define MAXM 26
#define MAXK 162
#define MOD 998244353

map<pair<int,int>,int> num;
int N,M,trie[MAXN][MAXM],t,t2;
bool term[MAXN];
queue<pair<int,int>> q;

struct matrix {
	long long a[MAXK][MAXK];
	matrix() {memset(a,0,sizeof(a));}
	matrix(int v[MAXK][MAXK]) {memcpy(a,v,sizeof(a));}
	void addE() {for(int i = 0;i < MAXK;i++) a[i][i]++;}
	matrix operator *(const matrix &b) {
		matrix ret;
		for(int i = 0;i < MAXK;i++)
			for(int j = 0;j < MAXK;j++)
				for(int k = 0;k < MAXK;k++)
					ret.a[i][k]=(ret.a[i][k] + a[i][j] * 1LL * b.a[j][k]) % MOD;
		return ret;
	}
};

matrix fastpow(matrix x,long long a) {
	matrix ret;ret.addE();
	while(a) {
		if(a & 1) ret = ret*x;
		x = x * x;
		a >>= 1;
	}
	return ret;
}

void add(string str) {
	int ptr = 0;
	for(int i = 0;i < str.size();++i) {
		if(trie[ptr][str[i] - 'a'] == -1) {
			trie[ptr][str[i] - 'a'] = ++t;
		}
		ptr = trie[ptr][str[i] - 'a'];
	}
	term[ptr] = true;
	return;
}

int get(int u,int v) {
	if(u > v) swap(u,v);
	if(num.find({u,v}) == num.end()) {
		num[{u,v}] = t2++;
		q.push({u,v});
	}
	return num[{u,v}];
}


int main() {
	memset(trie,-1,sizeof(trie));
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		string str;
		cin >> str;
		add(str);
	}

	get(0,0);

	matrix mat;
	while(!q.empty()) {
		pair<int,int> cur = q.front();
		q.pop();
		int c = get(cur.first,cur.second);
		for(int i = 0;i < MAXM;++i) {
			int nu = trie[cur.first][i];
			int nv = trie[cur.second][i];
			if(nu == -1 || nv == -1) continue;
			mat.a[c][get(nu,nv)]++;
			if(term[nu]) mat.a[c][get(0,nv)]++;
			if(term[nv]) mat.a[c][get(nu,0)]++;
			if(term[nu] && term[nv]) mat.a[c][get(0,0)]++;
		}
	}
	mat = fastpow(mat,M);
	cout << mat.a[0][0] << endl;
	return 0;
}