//2019.04.14
//luoguP3966 [TJOI2013]单词 ac自动机+fail树
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
int n,cnt,tot;
char s[1000009];
int o[1000009][27],fail[1000009],sm[1000009];
vector<int> id[1000009];
int hd[1000009],eg[1000009],nxt[1000009];
int ans[1000009];
void add(int x)
{
	int p=0,l=strlen(s+1);
	for(int i=1;i<=l;i++)
		s[i]-='a'-1;
	for(int i=1;i<=l;i++)
	{
		if(!o[p][s[i]])
			o[p][s[i]]=++cnt;
		p=o[p][s[i]];
		sm[p]++;
	}
	id[p].push_back(x);
}
void getfail()
{
	queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=1;i<=26;i++)
			if(o[x][i])
			{
				if(x)
					fail[o[x][i]]=o[fail[x]][i];
				q.push(o[x][i]);
			}
			else
				o[x][i]=o[fail[x]][i];
	}
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
		sm[x]+=sm[eg[i]];
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("ac.in","r",stdin);
	freopen("ac.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		add(i);
	}
	getfail();
	for(int i=1;i<=cnt;i++)
		ins(fail[i],i);
	dfs(0);
	for(int i=1;i<=cnt;i++)
		for(int j=0;j<(int)id[i].size();j++)
			ans[id[i][j]]=sm[i];
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}