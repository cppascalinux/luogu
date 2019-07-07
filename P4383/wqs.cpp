//2019.07.07
//luoguP4383 [八省联考2018]林克卡特树lct 不难发现原题就是在树上选择k+1条点不相交的路径,使得总长度最长,可以直接O(nk)树形dp,然后不难发现每选一条链带来的贡献
//是递减的,也就是这是个上凸函数,于是可以直接套用wqs二分,时间复杂度O(nlogn)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define inf 0x7F7F7F7F
#define infl 0x3F3F3F3F3F3F3F3FLL
#define li long long
#define pli pair<li,int>
#define fi first
#define se second
using namespace std;
int n,m,tot;
int hd[300009],eg[600009],nxt[600009],len[600009];
pli f[300009],g[300009];
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x,int fa,li w)
{
	pli t[3];
	memset(t,0,sizeof(t));
	t[1].fi=t[2].fi=-infl;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			dfs(eg[i],x,w);
			t[2]=max(t[2],max(pli(t[1].fi+g[eg[i]].fi+len[i]+w,t[1].se+g[eg[i]].se-1),pli(t[2].fi+f[eg[i]].fi,t[2].se+f[eg[i]].se)));
			t[1]=max(t[1],max(pli(t[0].fi+g[eg[i]].fi+len[i],t[0].se+g[eg[i]].se),pli(t[1].fi+f[eg[i]].fi,t[1].se+f[eg[i]].se)));
			t[0]=max(t[0],pli(t[0].fi+f[eg[i]].fi,t[0].se+f[eg[i]].se));
		}
	t[1]=max(t[1],pli(t[0].fi-w,t[0].se+1));
	g[x]=t[1];
	f[x]=max(t[0],max(t[1],t[2]));
}
int check(li w)
{
	dfs(1,0,w);
	return f[1].se>=m;
}
void solve()
{
	li l=-3e11,r=3e11;
	while(l<r)
	{
		li mid=(l+r+1)>>1;
		if(check(mid))
			l=mid;
		else
			r=mid-1;
	}
	// printf("l:%lld\n",l);
	check(l);
	printf("%lld",f[1].fi+l*m);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("wqs.in","r",stdin);
	freopen("wqs.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	m++;
	for(int i=1,a,b,c;i<=n-1;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		ins(a,b,c),ins(b,a,c);
	}
	solve();
	return 0;
}