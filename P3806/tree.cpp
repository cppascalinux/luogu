//utf-8 luogu3806 点分治1
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define inf 0x7F7F7F7F
#define rg register int
using namespace std;
int n,m,tot,mn,rt;
int hd[10009],nxt[20009],eg[20009],len[20009];
int sz[10009],vis[10009];
int st[10009],top;
int qr[109],ans[109];
char buc[10000009];
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void getrt(int x,int fa,int siz)
{
	sz[x]=1;
	int mx=0;
	for(int i=hd[x];i;i=nxt[i])
	{
		int p=eg[i];
		if(p^fa&&!vis[p])
		{
			getrt(p,x,siz);
			sz[x]+=sz[p];
			mx=max(mx,sz[p]);
		}
	}
	mx=max(mx,siz-sz[x]);
	if(mx<mn)
	{
		mn=mx;
		rt=x;
	}
}
void dfs(int x,int fa,int suml)
{
	st[++top]=suml;
	for(int i=hd[x];i;i=nxt[i])
	{
		int p=eg[i];
		if(p^fa&&!vis[p])
			dfs(p,x,suml+len[i]);
	}
}
void cal(int x)
{
	top=0;
	int lst=1;
	buc[0]=1;
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]])
		{
			dfs(eg[i],0,len[i]);
			for(rg j=1;j<=m;j++)
				if(!ans[j])
					for(rg k=lst;k<=top;k++)
						if(st[k]<=qr[j]&&buc[qr[j]-st[k]])
							ans[j]=1;
			for(rg j=lst;j<=top;j++)
				buc[st[j]]=1;
			lst=top+1;
		}
	for(rg i=1;i<=top;i++)
		buc[st[i]]=0;
}
void solve(int x,int siz)
{
	// printf("x:%d\n",x);
	vis[x]=1;
	cal(x);
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]])
		{
			int p=eg[i];
			mn=inf;
			int tsz=sz[p]>sz[x]?siz-sz[x]:sz[p];
			getrt(p,0,tsz);
			solve(rt,tsz);
		}
}
int main()
{
	int stt=clock();
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	int a,b,c;
	for(rg i=1;i<=n-1;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		ins(a,b,c);
		ins(b,a,c);
	}
	for(rg i=1;i<=m;i++)
		scanf("%d",qr+i);
	mn=inf;
	getrt(1,0,n);
	solve(rt,n);
	for(rg i=1;i<=m;i++)
		if(ans[i])
			printf("AYE\n");
		else
			printf("NAY\n");
	int edt=clock();
	// cerr<<edt-stt<<endl;
	return 0;
}