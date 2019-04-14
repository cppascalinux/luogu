//2019.04.14
//luoguP3181 [HAOI2016]找相同字符 sam+parent树
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int n,m,lst=1,tot=1,sme;
char s[200009],t[200009];
int o[400009][27],lnk[400009],len[400009],cnt[400009];
ll sm[400009];
int hd[400009],eg[400009],nxt[400009];
void add(int c)
{
	int cur=++tot,p;
	len[cur]=len[lst]+1;
	cnt[cur]=1;
	for(p=lst;p&&!o[p][c];p=lnk[p])
		o[p][c]=cur;
	if(!p)
		lnk[cur]=1;
	else
	{
		int q=o[p][c];
		if(len[q]==len[p]+1)
			lnk[cur]=q;
		else
		{
			int cln=++tot;
			len[cln]=len[p]+1;
			lnk[cln]=lnk[q];
			memcpy(o[cln],o[q],27<<2);
			for(;p&&o[p][c]==q;p=lnk[p])
				o[p][c]=cln;
			lnk[cur]=lnk[q]=cln;
		}
	}
	lst=cur;
}
void ins(int a,int b)
{
	eg[++sme]=b;
	nxt[sme]=hd[a];
	hd[a]=sme;
}
void dfs1(int x)
{
	for(int i=hd[x];i;i=nxt[i])
	{
		dfs1(eg[i]);
		cnt[x]+=cnt[eg[i]];
	}
}
void dfs2(int x)
{
	sm[x]+=(ll)cnt[x]*(len[x]-len[lnk[x]]);
	for(int i=hd[x];i;i=nxt[i])
	{
		sm[eg[i]]+=sm[x];
		dfs2(eg[i]);
	}
}
void solve()
{
	int p=1,mx=0;
	ll ans=0;
	for(int i=1;i<=m;i++)
	{
		while(p&&!o[p][t[i]])
		{
			p=lnk[p];
			mx=min(mx,len[p]);
		}
		if(p)
		{
			p=o[p][t[i]];
			mx++;
		}
		else
			p=1,mx=0;
		ans+=sm[lnk[p]];
		ans+=(ll)cnt[p]*(mx-len[lnk[p]]);
	}
	printf("%lld",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1);
	m=strlen(t+1);
	for(int i=1;i<=n;i++)
		add(s[i]-'a'+1);
	for(int i=1;i<=m;i++)
		t[i]-='a'-1;
	for(int i=2;i<=tot;i++)
	{
		ins(lnk[i],i);
		// printf("i:%d lnk:%d\n",i,lnk[i]);
	}
	dfs1(1);
	dfs2(1);
	solve();
	return 0;
}