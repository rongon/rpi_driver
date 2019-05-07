#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEVICE_NAME "/dev/sample_02_device"

int main(void)
{
  int fd;
  long ioctl_data;
  char write_data[1];
  char read_data[1];

  if ((fd = open(DEVICE_NAME, O_RDWR | O_SYNC)) < 0) {
    perror("failed to open()\n");
    return -1;
  }

  ioctl(fd, 0, &ioctl_data);

  write_data[0] = '1';
  write(fd, write_data, sizeof(write_data));
  read(fd, read_data, sizeof(read_data));

  sleep(1);

  write_data[0] = '0';
  write(fd, write_data, sizeof(write_data));
  read(fd, read_data, sizeof(read_data));

  close(fd);

  return 0;
}
