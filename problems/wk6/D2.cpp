
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
const int MAXN =1050;
const int MAXM=440020;
const int INF=0x3f3f3f3f;
using namespace std;
struct Edge {
    int to,cap,flow,next;
} edge[MAXM];
int head[MAXN],tot,gap[MAXN],d[MAXN],cur[MAXN],que[MAXN],p[MAXN];

int n,start,endd;
void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,int c)
{
    edge[tot]=(Edge){v,c,0,head[u]};
    head[u] = tot++;
    edge[tot]=(Edge){u,c,c,head[v]};
    head[v] = tot++;
}

int isap(int source,int sink,int N)
{
    memset(gap,0,sizeof(gap));
    memset(d,0,sizeof(d));
    memcpy(cur,head,sizeof(head));
    int top = 0,x = source,flow = 0;
    while(d[source] < N) {
        if(x == sink) {
            int Min = INF,inser=0;
            for(int i = 0; i < top; ++i) {
                if(Min > edge[p[i]].cap - edge[p[i]].flow) {
                    Min = edge[p[i]].cap - edge[p[i]].flow;
                    inser = i;
                }
            }
            for(int i = 0; i < top; ++i) {
                edge[p[i]].flow += Min;
                edge[p[i]^1].flow -= Min;
            }
            if(Min!=INF) flow += Min;
            top = inser;
            x = edge[p[top]^1].to;
            continue;
        }
        int ok = 0;
        for(int i = cur[x]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow && d[v]+1 == d[x]) {
                ok = 1;
                cur[x] = i;
                p[top++] = i;
                x = edge[i].to;
                break;
            }
        }
        if(!ok) {
            int Min = N;
            for(int i = head[x]; i != -1; i = edge[i].next) {
                if(edge[i].cap > edge[i].flow && d[edge[i].to] < Min) {
                    Min = d[edge[i].to];
                    cur[x] = i;
                }
            }
            if(--gap[d[x]] == 0) break;
            gap[d[x] = Min+1]++;
            if(x != source) x = edge[p[--top]^1].to;
        }
    }
    return flow;
}
int s1,s2;
int vis[MAXN];
void dfs1(int loc)
{
    for(int i=head[loc];i!=-1;i=edge[i].next)
    {
        int v=edge[i].to;
        if(!vis[v]&&edge[i].cap>edge[i].flow){
            vis[v]=1;
            s1++;
            dfs1(v);
        }
    }
}

void dfs2(int loc)
{
    for(int i=head[loc];i!=-1;i=edge[i].next)
    {
        int v=edge[i].to;
        if(!vis[v]&&edge[i^1].cap>edge[i^1].flow){
            vis[v]=1;
            s2++;
            dfs2(v);
        }
    }
}

void solve()
{
    s1=s2=0;
    isap(0,n+1,n+2);
    memset(vis,0,sizeof(vis));
    vis[0]=vis[n+1]=1;
    dfs1(0);
    memset(vis,0,sizeof(vis));
    vis[0]=vis[n+1]=1;
    dfs2(n+1);
    if(s1+s2==n)
        printf("UNIQUE\n");
    else
        printf("AMBIGUOUS\n");
}

int main()
{
    int m,a,b,c;
    while(~scanf("%d%d%d%d",&n,&m,&start,&endd)&&(m+n+start+endd))
    {
        init();
        addedge(0,start,INF);
        addedge(endd,n+1,INF);
        while(m--){
            scanf("%d%d%d",&a,&b,&c);
            addedge(a,b,c);
            addedge(b,a,c);
        }
        solve();
    }
    return 0;
}
