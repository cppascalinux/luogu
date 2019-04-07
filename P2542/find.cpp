#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define lb(x) (x&-x)//二进制最低位
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m,cnt,tme;//点数,边数,操作总数,DFS时间戳
int hd[30009],eg[60009],nxt[60009],tot;//存图
int dfn[30009],ed[30009],dep[30009];//依次为:DFS序,子树中DFS序最大值,节点深度
int c[30009];//树状数组
int fn[30009];//并查集数组
int f[30009][16];//倍增数组
pii e[100009],q[40009];//边集,询问
int del[100009],ont[100009];//边是否被删除,是否为生成树上的边
int typ[40009],ans[40009];//询问的种类,答案
map<pii,int> mp;//记录边的编号
void add(int x,int val)//树状数组[1,x]区间加val
{
    for(int i=x;i;i-=lb(i))
        c[i]+=val;
}
int ask(int x)//x单点求值
{
    int ans=0;
    for(int i=x;i<=n;i+=lb(i))
        ans+=c[i];
    return ans;
}
int fnd(int x)//并查集
{
    return x==fn[x]?x:fn[x]=fnd(fn[x]);
}
void ins(int a,int b)//加边
{
    eg[++tot]=b;
    nxt[tot]=hd[a];
    hd[a]=tot;
}
void dfs(int x,int fa)
{
    dep[x]=dep[fa]+1;
    ed[x]=dfn[x]=++tme;//标记DFS序
    f[x][0]=fa;//标记父亲
    for(int i=1;i<=15;i++)//预处理倍增数组
        f[x][i]=f[f[x][i-1]][i-1];
    for(int i=hd[x];i;i=nxt[i])
        if(eg[i]!=fa)//防止返祖访问
        {
            dfs(eg[i],x);
            ed[x]=max(ed[x],ed[eg[i]]);//更新ed
        }
}
int getlca(int x,int y)//倍增求LCA
{
    if(dep[x]<dep[y])
        swap(x,y);
    int l=dep[x]-dep[y];
    for(int i=0;i<=15;i++)
        if(l&(1<<i))
            x=f[x][i];
    if(x==y)
        return x;
    for(int i=15;i>=0;i--)
        if(f[x][i]!=f[y][i])
            x=f[x][i],y=f[y][i];
    return f[x][0];
}
void modify(int x,int y)//核心:并查集缩点(其实和树链剖分的修改操作很像)
{
    int fx=fnd(x),fy=fnd(y),lca=getlca(x,y);
    while(fx!=fy)
    {
        if(dep[fx]<dep[fy])//优先将深的点向上跳
            swap(fx,fy);
        if(fx!=lca)//将fx到fx父亲的边的边权-1,若fx为LCA则不用修改
        {
            add(ed[fx],-1);//树状数组区间修改
            add(dfn[fx]-1,1);//树状数组区间修改
        }
        x=fnd(f[fx][0]);//fx父亲所在集合的根
        fn[fx]=x;//将fx的根设置为fx父亲所在集合的根
        fx=x;//继续向上跳
    }
}//这里每条边只会被修改一次,所以时间复杂度均摊O(N)
int query(int x,int y)//询问u-v路径的边权和
{
    return ask(dfn[x])+ask(dfn[y])-2*ask(dfn[getlca(x,y)]);
}
void init()
{
    for(int i=1;i<=n;i++)//初始化并查集
        fn[i]=i;
    for(int i=1;i<=m;i++)//得到一棵生成树
        if(!del[i])
        {
            int a=e[i].fi,b=e[i].se;
            if(fnd(a)!=fnd(b))//若a,b不连通
            {
                ont[i]=1;//标记树边
                fn[fnd(a)]=fnd(b);//并查集合并
                ins(a,b);//加边
                ins(b,a);//加边
            }
        }
    dfs(1,0);
    for(int i=2;i<=n;i++)//将所有边的边权设为1
    {
        add(ed[i],1);//树状数组区间修改
        add(dfn[i]-1,-1);//树状数组区间修改
    }
    for(int i=1;i<=n;i++)//初始化并查集
        fn[i]=i;
    for(int i=1;i<=m;i++)//添加未被删除的非树边
        if(!del[i]&&!ont[i])
            modify(e[i].fi,e[i].se);
}
void solve()
{
    for(int i=cnt;i>=1;i--)//倒序处理操作
    {
        if(!typ[i])
            modify(q[i].fi,q[i].se);//添加非树边
        else
            ans[i]=query(q[i].fi,q[i].se);//处理询问
    }
    for(int i=1;i<=cnt;i++)//正序输出
        if(typ[i])
            printf("%d\n",ans[i]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        if(a>b)
            swap(a,b);
        e[i]=pii(a,b);
        mp[e[i]]=i;//用map记录边的编号
    }
    int c,a,b;
    scanf("%d",&c);
    while(c!=-1)
    {
        scanf("%d%d",&a,&b);
        if(a>b)
            swap(a,b);
        q[++cnt]=pii(a,b);
        typ[cnt]=c;//记录操作种类
        if(!c)
            del[mp[q[cnt]]]=1;//这条边已被删除
        scanf("%d",&c);
    }
    init();
    solve();
    return 0;
}