#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define db long double
#define eps 1e-12L
#define pcc pair<cp,cp>
#define fi first
#define se second
using namespace std;
char *p1,*p2,buffer[10000009];
db tmp[100],*pwl;
int sgn(db x)
{
	return x>eps?1:(x<-eps?-1:0);
}
struct cp
{
	db x;
	int y;
	cp(){}
	cp(db a,int b){x=a,y=b;}
	void clr()
	{
		if(x==0)
		{
			x=y=0;
			return;
		}
		while(x>=10||x<=-10)
		{
			x/=10;
			y++;
		}
		while(x<1&&x>-1)
		{
			x*=10;
			y--;
		}
	}
	bool operator <(cp p)
	{
		if(sgn(x)!=sgn(p.x))
			return sgn(x)<sgn(p.x);
		return ((y<p.y)^(sgn(x)==-1))||(y==p.y&&sgn(x-p.x)<0);
	}
	bool operator >(cp p)
	{
		if(sgn(x)!=sgn(p.x))
			return sgn(x)>sgn(p.x);
		return ((y>p.y)^(sgn(x)==-1))||(y==p.y&&sgn(x-p.x)>0);
	}
	bool operator ==(cp p){return y==p.y&&sgn(x-p.x)==0;}
	bool operator >=(cp p){return !(*this<p);}
	bool operator <=(cp p){return !(*this>p);}
	cp operator *(cp p){cp t(x*p.x,y+p.y);t.clr();return t;}
	cp operator /(cp p){cp t(x/p.x,y-p.y);t.clr();return t;}
	cp operator +(cp p){cp q=*this;if(q.y>p.y)swap(p,q);p.x+=q.x/pwl[p.y-q.y];p.clr();return p;}
	cp operator -(cp p){cp q=*this;q.x-=p.x/pwl[q.y-p.y];q.clr();return q;}
};
int n;
db p[1000009];
cp sa[1000009],sb[1000009];
pcc st[1000009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=(x*10)+(ch&15),ch=gc();
}
cp cross(pcc o,pcc a,pcc b)
{
	cp x1=a.fi-o.fi,y1=a.se-o.se;
	cp x2=b.fi-o.fi,y2=b.se-o.se;
	return x1*y2-x2*y1;
}
cp bin(int l,int r,cp k)
{
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if((st[mid].se-st[mid-1].se)/(st[mid].fi-st[mid-1].fi)<=k)
			l=mid;
		else
			r=mid-1;
	}
	return k*st[l].fi-st[l].se;
}
void solve()
{
	int top=0;
	st[++top]=pcc(cp(1,0),cp(0,0));
	cp ans(0,0);
	int p=1;
	for(int i=1;i<=n;i++)
	{
		while(p<top&&(st[p+1].se-st[p].se)/(st[p+1].fi-st[p].fi)<=sb[i])
			p++;
		cp t=sb[i]*st[p].fi-st[p].se;
		t=t*(cp(1,0)/sa[i]);
		if(t>ans)
			ans=t;
		pcc np=pcc(sa[i],sa[i]*sb[i]);
		while(top>1&&cross(st[top-1],st[top],np)<=(cp(0,0)))
			top--;
		p=min(p,top);
		st[++top]=np;
	}
	int t=ans.y+6;
	printf("%d",(int)(ans.x*pwl[t]+0.1));
}
void dbg()
{
	printf("1-0.1:%Lf %d\n",(cp(1,-2)-cp(1,-1)).x,(cp(1,-2)-cp(1,-1)).y);
}
int main()
{
	for(int ttt=1;ttt<=10;ttt++)
	{
		char sin[20],sout[20];
		sprintf(sin,"a%d.in",ttt);
		sprintf(sout,"a%d.out",ttt);
	freopen(sin,"r",stdin);
	freopen(sout,"w",stdout);
	rd(n);
	pwl=tmp+50;
	for(int i=-20;i<=20;i++)
		pwl[i]=powl(10.0,i);
	for(int i=1,a;i<=n;i++)
	{
		rd(a);
		p[i]=a/(db)1000000.0;
	}
	sa[0]=cp(1,0);
	sb[0]=cp(0,0);
	db tmp=1;
	for(int i=1;i<=n;i++)
	{
		tmp*=1/(1-p[i]);
		cp a=cp(1/(1-p[i]),0);
		a.clr();
		sa[i]=sa[i-1]*a;
		cp b=cp(p[i]/(1-p[i]),0);
		b.clr();
		sb[i]=sb[i-1]+b;
	}
	// printf("%Lf",tmp);
	// printf("san:%.20Lf %d\n",sa[n].x,sa[n].y);
	// dbg();
	solve();
	cerr<<clock();
	}
	return 0;
}
