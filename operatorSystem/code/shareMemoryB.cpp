#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main() {
  int shmid;
  char *shmaddr;

  // 获取共享内存
  shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
  if (shmid == -1) {
    perror("shmget");
    exit(1);
  }

  // 将共享内存连接到进程的地址空间
  shmaddr = (char *)shmat(shmid, NULL, 0);
  if (shmaddr == (char *)-1) {
    perror("shmat");
    exit(1);
  }

  // 从共享内存读取数据并打印
  printf("Message: %s\n", shmaddr);

  // 分离共享内存
  if (shmdt(shmaddr) == -1) {
    perror("shmdt");
    exit(1);
  }

  return 0;
}
