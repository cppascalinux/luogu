//2019.04.09
//luoguP3975 [TJOI2015]弦论 sam
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
int n,tot,typ,lst;
ll kth;
char s[500009];
int sam[1000009][27],lnk[1000009],len[1000009],cnt[1000009];
ll sm[1000009];
int deg[1000009],st[1000009];
void ins(int c)
{
	int p,cur=++tot;
	len[cur]=len[lst]+1;
	cnt[cur]=1;
	for(p=lst;p!=-1&&!sam[p][c];p=lnk[p])
		sam[p][c]=cur;
	if(p==-1)
		lnk[cur]=0;
	else
	{
		int q=sam[p][c];
		if(len[q]==len[p]+1)
			lnk[cur]=q;
		else
		{
			int cln=++tot;
			len[cln]=len[p]+1;
			lnk[cln]=lnk[q];
			memcpy(sam[cln],sam[q],27<<2);
			for(;p!=-1&&sam[p][c]==q;p=lnk[p])
				sam[p][c]=cln;
			lnk[cur]=lnk[q]=cln;
		}
	}
	lst=cur;
}
void init1()
{
	if(typ==0)
	{
		for(int i=1;i<=tot;i++)
			cnt[i]=1;
		return;
	}
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
		if(!x)
			break;
		cnt[lnk[x]]+=cnt[x];
		if(!--deg[lnk[x]])
			q.push(lnk[x]);
	}
	cnt[0]=0;
}
void init2()
{
	for(int i=0;i<=tot;i++)
		for(int j=1;j<=26;j++)
			if(sam[i][j])
				deg[sam[i][j]]++;
	queue<int> q;
	q.push(0);
	int tp=0;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		st[++tp]=x;
		for(int i=1;i<=26;i++)
			if(sam[x][i])
				if(!--deg[sam[x][i]])
					q.push(sam[x][i]);
	}
	for(int i=tp;i>=1;i--)
	{
		sm[st[i]]=cnt[st[i]];
		for(int j=1;j<=26;j++)
			if(sam[st[i]][j])
				sm[st[i]]+=sm[sam[st[i]][j]];
	}
}
void solve()
{
	int p=0,tp=0;
	if(kth>sm[0])
	{
		printf("-1");
		return;
	}
	while(kth)
	{
		kth-=cnt[p];
		if(kth<=0)
			break;
		// printf("p:%d kth:%lld\n",p,kth);
		for(int i=1;i<=26;i++)
			if(sam[p][i])
			{
				if(kth<=sm[sam[p][i]])
				{
					st[++tp]=i;
					p=sam[p][i];
					break;
				}
				else
					kth-=sm[sam[p][i]];
			}
	}
	// printf("tp:%d\n",tp);
	for(int i=1;i<=tp;i++)
		printf("%c",(char)(st[i]+'a'-1));
}
void dbg()
{
	for(int i=0;i<=tot;i++)
		printf("i:%d lnk:%d len:%d cnt:%d sm:%lld\n",i,lnk[i],len[i],cnt[i],sm[i]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%s",s+1);
	scanf("%d%lld",&typ,&kth);
	n=strlen(s+1);
	lnk[0]=-1;
	for(int i=1;i<=n;i++)
		ins(s[i]-'a'+1);
	init1();
	init2();
	// dbg();
	solve();
	return 0;
}