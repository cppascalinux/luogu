//2018.12.14
//luogu3338 zjoi2014 力 fft
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define rg register int
#define db double
#define pi 3.14159265358979323846
using namespace std;
int n,bit,len;
db q[100009],ans[100009];
int inv[270009];
struct cp
{
	db x,y;
	cp(){}
	cp(db a,db b){x=a,y=b;}
	cp operator +(cp p){return cp(x+p.x,y+p.y);}
	cp operator -(cp p){return cp(x-p.x,y-p.y);}
	cp operator *(cp p){return cp(x*p.x-y*p.y,x*p.y+y*p.x);}
	cp operator /(db v){return cp(x/v,y/v);}
}rt[2][270009],sm1[270009],sm2[270009];
void init()
{
	while((1<<bit)<2*n+1)
		bit++;
	len=1<<bit;
	for(rg i=0;i<len;i++)
		inv[i]=(inv[i>>1]>>1)|((i&1)<<(bit-1));
	for(rg i=0;i<len;i++)
		rt[0][i]=cp(cos(2*pi/len*i),sin(2*pi/len*i));
	for(rg i=0;i<len;i++)
		rt[1][i]=rt[0][(len-i)%len];
}
void fft(int c,cp *s)
{
	for(rg i=0;i<len;i++)
		if(i<inv[i])
			swap(s[i],s[inv[i]]);
	for(rg l=2;l<=len;l<<=1)
	{
		int p=l>>1;
		for(rg j=0;j<len;j+=l)
			for(rg i=0;i<p;i++)
			{
				cp t=rt[c][len/l*i]*s[i+j+p];
				s[i+j+p]=s[i+j]-t;
				s[i+j]=s[i+j]+t;
			}
	}
	if(c)
		for(rg i=0;i<len;i++)
			s[i]=s[i]/len;
}
void solve()
{
	for(rg i=1;i<=n;i++)
	{
		sm1[i].x=q[i];
		sm2[i].x=1/(1.0*i*i);
	}
	fft(0,sm1);
	fft(0,sm2);
	for(rg i=0;i<len;i++)
		sm1[i]=sm1[i]*sm2[i];
	fft(1,sm1);
	for(rg i=1;i<=n;i++)
		ans[i]+=sm1[i].x;
	// for(rg i=1;i<=n;i++)
	// 	printf("i:%d ans:%lf\n",i,ans[i]);
	for(rg i=0;i<len;i++)
		sm1[i]=cp(0,0);
	for(rg i=1;i<=n;i++)
		sm1[i].x=q[n-i+1];
	fft(0,sm1);
	for(rg i=0;i<len;i++)
		sm1[i]=sm1[i]*sm2[i];
	fft(1,sm1);
	for(rg i=1;i<=n;i++)
		ans[i]-=sm1[n-i+1].x;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("force.in","r",stdin);
	freopen("force.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(rg i=1;i<=n;i++)
		scanf("%lf",q+i);
	init();
	solve();
	for(rg i=1;i<=n;i++)
		printf("%lf\n",ans[i]);
	return 0;
}