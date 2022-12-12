#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

// scores
const unsigned int result_table[3][3] = {{4, 8, 3}, {1, 5, 9}, {7, 2, 6}};

// indexes
const unsigned int part2_index_table[3][3] = {{2, 0, 1}, {0, 1, 2}, {1, 2, 0}};

unsigned int find_total_score(char *input, int size) {
  char *end = input + size;
  unsigned int total_score = 0;
  unsigned int cur_char;
  unsigned int index_opponent;
  unsigned int index_self;
  while (input < end) {
    cur_char = *input;
    index_opponent = cur_char - 'A';
    input += 2;
    cur_char = *input;
    index_self = cur_char - 'X';
    total_score += result_table[index_opponent][index_self];
    input += 2;
  }
  return total_score;
}

unsigned int find_total_score_part_2(char *input, int size) {
  char *end = input + size;
  unsigned int total_score = 0;
  unsigned int cur_char;
  unsigned int index_opponent;
  unsigned int index_self;
  while (input < end) {
    cur_char = *input;
    index_opponent = cur_char - 'A';
    input += 2;
    cur_char = *input;
    index_self = part2_index_table[index_opponent][cur_char - 'X'];
    total_score += result_table[index_opponent][index_self];
    input += 2;
  }
  return total_score;
}

int main(void) {
  int file = open("input.txt", O_RDONLY);
  int size = (int)lseek(file, 0, SEEK_END);
  char *input = (char *)mmap(NULL, size, PROT_READ, MAP_PRIVATE, file, 0);
  close(file);
  printf("Total Score Part 1 = %d\n", find_total_score(input, size));
  printf("Total Score Part 2 = %d\n", find_total_score_part_2(input, size));
  return 0;
}
