#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ui unsigned int
#define ll long long
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
struct node
{
	ui val;
	int id,rnk;
	node(){}
	node(ui a,int b,int c){val=a,id=b,rnk=c;}
	bool operator <(const node &p) const
	{
		return val<p.val;
	}
};
char *p1,*p2,buffer[10000009];
int n,k,rt,cnt;
ui v[500009],sm[500009];
int ch[20000009][2],sz[20000009];
template<class T>
void rd(T &x)
{
	char c=0;
	x=0;
	while(c<'0'||c>'9')
		c=gc();
	while(c>='0'&&c<='9')
		x=x*10+(c-'0'),c=gc();
}
void add(int &a,ui val,int bit)
{
	if(!a)
		a=++cnt;
	sz[a]++;
	if(bit==-1)
		return;
	if(val&(1U<<bit))
		add(ch[a][1],val,bit-1);
	else
		add(ch[a][0],val,bit-1);
}
ui kth(int a,ui val,int ks,int bit)
{
	if(bit==-1)
		return 0;
	int rp=val&(1U<<bit)?0:1;
	int rsm=sz[ch[a][rp]];
//	printf("a:%d val:%u bit:%d ks:%d rp:%d rsm:%d nxt:%d\n",a,val,bit,ks,rp,rsm,ks<=rsm?rp:rp^1);
	if(ks<=rsm)
	{
	//	printf("bit:%d\n",bit);
		return kth(ch[a][rp],val,ks,bit-1)+(1U<<bit);
	}
	return kth(ch[a][rp^1],val,ks-rsm,bit-1);
}
void solve()
{
	ll ans=0;
	priority_queue<node> pq;
	for(int i=0;i<=n;i++)
	{
		ui val=kth(rt,sm[i],1,31);
		pq.push(node(val,i,1));
//		printf("i:%d val:%u\n",i,val);
	}
	for(int i=1;i<=2*k;i++)
	{
		node t=pq.top();
		pq.pop();
		ans+=t.val;
		if(t.rnk<n)
		{
			t.rnk++;
			t.val=kth(rt,sm[t.id],t.rnk,31);
			pq.push(t);
		}
	}
	printf("%lld\n",ans>>1);
}
void dfs(int a,int bit,ui totm)
{
	printf("a:%d sz:%d bit:%d totm:%u lsm:%d rsm:%d\n",a,sz[a],bit,totm,sz[ch[a][0]],sz[ch[a][1]]);
	if(ch[a][0])
		dfs(ch[a][0],bit-1,totm);
	if(ch[a][1])
		dfs(ch[a][1],bit-1,totm+(1U<<bit));
}
int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	rd(n),rd(k);
	for(int i=1;i<=n;i++)
		rd(v[i]);
	for(int i=1;i<=n;i++)
		sm[i]=sm[i-1]^v[i];
	for(int i=0;i<=n;i++)
		add(rt,sm[i],31);
//	for(int i=0;i<=n;i++)
//		printf("i:%d sm:%u\n",i,sm[i]);
//	dfs(rt,31,0);
	solve();
	return 0;
}
