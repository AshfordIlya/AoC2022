#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

unsigned int find_sums(char *input, int size) {
	unsigned int sum[3] = {0};
	unsigned int tmp_sum = 0;
	unsigned int tmp_num = 0;
	char *end = input + size;
	char cur_char = *input;
	while (input != end) {
		while (cur_char != '\n') {
			tmp_num *= 10;
			tmp_num += cur_char - '0';
			input++;
			cur_char = *input;
		}
		tmp_sum += tmp_num;
		tmp_num = 0;
		input++;
		cur_char = *input;
		if(cur_char == '\n') {
			for (int i = 0; i < 3; i++) {
				if(tmp_sum > sum[i]) {
					int swap_sum = sum[i];
					sum[i] = tmp_sum;
					for(int j = i+1; j < 3; j++) {
						tmp_sum = sum[j];
						sum[j] = swap_sum;
						swap_sum = tmp_sum;
					}
					break;
				}
			}
			tmp_sum = 0;
		}
	}
	return sum[0]+sum[1]+sum[2];
}

int main(void) {
	int file = open("input.txt", O_RDONLY);
	int size = (int)lseek(file, 0, SEEK_END);
	char *input = (char*)mmap(NULL, size, PROT_READ, MAP_PRIVATE, file, 0);
	close(file);
	printf("%d\n", find_sums(input, size));
	return 0;
}
