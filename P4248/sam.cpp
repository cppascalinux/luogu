//2019.04.09
//luoguP4248 [AHOI2013]差异 后缀自动机+后缀树+树形dp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int n,lst,cnt,tot;
ll ans;
char s[500009];
int o[1000009][27],lnk[1000009],len[1000009];
int	hd[1000009],eg[1000009],nxt[1000009];
int sz[1000009],deg[1000009];
void add(int c)
{
	lnk[0]=-1;
	int cur=++cnt,p;
	len[cur]=len[lst]+1;
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
			lnk[cur]=lnk[q]=cln;
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
	if(!deg[x])
		sz[x]=1;
	// printf("x:%d len:%d sz:%d\n",x,len[x],sz[x]);
	for(int i=hd[x];i;i=nxt[i])
	{
		dfs(eg[i]);
		ans-=2LL*len[x]*sz[x]*sz[eg[i]];
		sz[x]+=sz[eg[i]];
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sa.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n/2;i++)
		swap(s[i],s[n-i+1]);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	for(int i=1;i<=n;i++)
		add(s[i]);
	for(int i=1;i<=cnt;i++)
	{
		ins(lnk[i],i);
		deg[lnk[i]]++;
	}
	// for(int i=0;i<=cnt;i++)
	// 	printf("i:%d lnk:%d len:%d\n",i,lnk[i],len[i]);
	dfs(0);
	ans+=(ll)n*(n+1)*(n-1)/2;
	printf("%lld",ans);
	return 0;
}