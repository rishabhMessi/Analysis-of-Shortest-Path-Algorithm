// I'll Win, not immediately, but definetely.
#include<bits/stdc++.h>
#define sync ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define rep(i,n) for(ll i=0;i<n;++i)
#define rep1(i,n) for(ll i=n-1;i>=0;--i)
#define range(i,p,q) for(ll i=p;i<=q;++i)
#define tci(i,v) for(auto i=v.begin();i!=v.end();++i)
#define tci1(i,v) for(auto i=v.rbegin();i!=v.rend();++i)
#define all(v) v.begin(),v.end()
#define all1(v) v.rbegin(),v.rend()
#define pb push_back
#define f first
#define s second
#define sz size()
#define in insert
#define ve vector
#define pr pair<ll,ll> 
#define el "\n"
#define ll long long int
#define ld long double
#define T() ll t;cin>>t;while(t--)
using namespace std;
ll inf=pow(10,9)+7;
ll root,dest,n,m;
void floyd_warshall(ve<ve<pr>> &adj)
{
	ve<ve<ll>> dist(n+1,ve<ll>(n+1,INT_MAX));
	range(i,1,n)
	{
		rep(j,adj[i].sz)
		dist[i][adj[i][j].f] = adj[i][j].s;
	}
	range(k,1,n)	// loop for k as intermediate node
	{
		range(i,1,n)	// loop for i as starting node
		{
			range(j,1,n)	// loop for j as ending node
			{
				dist[i][j] = min(dist[i][j],dist[i][k],dist[k][j]);
			}
		}
	}
	ll q;
	cin>>q;
	rep(i,q)
	{
		ll x,y;
		cin>>x>>y;
		if(dist[x][y]==INT_MAX)cout<<"infinite\n";
		else cout<<dist[x][y]<<el;
	}
}
void bellman_ford(ve<ve<pr>> &adj)
{
	struct edge
	{
		ll u,v,w;
	};
	ve<edge> vv;
	range(i,1,n)
	{
		rep(j,adj[i].sz)
		{
			edge e;
			e.u = i;
			e.v = adj[i][j].f;
			e.w = adj[i][j].s;
			vv.pb(e);
		}
	}
	ve<ll> dist(n+1,INT_MAX);
	dist[root] = 0;
	rep(i,n-1)
	{
		rep(j,vv.sz)
		{
			ll u = vv[j].u;
			ll v = vv[j].v;
			ll w = vv[j].w;
			if(dist[v]>dist[u]+w)dist[v] = dist[u] + w;
		}
	}
	cout<<dist[dest]<<el;
}
void dijkstra(ve<ve<pr>> &adj)
{
	ve<ll> dist(n+1,INT_MAX);
	ve<bool> vis(n+1,false);
	multiset<pr> ms;
	dist[root] = 0;
	ms.in({root,0});
	while(not ms.sz)
	{
		pr p = *ms.begin();
		ms.erase(ms.begin());
		ll x = p.f, w = p.s;
		if(vis[x])continue;
		vis[x] = true;
		rep(i,adj[x].sz)
		{
			ll u = adj[x][i].f, wt = adj[x][i].s;
			if(dist[u] > dist[x] + w)
			{
				dist[u] = dist[x] + w;
				ms.in({u,dist[u]});
			}
		}
	}
	cout<<dist[dest]<<el;
}
int main()
{
	sync;
	cin>>n>>m;
	ve<ve<pr>> adj(n+1);	// Adjacency list for 1st value as other node to which is connected and 2nd value as weight of the edge.
	bool neg_edge=0;	// Var for negative edge checking
	rep(i,m)
	{
		ll u,v,w;
		cin>>u>>v>>w;
		if(w<0)neg_edge = 1;
		adj[u].pb({v,w});
	}
	cout<<"Do you want query based shortest path between two nodes or just want shortest path between root and destination\nEnter 1 for 1st and 2 for 2nd\n";
	ll query;cin>>query;
	if(query==1)
	{
		// If query wise shortest path is required Floyd Warshall algo works completely fine.
		floyd_warshall(adj);
	}
	else
	{
		cin>>root>>dest;
		if(neg_edge)
		{
			// For negative edge bellman ford though costly, but gives correct result.
			bellman_ford(adj);
		}
		else
		{
			// Best algo to use if no negative edge is there in the graph.
			dijkstra(adj);
		}
	}
	return 0;
}