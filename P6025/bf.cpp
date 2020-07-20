#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int mx;
void build(int a,int l,int r)
{
	mx=max(mx,a);
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(a<<1,l,mid);
	build(a<<1|1,mid+1,r);
}
int calf(int x)
{
	mx=0;
	build(1,1,x);
	return mx;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("tree.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	int l,r,ans=0;
	scanf("%d%d",&l,&r);
	for(int i=l;i<=r;i++)
		ans^=calf(i);
	printf("%d",ans);
	return 0;
}