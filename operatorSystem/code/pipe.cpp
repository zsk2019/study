// 管道通信

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    std::cerr << "Failed to create pipe." << std::endl;
    return 1;
  }

  pid_t pid = fork();
  if (pid == -1) {
    std::cerr << "Failed to fork." << std::endl;
    return 1;
  }

  if (pid > 0) {
    // Parent process
    close(pipefd[1]); // Close the write end of the pipe

    char buffer[1024];
    ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer));
    if (bytesRead == -1) {
      std::cerr << "Failed to read from pipe." << std::endl;
      return 1;
    }

    std::cout << "Parent process received message: " << buffer << std::endl;

    close(pipefd[0]); // Close the read end of the pipe
    wait(NULL);       // Wait for the child process to exit

  } else {
    // Child process
    close(pipefd[0]); // Close the read end of the pipe

    std::string message = "Hello, Parent Process!";
    ssize_t bytesWritten = write(pipefd[1], message.c_str(), message.length());
    if (bytesWritten == -1) {
      std::cerr << "Failed to write to pipe." << std::endl;
      return 1;
    }

    close(pipefd[1]); // Close the write end of the pipe
  }

  return 0;
}
/*

在这个示例中，使用 pipe() 函数创建了一个管道，返回的 pipefd
数组包含了读端和写端的文件描述符。

然后使用 fork()
函数创建了一个子进程。父进程关闭了写端（pipefd[1]），然后从管道中读取数据，并打印收到的消息。

子进程关闭了读端（pipefd[0]），然后将消息写入管道（pipefd[1]）。

最后，父进程和子进程都关闭了管道的文件描述符，并且子进程通过 wait()
函数等待父进程退出。

运行该示例，父进程将从子进程接收到消息并打印出来。同样地，管道是一种半双工通信方式，所以在示例中，父进程和子进程的通信是单向的，只能父进程读取子进程写入的数据。

请注意，上述示例使用了 C++ 的标准库以及 POSIX
的系统调用来操作管道和进程。具体的实现方式可能因不同的操作系统而有所差异，可以根据编译器和操作系统的要求进行调整。



*/