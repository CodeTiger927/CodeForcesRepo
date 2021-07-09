#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,mod,f[55][2005]={1},s[55][2005]={1},ans[55];
int main(){
	cin>>n>>mod;
	for(int i=1;i<=n*(n-1)/2;i++)s[0][i]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n*(n-1)/2;j++){
			if(j-i>=0)f[i][j]=(s[i-1][j]-s[i-1][j-i]+mod)%mod;
			else f[i][j]=s[i-1][j];
			s[i][j]=((j?s[i][j-1]:0)+f[i][j])%mod;
		}
	}
	for(int i=1;i<=n;i++){
		long long sum = 0;
		for(int j=1;j<=i;j++){
			for(int k=j+1;k<=i;k++){
				for(int o=0;o<=(i-1)*(i-2)/2;o++){
					int t=o-(k-j)-1;
					if(t<0)continue;
					sum += 1ll*f[i-1][o]*s[i-1][t] % mod;
					ans[i]=(ans[i]+1ll*f[i-1][o]*s[i-1][t]%mod)%mod;
				}
			} 
		}
		// cout << sum << endl;
	}
	for(int i=2;i<=n;i++)ans[i]=(ans[i]+1ll*i*ans[i-1])%mod;
	cout<<ans[n];
}