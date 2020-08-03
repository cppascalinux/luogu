//2020.08.03
//luoguP3346 [ZJOI2015]诸神眷顾的幻想乡 大概就是以每个叶子节点为根节点建广义sam..每条路径一定是两个叶子之间的路径的子串..
//时间复杂度O(20*n*c)...(好暴力qwq)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define PB push_back
#define LL long long
using namespace std;
int n,m,tot=1;
int cl[100009],deg[100009];
vector<int> e[100009];
int nxt[4000009][11],lnk[4000009],len[4000009];
int ins(int cur,int c)
{
	if(!nxt[cur][c])
		nxt[cur][c]=++tot;
	return nxt[cur][c];
}
void dfs(int x,int fa,int cur)
{
	cur=ins(cur,cl[x]);
	for(int t:e[x])
		if(t!=fa)
			dfs(t,x,cur);
}
void add(int lst,int c)
{
	int cur=nxt[lst][c],p=lnk[lst];
	len[cur]=len[lst]+1;
	for(;p&&!nxt[p][c];p=lnk[p])
		nxt[p][c]=cur;
	if(!p)
		return lnk[cur]=1,void();
	int q=nxt[p][c];
	if(len[q]==len[p]+1)
		return lnk[cur]=q,void();
	int cln=++tot;
	len[cln]=len[p]+1,lnk[cln]=lnk[q];
	for(int i=1;i<=m;i++)
		if(len[nxt[q][i]])
			nxt[cln][i]=nxt[q][i];
	for(;p&&nxt[p][c]==q;p=lnk[p])
		nxt[p][c]=cln;
	lnk[q]=lnk[cur]=cln;
}
void build()
{
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=1;i<=m;i++)
			if(nxt[x][i])
				add(x,i),q.push(nxt[x][i]);
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",cl+i),cl[i]++;
	for(int i=1,a,b;i<=n-1;i++)
		scanf("%d%d",&a,&b),e[a].PB(b),e[b].PB(a),deg[a]++,deg[b]++;
	for(int i=1;i<=n;i++)
		if(deg[i]==1)
			dfs(i,0,1);
	build();
	LL ans=0;
	for(int i=1;i<=tot;i++)
		ans+=len[i]-len[lnk[i]];
	printf("%lld",ans);
	return 0;
}