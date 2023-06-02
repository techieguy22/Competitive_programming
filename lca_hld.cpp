
#include <bits/stdc++.h>
using namespace std;
#define uint  unsigned long long int
#define int long long int
// #define double long double
#define vi vector<int>
#define ub upper_bound
#define lb lower_bound
#define vp vector<pair<int,int>>
#define pb push_back
#define po pop_back()
#define pii pair<int,int>
#define mod 998244353
#define precise	cout.setf(ios::fixed, ios::floatfield);cout.precision(9);
using namespace std;

void dfs(int i,vi adj[],vi& count,vi& heavy,vi &depth){
    count[i]++;
    for(auto j:adj[i]){
        depth[j]=depth[i]+1;
        dfs(j,adj,count,heavy,depth);
        count[i]+=count[j];
        if(heavy[i]==-1)heavy[i]=j;
        if(count[j]>count[heavy[i]]){
            heavy[i]=j;
        }
        
    }
}
// int idx=0;
void dfshld(int i,int chain,vi &head,vi &heavy,vi adj[]){
    head[i]=chain;
    if(heavy[i]!=-1){
        dfshld(heavy[i],chain,head,heavy,adj);
    }
    for(auto j:adj[i]){
        if(j!=heavy[i]){
            dfshld(j,j,head,heavy,adj);
        }
    }
}

int lca(int u,int v,vi &depth,vi &head,vi &par){
    while(depth[head[u]]!=depth[head[v]]){
        if(depth[head[u]]>depth[head[v]])swap(u,v);
        v=par[head[v]];
    }
    if(depth[u]<depth[v])return u;
    else return v;
}
void solve(){
    int n;
    cin>>n;
    vi adj[n+1];
    vi par(n+1),depth(n+1,0),heavy(n+1,-1),head(n+1,-1),count(n+1,0);
    
    for(int i=1;i<=n;i++){
        int m,w;cin>>m;
        for(int j=0;j<m;j++){
            cin>>w;
            adj[i].pb(w);
            par[w]=i;
        }
    }
    dfs(1,adj,count,heavy,depth);
    dfshld(1,1,head,heavy,adj);
    // for(auto j:par) cout<<j<<" ";
    
    int q;cin>>q;
    while(q--){
        int u,v;cin>>u>>v;
        cout<<lca(u,v,depth,head,par)<<"\n";
    }
}

signed main(){
    ios_base :: sync_with_stdio(false); cin.tie(nullptr);
    int t=1;
    cin>>t;
    for(int i=1;i<=t;i++){
        cout<<"Case "<<i<<":\n";
        solve();
        // cout<<"\n";
    }
}
