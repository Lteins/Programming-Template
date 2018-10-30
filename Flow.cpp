#include<iostream>
#include<vector>
#include<queue>
#include<math.h>
using namespace std;

typedef long long ll;
// Implementation of Dinic's algorithm to find MAximum flow in netwrok
// Uses Adjacency list representation
// @Note: vertex index starting from 1

//Maximum amount of vertex the graph can hold
const ll MAX = 15000;

//Complexity O(V^2E)
class Dinic {
private:
    struct edge {
        ll a, b, cap, flow;
    };
    ll n, source, sink;
    ll dis[MAX];
    ll ptr[MAX];
    vector<edge> e;
    vector<ll> adj[MAX];
public:
    Dinic(ll a, ll b, ll c) {
        n = a;
        source = b;
        sink = c;
    }
    void set_dis() {
        for(ll i=1; i<=n; ++i) {
            dis[i] = -1;
        }
    }
    void set_ptr() {
        for(ll i=1; i<=n; ++i) {
            ptr[i] = 0;
        }
    }
    void add_edge(ll a, ll b, ll cap) {
        edge e1 = {a, b, cap, 0};
        edge e2 = {b, a, 0, 0};
        adj[a].push_back((ll)e.size());
        e.push_back(e1);
        adj[b].push_back((ll)e.size());
        e.push_back(e2);
    }
    bool bfs() {
        queue<ll> q;
        q.push(source);
        set_dis();
        dis[source] = 0;
        while(!q.empty() && dis[sink] == -1) {
            ll v = q.front();
            q.pop();
            for(ll i=0; i<adj[v].size(); ++i) {
                ll id = adj[v][i];
                ll to = e[id].b;
                if (dis[to] == -1 && e[id].flow < e[id].cap) {
                    dis[to] = dis[v] + 1;
                    q.push(to);
                }
            }
        }
        while(!q.empty()) {
            q.pop();
        }
        return dis[sink] != -1;
    }
    ll dfs(ll v, ll flow) {
        if (!flow) {
            return 0;
        }
        if (v == sink) {
            return flow;
        }
        for(; ptr[v]<(ll)adj[v].size(); ++ptr[v]) {
            ll id = adj[v][ptr[v]];
            ll to = e[id].b;
            if (dis[to] != dis[v] + 1) {
                continue;
            }
            ll pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
    ll max_flow() {
        ll flow = 0;
        while(bfs()) {
            set_ptr();
            ll pushed;
            while(pushed = dfs(source, INT_MAX)) {
                flow += pushed;
            }
        }
        return flow;
    }
    void print_graph() {
        for(size_t i=0; i<(ll)e.size(); ++i) {
            printf("from: %d to : %d flow : %d cap : %d\n", e[i].a, e[i].b, e[i].flow, e[i].cap);
        }
    }
};

int main(void){
    Dinic din(6, 2, 6);
    din.add_edge(1, 2, 10);
    din.add_edge(1, 3, 10);
    din.add_edge(2, 3, 2);
    din.add_edge(2, 5, 8);
    din.add_edge(3, 5, 9);
    din.add_edge(2, 4, 4);
    din.add_edge(5, 4, 6);
    din.add_edge(4, 6, 10);
    din.add_edge(5, 6, 10);
    cout << din.max_flow() << endl;
}