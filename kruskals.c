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
edge * create_mst();


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
  create_mst();
  printf("Edges in the MST:\n\n");
  print_edges(MST, MST_E);

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


edge * create_mst()
{
  int trees[N];
  int tree_count = 0;
  int prev_tree, new_tree;
  edge curr_edge;

  for (int i = 0; i < N; ++i) { trees[i] = -1; }

  for (int e = 0, t = 0; e < E && t < MST_E; ++e) {

    curr_edge = Edges[e];

    if (trees[curr_edge.vertex1] == -1 && trees[curr_edge.vertex2] == -1) {
      ++tree_count;
      trees[curr_edge.vertex1] = tree_count;
      trees[curr_edge.vertex2] = tree_count;
    } else if (trees[curr_edge.vertex1] == -1) {
      trees[curr_edge.vertex1] = trees[curr_edge.vertex2];
    } else if (trees[curr_edge.vertex2] == -1) {
      trees[curr_edge.vertex2] = trees[curr_edge.vertex1];
    } else if (trees[curr_edge.vertex1] != trees[curr_edge.vertex2]) {
      --tree_count;

      if (trees[curr_edge.vertex1] > trees[curr_edge.vertex2]) {
        prev_tree = trees[curr_edge.vertex1];
        new_tree = trees[curr_edge.vertex2];
      } else {
        prev_tree = trees[curr_edge.vertex2];
        new_tree = trees[curr_edge.vertex1];
      }

      for (int i = 0; i < N; ++i) {
        if (trees[i] == prev_tree) {
          trees[i] = new_tree;
        } else if (trees[i] > prev_tree) {
          --trees[i];
        }
      }
    } else { continue; }

    MST[t].weight = curr_edge.weight;
    MST[t].vertex1 = curr_edge.vertex1;
    MST[t].vertex2 = curr_edge.vertex2;
    ++t;
  }

  return MST;
}

































