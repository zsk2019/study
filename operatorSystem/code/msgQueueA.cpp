#include <cstring>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
struct MyData {
  int id;
  char name[20];
  // 添加其他你需要的字段
};

int main() {
  key_t key;
  int msgid;
  struct MyData data;

  // 生成一个唯一的key
  key = ftok("path/to/some/file", 'A');
  if (key == -1) {
    perror("ftok");
    return 1;
  }

  // 创建消息队列
  msgid = msgget(key, 0666 | IPC_CREAT);
  if (msgid == -1) {
    perror("msgget");
    return 1;
  }

  // 发送数据
  data.id = 1;
  strncpy(data.name, "John", sizeof(data.name));
  if (msgsnd(msgid, &data, sizeof(data), 0) == -1) {
    perror("msgsnd");
    return 1;
  }

  // 接收数据
  if (msgrcv(msgid, &data, sizeof(data), 0, 0) == -1) {
    perror("msgrcv");
    return 1;
  }

  // 打印接收到的数据
  std::cout << "Received data: " << data.id << ", " << data.name << std::endl;

  // 删除消息队列
  if (msgctl(msgid, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    return 1;
  }

  return 0;
}
