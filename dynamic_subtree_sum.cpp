#include <bits/stdc++.h>
using namespace std;
#define uint  unsigned long long int
#define int long long int
#define vi vector<int>
#define ub upper_bound
#define lb lower_bound
#define vp vector<pair<int,int>>
#define pb push_back
#define po pop_back()
#define pii pair<int,int>
#define mod 1000000007
using namespace std;
int tim=1;
vi adj[200001];
 
vi start(200001);
vi en_d(200001);
vi linear_tree(400005);
vi F_tree;
void add_FT(int i,int val){
    while(i<F_tree.size()){
        F_tree[i]+=val;
        i+=i&(-i);
    }
}
 
int sumFT(int i){
    int sum=0;
    while(i>0){
        sum+=F_tree[i];
        i-=i&(-i);
    }
    return sum;
}
void fenwick_tree(){
    for(int i=1;i<=tim;i++){
        add_FT(i,linear_tree[i]);
    }
}
 
void dfs(int i,int parent,vi &v, vi &vis){
    vis[i]=1;
    start[i]=tim;
    linear_tree[tim++]=v[i];
    for(auto j:adj[i]){
        if(vis[j]==0 && j!=parent){
            dfs(j,i,v,vis);
        }
    }
    en_d[i]=tim;
    linear_tree[tim++]=v[i];
}
void solve(){
    int n,q;
    cin>>n>>q;
    vi v(n+1);
    for(int i=1;i<=n;i++)cin>>v[i];
    for(int i=0;i<n-1;i++){
        int a,b;cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vi vis(200001,0);
    dfs(1,-1,v,vis);
    // for(auto i:linear_tree){
    //     // cout<<i<<" ";
    //     // if(i==0)break;
        
    // }
    for(int i=0;i<linear_tree.size();i++)F_tree.pb(0);
    fenwick_tree();
    for(int i=0;i<q;i++){
        int w;cin>>w;
        if(w==1){
            int x,y;cin>>x>>y;
            int change=y-v[x];
            v[x]=y;
            add_FT(start[x],change);
            add_FT(en_d[x],change);
        }
        else{
            int x;cin>>x;
            cout<<(sumFT(en_d[x])-sumFT(start[x]-1))/2<<"\n";
        }
    }
}
signed main(){
    ios_base :: sync_with_stdio(false); cin.tie(nullptr);
    int t=1;//cin>>t;
    while(t--){
        solve();
        // cout<<"\n";
        // cout<<fun(1234,0)<<" ";
    }
}
