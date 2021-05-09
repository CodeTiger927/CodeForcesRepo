using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <random>
#include <chrono>

#define MAXN 300005

vector<int> pref[MAXN];

int N,Q,arr[MAXN],freq[MAXN],tmp[MAXN];
vector<int> indices[MAXN];

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int count(int l,int r,int x) {
    int f = (upper_bound(indices[x].begin(),indices[x].end(),r) - lower_bound(indices[x].begin(),indices[x].end(),l));
    return f;
}

int findMajority(int l,int r) {
    int curL = (r - l + 1);
    int need = (curL + 1) / 2;
    for(int i = 0;i < 40;++i) {
        int x = uniform_int_distribution<int>(l,r)(rng);
        int f = count(l,r,arr[x]);
        if(f >= need) return arr[x];
    }
    return -1;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> Q;
    for(int i = 0;i < N;++i) {
        cin >> arr[i];
        tmp[i + 1] = arr[i];
        freq[arr[i]]++;
        indices[arr[i]].push_back(i);
    }

    for(int i = 0;i < Q;++i) {
        int l,r;
        cin >> l >> r;
        l--;r--;
        int mostCommon = findMajority(l,r);
        if(mostCommon == -1) {
            cout << 1 << "\n";
            continue;
        }
        int curL = (r - l + 1);
        
        int cnt = count(l,r,mostCommon);
        int curLim = (curL + 1) / 2;
        if(cnt <= curLim) {
            cout << 1 << "\n";
            continue;
        }
        int ans = (curL & 1) + (((cnt - curLim)) * 2);
        cout << ans << "\n";   
    }
    cout << endl;
    return 0;
}