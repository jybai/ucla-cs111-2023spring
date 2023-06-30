#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fds[2][2];

	if (pipe(fds[0]) < 0)
		exit(1);
	if (pipe(fds[1]) < 0)
		exit(1);

	if (argc <= 1) {
		errno = EINVAL;
		exit(1);
	}

	for (int i = 1; i < argc; ++i) {
		// open to setup fin and fout
		pid_t pid;
		pid = fork();
		if (pid < 0) {
			exit(-1);
		}
		else if (pid == 0) {
			// dup2 to replace stdin with fin, close fin
			if (i > 1) {
				if (dup2(fds[i % 2][0], 0) < 0)
					exit(1);
			}
			// dup2 to replace stdout with fout, close fout
			if (i < argc - 1) {
				if (dup2(fds[(i + 1) % 2][1], 1) < 0)
					exit(1);
			}
			if (close(fds[0][0]) < 0)
				exit(1);
			if (close(fds[0][1]) < 0)
				exit(1);
			if (close(fds[1][0]) < 0)
				exit(1);
			if (close(fds[1][1]) < 0)
				exit(1);

			execlp(argv[i], argv[i], NULL);
			exit(1);
		}
		else {
			// close fin and fout
			if (close(fds[i % 2][0]) < 0)
				exit(1);
			if (close(fds[i % 2][1]) < 0)
				exit(1);
			int e = 0;
			wait(&e);
			if (WEXITSTATUS(e))
				exit(WEXITSTATUS(e));

			if (pipe(fds[i % 2]) < 0)
				exit(1);

		}
	}
	if (close(fds[0][0]) < 0)
		exit(1);
	if (close(fds[0][1]) < 0)
		exit(1);
	if (close(fds[1][0]) < 0)
		exit(1);
	if (close(fds[1][1]) < 0)
		exit(1);
	return 0;
}
