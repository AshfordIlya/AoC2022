#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#define LOWER_ALPHABET_START 32
#define LOWERCASE_PRIORITY_OFFSET 31
#define UPPERCASE_PRIORITY_OFFSET 27
#define BITFIELD_SIZE 58
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
          total_priority += cur_char - LOWERCASE_PRIORITY_OFFSET;
        else
          total_priority += cur_char + UPPERCASE_PRIORITY_OFFSET;
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

unsigned int sum_priorities_part2(char *input, int size) {
  unsigned int total_priority = 0;
  char *end = input + size;
  while (input != end) {
    unsigned long alphabets[3] = {0};
    for (int i = 0; i < 3; i++) {
      while (*input != '\n') {
        alphabets[i] |= 1UL << (*input - 'A');
        input++;
      }
      input++;
    }
    unsigned long bitwise_and = (alphabets[0] & alphabets[1]);
    bitwise_and &= alphabets[2];
    unsigned int index = 0;
    while (bitwise_and != 1) {
      bitwise_and >>= 1;
      index++;
    }
    if (index >= LOWER_ALPHABET_START)
      total_priority += index - LOWERCASE_PRIORITY_OFFSET;
    else
      total_priority += index + UPPERCASE_PRIORITY_OFFSET;
  }
  return total_priority;
}

int main(void) {
  int file = open("input.txt", O_RDONLY);
  int size = (int)lseek(file, 0, SEEK_END);
  char *input = (char *)mmap(NULL, size, PROT_READ, MAP_PRIVATE, file, 0);
  close(file);
  printf("part 1 = %d\n", sum_priorities(input, size));
  printf("part 2 = %d\n", sum_priorities_part2(input, size));
  return 0;
}