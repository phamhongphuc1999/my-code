#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>

void p1()
{
  printf("PID: %d\n", (int)getpid());
  int i = 10;
  int rc = fork();
  if (rc < 0)
  {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (rc == 0)
  {
    i = 101;
    printf("Children PID: %d; i = %d\n", (int)getpid(), i);
  }
  else
  {
    i = 1000;
    printf("Parent PID: %d; i = %d\n", (int)getpid(), i);
  }
}

void p2()
{
  printf("PID: %d\n", (int)getpid());
  FILE *fptr;
  char buffer[100];
  fptr = fopen("process2-p2.output", "w+");
  if (fptr == NULL)
  {
    printf("Error opening file!\n");
    return;
  }
  int rc = fork();
  if (rc < 0)
  {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (rc == 0)
  {
    for (int i = 0; i < 1000; i++)
    {
      fprintf(fptr, "Children process writing%d...\n", i);
    }
    printf("Children PID: %d\n", (int)getpid());
  }
  else
  {
    for (int i = 0; i < 1000; i++)
    {
      fprintf(fptr, "Parent process writing%d...\n", i);
    }
    printf("Parent PID: %d\n", (int)getpid());
  }
  fclose(fptr);
}

// using simple shared memory
void p3()
{
  printf("PID: %d\n", (int)getpid());
  // create shared memory
  int *key = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  *key = 1;
  int rc = fork();

  if (rc < 0)
  {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (rc == 0)
  {
    printf("Hello!\n", (int)getpid());
    *key = 0;
    exit(0);
  }
  else
  {
    while (*key == 1)
    {
    }
    printf("Goodbye\n", (int)getpid());

    // free shared memory
    munmap(key, sizeof(int));
  }
}

void p3Semaphore()
{
  printf("PID: %d\n", (int)getpid());
  // create shared memory
  sem_t *sem = (sem_t *)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
                             MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  sem_init(sem, 1, 0);
  int rc = fork();

  if (rc < 0)
  {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (rc == 0)
  {
    printf("Hello!\n", (int)getpid());
    sleep(2);
    sem_post(sem);
    exit(0);
  }
  else
  {
    sem_wait(sem);
    printf("Goodbye\n", (int)getpid());

    // free shared memory
    sem_destroy(sem);
    munmap(sem, sizeof(sem_t));
  }
}

void p4()
{
  int rc = fork();
  if (rc < 0)
  {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (rc == 0)
  {
    char *args[5];
    args[0] = strdup("expr");
    args[1] = strdup("3");
    args[2] = strdup("+");
    args[3] = strdup("5");
    args[4] = NULL;

    execvp(args[0], args);
    printf("exec failed\n");
  }
  else
  {
    int wc = wait(NULL);
    printf("End parent process\n");
  }
}

void p5()
{
  int rc = fork();

  if (rc < 0)
  {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (rc == 0)
  { // child
    printf("Child PID: %d\n", getpid());
    exit(0);
  }
  else
  { // parent
    int status;
    pid_t child_pid = rc;

    pid_t wc = waitpid(child_pid, &status, 0);

    printf("End parent process, waited PID: %d\n", wc);

    if (WIFEXITED(status))
    {
      printf("Child exited with code %d\n", WEXITSTATUS(status));
    }
  }
}

void p8()
{
  int fd[2];
  pipe(fd);

  int rc = fork();

  if (rc == 0)
  {                                       // child
    close(fd[0]);                         // close read end
    write(fd[1], "From child: Hello", 5); // write to pipe
  }
  else
  {               // parent
    close(fd[1]); // close write end
    char buf[100];
    read(fd[0], buf, 100); // read from pipe
    printf("Parent: %s\n", buf);
  }
}

int main(int argc, char *argv[])
{
  p8();
  return 0;
}