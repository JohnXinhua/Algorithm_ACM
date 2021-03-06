/*
Author      : Rashedul Hasan Rijul ( Silent_coder ).
Algo        : Treap (Balanced BST).
Created on  : 2014-07-29
*/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<map>
#include<set>
using namespace std;

#define maxm 2010
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

//  TREAP  >>>>>>>>>>>>>>>>>>>>>>>>>

typedef int treap_type;

struct node{

    treap_type value,min_val,max_val,diff;
    ii priority;
    int cnt;
    node *left,*right;

    node(){}
    node(treap_type _value){
        cnt=1;
        value=min_val=max_val=_value;
        diff=inf;
        priority=rand();
        left=right=NULL;
    }
};

// 1-based . . . . . . . . . .
struct treap{

    node *root;

    void fix(node * &t){
        if(t==NULL) return ;
        t->cnt=get_count(t->left)+get_count(t->right)+1;
		t->diff=inf;

        if(t->left){
            t->min_val=t->left->min_val;
            t->diff=mini(t->left->diff,t->value - t->left->max_val);
        }
		else t->min_val=t->value;

        if(t->right){
            t->max_val=t->right->max_val;
            t->diff=mini( t->diff,mini( t->right->diff , t->right->min_val- t->value) );
        }
		else t->max_val=t->value;
    }

    inline int get_count(node* t){
        return t ? t->cnt : 0;
    }

    inline void left_rotate(node* &t){
        node* tmp = t->left;
        t->left = tmp->right;
        tmp->right = t;
        t = tmp;
    }

    inline void right_rotate(node* &t){
        node* tmp = t->right;
        t->right = tmp->left;
        tmp->left = t;
        t = tmp;
    }

    bool insert(node * &t,treap_type value){

        if(t==NULL){
            t=new node(value);
            fix(t);
            return true;
        }

        if(t->value==value) return false;
        bool ret;

        if(value < t->value) ret=insert(t->left,value);
        else                 ret=insert(t->right,value);

        if(t->left && t->left->priority > t->priority){
            left_rotate(t);
        }
        else if(t->right && t->right->priority > t->priority){
            right_rotate(t);
        }

        if(t->left) fix(t->left);
        if(t->right) fix(t->right);
        fix(t);

        return ret;
    }

    bool insert(treap_type value){
        return insert(root,value);
    }

    inline ii get_priority(node* t){
        return t ? t->priority : -1;
    }

    bool erase(node* &t, treap_type val){

        if(!t) return false;

        bool ret;
        if(t->value != val){
            ret=erase(val < t->value ? t->left : t->right, val);
        }
        else{
            if(!t->left && !t->right){
                delete t;
                t = NULL;
            }else{
                if(get_priority(t->left) < get_priority(t->right))
                    right_rotate(t);
                else
                    left_rotate(t);

                ret=erase(t, val);
            }
        }

        if(t){
            if(t->left)  fix(t->left);
            if(t->right) fix(t->right);
            fix(t);
        }

        return ret;
    }

    bool erase(treap_type value){
		return erase(root,value);
    }

    node* find(node * t,int value){

        if(t==NULL) return NULL;

		node *ret;
        if(value > t->value){
            ret=find(t->right,value);
			if(ret==NULL) return t;
            return ret;
        }
        else if(value==t->value){
            return t;
        }
        else{
            return find(t->left,value);
        }
    }

    node* find(int value){
        return find(root,value);
    }

    treap_type find_max(int beg,int end){
        if(beg>end) swap(beg,end);
        return 0;
    }

    treap_type find_min(int beg,int end){
        if(beg>end) swap(beg,end);
        return 0;
    }
};

// END >>>>>>>>>>>>>>>>>>

treap tree;

ii find_min(node *t,int left,int beg,int end){

    if(t==NULL) return inf;

    ii r_left=left;
    ii r_right=left+t->cnt-1;

    ii sz=tree.get_count(t->left)+1;
	ii curr_ind=left+tree.get_count(t->left);

    if(beg<=r_left && end>=r_right){
        return t->diff;
    }

    ii ret=inf;

    if(beg>curr_ind)             ret=mini(ret,find_min(t->right,curr_ind+1,beg,end));
    else if(end<curr_ind)        ret=mini(ret,find_min(t->left,left,beg,end));

    else                         ret=mini(mini(find_min(t->left,left,beg,end)
                                               ,find_min(t->right,curr_ind+1,beg,end)),ret);

    if(curr_ind>beg && curr_ind<=end && t->left){
        ret=mini(ret,t->value - t->left->max_val);
    }
    if(curr_ind<end && curr_ind>=beg && t->right){
        ret=mini(ret,t->right->min_val - t->value);
    }

    return ret;
}

ii find_min(int k,int l){

    if(l<=k) return -1;
    return find_min(tree.root,1,k,l);
}

ii find_kth(node *t,int kth){

    if(tree.get_count(t)<kth){
		return -1;
    }

    int sz=tree.get_count(t->left)+1;

    if(sz==kth){
        return t->value;
    }

    if(kth<sz){
        return find_kth(t->left,kth);
    }
    else{
        return find_kth(t->right,kth-sz);
    }
}

ii find_max(int k,int l){

    if(l<=k) return -1;
    return find_kth(tree.root,l)-find_kth(tree.root,k);
}


int find_count(node *t,int value){

	if(t==NULL) return 0;

	if(value==t->value)   return tree.get_count(t->left);
	else if(value > t->value)  return tree.get_count(t->left)
								+find_count(t->right,value)+1;
	else return find_count(t->left,value);
}

int n,m;
char type[5];

int main(){

    int i,j,k,l,test,t=1,val;

    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    scanf("%d",&test);

    while(test--){

        scanf("%s",type);

        //printf("%s\n",type);

        if(type[0]=='I'){
            scanf("%d",&val);
            tree.insert(val);
        }

        if(type[0]=='D'){
            scanf("%d",&val);
            tree.erase(val);
        }

        if(type[0]=='N'){
            scanf("%d %d",&k,&l);
            printf("%d\n",find_min(k+1,l+1));
        }

        if(type[0]=='X'){
            scanf("%d %d",&k,&l);
            printf("%d\n",find_max(k+1,l+1));
        }

    }

    return 0;
}

