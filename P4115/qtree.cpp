//2018.11.21
//utf-8 luogu4115 qtree4 动态点分治+双优先队列实现支持删除操作+双优先队列防止取同一子树内的值+rmq求lca求路径长度
//还卡常数。。少一点剪枝都过不去。。
#pragma GCC optimize(3)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<ctime>
#define inf 0x3F3F3F3F
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define getm(a,b) (dep[a]<dep[b]?a:b)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,tot,mn,rt;
int col[100009];
int hd[100009],eg[200009],nxt[200009],len[200009];
int dep[100009],dis[100009];
int fm[19][200009],top;
int fu[200009],pos[100009];
int sz[100009],vis[100009];
int fat[100009];
char typ[10];
struct dpq
{
	priority_queue<int> pq1,pq2;
	void push(int x)
	{
		pq1.push(x);
	}
	void del(int x)
	{
		pq2.push(x);
	}
	int size()
	{
		return pq1.size()-pq2.size();
	}
	void pop()
	{
		if(!size())
			return;
		while(pq2.size()&&pq1.top()==pq2.top())
		{
			pq1.pop();
			pq2.pop();
		}
		pq1.pop();
	}
	int top()
	{
		if(!size())
			return -inf;
		while(pq2.size()&&pq1.top()==pq2.top())
		{
			pq1.pop();
			pq2.pop();
		}
		return pq1.top();
	}
	int stop()
	{
		if(size()<2)
			return -inf;
		int x=top();
		pop();
		int y=top();
		push(x);
		return y;
	}
}pq1[100009],pq2[100009],ans;
void read(int &x)
{
	rc ch=0,inv=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc(),(ch=='-'&&(inv=1));
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
	inv&&(x=-x);
}
void readc(char &x)
{
	x=0;
	while(x<'A'||x>'Z')
		x=gc();
}
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x,int fa,int suml)
{
	dep[x]=dep[fa]+1;
	dis[x]=suml;
	fm[0][++top]=x;
	pos[x]=top;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]^fa)
		{
			dfs(eg[i],x,suml+len[i]);
			fm[0][++top]=x;
		}
}
void init()
{
	for(rg i=1;i<=18;i++)
		for(rg j=1;j<=top-(1<<i)+1;j++)
			fm[i][j]=getm(fm[i-1][j],fm[i-1][j+(1<<(i-1))]);
	fu[1]=0;
	for(rg i=2;i<=top;i++)
		fu[i]=fu[i>>1]+1;
}
int getl(int a,int b)
{
	if(pos[a]>pos[b])
		swap(a,b);
	int l=fu[pos[b]-pos[a]+1];
	int lca=getm(fm[l][pos[a]],fm[l][pos[b]-(1<<l)+1]);
	return dis[a]+dis[b]-dis[lca]*2;
}
void getrt(int x,int fa,int siz)
{
	sz[x]=1;
	int mx=0;
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]]&&eg[i]^fa)
		{
			getrt(eg[i],x,siz);
			sz[x]+=sz[eg[i]];
			mx=max(mx,sz[eg[i]]);
		}
	mx=max(mx,siz-sz[x]);
	if(mx<mn)
	{
		mn=mx;
		rt=x;
	}
}
void solve(int x,int siz)
{
	vis[x]=1;
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]])
		{
			mn=inf;
			int nsiz=sz[eg[i]]>sz[x]?siz-sz[x]:sz[eg[i]];
			getrt(eg[i],0,nsiz);
			fat[rt]=x;
			solve(rt,nsiz);
		}
}
void add(int x,int st)
{
	if(x==st)
	{
		int sum1=-inf,sum2=-inf;
		if(pq2[x].size()>=2)
			sum1=pq2[x].top()+pq2[x].stop();
		pq2[x].push(0);
		if(pq2[x].size()>=2)
			sum2=pq2[x].top()+pq2[x].stop();
		if(sum1!=sum2)
		{
			if(sum1>-inf)
				ans.del(sum1);
			if(sum2>-inf)
				ans.push(sum2);
		}
	}
	if(!fat[x])
		return;
	int fa=fat[x];
	int l=getl(st,fa);
	int sum1=-inf,sum2=-inf,top1=-inf,top2=-inf;
	if(pq2[fa].size()>=2)
		sum1=pq2[fa].top()+pq2[fa].stop();
	if(pq1[x].size())
		top1=pq1[x].top();
	pq1[x].push(l);
	if(pq1[x].size())
		top2=pq1[x].top();
	if(top1!=top2)
	{
		if(top1>-inf)
			pq2[fa].del(top1);
		if(top2>-inf)
			pq2[fa].push(top2);
		if(pq2[fa].size()>=2)
			sum2=pq2[fa].top()+pq2[fa].stop();
		if(sum1!=sum2)
		{
			if(sum1>-inf)
				ans.del(sum1);
			if(sum2>-inf)
				ans.push(sum2);
		}
	}
	add(fa,st);
}
void dte(int x,int st)
{
	if(x==st)
	{
		int sum1=-inf,sum2=-inf;
		if(pq2[x].size()>=2)
			sum1=pq2[x].top()+pq2[x].stop();
		pq2[x].del(0);
		if(pq2[x].size()>=2)
			sum2=pq2[x].top()+pq2[x].stop();
		if(sum1!=sum2)
		{
			if(sum1>-inf)
				ans.del(sum1);
			if(sum2>-inf)
				ans.push(sum2);
		}
	}
	if(!fat[x])
		return;
	int fa=fat[x];
	int l=getl(st,fa);
	int sum1=-inf,sum2=-inf,top1=-inf,top2=-inf;
	if(pq2[fa].size()>=2)
		sum1=pq2[fa].top()+pq2[fa].stop();
	if(pq1[x].size())
		top1=pq1[x].top();
	pq1[x].del(l);
	if(pq1[x].size())
		top2=pq1[x].top();
	if(top1!=top2)
	{
		if(top1>-inf)
			pq2[fa].del(top1);
		if(top2>-inf)
			pq2[fa].push(top2);
		if(pq2[fa].size()>=2)
			sum2=pq2[fa].top()+pq2[fa].stop();
		if(sum1!=sum2)
		{
			if(sum1>-inf)
				ans.del(sum1);
			if(sum2>-inf)
				ans.push(sum2);
		}
	}
	dte(fa,st);
}
// void dte(int x,int st)
// {
// 	if(x==st)
// 	{
// 		if(pq2[x].size()>=2)
// 		{
// 			int sum=pq2[x].top()+pq2[x].stop();
// 			ans.del(sum);
// 		}
// 		pq2[x].del(0);
// 		if(pq2[x].size()>=2)
// 		{
// 			int sum=pq2[x].top()+pq2[x].stop();
// 			ans.push(sum);
// 		}
// 	}
// 	if(!fat[x])
// 		return;
// 	int l=getl(st,fat[x]);
// 	if(pq2[fat[x]].size()>=2)
// 	{
// 		int sum=pq2[fat[x]].top()+pq2[fat[x]].stop();
// 		ans.del(sum);
// 	}
// 	if(pq1[x].size())
// 		pq2[fat[x]].del(pq1[x].top());
// 	pq1[x].del(l);
// 	if(pq1[x].size())
// 		pq2[fat[x]].push(pq1[x].top());
// 	if(pq2[fat[x]].size()>=2)
// 	{
// 		int sum=pq2[fat[x]].top()+pq2[fat[x]].stop();
// 		ans.push(sum);
// 	}
// 	dte(fat[x],st);
// }
int main()
{
	// int stt=clock();
	#ifndef ONLINE_JUDGE
	char *ppp=(char*)malloc(256<<20)+(256<<20);
	__asm__("movl %0,%%esp"::"r"(ppp));
	freopen("qtree.in","r",stdin);
	freopen("qtree.out","w",stdout);
	#endif
	read(n);
	int a,b,c;
	for(rg i=1;i<=n-1;i++)
	{
		read(a);
		read(b);
		read(c);
		ins(a,b,c);
		ins(b,a,c);
	}
	dfs(1,0,0);
	init();
	mn=inf;
	getrt(1,0,n);
	solve(rt,n);
	// for(rg i=1;i<=n;i++)
	// 	printf("i:%d fat:%d\n",i,fat[i]);
	read(m);
	for(rg i=1;i<=n;i++)
		add(i,i);
	int sum=n;
	for(rg i=1;i<=m;i++)
	{
		char ch;
		readc(ch);
		if(ch=='C')
		{
			int a;
			read(a);
			col[a]^=1;
			if(!col[a])
			{
				sum++;
				add(a,a);
			}
			else
			{
				sum--;
				dte(a,a);
			}
		}
		else
		{
			if(!sum)
				printf("They have disappeared.\n");
			else
			{
				int t=ans.top();
				t=max(t,0);
				printf("%d\n",t);
			}
		}
	}
	// int edt=clock();
	// cerr<<edt-stt;
	return 0;
}