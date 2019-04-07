#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define long long long
#define mod 201314
#define mo(x) {while(x>=mod) x-=mod;}
using namespace std;
int n,m,tot,sum;
int ans[50010];
int head[50010],edge[100010],next[100010];
int dep[50010],s[50010],son[50010],id[50010],pos[50010],f[50010],top[50010];
int cnt[200010],lazy[200010],l[200010],r[200010];
int qx[50010];
vector<int> v1[50010],v2[50010];
void add(int a,int b)
{
	edge[++tot]=b;
	next[tot]=head[a];
	head[a]=tot;
}
void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	f[x]=fa;
	s[x]=1;
	for(int i=head[x];i;i=next[i])
		if(edge[i]^fa)
		{
			dfs1(edge[i],x);
			s[x]+=s[edge[i]];
			if(s[edge[i]]>s[son[x]])
				son[x]=edge[i];
		}
}
void dfs2(int x,int t)
{
	id[x]=++sum;
	pos[sum]=x;
	top[x]=t;
	if(son[x])
		dfs2(son[x],t);
	for(int i=head[x];i;i=next[i])
		if(edge[i]^f[x]&&edge[i]^son[x])
			dfs2(edge[i],edge[i]);
}
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	if(ll^rr)
	{
		int mid=(ll+rr)>>1;
		build(a<<1,ll,mid);
		build(a<<1|1,mid+1,rr);
	}
}
void down(int a)
{
	int la=a<<1,ra=a<<1|1,t=lazy[a];
	cnt[la]=(cnt[la]+(long)t*(r[la]-l[la]+1))%mod;
	lazy[la]=(lazy[la]+t)%mod;
	cnt[ra]=(cnt[ra]+(long)t*(r[ra]-l[ra]+1))%mod;
	lazy[ra]=(lazy[ra]+t)%mod;
	lazy[a]=0;
}
void add(int a,int ll,int rr,int val)
{
	if(r[a]<ll||l[a]>rr)
		return;
	if(l[a]>=ll&&r[a]<=rr)
	{
		cnt[a]=(cnt[a]+(long)val*(r[a]-l[a]+1))%mod;
		lazy[a]=(lazy[a]+val)%mod;
		return;
	}
	down(a);
	add(a<<1,ll,rr,val);
	add(a<<1|1,ll,rr,val);
	cnt[a]=(cnt[a<<1]+cnt[a<<1|1])%mod;
}
int ask(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return 0;
	if(l[a]>=ll&&r[a]<=rr)
		return cnt[a];
	down(a);
	return (ask(a<<1,ll,rr)+ask(a<<1|1,ll,rr))%mod;
}
void insert(int x)
{
	int fx;
	while(x)
	{
		fx=top[x];
		add(1,id[fx],id[x],1);
		x=f[fx];
	}
}
int query(int x)
{
	int fx,ans=0;
	while(x)
	{
		fx=top[x];
		ans=(ans+ask(1,id[fx],id[x]))%mod;
		x=f[fx];
	}
	return ans;
}
void solve()
{
	for(int i=1;i<=n;i++)
	{
		insert(i);
		for(int j=0;j<v1[i].size();j++)
			ans[v1[i][j]]=((ans[v1[i][j]]-query(qx[v1[i][j]]))%mod+mod)%mod;
		for(int j=0;j<v2[i].size();j++)
			ans[v2[i][j]]=(ans[v2[i][j]]+query(qx[v2[i][j]]))%mod;
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("chain.in","r",stdin);
	freopen("chain.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++)
	{
		int a;
		scanf("%d",&a);
		a++;
		add(a,i);
		add(i,a);
	}
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d%d",&a,&b,qx+i);
		++b;
		++qx[i];
		v1[a].push_back(i);
		v2[b].push_back(i);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	solve();
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}