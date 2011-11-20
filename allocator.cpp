
#include<stdio.h>
#include<string.h>
#define MAXN 5100
#define MAXE 100001
#define QMAX 5100
#define oo 0x77777777
struct Edge{
	int v,w,p;
	Edge *next,*pair;
} *edge[MAXN],mempool[MAXE],*fe[MAXN];
struct point {
    int x, y;
} men[1001], house[1001];
int cntmen, cnthouse;
int memnum,S,T,N,K,piS,cost,vis[MAXN],ins[MAXN],ft[MAXN],
dis[MAXN],Closed,Open,Size,Que[QMAX];
int star_matcher[13][2] = {{0,0}, {9,7},{12,8},{11,4},{11,3},{10,6},{10,5}, {1,9},{12,2},{1,7},{5,6},{4,3},{8,2}};
int is_has[1001][1001], people[1001][1001];
char man[100][20], woman[100][20];


inline int abs(int x) {
    return x >= 0 ? x : -x;
}

inline int mandis(point a, point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

inline int min(int a, int b){
	return a<b?a:b;
}
void add(int s, int t, int p, int w){
	Edge *x=&mempool[memnum++],*y=&mempool[memnum++];
	x->v=t,x->w=w,x->p=p,x->next=edge[s],edge[s]=x,x->pair=y;
	y->v=s,y->w=0,y->p=-p,y->next=edge[t],edge[t]=y,y->pair=x;
}
int spfa(){
	memset(dis,0x77,sizeof(dis));
	memset(ins,0,sizeof(ins));
	memset(ft,0,sizeof(ft));
	memset(fe,0,sizeof(fe));
	Closed=-1,Open=0,Que[0]=S,dis[S]=0,ins[S]=1,Size=1;
	while (Size){
		Closed=(Closed+1)%QMAX;
		int now=Que[Closed];
		ins[now]=0,--Size;
		for(Edge *tmp=edge[now];tmp;tmp=tmp->next){
			int j=tmp->v;
			if(tmp->w&&dis[now]+tmp->p<dis[j])
			{
				dis[j]=dis[now]+tmp->p;
				ft[j]=now;
				fe[j]=tmp;
				if(!ins[j]){
					ins[j]=1;
					++Size;
					Open=(Open+1)%QMAX;
					Que[Open]=j;
				}
			}
		}
	}
	return dis[T]<oo;
}
void aug()
{
	int delta=oo;
	for(int i=T;i!=S;i=ft[i]){
		if(fe[i]->w<delta){
			delta=fe[i]->w;
		}
	}
	for(int i=T;i!=S;i=ft[i]){
		fe[i]->w-=delta;
		fe[i]->pair->w+=delta;
		cost+=fe[i]->p*delta;
	}
}

int calcsim(int manid, int womanid) {
    int id1 = manid + 25, id2 = womanid;
    int sim = 0;
    if (!people[id2][2] || !people[id1][2]) {
        ++sim;
    } else {
        if (people[id2][2] == star_matcher[people[id1][2]][0] || people[id2][2] == star_matcher[people[id1][2]][1]) { // Calc star similarity
            ++sim;
        }
    }
    for (int i = 1; i <= 16; ++i) {
        if (i != 2) {
            if (people[id1][i] == people[id2][i] || !people[id1][i] || !people[id2][i]) {
                ++sim;
            }
        }
    }
    for (int i = 0; i < 100; ++i) {
        if (is_has[id1][i] && is_has[id2][i]) {
            ++sim;
        }
    }
    return sim;
}

int main(){
    freopen("data.in", "r", stdin);
    freopen("plan.txt", "w", stdout);
    for (int i = 1; i <= 50; ++i) {
        for (int j = 1; j <= 16; ++j) {
            scanf("%d", &people[i][j]);
        }
        int tmp, x;
        scanf("%d", &tmp);
        for (int j = 1; j <= tmp; ++j) {
            scanf("%d", &x);
            is_has[i][x] = 1;
        }
    }
    S = 0, T = 51;
    for (int i = 1; i <= 25; ++i) {
        for (int j = 1; j <= 25; ++j) {
            add(i, j + 25, -calcsim(i, j), 1);
        }
    }
    for (int i = 1; i <= 25; ++i) {
        add(S, i, 0, 1);
    }
    for (int i = 1; i <= 25; ++i) {
        add(i + 25, T, 0, 1);
    }
    cost = 0;
    while(spfa()){
        aug();
    }
    for (int now = 1; now <= 25; ++now) {
        for (Edge *e = edge[now]; e; e = e -> next){
            if (!e -> w) {
                printf("%d %d\n", e -> v - 25, now + 25);
                //printf("Allocate man id.%d to woman id.%d, with similarity %d\n", now, e -> v - 25, calcsim(now, e -> v - 25));        
            }
        }
    }
    //printf("Total similarity maximized: %d\n",-cost);	
	return 0;
}
