//2019.04.20
//luoguP4094 [HEOI2016/TJOI2016]字符串 后缀自动机+倍增+线段树合并/dfs序+主席树
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,lst=1,tot=1,sme,smt;
char s[100009];
int o[200009][27],lnk[200009],len[200009],id[200009],pos[100009];
int hd[200009],eg[200009],nxt[200009];
int rt[200009],lp[8000009],rp[8000009],sz[8000009];
void addsam(int lp,int c)
{
	int cur=++tot,p;
	len[cur]=len[lst]+1;
	id[cur]=lp;
	pos[lp]=cur;
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
			int cln=++tot;
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
	eg[++sme]=b;
	nxt[sme]=hd[a];
	hd[a]=sme;
}
void add(int &a,int l,int r,int id)
{
	if(!a)
		a=++smt;
	sz[a]++;
	if(l<r)
	{
		int mid=(l+r)>>1;
		if(id<=mid)
			add(lp[a],l,mid,id);
		else
			add(rp[a],mid+1,r,id);
	}
}
int ask(int a,int l,int r,int ll,int rr)
{
	if(l>rr||r<ll)
		return 0;
	if(l>=ll&&r<=rr)
		return sz[a];
	int mid=(l+r)>>1;
	return ask(lp[a],l,mid,ll,rr)+ask(rp[a],mid+1,r,ll,rr);
}
int merge(int a,int b)
{
	if(!a||!b)
		return a|b;
	int cur=++smt;
	sz[cur]=sz[a]+sz[b];
	lp[cur]=merge(lp[a],lp[b]);
	rp[cur]=merge(rp[a],rp[b]);
	return cur;
}
void dfs(int x)
{
	o[x][0]=lnk[x];
	for(int i=1;i<=18;i++)
		o[x][i]=o[o[x][i-1]][i-1];
	if(id[x])
		add(rt[x],1,n,id[x]);
	for(int i=hd[x];i;i=nxt[i])
	{
		dfs(eg[i]);
		rt[x]=merge(rt[x],rt[eg[i]]);
	}
}
int get(int p,int l)
{
	p=pos[p];
	for(int i=18;i>=0;i--)
		if(len[o[p][i]]>=l)
			p=o[p][i];
	return p;
}
void bin(int pa,int pb,int pc,int pd)
{
	int l=0,r=min(pd-pc+1,pb-pa+1);
	// printf("l:%d r:%d\n",l,r);
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		int np=get(pd,mid);
		// printf("pd:%d mid:%d np:%d\n",pd,mid,np);
		if(ask(rt[np],1,n,pa+mid-1,pb)>0)
			l=mid;
		else
			r=mid-1;
	}
	printf("%d\n",l);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sa.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	reverse(s+1,s+n+1);
	for(int i=1;i<=n;i++)
		addsam(i,s[i]-'a'+1);
	for(int i=2;i<=tot;i++)
		ins(lnk[i],i);
	dfs(1);
	// printf("sm1:%d\n",ask(rt[1],1,n,n,n));
	for(int i=1,a,b,c,d;i<=m;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		bin(n+1-b,n+1-a,n+1-d,n+1-c);
	}
	return 0;
}