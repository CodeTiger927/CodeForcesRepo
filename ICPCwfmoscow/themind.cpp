using namespace std;

#include <iostream>
#include <iomanip>
#include <cstring>

int N,a[5];
int cuts[] = {3,7,12,19,28};

int main() {
    cin >> N;
    cout << setprecision(15);
    for(int i = 0;i < N;++i) {
        for(int j = 0;j < 5;++j) cin >> a[j];
        int p = 0;
        while(p < 5 && a[0] >= cuts[p]) p++;;
        for(int j = 0;j < 5;++j) {
            cout << (j == p ? 1 : 0) << " ";
        }
        cout << endl;
    }
    return 0;
}