#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define rg register int
#define db double
#define pi 3.14159265358979323846
using namespace std;
struct cp
{
	db x,y;
	cp(){}
	cp(db a,db b){x=a,y=b;}
	cp operator +(cp p){return cp(x+p.x,y+p.y);}
	cp operator -(cp p){return cp(x-p.x,y-p.y);}
	cp operator *(cp p){return cp(x*p.x-y*p.y,x*p.y+y*p.x);}
	cp operator /(db v){return cp(x/v,y/v);}
};
int n,m,bit,len,smt;
char s[300009],t[300009],tmp[300009];
int sm[300009];
int inv[1050009];
cp ns[1050009],nt[1050009];
cp rt[2][1050009];
int ans[300009];
void init()
{
	while((1<<bit)<n+m+1)
		bit++;
	len=1<<bit;
	for(rg i=0;i<len;i++)
		inv[i]=(inv[i>>1]>>1)|((i&1)<<(bit-1));
	for(rg i=0;i<len;i++)
		rt[0][i]=cp(cos(2*pi/len*i),sin(2*pi/len*i));
	rt[1][0]=rt[0][0];
	for(rg i=1;i<len;i++)
		rt[1][i]=rt[0][len-i];
}
void fft(int c,cp *s)
{
	for(rg i=0;i<len;i++)
		if(i<inv[i])
			swap(s[i],s[inv[i]]);
	for(rg l=2;l<=len;l<<=1)
	{
		int p=l>>1,it=len/l;
		for(rg j=0;j<len;j+=l)
			for(rg i=0;i<p;i++)
			{
				cp t=rt[c][it*i]*s[i+j+p];
				s[i+j+p]=s[i+j]-t;
				s[i+j]=s[i+j]+t;
			}
	}
	if(c)
		for(rg i=0;i<len;i++)
			s[i]=s[i]/len;
}
void mul(cp *a,cp *b)
{
	fft(0,a);
	fft(0,b);
	for(rg i=0;i<len;i++)
		a[i]=a[i]*b[i];
	fft(1,a);
}
void solve()
{
	reverse(t,t+m);
	sm[0]=(int)s[0]*s[0];
	for(rg i=1;i<n;i++)
		sm[i]=sm[i-1]+(int)s[i]*s[i];
	for(rg i=0;i<m;i++)
		smt+=(int)t[i]*t[i];
	for(rg i=0;i<n;i++)
		ns[i].x=s[i];
	for(rg i=0;i<m;i++)
		nt[i].x=t[i];
	mul(ns,nt);
	for(rg i=m-1;i<n;i++)
	{
		ans[i]=smt+sm[i]-2*(int)(ns[i].x+0.5);
		if(i-m>=0)
			ans[i]-=sm[i-m];
	}
	memset(ns,0,sizeof(ns));
	memset(nt,0,sizeof(nt));
	for(rg i=0;i<n;i++)
		ns[i].x=s[i]*s[i];
	for(rg i=0;i<m;i++)
		if(!t[i])
			nt[i].x=1;
	mul(ns,nt);
	for(rg i=m-1;i<n;i++)
		ans[i]-=(int)(ns[i].x+0.5);
	memset(ns,0,sizeof(ns));
	memset(nt,0,sizeof(nt));
	for(rg i=0;i<n;i++)
		if(!s[i])
			ns[i].x=1;
	for(rg i=0;i<m;i++)
		nt[i].x=t[i]*t[i];
	mul(ns,nt);
	for(rg i=m-1;i<n;i++)
		ans[i]-=(int)(ns[i].x+0.5);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	scanf("%d%d%s%s",&m,&n,t,s);
	for(rg i=0;i<n;i++)
		if(s[i]=='*')
			s[i]=0;
		else
			s[i]-='a'-1;
	for(rg i=0;i<m;i++)
		if(t[i]=='*')
			t[i]=0;
		else
			t[i]-='a'-1;
	init();
	solve();
	int sm=0;
	// for(rg i=m-1;i<n;i++)
	// 	printf("i:%d ans:%d\n",i,ans[i]);
	for(rg i=m-1;i<n;i++)
		if(!ans[i])
			sm++;
	printf("%d\n",sm);
	for(rg i=m-1;i<n;i++)
		if(!ans[i])
			printf("%d ",i-m+2);
	return 0;
}