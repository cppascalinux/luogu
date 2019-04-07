// luogu-judger-enable-o2
#include <cstdio>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 2*(100000 + 6);
struct Edge {
    int t, c;
};

typedef long long ll;
struct item {
    ll mn, mx, ans;
};
item merge(item A, item B) {
    item ans = {};
    ans.mx = max(A.mx, B.mx);
    ans.mn = min(A.mn, B.mn);
    ans.ans = max(max(A.ans, B.ans), B.mx-A.mn);
    return ans;
}
namespace segt {
    #define maxn (maxn*2)
    int lch[maxn], rch[maxn], ncnt; item msg[maxn];
    void build(int rt, int L, int R, ll* dis, ll*mxl) {
        if(L == R) {
            msg[rt] = (item){dis[L]-mxl[L], dis[L]+mxl[L], mxl[L]};
            return;
        }
        int mid = (L+R)>>1;
        lch[rt] = ++ ncnt; build(lch[rt], L,   mid, dis, mxl);
        rch[rt] = ++ ncnt; build(rch[rt], mid+1, R, dis, mxl);
        msg[rt] = merge(msg[lch[rt]], msg[rch[rt]]);
    }
    vector<item> vec;
    void query(int rt, int l, int r, int L, int R) {
        if(r< L || R< l) return;
        if(L<=l && r<=R) {
            vec.push_back(msg[rt]);
            return;
        }
        int mid = (l + r)>>1;
        query(lch[rt], l,   mid, L, R);
        query(rch[rt], mid+1, r, L, R);
    }
    ll Qry(int L, int R, const int N) {
        vec.clear();
        query(1, 1, N, L, R);
        for(int i = 1; i < (int)vec.size(); i ++) {
            vec[i] = merge(vec[i-1], vec[i]);
        }
        return vec[vec.size()-1].ans;
    }
    #undef maxn
}

namespace graph {
    vector<Edge> nxt[maxn];
    stack<int> stk;
    bool ins[maxn], inc[maxn], vis[maxn], hascir;
    int ary[maxn], ccnt;
    ll dep[maxn], dis[maxn], mxl[maxn], val[maxn];
    void addedge(int f, int t, int c) {
        nxt[f].push_back((Edge){t, c});
        nxt[t].push_back((Edge){f, c});
    }
    void dfs_cir(int x, int f, ll cst) {
        //printf("dfs_cir x = %d, f = %d, cst = %lld\n", x, f, cst);
        vis[x] = 1;
        dep[x] = dep[f] + cst;
        if(!hascir) {
            ins[x] = 1;
            stk.push(x);
        }
        for(int i = 0; i < (int)nxt[x].size(); i ++) {
            int t = nxt[x][i].t;
            if(!vis[t]) {
                dfs_cir(t, x, nxt[x][i].c);
            }else if(!hascir && t!=f){
                if(ins[t]) {
                    //printf("find cir t = %d\n", t);
                    inc[t] = 1; /// in circle
                    hascir = 1;
                    while(stk.top() != t) {
                        inc[stk.top()] = 1;
                        ary[++ ccnt] = stk.top();
                        dis[   ccnt] = dep[ary[ccnt]] - dep[t];
                        stk.pop(); 
                    }
                    stk.pop(); /// pop t
                    ary[++ ccnt] = t;
                    dis[   ccnt] = 0;
                    dis[      0] = dep[x] + nxt[x][i].c;
                }
            }
        }
        if(!hascir) {
            stk.pop();
            ins[x] = 0;
        }
    }
    void dfs_tre(int x, int f, ll cst, ll& MXL, int& distn) {
        //printf("   dfs_tree x = %d, f = %d, cst = %lld\n", x, f, cst);
        dep[x] = dep[f] + cst;
        if(dep[x] >= MXL) {
            MXL = dep[x];
            distn = x;
        }
        for(int i = 0; i < (int)nxt[x].size(); i ++) {
            int t = nxt[x][i].t;
            if(t == f || inc[t]) continue;
            dfs_tre(t, x, nxt[x][i].c, MXL, distn);
        }
    }
    //int f[maxn][21], lg[maxn];
//	void init(int N) {
//		for(int i = 1; i <= N; i ++) {
//			f[i][0] = i; /// min val pos
//		}
//		for(int j = 1; (1<<j) <= N; j ++) {
//			for(int i = 1; i+(1<<j)-1 <= N; i ++) {
//				//f[i][j] <- f[i][j-1], f[i+(1<<(j-1))][j-1]
//				int Lp = f[i][j-1], Rp = f[i+(1<<(j-1))][j-1];
//				if(val[Lp] < val[Rp]) {
//					f[i][j] = Lp;
//				}else {
//					f[i][j] = Rp;
//				}
//			}
//		}
//		for(int i = 2; i <= N; i ++) {
//			lg[i] = lg[i/2] + 1;
//		}
//	}
//	ll qry_min(int L, int R) {
//		if(R < L) return 0x7f7f7f7f7f7f7f7fLL;
//		int g = lg[R-L+1];
//		int Lp = f[L][g], Rp = f[R-(1<<g)+1][g];
//		return min(val[Lp], val[Rp]);
//	}
    ll make_cir() {
        reverse(dis + 1, dis + ccnt + 1);
        reverse(ary + 1, ary + ccnt + 1);
        ll ans = 0;
        for(int i = 1; i <= ccnt; i ++) {
            int u, v; ll tmp = 0;
            dfs_tre(ary[i], 0, 0, mxl[i], u);
            inc[ary[i]] = 0;
            dfs_tre(u, 0, 0, tmp, v);
            inc[ary[i]] = 1;
            ans = max(ans, tmp);
        }
		printf("ans:%lld\n",ans);
        for(int i = 1; i <= ccnt; i ++) {
            ary[i + ccnt] = ary[i];
            mxl[i + ccnt] = mxl[i];
            dis[i + ccnt] = dis[i] + dis[0];
        }
        for(int i = 1; i <= 2*ccnt; i ++) {
            val[i] = dis[i] - mxl[i];
        }
//		init(2 * ccnt);
//		ll ans2 = 0x7f7f7f7f7f7f7f7fLL;
//		for(int i = 1; i <= 2*ccnt; i ++) {
//			printf("[%3d] %3d, %3d, %3d, %3d\n", i, ary[i], val[i], dis[i], mxl[i]);
//		}
//		for(int i = ccnt+1; i <= 2*ccnt; i ++) {
//			int L = i-ccnt+1;
//			ll mind = qry_min(L, i-1), tmp;
//			ans2 = min(ans2, tmp = dis[i]-mind+mxl[i]);
//			printf("i = %d, tmp = %lld, mind = %lld\n", i, tmp, mind);
//		}
//		return max(ans, ans2);
        segt::build(++ segt::ncnt, 1, 2*ccnt, dis, mxl);
        ll ans2 = 0x7f7f7f7f7f7f7f7fLL;
        for(int i = ccnt; i < 2*ccnt; i ++) {
            ll tmp;
            ans2 = min(ans2, tmp = segt::Qry(i-ccnt+1, i, 2*ccnt));
            //printf("i = %d, tmp = %lld\n", i, tmp);
        }
        //printf("ans = %lld, ans2 = %lld\n", ans, ans2);
        return max(ans, ans2);
    }
}

int main() {
    freopen("fastfood.in", "r", stdin);
	freopen("ggn.out","w",stdout);
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        graph::addedge(u, v, w);
    }
    graph::dfs_cir(1, 0, 0);
    ll ans = graph::make_cir();
    printf("%.1lf\n", (double)ans/2);
    return 0;
}
