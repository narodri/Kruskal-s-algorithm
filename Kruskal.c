#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _edge{
	int start, end, weight;
}edge;

edge e[50000001];
int n=0;
void insert(edge new, int *n){
	if((*n) >= 50000000){
		printf("The heap is full\n"); exit(1);
	}
	int i = ++(*n);
	while((i!=1)&&(new.weight < e[i/2].weight)){
		e[i] = e[i/2]; i /= 2;
	}
	e[i]=new;
}
edge delete(int *n){
	if((*n) <= 0){
		printf("The heap is empty\n");
	}
	// n=1 일때 마지막 원소 a 가 반환되어도 e[1]=a 로 초기화되어 있어서 문제가 발생할 수 있음
	int anc=1, des=2;
	edge pop = e[1], temp;
	temp = e[(*n)]; --(*n);
	while(des <= (*n)){
		if((des < (*n))&&(e[des].weight > e[des+1].weight)) ++des;
		if(temp.weight <= e[des].weight) break;
		e[anc] = e[des]; anc = des; des *= 2;
	}
	e[anc] = temp;
	return pop;
}

int root[10000] = {-1,};
int find_root(int x){ // 주의 : root의 'index'를 반환한다. (non-negative)
	int i;
	for(i=x;root[i] >= 0;i=root[i]); return i;
}
void Union(int x, int y){
	int sum_negative = root[x] + root[y];
	if(root[x] > root[y]) {
		root[x] = y; root[y]=sum_negative;
	}
	else{
		root[y] = x; root[x]=sum_negative;
	}
}

int main(int argc, char **file_name){
    if(argc != 2){
		printf("usage: ./Kruskal input_filename\n");
		return 0;
	}
	else{
		clock_t start = clock();
		FILE *file_in, *file_out;
		file_in = fopen(file_name[1], "r");
		if(file_in == NULL){
			printf("The input file does not exist\n");
			return 0;
		}
		file_out = fopen("Kruskal_result.txt", "w");
		if(file_out == NULL){
			printf("fail to open file\n");
			return 0;
		}
		int vertices, edges, weight_sum=0, count_vertices=0;
		fscanf(file_in, "%d%d", &vertices, &edges);
		for(int i=0;i<=vertices;++i) root[i] = -1;
		for(int i=0;i<edges;++i) {
			edge new;
			fscanf(file_in, "%d%d%d", &new.start ,&new.end,&new.weight);
			insert(new, &n); 
		}
		for(int i=0;i<edges;++i) {
			edge pop = delete(&n);
			if(find_root(pop.start) != find_root(pop.end)){
				Union(find_root(pop.start), find_root(pop.end));
				weight_sum += pop.weight; count_vertices += 1;
				fprintf(file_out, "%d %d %d\n", pop.start ,pop.end, pop.weight);
			}
		}
		fprintf(file_out, "%d\n", weight_sum);
		if(count_vertices==vertices-1) fprintf(file_out, "CONNECTED\n");
		else fprintf(file_out, "DISCONNECTED\n");
		printf("output written to Kruskal_result.txt\n");
		fclose(file_in); fclose(file_out);
		printf("running time: %lf seconds\n", (double)(clock()-start)/CLOCKS_PER_SEC);
		return 0;
		}
	}