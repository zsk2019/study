#include <fcntl.h>
#include <iostream>
#include <unistd.h>

const char *pipePath = "/tmp/my_named_pipe";

int main() {
  int fd = open(pipePath, O_WRONLY);
  if (fd == -1) {
    std::cerr << "Failed to open named pipe for writing." << std::endl;
    return 1;
  }

  std::string message = "Hello, Process B!";
  ssize_t bytesWritten = write(fd, message.c_str(), message.length());
  if (bytesWritten == -1) {
    std::cerr << "Failed to write to named pipe." << std::endl;
    return 1;
  }

  close(fd);

  return 0;
}

/*

首先，需要确保在运行示例之前，命名管道 /tmp/my_named_pipe
已经存在。可以通过执行以下命令创建命名管道：

bash

mkfifo /tmp/my_named_pipe



*/