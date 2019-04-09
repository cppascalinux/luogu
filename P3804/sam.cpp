//2019.04.09
//P3804 【模板】后缀自动机
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
int n,lst,tot;
char s[1000009];
int nxt[2000009][27],lnk[2000009],len[2000009],cnt[2000009],deg[2000009];
void ins(int c)
{
	int cur=++tot;
	len[cur]=len[lst]+1;
	cnt[cur]=1;
	int p;
	for(p=lst;p!=-1&&!nxt[p][c];p=lnk[p])
		nxt[p][c]=cur;
	if(p==-1)
		lnk[cur]=0;
	else
	{
		int q=nxt[p][c];
		if(len[p]+1==len[q])
			lnk[cur]=q;
		else
		{
			int cln=++tot;
			len[cln]=len[p]+1;
			lnk[cln]=lnk[q];
			memcpy(nxt[cln],nxt[q],27<<2);
			for(;p!=-1&&nxt[p][c]==q;p=lnk[p])
				nxt[p][c]=cln;
			lnk[q]=lnk[cur]=cln;
		}
	}
	lst=cur;
}
void solve()
{
	for(int i=1;i<=tot;i++)
		deg[lnk[i]]++;
	queue<int> q;
	for(int i=1;i<=tot;i++)
		if(!deg[i])
			q.push(i);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		cnt[lnk[x]]+=cnt[x];
		if(!--deg[lnk[x]])
			q.push(lnk[x]);
	}
	// for(int i=1;i<=tot;i++)
	// 	printf("i:%d lnk:%d len:%d cnt:%d\n",i,lnk[i],len[i],cnt[i]);
	ll ans=0;
	for(int i=1;i<=tot;i++)
		if(cnt[i]>1)
			ans=max(ans,(ll)cnt[i]*len[i]);
	printf("%lld",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	lnk[0]=-1;
	for(int i=1;i<=n;i++)
		ins(s[i]);
	solve();
	return 0;
}