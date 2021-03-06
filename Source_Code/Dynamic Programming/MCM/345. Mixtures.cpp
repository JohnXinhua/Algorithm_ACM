#include<stdio.h>
#include<string.h>

#define maxm 110
#define mod 100
#define ii int
#define inf 1<<29

ii dp[maxm][maxm];
bool vis[maxm][maxm];
int sum[maxm],a[maxm],n;

ii cal(int a,int b);
ii mini(ii a,ii b){
	if(a<b) return a;
	return b;
}

int main(){

	int i,j,k,l,test,t=1;

	//freopen("in.txt","r",stdin);

	while(scanf("%d",&n)==1){

		memset(sum,0,sizeof(sum));
		memset(vis,0,sizeof(vis));

		for(i=1;i<=n;i++){
			scanf("%d",&a[i]);
			sum[i]=sum[i-1]+a[i];
		}

		printf("%d\n",cal(1,n));

	}


	return 0;
}

ii cal(int b,int e){

	if(b>=e) return 0;

	if(b==e-1){
		return (a[b]*a[e]);
	}

	if(vis[b][e]) return dp[b][e];
	vis[b][e]=1;

	int i,j,k,l;
	ii ret=inf,ret1,val,val1;

	for(i=b;i<e;i++){

		ret1=cal(b,i)+cal(i+1,e);
		val=sum[i]-sum[b-1];
		val%=mod;

		val1=sum[e]-sum[i];
		val1%=mod;

		ret1+=(val*val1);
		ret=mini(ret,ret1);
	}

	return dp[b][e]=ret;

}
