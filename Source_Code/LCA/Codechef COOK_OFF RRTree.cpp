/*
Problem : Codechef cook_off RRTree
Algo    : LCA (Euler tour) (finding diametre of a tree online ) .
Author  : Rashedul Hasan Rijul (Silent_coder).
*/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<map>
#include<set>
using namespace std;

#define maxm 300100
#define inf (1<<29)
#define ii int

#define pi  acos(-1.0)
#define eps 1e-9
#define iseq(a,b) (fabs(a-b)<eps)

#define pii pair<int,int>
#define mp  make_pair
#define uu first
#define vv second

ii on(ii n,ii k){ return (n|(1<<k)); }
ii off(ii n,ii k){ return (n-(n&(1<<k))); }
bool chck(ii n,ii k){ return (n&(1<<k)); }

ii mini(ii a,ii b){ if(a<b) return a;  return b;  }
ii maxi(ii a,ii b){ if(a>b) return a;  return b;  }

int n,tim;
int euler[3*maxm],fst[maxm],lst[maxm],lev[maxm];
int p[maxm];
vector<int>v[maxm];

struct tree{
    int mn,ind;
};
tree T[4*maxm];

void dfs(int u,int d){

    lev[u]=d;
    euler[tim]=u;
    fst[u]=tim++;

    for(int i=0;i<v[u].size();i++){
        dfs(v[u][i],d+1);
        euler[tim++]=u;
    }
    if(u==1){
        euler[tim]=u;
        lst[u]=tim++;
    }
}
void init(int node,int b,int e){

    if(b==e){
        T[node].ind=euler[b];
        T[node].mn=lev[euler[b]];
        return ;
    }

    int left,right,mid;
    left=node<<1,right=left+1,mid=b+e,mid/=2;

    init(left,b,mid);
    init(right,mid+1,e);

    if(T[left].mn<T[right].mn) T[node]=T[left];
    else                       T[node]=T[right];
}

tree query(int node,int b,int e,int k,int l){

    if(b==k && e==l){
        return T[node];
    }

    int left,right,mid;
    left=node<<1,right=left+1,mid=b+e,mid/=2;

    if(l<=mid) return query(left,b,mid,k,l);
    else if(k>mid) return query(right,mid+1,e,k,l);
    tree ret1=query(left,b,mid,k,mid);
    tree ret2=query(right,mid+1,e,mid+1,l);


    if(ret1.mn<ret2.mn) return ret1;
    return                     ret2;
}

int find_dist(int u,int v){

    if(fst[u]>fst[v]) swap(u,v);

    /*puts("INSIDE");
    printf("%d %d\n",u,v);
    printf("%d %d\n",fst[u],fst[v]);
    */

    tree piv=query(1,1,tim,fst[u],fst[v]);

    int ret=lev[u]+lev[v]-2*lev[piv.ind];

   // puts("-------");

    return ret;
}


int main(){

    int i,j,k,l,test,t=1;

    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    scanf("%d",&test);

    while(test--){

        scanf("%d",&n);

        for(i=0;i<=n;i++){
            v[i].clear();
        }
        tim=1;

        for(i=2;i<=n;i++){
            scanf("%d",&p[i]);
            v[p[i]].push_back(i);
        }

        dfs(1,1);
        tim--;

        init(1,1,tim);

        int ans=0,d1=1,d2=1;

        for(i=2;i<=n;i++){
            if(p[i]==d1){
                ans++;
                d1=i;
            }
            else if(p[i]==d2){
                ans++;
                d2=i;
            }
            else{
                //printf("%d %d\n",d1,i);
                int ans1=find_dist(d1,i);
                if(ans1>ans){
                    d2=i;
                    ans=ans1;
                    printf("%d\n",ans);
                    continue;
                }
                ans1=find_dist(d2,i);
                if(ans1>ans){
                    d1=i;
                    ans=ans1;
                    printf("%d\n",ans);
                    continue;
                }
            }
            printf("%d\n",ans);
        }

    }

    return 0;
}

