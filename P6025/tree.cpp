//2020.07.20
//luoguP6025 线段树 考虑倒数第二层...节点不是1就是2,考虑添加总区间长度时,1,2的变化,变化位置的二进制序列很有规律(递增序列的反转)
//同时发现除了f(2^n)和f(2^n+1),其他的全都有偶数个,异或一下全没了
//考虑去计算异或前缀和g(x),那么只需要求出每个2^n项和2^n+1项的值,再算一下f(x)就行,答案就是g(r)^g(l-1)
//总时间复杂度O(log^2n)(应该能优化成O(logn)但懒得整了..)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;
LL calf(LL x)
{
	if(x==0)
		return 0;
	if(x==1)
		return 1;
	int tp=0;
	for(int i=0;i<=62;i++)
		if(x>>i&1)
			tp=i;
	LL t=x-(1LL<<tp);
	LL ans=(1LL<<(tp+1))-1;
	if(t==0)
		return ans;
	if(t==1)
		return ans+2;
	int ad=0;
	for(int i=0;i<=tp-1;i++)
	{
		if(t>1LL<<i)
			t-=1LL<<i;
		else
		{
			ad=i;
			break;
		}
	}
	LL tmp=1;
	for(int i=1;i<=ad;i++)
		tmp+=1LL<<(tp-i);
	return ans+tmp*2;
}
LL calg(LL x)
{
	if(x==0)
		return 0;
	LL ans=0;
	int stp=0;
	for(LL i=1;i<=x;i<<=1)
	{
		ans^=calf(i);
		if(i>1&&i+1<=x)
			ans^=calf(i+1);
		if(x==i||x==i+1)
			stp=1;
	}
	if(stp)
		return ans;
	if(!(x&1))
		ans^=calf(x);
	return ans;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	LL l,r;
	scanf("%lld%lld",&l,&r);
	printf("%lld",calg(r)^calg(l-1));
	// for(int i=1;i<=1024;i++)
	// 	printf("i:%d f:%lld\n",i,calf(i));
	return 0;
}