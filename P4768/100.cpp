#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define mp make_pair
#define ms(a) memset(a, 0, sizeof a)
#define rev(i, p) for(Edge *i = h[p]; i; i = i->next)
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf, 1, 100000, stdin), p1==p2)?EOF:*p1++)
char buf[100000], *p1, *p2; const int N = 410000;
inline int rd() {
	int x = 0; char ch = nc();
	while(!isdigit(ch)) ch = nc();
	while(isdigit(ch)) x = ((x+(x<<2))<<1)+(ch^48), ch = nc();
	return x;
}
int fa[N], dfn[N], oud[N], f[20][N], vis[N];
long long dis[N], ans;
int n, m, Q, K, S, val[N];
struct Data {
	int u, v, l, a;
	inline bool operator < (const Data &A) const {
		return a > A.a;
	}
}e1[N<<2];
struct Edge {
	int to, val;
	Edge *next;
}*h[N], e[N<<2];
int _, q[N];
inline void addEdge(int u, int v, int w = 0) {
	Edge *
	tmp = &e[++_]; tmp->to = v; tmp->val = w; tmp->next = h[u]; h[u] = tmp;
}
struct getDis {
	priority_queue<pair<int, int> > q;
	inline void Init() {
		_ = 0; ms(h);
		for(int i = 1; i <= m; i ++ ) {
			int u = e1[i].u, v = e1[i].v, w = e1[i].l;
			addEdge(u, v, w);
			addEdge(v, u, w);
		}
	}
	void Dijkstra() {
		ms(vis); memset(dis, 0x3f, sizeof dis);
		dis[1] = 0;
		q.push(mp(0, 1));
		while(!q.empty()) {
			int u = q.top().second; q.pop();
			if(vis[u]) continue;
			vis[u] = 1;
			rev(i, u) if(dis[i->to] > dis[u]+i->val) {
				dis[i->to] = dis[u]+i->val;
				q.push(mp(-dis[i->to], i->to));
			}
		}
	}

}Dijkstra;
struct Kruskal_Rebuild_Tree {
	inline void Init() {
		_ = 0; ms(h);
	}
	int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
	void Build_Tree() {
		for(int i = 1; i < n << 1; i ++ ) fa[i] = i;
		int cnt = n;
		sort(e1+1, e1+m+1);
		for(int i = 1; i <= m; i ++ ) {
			int dx = find(e1[i].u), dy = find(e1[i].v);
			if(dx != dy) {
				fa[dx] = fa[dy] = ++cnt;
				f[0][dx] = f[0][dy] = cnt;
				val[cnt] = e1[i].a;
				addEdge(cnt, dx), addEdge(cnt, dy);
				if(cnt == 2*n-1) break;
			}
		}
	}
}KRT;
struct getAns {
	void dfs(int p) {
		for(int i = 1; i < 20; i ++ ) f[i][p] = f[i-1][f[i-1][p]];
		rev(i, p) if(i->to != f[0][p]) {
			dfs(i->to);
			dis[p] = min(dis[p], dis[i->to]);
		}
		oud[p] = *q;
	}
	void Solve() {
		Q = rd(), K = rd(), S = rd();
		while(Q -- ) {
			int v = (rd()+K*ans-1)%n+1, p = (rd()+K*ans)%(S+1);
			int u = v;
			for(int i = 19; ~i; i -- ) if(val[f[i][u]] > p) u = f[i][u];
			printf("%lld\n", ans = dis[u]);
		}
	}
}Solve;
inline void init() {
	ms(dfn); ms(oud); ms(f); ms(q); ans = 0;
}
int main() {
	int T = rd();
	while(T -- ) {
		init();
		n = rd(), m = rd();
		for(int i = 1; i <= m; i ++ ) {
			e1[i].u = rd(), e1[i].v = rd(), e1[i].l = rd(), e1[i].a = rd();
		}
		Dijkstra.Init();
		Dijkstra.Dijkstra();
		KRT.Init();
		KRT.Build_Tree();
		Solve.dfs(2*n-1);
		Solve.Solve();
	}
}
