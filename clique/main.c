#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool or (bool *el, int n) {
  for (int i = 0; i < n; i++) {
    if (el[i]) {
      return true;
    }
  }

  return false;
}

void clique(bool **elements, int num_symbols, int num_clauses) {
  bool tmp[num_symbols];
  bool results[num_symbols];

  puts("Results:");
  for (int i = 0; i < (1 << num_symbols); i++) {
    bool invalid_result = false;

    for (int j = 0; j < num_symbols; j++) {
      results[j] = (i >> j) & 1;
    }

    for (int j = 0; j < num_clauses; j++) {
      for (int l = 0; l < num_symbols; l++) {
        tmp[l] = results[l] & elements[j][l];
      }

      bool result = or (tmp, num_symbols);

      if (!result) {
        invalid_result = true;
        break;
      }
    }

    if (!invalid_result) {
      for (int i = 0; i < num_symbols - 1; i++) {
        printf("%d ", results[i]);
      }
      printf("%d\n", results[num_symbols - 1]);
    }
  }
}

int main() {
  int num_clauses = 3;
  int num_symbols = 3;

  bool **elements = (bool **)malloc(num_clauses * sizeof(bool *));
  for (int i = 0; i < num_clauses; i++) {
    elements[i] = (bool *)malloc(num_symbols * sizeof(bool));
  }

  // The clauses must contain all elements, even if just simbolically (set them
  // to false in this case, which is a neutral element in OR operations)

  elements[0][0] = true;
  elements[0][1] = false;
  elements[0][2] = true;

  elements[1][0] = false;
  elements[1][1] = true;
  elements[1][2] = false;

  elements[2][0] = false;
  elements[2][1] = false;
  elements[2][2] = true;

  clique(elements, num_symbols, num_clauses);

  for (int i = 0; i < num_clauses; i++) {
    free(elements[i]);
  }
  free(elements);

  return 0;
}
