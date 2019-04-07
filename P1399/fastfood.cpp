//2018.11.24
//luogu1399 noi2013 快餐店 基环树删边直径 预处理前缀，后缀
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
#define ll long long
#define inf 0x7F7F7F7F7F7F7F7FLL
using namespace std;
int n,tot,cntc,rt;
ll mx;
ll sumc;
int hd[100009],eg[200009],nxt[200009],len[200009];
int vis[100009];
ll ins[100009];
int st[100009],top;
int onc[100009],stc[100009];
ll disc[100009],depc[100009];
ll fpre[100009],gpre[100009],fsuf[100009],gsuf[100009];
void add(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs1(int x,int fa,ll suml)
{
	// printf("x:%d suml:%lld\n",x,suml);
	if(vis[x])
	{
		if(ins[x])
		{
			sumc=suml-ins[x];
			for(rg i=top;st[i+1]!=x;i--)
			{
				onc[st[i]]=1;
				stc[++cntc]=st[i];
				disc[cntc]=ins[st[i]]-ins[x];
			}
		}
		return;
	}
	vis[x]=1;
	ins[x]=suml;
	st[++top]=x;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]^fa)
			dfs1(eg[i],x,suml+len[i]);
	ins[x]=0;
	top--;
}
void dfs2(int x,int fa,int from,ll suml)
{
	if(suml>mx)
	{
		mx=suml;
		rt=x;
	}
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]^fa&&(eg[i]==from||!onc[eg[i]]))
			dfs2(eg[i],x,from,suml+len[i]);
}
ll solve()
{
	ll ans=inf;
	for(rg i=1;i<=cntc;i++)
		fpre[i]=max(fpre[i-1],disc[1]-disc[i]+depc[i]);
	for(rg i=cntc;i>=1;i--)
		fsuf[i]=max(fsuf[i+1],disc[i]+depc[i]);
	ll tmin=0;
	for(rg i=1;i<=cntc;i++)
	{
		gpre[i]=max(gpre[i-1],disc[1]-disc[i]+depc[i]-tmin);
		tmin=min(tmin,disc[1]-disc[i]-depc[i]);
	}
	tmin=0;
	for(rg i=cntc;i>=1;i--)
	{
		gsuf[i]=max(gsuf[i+1],disc[i]+depc[i]-tmin);
		tmin=min(tmin,disc[i]-depc[i]);
	}
	for(rg i=1;i<=cntc-1;i++)
	{
		int p=i+1;
		ll tmp=max(max(gpre[i],gsuf[p]),fpre[i]+fsuf[p]+sumc-disc[1]);
		ans=min(ans,tmp);
		// if(tmp<=206160725755)
		// 	printf("i:%d stc:%d\n",i,stc[i]);
	}
	// printf("ans:%lld\n",ans);
	ans=min(ans,gpre[cntc]);
	return ans;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("fastfood.in","r",stdin);
	freopen("fastfood.out","w",stdout);
	#endif
	scanf("%d",&n);
	int a,b,c;
	for(rg i=1;i<=n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
		add(b,a,c);
	}
	dfs1(1,0,1);
	ll ans=0;
	for(rg i=1;i<=cntc;i++)
	{
		mx=-1;
		dfs2(stc[i],0,stc[i],0);
		depc[i]=mx;
		mx=-1;
		dfs2(rt,0,stc[i],0);
		ans=max(ans,mx);
	}
	// printf("ans:%lld\n",ans);
	// for(rg i=1;i<=cntc;i++)
	// 	printf("i:%d st:%d dis:%lld dep:%lld\n",i,stc[i],disc[i],depc[i]);
	ans=max(ans,solve());
	printf("%.1Lf",(long double)ans/2);
	return 0;
}