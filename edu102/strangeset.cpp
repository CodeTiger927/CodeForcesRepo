using namespace std;

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <cstring>

#define MAXN 3005
#define MAXK 105
#define INF 1e9

template<typename T>
struct dinic {
    struct edge {
        int u, rev;
        T cap, flow;
    };
    
    int n, s, t;
    T flow;
    vector<int> lst;
    vector<int> d;
    vector<vector<edge>> g;
    
    T scaling_lim;
    bool scaling;
    
    dinic() {}
    
    dinic(int n, int s, int t, bool scaling = false) : n(n), s(s), t(t), scaling(scaling) {
        g.resize(n);
        d.resize(n);
        lst.resize(n);
        flow = 0;
    }

    void add_edge(int v, int u, T cap, bool directed = true) {
        g[v].push_back({u, g[u].size(), cap, 0});
        g[u].push_back({v, int(g[v].size()) - 1, directed ? 0 : cap, 0});
    }

    T dfs(int v, T flow) {
        if (v == t)
            return flow;
        if (flow == 0)
            return 0;
        T result = 0;
        for (; lst[v] < g[v].size(); ++lst[v]) {
            edge& e = g[v][lst[v]];
            if (d[e.u] != d[v] + 1)
                continue;
            T add = dfs(e.u, min(flow, e.cap - e.flow));
            if (add > 0) {
                result += add;
                flow -= add;
                e.flow += add;
                g[e.u][e.rev].flow -= add;
            }
            if (flow == 0)
                break;
        }
        return result;
    }

    bool bfs() {
        fill(d.begin(), d.end(), -1);
        queue<int> q({s});
        d[s] = 0;
        while (!q.empty() && d[t] == -1) {
            int v = q.front(); q.pop();
            for (auto& e : g[v]) {
                if (d[e.u] == -1 && e.cap - e.flow >= scaling_lim) {
                    q.push(e.u);
                    d[e.u] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    T calc() {
        T max_lim = numeric_limits<T>::max() / 2 + 1;
        for (scaling_lim = scaling ? max_lim : 1; scaling_lim > 0; scaling_lim >>= 1) {
            while (bfs()) {
                fill(lst.begin(), lst.end(), 0);
                T add;
                while((add = dfs(s, numeric_limits<T>::max())) > 0)
                flow += add;
            }
        }   
        return flow;
    }
    
    vector<bool> min_cut() {
        vector<bool> res(n);
        for(int i = 0; i < n; i++) 
            res[i] = (d[i] != -1);
        return res;
    }
};

int arr[MAXN],cost[MAXN],pre[MAXK];

int main() {
    int N;
    cin >> N;
    for(int i = 0;i < N;++i) {
        cin >> arr[i];
    }
    for(int i = 0;i < N;++i) {
        cin >> cost[i];
    }
    int s = N;
    int t = N + 1;
    dinic<int> flow(N + 2,s,t,true);
    memset(pre,-1,sizeof(pre));
    for(int i = 0;i < N;++i) {
        if(cost[i] > 0) {
            flow.add_edge(s,i,cost[i]);
        }else{
            flow.add_edge(i,t,-cost[i]);
        }
        for(int j = 1;j <= 100;++j) {
            if(pre[j] != -1 && arr[i] % j == 0) {
                flow.add_edge(i,pre[j],INF);
            }
        }
        pre[arr[i]] = i;
    }
    long long ans = 0;
    for(int i = 0;i < N;++i) {
        if(cost[i] > 0) ans += cost[i];
    }
    ans -= flow.calc();
    cout << ans << endl;
    return 0;
}