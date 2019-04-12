//2019.04.12
//P3804 【模板】后缀自动机 标号从1开始
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
int n,cnt=1,lst=1,tot;
char s[1000009];
int o[2000009][29],lnk[2000009],len[2000009],sz[2000009];
int hd[2000009],eg[2000009],nxt[2000009];
ll ans;
void add(int c)
{
	int cur=++cnt,p;
	len[cur]=len[lst]+1;
	sz[cur]=1;
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
			int cln=++cnt;
			len[cln]=len[p]+1;
			lnk[cln]=lnk[q];
			memcpy(o[cln],o[q],27<<2);
			for(;p&&o[p][c]==q;p=lnk[p])
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
		sz[x]+=sz[eg[i]];
	}
	// printf("x:%d sz:%d len:%d\n",x,sz[x],len[x]);
	if(sz[x]>=2)
		ans=max(ans,(ll)len[x]*sz[x]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sam1.out","w",stdout);
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		add(s[i]-'a'+1);
	for(int i=2;i<=cnt;i++)
		ins(lnk[i],i);
	dfs(1);
	printf("%lld",ans);
	return 0;
}