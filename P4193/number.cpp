//2020.08.19
//luoguP4193 数字 显然D(x)=x%9...然后就按模9的剩余系进行讨论,用中国剩余定理合并就行
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;
const int mx=22680;
int sm;
int avl[22680];
void init()
{
	avl[0]=1;
	for(int i=1;i<=9;i++)
	{
		for(int j=i*i;j<mx;j+=i*9)
			avl[j]=1;
	}
	for(int i=0;i<mx;i++)
		sm+=avl[i];
}
LL solve(LL x)
{
	if(x<0)
		return 0;
	LL rep=(x+1)/mx,rv=(x+1)%mx;
	LL ans=rep*sm;
	for(int i=0;i<rv;i++)
		ans+=avl[i];
	return ans;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
#endif
	init();
	int t;
	scanf("%d",&t);
	while(t--)
	{
		LL l,r;
		scanf("%lld%lld",&l,&r);
		printf("%lld\n",solve(r)-solve(l-1));
	}
	return 0;
}