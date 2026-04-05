#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

struct stat attr;
int nBytes, src_fd, tgt_fd, dir_fd;

void printHelp(char *self) {
	printf("Try '%s --help' for more information.\n", self);
	// not gonna actually implement help
}

bool malformed(int argc, char *argv[]) {
	if (argc == 1) {
		printf("%s: no operands specified\n", argv[0]);
		printHelp(argv[0]);
		return true;
	}
	if (argc == 2) {
		printf("%s: missing destination after '%s'\n", argv[0], argv[1]);
		printHelp(argv[0]);
		return true;
	}
	return false;
}

void copy(int argc, char *src, char *dest) {
	stat(src, &attr);
	char buf[attr.st_size];
	src_fd = open(src, O_RDONLY, 0);

	if (argc == 3) {
		tgt_fd = creat(dest, attr.st_mode);
	} else {
		int oflag = O_CREAT|O_WRONLY|O_TRUNC;
		dir_fd = open(dest, O_RDONLY, 0);
		tgt_fd = openat(dir_fd, src, oflag, attr.st_mode);
	}

	nBytes = read(src_fd, buf, attr.st_size);
	write(tgt_fd, buf, nBytes);
}

int main(int argc, char *argv[]) {
	if (malformed(argc, argv)) return 1;
	for (int i = 1; i<argc-1; i++) { copy(argc, argv[i], argv[argc-1]); }
}
