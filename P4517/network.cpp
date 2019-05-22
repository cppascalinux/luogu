//2019.05.22
//luoguP4517 [JSOI2018]防御网络 期望的线性性,拆成贡献,割边直接算,环边用dp计算
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#include<vector>
#define li long long
#define mod 1000000007
using namespace std;
int n,m,tot,tme,tp,cnt,ans;
int mul[209];
int hd[209],eg[40009],nxt[40009];
int sz[209],dfn[209],low[209],st[209];
vector<int> pt[209];
int f[209],g[209],tz[209];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
void init()
{
	mul[0]=1;
	for(int i=1;i<=n;i++)
		mul[i]=mul[i-1]*2%mod;
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x,int fa)
{
	dfn[x]=low[x]=++tme;
	st[++tp]=x;
	sz[x]=1;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			if(!dfn[eg[i]])
			{
				dfs(eg[i],x);
				sz[x]+=sz[eg[i]];
				low[x]=min(low[x],low[eg[i]]);
			}
			else
				low[x]=min(low[x],dfn[eg[i]]);
		}
	if(dfn[x]==low[x])
	{
		ans=(ans+(li)(mul[sz[x]]-1)*(mul[n-sz[x]]-1))%mod;
		vector<int> tmp;
		for(int &i=tp;st[i+1]!=x;i--)
			tmp.push_back(st[i]);
		if(tmp.size()<=1)
			return;
		reverse(tmp.begin(),tmp.end());
		pt[++cnt]=tmp;
	}
}
void solve(int id)
{
	vector<int> &v=pt[id];
	int l=v.size();
	tz[1]=n-sz[v[1]];
	for(int i=2;i<=l-1;i++)
		tz[i]=sz[v[i-1]]-sz[v[i]];
	tz[l]=sz[v[l-1]];
	for(int i=1;i<=l-1;i++)//max length between points
	{
		g[i]=0;
		for(int j=1;j<=i;j++)//start point
		{
			f[j]=(mul[tz[j]]-1+mod)%mod;
			int s=f[j];
			for(int k=j+1;k<=l;k++)//current position
			{
				if(k>j+i)
					s=(s-f[k-i-1]+mod)%mod;
				f[k]=(li)s*(mul[tz[k]]-1+mod)%mod;
				s=(s+f[k])%mod;
			}
			for(int k=l-i+j;k<=l;k++)//legal end position
				g[i]=(g[i]+f[k])%mod;
		}
	}
	g[0]=0;
	for(int i=1;i<=l-1;i++)
		ans=(ans+(li)(g[i]-g[i-1]+mod)*(l-i))%mod;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("network.in","r",stdin);
	freopen("network.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	init();
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		ins(a,b),ins(b,a);
	}
	dfs(1,0);
	for(int i=1;i<=cnt;i++)
		solve(i);
	printf("%lld",(li)ans*qpow(mul[n],mod-2)%mod);
	return 0;
}