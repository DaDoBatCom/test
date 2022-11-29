#include<stdio.h>
#define MAX 100
#define Vc 9999
#define TenFile "dijkstra.txt"
int d[MAX], DinhTruoc[MAX], DaDuyet[MAX]={0};
struct DoThi{
    int SoDinh;
    int a[MAX][MAX];
};
void DocFile(DoThi &d){
    FILE *f;
    f = fopen(TenFile, "rt");
    if(f == NULL){
        printf("\nkhong mo duoc file!!");
        return;
    }
    fscanf(f, "%d", &d.SoDinh);
    for(int i=0; i<d.SoDinh; i++){
        for(int j=0; j<d.SoDinh; j++){
            fscanf(f, "%d", &d.a[i][j]);
        }
    }
    fclose(f);
}
int DinhChuaDuyetvaCoDinhNhoNhat(DoThi g){
    int u=-1, min = Vc;
    for(int i=0; i<g.SoDinh; i++){
        if(DaDuyet[i]==0 && d[i]<min){
            u=i;
            min=d[i];
        }
    }
    return u;
}
int InDuongDi(int S, int i){
    printf("\n(%d,%d)=%d, Duong di:%d", S, i, d[i], i);
    int k=i;
    while(k!=S){
        printf("<-%d", DinhTruoc[k]);
        k=DinhTruoc[k];
    }
}
void Dijkstra(DoThi g, int S, int F){//tim duong di ngnan nhat tuwf dinh bat dau den cac dinh con lai
    for(int i=0; i<g.SoDinh; i++){
        DinhTruoc[i] = -1;
        d[i]=Vc;
    }
    d[S]=0;
    int  u;
    while(DaDuyet[F] == 0){
        u = DinhChuaDuyetvaCoDinhNhoNhat(g);
        if(u==-1){
            break;
        }
        DaDuyet[u]=1;
        for(int v=0; v < g.SoDinh; v++){
            if(DaDuyet[v] == 0 && g.a[u][v]!=0 && d[v]>d[u]+g.a[u][v]){
                d[v]=d[u]+g.a[u][v];
                DinhTruoc[v]= u;
            }
        }
        // SoDinhDaDuyet--;
    }
    // printf("\ncac duong di tu dinh %d den cac dinh con lai: ", S);
    // for(int i=0; i<g.SoDinh; i++){
    //     if(d[i] >0 && d[i] < Vc){
    //         InDuongDi(S, i);
    //     }
    // } 
    if(DaDuyet[F]) 
        InDuongDi(S, F);
    else    
        printf("\nkhong co duong di tu %d den %d", S, F);
}
int main(){
	DoThi d;
    DocFile(d);
    int S, F;
    printf("\nnhap dinh bat dau: ");
    scanf("%d%d", &S, &F);
    Dijkstra(d, S, F);
	return 0;
}

