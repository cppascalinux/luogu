//2019.04.12
//luoguP2178 [NOI2015]品酒大会 后缀数组+后缀树+树形dp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define inf 0x7F7F7F7F
using namespace std;
int n,lst,tot,cnt;
char s[300009];
int v[300009];
int o[600009][29],lnk[600009],len[600009];
int hd[600009],eg[600009],nxt[600009],sz[600009],mn[600009],mx[600009];
ll ans1[300009],ans2[300009];
void add(int lsp,int c)
{
	lnk[0]=-1;
	int cur=++cnt,p;
	len[cur]=len[lst]+1;
	sz[cur]=1;
	mn[cur]=mx[cur]=v[lsp];
	for(p=lst;p!=-1&&!o[p][c];p=lnk[p])
		o[p][c]=cur;
	if(p!=-1)
	{
		int q=o[p][c];
		if(len[q]==len[p]+1)
			lnk[cur]=q;
		else
		{
			int cln=++cnt;
			len[cln]=len[p]+1;
			lnk[cln]=lnk[q];
			memcpy(o[cln],o[q],27<<2);
			for(;p!=-1&&o[p][c]==q;p=lnk[p])
				o[p][c]=cln;
			lnk[q]=lnk[cur]=cln;
		}
	}
	lst=cur;
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x)
{
	for(int i=hd[x];i;i=nxt[i])
	{
		dfs(eg[i]);
		ans1[len[x]]+=(ll)sz[x]*sz[eg[i]];
		sz[x]+=sz[eg[i]];
		ll &f=ans2[len[x]];
		if(mn[x]<inf)
		{
			f=max(f,(ll)mx[x]*mx[eg[i]]);
			f=max(f,(ll)mx[x]*mn[eg[i]]);
			f=max(f,(ll)mn[x]*mx[eg[i]]);
			f=max(f,(ll)mn[x]*mn[eg[i]]);
		}
		mx[x]=max(mx[x],mx[eg[i]]);
		mn[x]=min(mn[x],mn[eg[i]]);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sa.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++)
		scanf("%d",v+i);
	memset(mx,0x80,sizeof(mx));
	memset(mn,0x7F,sizeof(mn));
	memset(ans2,0x80,sizeof(ans2));
	for(int i=n;i>=1;i--)
		add(i,s[i]-'a'+1);
	for(int i=1;i<=cnt;i++)
		ins(lnk[i],i);
	dfs(0);
	for(int i=n-1;i>=0;i--)
	{
		ans1[i]+=ans1[i+1];
		ans2[i]=max(ans2[i],ans2[i+1]);
	}
	for(int i=0;i<=n-1;i++)
		printf("%lld %lld\n",ans1[i],ans1[i]?ans2[i]:0);
	return 0;
}