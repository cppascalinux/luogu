//2019.06.15
//luoguP4198 楼房重建 用线段树维护每个区间内斜率最大值,以及只考虑当前区间时的答案
//每次要合并左右区间:若左区间的max>=右区间的max,则右区间一定没有贡献,否则看右区间的左右儿子
//若左儿子的max<=左区间的max,则左儿子一定没有贡献,递归进右儿子计算贡献
//否则左区间对于右儿子一定没有影响,答案加上(父亲的贡献-左儿子的贡献),并递归进左儿子计算贡献
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define db double
#define eps 1e-10
using namespace std;
int n,m;
db mx[400009];
int sm[400009];
int sgn(db x)
{
	return x>eps?1:(x<-eps?-1:0);
}
void update(int a,int l,int r)
{
	int la=a*2,ra=a*2+1;
	mx[a]=max(mx[la],mx[ra]);
	if(sgn(mx[a])==0)
		return sm[a]=0,void();
	sm[a]=sm[la];
	if(sgn(mx[ra]-mx[la])>0)
	{
		l=(l+r)/2+1;
		int t=ra;
		while(1)
		{
			if(l==r)
			{
				if(sgn(mx[t]-mx[la])>0)
					sm[a]++;
				break;
			}
			if(sgn(mx[la]-mx[t*2])>=0)
				l=(l+r)/2+1,t=t*2+1;
			else
			{
				sm[a]+=sm[t]-sm[t*2];
				r=(l+r)/2,t=t*2;
			}
		}
	}
}
void sett(int a,int l,int r,int pos,db val)
{
	if(l==r)
		return mx[a]=val,sm[a]=1,void();
	int mid=(l+r)/2;
	if(pos<=mid)
		sett(a*2,l,mid,pos,val);
	else
		sett(a*2+1,mid+1,r,pos,val);
	update(a,l,r);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("build.in","r",stdin);
	freopen("build.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		sett(1,1,n,a,(db)b/a);
		printf("%d\n",sm[1]);
	}
	return 0;
}