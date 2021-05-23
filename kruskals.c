// Kelsey Werner
// Homework 7: Graph Algorithms
// 06/01/2021


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
         // for usleep


int N ; // number of nodes (vertices)
int A[100][100] ; // adjacency matrix of the graph
typedef struct edge {
  int weight;
  int vertex1;
  int vertex2;
} edge; // individual edge
int E = 0; // number of edges in the graph
edge Edges[1000]; // all edges of graph
int MST_E; // number of edges in the MST
edge * MST; // minimum search tree

int input_graph();
int print_graph();
void collect_edges();
void print_edges(edge *, int);
void mergesort(edge * arr, int lo, int hi);
void merge(edge * arr, int lo1, int hi1, int lo2, int hi2);


int main()
{
  // create adjacency list of graph vertices
  input_graph() ;// N, A{}{}
  printf("Graph:\n");
  print_graph() ;

  MST_E = N - 1;
  MST = malloc(sizeof(edge) * MST_E);

  // collect and sort list of edges in the graph
  collect_edges();
  printf("All edges in graph:\n\n");
  print_edges(Edges, E);
  mergesort(Edges, 0, E - 1);
  printf("Sorted edges in graph:\n\n");
  print_edges(Edges, E);

  // create minimum search tree




  free(MST);
}


int input_graph()
{
  int r,c ;
  char w[10] ;

  scanf("%d",&N) ;

  // scan the first row of labels....not used
  for (c = 0 ; c < N ; c++) {
    scanf("%s",w) ;
  }


  for (r = 0 ; r < N ; r++) {
    scanf("%s",w) ; // label ... not used
    for (c = 0 ; c < N ; c++) {
      scanf("%s",w) ;
      if (w[0] == '-') {
	A[r][c] = -1 ;
      } else {
	A[r][c] = atoi(w) ;// ascii to integer
      }

    }
  }

}


int print_graph()
{
  int r,c ;

  printf("\n%d\n\n",N) ;

  printf("  ") ;
  for (c = 0 ; c < N ; c++) {
    printf("   %c",c+'A') ;
  }

  printf("\n") ;

  for (r = 0 ; r < N ; r++) {
    printf("%c  ",r+'A') ;
    for (c = 0 ; c < N ; c++) {
      if (A[r][c] == -1) {
	printf("  - ") ;
      } else {
	printf("%3d ",A[r][c]) ;
      }
    }
    printf("\n") ;
  }
  printf("\n") ;
}


void collect_edges()
{
  for (int r = 0; r < N; ++r) {
    for (int c = r + 1; c < N; ++c) {
      if (A[r][c] != -1) {
        Edges[E].weight = A[r][c] ;
        Edges[E].vertex1 = r;
        Edges[E].vertex2 = c;
        ++E;
      }
    }
  }
}


void print_edges(edge * edges, int count)
{
  for (int e = 0; e < count; ++e){
    printf("%d%c%c ", edges[e].weight, edges[e].vertex1+'A', edges[e].vertex2+'A');
  }
  printf("\n\n");
}


void mergesort(edge * arr, int lo, int hi)
{
  int mid;

  if (lo < hi) {
    mid = (lo + hi) / 2;
    mergesort(arr, lo, mid);
    mergesort(arr, mid + 1, hi);
    merge(arr, lo, mid, mid + 1, hi);
  }
}


void merge(edge * arr, int lo1, int hi1, int lo2, int hi2)
{
  edge temp[E];
  int c1 = lo1;
  int c2 = lo2;
  int t_index = 0;
  int i, j;

  while (c1 <= hi1 && c2 <=hi2) {
    if (arr[c1].weight < arr[c2].weight)
      temp[t_index++] = arr[c1++];
    else
      temp[t_index++] = arr[c2++];
  }

  while (c1 <= hi1)
    temp[t_index++] = arr[c1++];

  while (c2 <= hi2)
    temp[t_index++] = arr[c2++];

  for (i = lo1, j = 0; i <= hi2; ++i, ++j)
    arr[i] = temp[j];
}






















