//2020.08.05
//luoguP5357 【模板】AC自动机（二次加强版） 就模板呗..
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cassert>
#include<vector>
using namespace std;
int n,tot;
char s[2000009];
int pos[200009];
int nxt[200009][27],fl[200009],sz[200009];
vector<int> e[200009];
int add()
{
	int l=strlen(s+1),cur=0;
	for(int i=1;i<=l;i++)
	{
		int c=s[i]-'a'+1;
		if(!nxt[cur][c])
			nxt[cur][c]=++tot;
		cur=nxt[cur][c];
	}
	return cur;
}
void build()
{
	queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=1;i<=26;i++)
			if(nxt[x][i])
			{
				if(x)
					fl[nxt[x][i]]=nxt[fl[x]][i];
				q.push(nxt[x][i]);
			}
			else
				nxt[x][i]=nxt[fl[x]][i];
	}
}
void dfs(int x)
{
	for(int t:e[x])
		dfs(t),sz[x]+=sz[t];
}
void solve()
{
	int m=strlen(s+1);
	for(int i=1,cur=0;i<=m;i++)
		cur=nxt[cur][s[i]-'a'+1],sz[cur]++;
	for(int i=1;i<=tot;i++)
		e[fl[i]].push_back(i);
	dfs(0);
	for(int i=1;i<=n;i++)
		printf("%d\n",sz[pos[i]]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("ac.in","r",stdin);
	freopen("ac.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%s",s+1),pos[i]=add();
	build();
	scanf("%s",s+1);
	solve();
	return 0;
}