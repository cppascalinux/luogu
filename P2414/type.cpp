//luoguP2414 [NOI2011]阿狸的打字机 trie+ac自动机+树状数组
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m,cnt,tot,tme;
char s[100009];
int id[100009],st[100009];
int tri[100009][27],ori[100009][27],fail[100009];
int hd[100009],eg[100009],nxt[100009];
int dfn[100009],ed[100009],csm[100009];
vector<pii> vec[100009];
int ans[100009];
void addc(int x,int val)
{
	for(;x<=cnt+1;x+=x&-x)
		csm[x]+=val;
}
int askc(int x)
{
	int val=0;
	for(;x;x-=x&-x)
		val+=csm[x];
	return val;
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void init()
{
	queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=1;i<=26;i++)
			if(tri[x][i])
			{
				ori[x][i]=1;
				int p=tri[x][i];
				if(x)
					fail[p]=tri[fail[x]][i];
				q.push(p);
			}
			else
				tri[x][i]=tri[fail[x]][i];
	}
}
void dfs1(int x)
{
	ed[x]=dfn[x]=++tme;
	for(int i=hd[x];i;i=nxt[i])
	{
		dfs1(eg[i]);
		ed[x]=max(ed[x],ed[eg[i]]);
	}
}
void dfs2(int x)
{
	addc(dfn[x],1);
	for(int i=0;i<(int)vec[x].size();i++)
	{
		int p=vec[x][i].fi,id=vec[x][i].se;
		ans[id]=askc(ed[p])-askc(dfn[p]-1);
	}
	for(int i=1;i<=26;i++)
		if(ori[x][i])
			dfs2(tri[x][i]);
	addc(dfn[x],-1);
}
void dbg()
{
	for(int i=0;i<=cnt;i++)
		printf("i:%d dfn:%d ed:%d fail:%d\n",i,dfn[i],ed[i],fail[i]);
	for(int i=0;i<=cnt;i++)
	{
		printf("i:%d\n",i);
		for(int j=1;j<=26;j++)
			printf("\tj:%d tri:%d\n",j,tri[i][j]);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("type.in","r",stdin);
	freopen("type.out","w",stdout);
#endif
	scanf("%s",s+1);
	int l=strlen(s+1),tp=0,now=0;
	for(int i=1;i<=l;i++)
		if(s[i]=='P')
			id[++n]=now;
		else if(s[i]=='B')
			now=st[--tp];
		else
		{
			s[i]-='a'-1;
			if(!tri[now][s[i]])
				tri[now][s[i]]=++cnt;
			now=tri[now][s[i]];
			st[++tp]=now;
		}
	init();
	for(int i=1;i<=cnt;i++)
		ins(fail[i],i);
	scanf("%d",&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		vec[id[b]].push_back(pii(id[a],i));
	}
	dfs1(0);
	dfs2(0);
	// dbg();
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}