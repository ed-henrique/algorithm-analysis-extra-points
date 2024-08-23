#include <time.h>
#include <stdio.h>
#include <limits.h>

// Matrix Dimensions
int idx_i1=30, idx_j1=35;
int idx_i2=35, idx_j2=15;
int idx_i3=15, idx_j3= 5;
int idx_i4= 5, idx_j4=10;
int idx_i5=10, idx_j5=20;
int idx_i6=20, idx_j6=25;

void printBest(int positions[6][6], int i, int j) {
  if (i == j) {
    printf("%c", i + 'A');
  } else {
    printf("(");
    printBest(positions, i, positions[i][j]);
    printBest(positions, positions[i][j] + 1, j);
    printf(")");
  }
}

void minimumMultiplicationWithoutMemo(int n, int arrays[7]) {
  int p[n-1][n-1];
  int result[n-1][n-1];

  for (int j = 1; j < n - 1; j++) {
    for (int i = j - 1; i >= 0; i--) {
      int mk = 0, m = INT_MAX;
      for (int k = i; k < j; k++) {
        int current = result[i][k] + result[k+1][j] + arrays[i] * arrays[k+1] * arrays[j+1];
        if (current < m) {
          m = current;
          mk = k;
        }
      }

      result[i][j] = m;
      p[i][j] = mk;
    }
  }

  // printBest(p, 0, 5);
  printf("\n");
}

int main() {
  int p[7] = { idx_i1, idx_i2, idx_i3, idx_i4, idx_i5, idx_i6, idx_j6 };

  clock_t inicio, fim;
  double tempo_decorrido;

  inicio = clock();
  minimumMultiplicationWithoutMemo(7, p);
  fim = clock();

  tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC;

  printf("%.10f\n", tempo_decorrido);

  return 0;
}
