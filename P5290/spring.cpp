//luogu P5290 [十二省联考2019]春节十二响 贪心+启发式合并
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
int n,tot;
int m[200009];
int hd[200009],eg[200009],nxt[200009];
int sz[200009],son[200009];
priority_queue<int> pq[29];
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs1(int x)
{
	sz[x]=1;
	for(int i=hd[x];i;i=nxt[i])
	{
		dfs1(eg[i]);
		sz[x]+=sz[eg[i]];
		if(sz[eg[i]]>sz[son[x]])
			son[x]=eg[i];
	}
}
void dfs2(int x,int id)
{
	// printf("x:%d son:%d m:%d\n",x,son[x],m[x]);
	if(son[x])
		dfs2(son[x],id);
	priority_queue<int> tmp;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=son[x])
		{
			dfs2(eg[i],id+1);
			for(;!pq[id+1].empty()&&!pq[id].empty();pq[id+1].pop(),pq[id].pop())
			{
				int np=max(pq[id+1].top(),pq[id].top());
				// printf("x:%d eg:%d np:%d\n",x,eg[i],np);
				tmp.push(np);
			}
			for(;!pq[id+1].empty();pq[id+1].pop())
				pq[id].push(pq[id+1].top());
			for(;!tmp.empty();tmp.pop())
				pq[id].push(tmp.top());
		}
	pq[id].push(m[x]);
	// printf("x:%d ",x);
	// for(;!pq[id].empty();pq[id].pop())
	// {
	// 	printf("%d ",pq[id].top());
	// 	tmp.push(pq[id].top());
	// }
	// printf("\n");
	// for(;!tmp.empty();tmp.pop())
	// 	pq[id].push(tmp.top());
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("spring.in","r",stdin);
	freopen("spring.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",m+i);
	for(int i=2,a;i<=n;i++)
	{
		scanf("%d",&a);
		ins(a,i);
	}
	dfs1(1);
	dfs2(1,1);
	ll ans=0;
	for(;!pq[1].empty();pq[1].pop())
	{
		// printf("top:%d\n",pq[1].top());
		ans+=pq[1].top();
	}
	printf("%lld",ans);
	return 0;
}