using namespace std;

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

#define MAXN 300005

struct aho_corasick {
	struct node {
		// Current Value
		int cv;
		// Is it a terminal or not
		bool term;
		// Next node on trie
		map<int,int> nxt;
		// Next node with nxt + fail pointer
		map<int,int> go;
		// Fail pointer
		int fail;
		// Parent node on trie
		int p;

		// Nearest node on fail tree that is a terminal
		int sfail;
		// Maximum values
		multiset<int> vals;

		node() {
			nxt.clear();
			go.clear();
			fail = -1;
			term = false;
			p = -1;
			cv = -1;

			vals.clear();
			sfail = -1;
		}
	};
	vector<node> nodes;

	aho_corasick() {
		nodes = vector<node>(1,node());
	}

	// Add a string to the automaton
	int add(const string& str) {
		int cur = 0;
		for(int i = 0;i < str.size();++i) {
			int c = str[i] - 'a';
			if(!nodes[cur].nxt.count(c)) {
				nodes.push_back(node());
				nodes[cur].nxt[c] = nodes.size() - 1;
				nodes.back().p = cur;
				nodes.back().cv = c;
			}
			cur = nodes[cur].nxt[c];
		}
		nodes[cur].term = true;
		nodes[cur].vals.insert(0);
		return cur;
	}

	// Nxt + Fail
	int go(int v,int c) {
		if(nodes[v].go.count(c)) {
			return nodes[v].go[c];
		}
		if(nodes[v].nxt.count(c)) {
			return nodes[v].go[c] = nodes[v].nxt[c];
		}
		if(v == 0) {
			return nodes[v].go[c] = 0;
		}
		return nodes[v].go[c] = go(fail(v),c);
	}

	// Fail pointer
	int fail(int v) {
		if(nodes[v].fail != -1) {
			return nodes[v].fail;
		}
		if(v == 0 || nodes[v].p == 0) {
			return nodes[v].fail = 0;
		}
		return nodes[v].fail = go(fail(nodes[v].p),nodes[v].cv);
	}

	int sfail(int v) {
		if(nodes[v].sfail != -1) {
			return nodes[v].sfail;
		}
		if(v == 0 || nodes[v].p == 0) {
			return nodes[v].sfail = 0;
		}
		int f = fail(v);
		if(nodes[f].term) {
			return nodes[v].sfail = f;
		}
		return nodes[v].sfail = sfail(f);
	}

	int feed(const string& str) {
		int cur = 0;
		int ans = -1;
		for(int i = 0;i < str.size();++i) {
			int c = str[i] - 'a';
			cur = go(cur,c);
			int u = cur;
			while(u) {
				if(nodes[u].term) {
					ans = max(ans,*(nodes[u].vals.rbegin()));
				}
				u = sfail(u);
			}
		}
		return ans;
	}

	// For debugging
	string printNode(int v) {
		string res = "";
		while(v) {
			res += (char)('a' + nodes[v].cv);
			v = nodes[v].p;
		}
		reverse(res.begin(),res.end());
		return res;
	}
};

int N,Q,pos[MAXN],val[MAXN];
aho_corasick ac = aho_corasick();

int main() {
	cin >> N >> Q;
	for(int i = 0;i < N;++i) {
		string str;
		cin >> str;
		pos[i] = ac.add(str);
	}
	for(int i = 0;i < Q;++i) {
		int t;
		cin >> t;
		if(t == 1) {
			int a,b;
			cin >> a >> b;
			a--;
			ac.nodes[pos[a]].vals.erase(ac.nodes[pos[a]].vals.find(val[a]));
			ac.nodes[pos[a]].vals.insert(b);
			val[a] = b;
		}else{
			string str;
			cin >> str;
			cout << ac.feed(str) << endl;
		}
	}
	return 0;
}