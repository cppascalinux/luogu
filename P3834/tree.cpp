#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,1000000,stdin),p1==p2)?EOF:*p1++)
#define rg register int
#define cp(a,b) {lp[a]=lp[b];rp[a]=rp[b];sum[a]=sum[b];}
using namespace std;
char *p1,*p2,buffer[1000000];
int n,m,d,tot;
int xx[200010],id[200010];
int val[200010],root[200010];
int sum[3600010],lp[3600010],rp[3600010];
void read(int &x)
{
	char ch=0;
	int inv=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc(),inv=ch=='-'?1:0;
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+ch-'0',ch=gc();
	x=inv?-x:x;
}
void init()
{
	memcpy(xx,val,sizeof(xx));
	sort(xx+1,xx+n+1);
	d=unique(xx+1,xx+n+1)-xx-1;
	for(int i=1;i<=n;i++)
	{
		int tmp=val[i];
		val[i]=lower_bound(xx+1,xx+d+1,val[i])-xx;
		id[val[i]]=tmp;
	}
}
void add(int &a,int l,int r,int x)
{
	int p=++tot;
	cp(p,a);
	a=p;
	sum[a]++;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(x<=mid)
		add(lp[a],l,mid,x);
	else
		add(rp[a],mid+1,r,x);
}
int ask(int a,int b,int l,int r,int x)
{
	if(l==r)
		return l;
	int cnt=sum[lp[b]]-sum[lp[a]];
	int mid=(l+r)>>1;
	if(x<=cnt)
		return ask(lp[a],lp[b],l,mid,x);
	else
		return ask(rp[a],rp[b],mid+1,r,x-cnt);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	#endif
	read(n),read(m);
	for(rg i=1;i<=n;i++)
		read(val[i]);
	init();
//	for(int i=1;i<=n;i++)
//		printf("i:%d val:%d id:%d\n",i,val[i],id[val[i]]);
	for(rg i=1;i<=n;i++)
	{
		root[i]=root[i-1];
		add(root[i],1,d,val[i]);
	}
	for(rg i=1;i<=m;i++)
	{
		rg a,b,c;
		read(a),read(b),read(c);
		printf("%d\n",id[ask(root[a-1],root[b],1,d,c)]);
	}
	return 0;
}