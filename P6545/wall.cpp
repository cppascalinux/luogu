//fuck ccf
#include<bits/stdc++.h>
#define fi first
#define se second
typedef long long ll;
typedef std::pair<int,int> pii;
using namespace std;
struct node
{
	int x,y;
	ll l;
	bool operator<(const node &o)const{return l>o.l;}
};
struct edge
{
	int v;
	ll l;
	edge(){}
	edge(int a,ll b):v(a),l(b){}
	bool operator<(const edge &o)const{return l>o.l;}
};
int n,m;
int vl[409][409];
int dr[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int ls[409][409][4];
int v0[409][409],pre[409][409];
int cut[409][409][4];
ll d0[409][409];
vector<edge> g1[1000009];
int v1[1000009];
ll d1[1000009];
void dij0()
{
	priority_queue<node> pq;
	memset(d0,0x3F,sizeof(d0));
	d0[1][1]=0;
	pq.push(node{1,1,0});
	while(!pq.empty())
	{
		node t=pq.top();
		pq.pop();
		if(v0[t.x][t.y])
			continue;
		v0[t.x][t.y]=1;
		for(int i=0;i<4;i++)
		{
			int nx=t.x+dr[i][0],ny=t.y+dr[i][1];
			if(nx>=1&&nx<=n+1&&ny>=1&&ny<=m+1&&!v0[nx][ny]&&d0[nx][ny]>t.l+ls[t.x][t.y][i])
			{
				d0[nx][ny]=t.l+ls[t.x][t.y][i];
				pre[nx][ny]=i^1;
				pq.push(node{nx,ny,d0[nx][ny]});
			}
		}
	}
}
void adde(int a,int b,ll l)
{
	g1[a].emplace_back(b,l);
	g1[b].emplace_back(a,l);
}
void build()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(vl[i][j])
			{
				cut[i][j][0]=cut[i][j][2]=1;
				cut[i+1][j][1]=cut[i+1][j][2]=1;
				cut[i][j+1][0]=cut[i][j+1][3]=1;
				cut[i+1][j+1][1]=cut[i+1][j+1][3]=1;
			}
	memset(v0,0,sizeof(v0));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(vl[i][j])
			{
				for(int tx=i,ty=j;tx!=1||ty!=1;)
				{
					if(v0[tx][ty])
						break;
					v0[tx][ty]=1;
					int d=pre[tx][ty];
					int nx=tx+dr[d][0];
					int ny=ty+dr[d][1];
					cut[tx][ty][d]=cut[nx][ny][d^1]=1;
					tx=nx,ty=ny;
				}
			}
	cut[1][1][1]=cut[1][1][3]=1;
	for(int i=1;i<=n+1;i++)
		for(int j=1;j<=m+1;j++)
		{
			int id=((i-1)*(m+1)+j-1)*4;
			if(!cut[i][j][0])
				adde(id+3,id+4,0);
			if(!cut[i][j][1])
				adde(id+1,id+2,0);
			if(!cut[i][j][2])
				adde(id+2,id+4,0);
			if(!cut[i][j][3])
				adde(id+1,id+3,0);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m+1;j++)
		{
			int id=((i-1)*(m+1)+j-1)*4;
			int nid=(i*(m+1)+j-1)*4;
			adde(id+4,nid+2,ls[i][j][0]);
			adde(id+3,nid+1,ls[i][j][0]);
		}
	for(int i=1;i<=n+1;i++)
		for(int j=1;j<=m;j++)
		{
			int id=((i-1)*(m+1)+j-1)*4;
			int nid=((i-1)*(m+1)+j)*4;
			adde(id+2,nid+1,ls[i][j][2]);
			adde(id+4,nid+3,ls[i][j][2]);
		}
}
void dij1()
{
	priority_queue<edge> pq;
	memset(d1,0x3F,sizeof(d1));
	d1[2]=0;
	pq.emplace(2,0);
	while(!pq.empty())
	{
		edge t=pq.top();
		pq.pop();
		if(v1[t.v])
			continue;
		v1[t.v]=1;
		for(edge u:g1[t.v])
			if(!v1[u.v]&&d1[u.v]>t.l+u.l)
			{
				d1[u.v]=t.l+u.l;
				pq.emplace(u.v,d1[u.v]);
			}
	}
	printf("%lld\n",d1[3]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			scanf("%d",vl[i]+j);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m+1;j++)
		{
			scanf("%d",&ls[i][j][0]);
			ls[i+1][j][1]=ls[i][j][0];
		}
	}
	for(int i=1;i<=n+1;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&ls[i][j][2]);
			ls[i][j+1][3]=ls[i][j][2];
		}
	}
	dij0();
	build();
	dij1();
	return 0;
}