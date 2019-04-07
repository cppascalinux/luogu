//2019.01.31
//luogu1337 吊打xxx 二分+计算几何
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define db double
#define eps 1e-8
using namespace std;
int sgn(db x)
{
	return x>eps?1:(x<-eps?-1:0);
}
struct pt
{
	db x,y;
	pt(){}
	pt(db a,db b){x=a,y=b;}
	bool operator ==(pt p){return sgn(x-p.x)==0&&sgn(y-p.y)==0;}
	bool operator !=(pt p){return sgn(x-p.x)!=0||sgn(y-p.y)!=0;}
	pt operator +(pt p){return pt(x+p.x,y+p.y);}
	pt operator -(pt p){return pt(x-p.x,y-p.y);}
	pt operator *(db v){return pt(x*v,y*v);}
	pt operator /(db v){return pt(x/v,y/v);}
	db operator ^(pt p){return x*p.y-y*p.x;}
	db operator *(pt p){return x*p.x+y*p.y;}
	db getl(){return sqrt(x*x+y*y);}
	pt geti(){return *this/getl();}
	pt rot(){return pt(y,-x);}
};
db cross(pt o,pt a,pt b)
{
	return (a-o)^(b-o);
}
struct ln
{
	pt p,q;
	ln(){}
	ln(pt a,pt b){p=a,q=b;}
	ln(db x1,db y1,db x2,db y2){p=pt(x1,y1),q=pt(x2,y2);}
	pt operator ^(ln l)
	{
		db h1=cross(p,l.p,q),h2=-cross(p,l.q,q);
		return (l.q*h1+l.p*h2)/(h1+h2);
	}
	bool inc(pt x){return sgn(cross(x,p,q))>=0;}
};
int n,m;
int xt[1009],yt[1009],wt[1009];
pt t0[100009],t1[100009];
int inp[100009];
pt get(pt p)
{
	pt ans(0,0);
	for(int i=1;i<=n;i++)
		if(p!=pt(xt[i],yt[i]))
			ans=(ans+pt(xt[i]-p.x,yt[i]-p.y).geti()*(db)wt[i]);
	return ans.rot();
}
void cut(ln l)
{
	memset(inp,0,(m+1)<<2);
	for(int i=1;i<=m;i++)
		if(l.inc(t0[i]))
			inp[i]=1;
	int tp=0;
	for(int i=1;i<=m;i++)
	{
		if(inp[i])
		{
			t1[++tp]=t0[i];
			if(!inp[i%m+1])
			{
				pt p=l^ln(t0[i],t0[i%m+1]);
				if(p!=t0[i])
					t1[++tp]=p;
			}
		}
		else if(inp[i%m+1])
		{
			pt p=l^ln(t0[i],t0[i%m+1]);
			if(p!=t0[i%m+1])
				t1[++tp]=p;
		}
	}
	m=tp;
	for(int i=1;i<=m;i++)
		t0[i]=t1[i];
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("bin.in","r",stdin);
	freopen("bin.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",xt+i,yt+i,wt+i);
	t0[1]=pt(-10000,-10000);
	t0[2]=pt(10000,-10000);
	t0[3]=pt(10000,10000);
	t0[4]=pt(-10000,10000);
	m=4;
	// cut(ln(0,0,10000,5000));
	for(int i=1;i<=100;i++)
	{
		pt p(0,0);
		for(int j=1;j<=m;j++)
			p=p+t0[j];
		p=p/m;
		pt t=get(p);
		// printf("i:%d px:%lf py:%lf tx:%lf ty:%lf\n",i,p.x,p.y,t.x,t.y);
		cut(ln(p,p+t));
		// for(int j=1;j<=m;j++)
		// 	printf("j:%d x:%lf y:%lf\n",j,t0[j].x,t0[j].y);
	}
	printf("%.3lf %.3lf",t0[1].x,t0[1].y);
	return 0;
}