#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#define LOWER_ALPHABET_START 32

unsigned int sum_priorities(char *input, int size) {
  unsigned int total_priority = 0;
  unsigned int line_sz = 0;
  char *end = input + size;
  char cur_char = *input;
  unsigned long alphabet = 0;
  while (input != end) {
    while (cur_char != '\n') {
      input += 2;
      line_sz += 2;
      cur_char = *input;
    }
    input -= line_sz;
    line_sz >>= 1U;
    for (int i = 0; i < line_sz; i++) {
      cur_char = *input - 'A';
      alphabet |= 1UL << cur_char;
      input++;
    }
    for (int i = 0; i < line_sz; i++) {
      cur_char = *input - 'A';
      if ((alphabet >> cur_char) & 1U) {
        if (cur_char >= LOWER_ALPHABET_START)
          total_priority += cur_char - 31;
        else
          total_priority += cur_char + 27;
        input += line_sz - i;
        break;
      }
      input++;
    }
    alphabet &= 0U;
    line_sz = 0;
    input++;
  }
  return total_priority;
}

int main(void) {
  int file = open("input.txt", O_RDONLY);
  int size = (int)lseek(file, 0, SEEK_END);
  char *input = (char *)mmap(NULL, size, PROT_READ, MAP_PRIVATE, file, 0);
  close(file);
  printf("%d\n", sum_priorities(input, size));
  return 0;
}