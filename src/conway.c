#include <stdlib.h>
#include <unistd.h>

#define LIN 30
#define COL 100

int matrix[LIN][COL];
int matrix_att[LIN][COL];

void initial_state() {
   int i,j;
   for (i=0; i<LIN; i++) {
      for (j=0; j<COL; j++) {
         matrix[i][j] = (i+j)%2;
      }
   }
}

void init() {
   int i,j;
   for (i=0; i<LIN; i++) {
      for (j=0; j<COL; j++) {
         matrix[i][j] = 0;
      }
   }
}

void print_matrix() {
   int i,j;
   for (i=0; i<LIN; i++) {
      for (j=0; j<COL; j++) {
         if (matrix[i][j] == 1)
            printf("#");
         else
            printf(" ");
      }
      printf("\n");
   }
}

int neighbors_number(int x, int y) {
   int number = 0;
   if (x > 0) {
      if (matrix[x-1][y] == 1)
         number += 1;
      if (y > 0)
         if (matrix[x-1][y-1] == 1)
            number += 1;
      if (y < COL-1)
         if (matrix[x-1][y+1] == 1)
            number += 1;
   }
   if (x < LIN-1) {
      if (matrix[x+1][y] == 1)
         number += 1;
      if (y > 0)
         if (matrix[x+1][y-1] == 1)
            number += 1;
      if (y < COL-1)
         if (matrix[x+1][y+1] == 1)
            number += 1;
   }
   if (y > 0)
      if (matrix[x][y-1] == 1)
         number += 1;
   if (y < COL-1)
      if (matrix[x][y+1] == 1)
         number += 1;

   return number;
}

int lives(int x, int y) {
   int neighbor = neighbors_number(x, y);
   if (neighbor < 2 || neighbor > 3)
      return 0;
   if (neighbor == 2 && matrix[x][y] == 0)
      return 0;
   return 1;
}

void copyMat() {
   int i,j;
   for (i=0; i<LIN; i++)
      for (j=0; j<COL; j++)
         matrix[i][j] = matrix_att[i][j];
}

int main() {
   init();
   initial_state();
   print_matrix();

   int i,j;
   char x;
   while (1) {
      for (i=0; i<LIN; i++) {
         for (j=0; j<COL; j++) {
            matrix_att[i][j] = lives(i, j);
         }
      }
      copyMat();
      usleep(100000);
      system("clear");
      print_matrix();
   }
}
