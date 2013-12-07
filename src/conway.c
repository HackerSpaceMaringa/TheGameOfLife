#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int LIN, COL;
int **matrix, **matrix_att;

void initial_state() {
   int i,j;
   for (i=0; i<LIN; i++) {
      for (j=0; j<COL; j++) {
         matrix[i][j] = (i+j)%2;
      }
   }
}

void create_matrix(FILE *file) {
   int i;
   matrix = (int **) malloc(sizeof(int) * LIN);
   matrix_att = (int **) malloc(sizeof(int) * LIN);
   for (i=0; i<LIN; i++) {
      matrix[i] = (int *) malloc(sizeof(int) * COL);
      matrix_att[i] = (int *) malloc(sizeof(int) * COL);
   }
}

void read_from_file(FILE *file) {
   int ch, cont = 0;
   while (cont < LIN*COL) {
      ch = fgetc(file);
      if (ch != '\n' && ch != ' ') {
         ch -= 48;
         matrix[cont/COL][cont%COL] = ch;
         cont++;
      } else if (ch == '\n') {
         cont = cont + COL - (cont%COL);
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

int main(int argc, char *argv[]) {
   LIN = atoi(argv[2]);
   COL = atoi(argv[3]);
   FILE *file = fopen(argv[1], "r");
   create_matrix(file);
   init();
   //initial_state();
   read_from_file(file);
   print_matrix();
   getchar();

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
