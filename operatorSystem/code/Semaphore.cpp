#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

// 定义信号量的键值
#define SEM_KEY 1234

// 定义共享资源
int sharedResource = 0;

// 定义信号量变量
int semId;

// 减少信号量值（获取资源）
void wait_semaphore() {
  struct sembuf sb;
  sb.sem_num = 0; // 操作的信号量索引
  sb.sem_op = -1; // 信号量操作，减1
  sb.sem_flg = 0; // 操作标志，常设为0

  if (semop(semId, &sb, 1) == -1) {
    perror("semop");
    exit(1);
  }
}

// 增加信号量值（释放资源）
void signal_semaphore() {
  struct sembuf sb;
  sb.sem_num = 0; // 操作的信号量索引
  sb.sem_op = 1;  // 信号量操作，加1
  sb.sem_flg = 0; // 操作标志，常设为0

  if (semop(semId, &sb, 1) == -1) {
    perror("semop");
    exit(1);
  }
}

int main() {
  // 创建信号量
  semId = semget(SEM_KEY, 1, IPC_CREAT | 0666);
  if (semId == -1) {
    perror("semget");
    exit(1);
  }

  // 初始化信号量计数器
  if (semctl(semId, 0, SETVAL, 1) == -1) {
    perror("semctl");
    exit(1);
  }

  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(1);
  }

  if (pid == 0) {
    // 子进程
    printf("Child process: Trying to acquire resource...\n");

    // 获取资源
    wait_semaphore();

    // 访问共享资源
    printf("Child process: Acquired resource, sharedResource = %d\n",
           sharedResource);
    sharedResource += 10;
    printf("Child process: Updated sharedResource, sharedResource = %d\n",
           sharedResource);

    // 释放资源
    signal_semaphore();

    exit(0);
  } else {
    // 父进程
    printf("Parent process: Trying to acquire resource...\n");

    // 获取资源
    wait_semaphore();

    // 访问共享资源
    printf("Parent process: Acquired resource, sharedResource = %d\n",
           sharedResource);
    sharedResource += 5;
    printf("Parent process: Updated sharedResource, sharedResource = %d\n",
           sharedResource);

    // 释放资源
    signal_semaphore();

    // 等待子进程结束
    wait(NULL);
  }

  // 删除信号量
  if (semctl(semId, 0, IPC_RMID) == -1) {
    perror("semctl");
    exit(1);
  }

  return 0;
}
