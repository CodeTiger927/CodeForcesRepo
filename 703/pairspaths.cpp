using namespace std;

#include <iostream>
#include <vector>
#include <unordered_map>

#define MAXN 300005

int N,M,parent[MAXN][20],aa[MAXN],ab[MAXN],depth[MAXN],sum[MAXN];
unordered_map<int,int> straight[MAXN];
vector<int> edges[MAXN],nodes[MAXN];

struct pair_hash {
    template <class T1,class T2>
	std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

void dfs(int cur) {
	for(int i = 0;i < edges[cur].size();++i) {
		int nxt = edges[cur][i];
		if(nxt == parent[cur][0]) continue;
		parent[nxt][0] = cur;
		depth[nxt] = depth[cur] + 1;
		dfs(nxt);
	}
	return;
}

void preCompSparseMatrix() {
	for(int i = 1;i < 20;++i) {
		for(int j = 0;j < N;++j) {
			parent[j][i] = parent[parent[j][i - 1]][i - 1];
		}
	}
}

int LCA(int u,int v) {
	if(depth[v] < depth[u]) return LCA(v,u);

	int dif = depth[v] - depth[u];
	for(int i = 0;i < 20;i++) {
		if((dif >> i) & 1) {
			v = parent[v][i];
		}
	}

	if(u == v) {
		return u;
	}

	for(int i = 19;i >= 0;--i) {
		if(parent[u][i] != parent[v][i]) {
			u = parent[u][i];
			v = parent[v][i];
		}
	}
	return parent[u][0];
}

// node under the ancestor
int top(int cur,int anc) {
	if(cur == anc) return cur;
	for(int i = 19;i >= 0;--i) {
		if(depth[parent[cur][i]] > depth[anc]) {
			cur = parent[cur][i];
		}
	}
	return cur;
}

long long dfs2(int cur) {
	long long res = 0;
	for(int i = 0;i < edges[cur].size();++i) {
		int nxt = edges[cur][i];
		if(nxt == parent[cur][0]) continue;
		res += dfs2(nxt);
		sum[cur] += sum[nxt];
		straight[cur][nxt] += sum[nxt];
	}
	// Straight intersect bent
	res += 1ll * nodes[cur].size() * sum[cur];

	// from each subtree, top(a),top(b)
	unordered_map<pair<int,int>,int,pair_hash> tab;
	unordered_map<int,int> tall;
	int counter = 0;
	int counter2 = 0;
	for(int i = 0;i < nodes[cur].size();++i) {
		int curP = nodes[cur][i];
		if(aa[curP] == cur && ab[curP] == cur) {
			res += 1ll * nodes[cur].size() - 1 - counter2;
			counter2++;
			continue;
		}
		int topA = (aa[curP] == cur) ? -1 : top(aa[curP],cur);
		int topB = (ab[curP] == cur) ? -1 : top(ab[curP],cur);
		if(topA > topB) swap(topA,topB);
		// bent intersects bent
		res += 1ll * counter - (topA != -1) * tall[topA] - tall[topB] + (topA != -1) * tab[make_pair(topA,topB)];
		counter++;
		// bent intersects straight a bit too much
		res -= 1ll * straight[cur][topA] + (topA != topB) * straight[cur][topB];
		tall[topA]++;
		tall[topB]++;
		tab[make_pair(topA,topB)]++;
	}
	return res;
}

int main() {
	cin >> N;
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(0);
	preCompSparseMatrix();
	cin >> M;
	for(int i = 0;i < M;++i) {
		cin >> aa[i] >> ab[i];
		aa[i]--;ab[i]--;
		int l = LCA(aa[i],ab[i]);
		nodes[l].push_back(i);
		straight[l][top(aa[i],l)]--;
		straight[l][top(ab[i],l)]--;
		sum[l] -= 2;
		straight[aa[i]][aa[i]]++;
		straight[ab[i]][ab[i]]++;
		sum[aa[i]]++;
		sum[ab[i]]++;
	}
	long long ans = dfs2(0);
	cout << ans << endl;
	return 0;
}