//2019.04.09
//luoguP5212 SubString sam+lct维护parent树
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define nrt(x) x==lc(f[x])||x==rc(f[x])
using namespace std;
int n,q,tot,lst;
char s[3000009],typ[10];
int ch[1200009][2],f[1200009],lz[1200009],v[1200009],st[1200009];
int o[1200009][3],lnk[1200009],len[1200009];
void down(int x)
{
	int lx=lc(x),rx=rc(x);
	if(lz[x])
	{
		int &t=lz[x];
		if(lx)
			v[lx]+=t,lz[lx]+=t;
		if(rx)
			v[rx]+=t,lz[rx]+=t;
		t=0;
	}
}
void rot(int x)
{
	int y=f[x],z=f[y],dx=x==rc(y),dy=y==rc(z);
	if(nrt(y))
		ch[z][dy]=x;
	f[x]=z;
	f[y]=x;
	f[ch[x][dx^1]]=y;
	ch[y][dx]=ch[x][dx^1];
	ch[x][dx^1]=y;
}
void splay(int x)
{
	int y,z,tp=0;
	for(y=x;nrt(y);y=f[y])
	{
		// printf("x:%d y:%d\n",x,y);
		// fflush(stdout);
		st[++tp]=y;
	}
	st[++tp]=y;
	for(;tp;tp--)
		down(st[tp]);
	while(nrt(x))
	{
		// printf("rua!\n");
		// fflush(stdout);
		y=f[x],z=f[y];
		if(nrt(y))
			rot((x==rc(y))^(y==rc(z))?x:y);
		rot(x);
	}
}
void access(int x)
{
	for(int y=0;x;y=x,x=f[x])
	{
		// printf("access\n");
		// fflush(stdout);
		splay(x);
		rc(x)=y;
	}
}
void add(int c)
{
	// printf("c:%d\n",c);
	// fflush(stdout);
	lnk[0]=-1;
	int cur=++tot,p;
	len[cur]=len[lst]+1;
	for(p=lst;p!=-1&&!o[p][c];p=lnk[p])
		o[p][c]=cur;
	if(p!=-1)
	{
		int q=o[p][c];
		if(len[q]==len[p]+1)
		{
			lnk[cur]=q;
			f[cur+1]=q+1;
		}
		else
		{
			int cln=++tot;
			len[cln]=len[p]+1;
			memcpy(o[cln],o[q],3<<2);

			lnk[cln]=lnk[q];
			splay(q+1);
			v[cln+1]=v[q+1];
			f[cln+1]=lnk[q]+1;

			for(;p!=-1&&o[p][c]==q;p=lnk[p])
				o[p][c]=cln;
			lnk[cur]=cln;
			f[cur+1]=cln+1;

			access(q+1);
			splay(lnk[q]+1);
			rc(lnk[q]+1)=0;
			f[q+1]=cln+1;
			lnk[q]=cln;
		}
	}
	lst=cur;

	access(cur+1);
	splay(cur+1);
	v[cur+1]++;
	lz[cur+1]++;
}
int solve()
{
	int p=0;
	for(int i=0;i<n;i++)
		s[i]-='A'-1;
	for(int i=0;i<n;i++)
		if(!o[p][s[i]])
			return 0;
		else
			p=o[p][s[i]];
	splay(p+1);
	return v[p+1];
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("lct.in","r",stdin);
	freopen("lct.out","w",stdout);
#endif
	scanf("%d",&q);
	scanf("%s",s);
	n=strlen(s);
	for(int i=0;i<n;i++)
		add(s[i]-'A'+1);
	int msk=0;
	while(q--)
	{
		// printf("q:%d\n",q);
		scanf("%s%s",typ,s);
		n=strlen(s);
		int tsk=msk;
		for(int i=0;i<n;i++)
		{
			tsk=(tsk*131LL+i)%n;
			swap(s[i],s[tsk]);
		}
		if(typ[0]=='A')
			for(int i=0;i<n;i++)
				add(s[i]-'A'+1);
		else
		{
			int ans=solve();
			msk^=ans;
			printf("%d\n",ans);
		}
	}
	return 0;
}