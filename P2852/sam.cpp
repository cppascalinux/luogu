//2020.08.03
//luoguP2852 [USACO06DEC]Milk Patterns G 后缀自动机,注意用map存储转移...
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
int n,k,tot=1,lst=1;
map<int,int> nxt[40009];
int lnk[40009],len[40009],sz[40009];
vector<int> v[40009];
void add(int c)
{
	int cur=++tot,p=lst;
	len[cur]=len[lst]+1,sz[cur]=1,lst=cur;
	for(;p&&!nxt[p].count(c);p=lnk[p])
		nxt[p][c]=cur;
	if(!p)
		return lnk[cur]=1,void();
	int q=nxt[p][c];
	if(len[q]==len[p]+1)
		return lnk[cur]=q,void();
	int cln=++tot;
	lnk[cln]=lnk[q],len[cln]=len[p]+1,nxt[cln]=nxt[q];
	for(;p&&nxt[p][c]==q;p=lnk[p])
		nxt[p][c]=cln;
	lnk[cur]=lnk[q]=cln;
}
void dfs(int x)
{
	for(int t:v[x])
		dfs(t),sz[x]+=sz[t];
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("sam.in","r",stdin);
	freopen("sam.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	for(int i=1,a;i<=n;i++)
		scanf("%d",&a),add(a);
	for(int i=2;i<=tot;i++)
		v[lnk[i]].push_back(i);
	dfs(1);
	int ans=0;
	for(int i=1;i<=tot;i++)
		if(sz[i]>=k)
			ans=max(ans,len[i]);
	printf("%d",ans);
	return 0;
}