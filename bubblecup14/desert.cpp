using namespace std;

#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

#define MAXN 500005

struct SplayTree {
  struct Node {
    int ch[2] = {0, 0}, p = 0;
    bool flip = 0;                       // Lazy tags
    int lazy = -1;
    int myvalue = -2;
    int pathvalue = -2;
    bool isedge = false;
  };
  vector<Node> T;
 
  SplayTree(int n) : T(n + 1) {}
  
  void push(int x) {
    if (!x) return;
    int l = T[x].ch[0], r = T[x].ch[1];
    if (T[x].flip) {
      T[l].flip ^= 1, T[r].flip ^= 1;
      swap(T[x].ch[0], T[x].ch[1]);
      T[x].flip = 0;
    }
    if (T[x].lazy != -1) {
      int val = T[x].lazy;
      if (T[x].isedge) {
        T[x].myvalue = val;
      }
      if (T[x].isedge || l || r) {
        T[x].pathvalue = val;
      }
      T[l].lazy = val;
      T[r].lazy = val;
      T[x].lazy = -1;
    }
  }
  
  void pull(int x) {
    int l = T[x].ch[0], r = T[x].ch[1]; push(l); push(r); 
 
    T[x].pathvalue = max({T[x].myvalue, T[l].pathvalue, T[r].pathvalue});
  }
  
  void set(int x, int d, int y) {
    T[x].ch[d] = y; T[y].p = x; pull(x); 
  }
 
  void splay(int x) { 
    auto dir = [&](int x) {
      int p = T[x].p; if (!p) return -1;
      return T[p].ch[0] == x ? 0 : T[p].ch[1] == x ? 1 : -1;
    };
    auto rotate = [&](int x) {
      int y = T[x].p, z = T[y].p, dx = dir(x), dy = dir(y);
      set(y, dx, T[x].ch[!dx]); 
      set(x, !dx, y);
      if (~dy) set(z, dy, x); 
      T[x].p = z;
    };
    for (push(x); ~dir(x); ) {
      int y = T[x].p, z = T[y].p;
      push(z); push(y); push(x);
      int dx = dir(x), dy = dir(y);
      if (~dy) rotate(dx != dy ? x : y);
      rotate(x);
    }
  }
};
 
struct LinkCut : SplayTree {
  LinkCut(int n) : SplayTree(n) {}
 
  int access(int x) {
    int u = x, v = 0;
    for (; u; v = u, u = T[u].p) {
      splay(u); 
      int& ov = T[u].ch[1];
      ov = v; pull(u);
    }
    return splay(x), v;
  }
 
  void reroot(int x) { 
    access(x); T[x].flip ^= 1; push(x); 
  }
 
  void link(int u, int v, int id) {
    // debug(u); debug(v); debug(id);
    assert(LCA(u, id) == 0);
    assert(LCA(v, id) == 0);
    Link(u, id);
    Link(v, id);
  }
  
  void Link(int u, int v) {
    u++; v++;
    // cerr << "Link " << u << ' ' << v << endl;
    reroot(u); access(v); 
    T[u].p = v; pull(v);
  }
  
  void Cut(int u, int v) {
    u++; v++;
    // cerr << "Cut " << u << ' ' << v << endl;
    reroot(u); access(v);
    T[v].ch[0] = T[u].p = 0; pull(v);
  }
 
  void cut(int u, int v, int id) {
    Cut(u, id);
    Cut(v, id);
  }
  
  // Rooted tree LCA. Returns 0 if u and v arent connected.
  int LCA(int u, int v) { 
    u++; v++;
    if (u == v) return u;
    access(u); int ret = access(v); 
    return T[u].p ? ret : 0;
  }
  
  // Query path [u..v]
  int path(int u, int v) {
    u++; v++;
    // cerr << "Getpath " << u << ' ' << v << endl;
    reroot(u); access(v); return T[v].pathvalue;
  }
 
  int getValue(int i) {
    return path(i, i);
  }
  
  void setpath(int u, int v, int i) {
    // debug(u); debug(v); debug(i);
    u++; v++;
    // cerr << "Setpath " << u << ' ' << v << ' ' << i << endl;
    reroot(u); access(v); T[v].lazy = i; push(v);
  }
 
  void uncycle(int u, int v, int i, int ei, int nu, int nv) {
    // cerr << "uncycle " << u << ' ' << v << ' ' << i << ' ' << ei << ' ' << nu << ' ' << nv << endl;
    setpath(nu, nv, -2);
    cut(u, v, i);
    link(nu, nv, ei);   
  }
};

int N,M;
pair<int,int> edges[MAXN];

int main() {
    cin >> N >> M;
    for(int i = 0;i < M;++i) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--;edges[i].second--;
    }
    LinkCut tree(N + M);
    for(int i = 0;i < M;++i) {
        tree.T[N + i + 1].isedge = true;
    }

    auto insert = [&](int i) {
        auto [u,v] = edges[i];
        if(tree.LCA(u,v) == 0) {
            tree.link(u,v,N + i);
            return true;
        }
        int s = tree.path(u,v);
        if(s >= 0) return false;
        tree.setpath(u,v,i);
        return true;
    };

    auto erase = [&](int i) {
        auto [u,v] = edges[i];
        int s = tree.getValue(N + i);
        if(s < 0) {
            tree.cut(u,v,N + i);
            return;
        }
        auto [uu,vv] = edges[s];
        tree.uncycle(u,v,N + i,N + s,uu,vv);
    };

    long long ans = 0;
    for(int i = 0,j = 0;i < M;++i) {
        while(j < M && insert(j)) j++;
        ans += j - i;
        erase(i);
    }
    cout << ans << endl;
    return 0;
}