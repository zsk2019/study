#include <fcntl.h>
#include <iostream>
#include <unistd.h>

const char *pipePath = "/tmp/my_named_pipe";

int main() {
  int fd = open(pipePath, O_RDONLY);
  if (fd == -1) {
    std::cerr << "Failed to open named pipe for reading." << std::endl;
    return 1;
  }

  char buffer[1024];
  ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
  if (bytesRead == -1) {
    std::cerr << "Failed to read from named pipe." << std::endl;
    return 1;
  }

  std::cout << "Process B received message: " << buffer << std::endl;

  close(fd);

  return 0;
}
