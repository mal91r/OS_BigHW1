// reader
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{
  size_t size = 5000;
  int fd;
  char buffer[size];
  ssize_t read_bytes;
  printf ("Start reading file...\n");
  printf("%s\n", argv[1]);
  if ((fd = open (argv[1], O_RDONLY)) < 0)
    {
      printf ("Can\'t open file\n");
      exit (-1);
    }
  do
    {
      read_bytes = read (fd, buffer, size);
      if (read_bytes == -1)
	{
	  printf ("Can\'t write this file\n");
	  exit (-1);
	}
      //buffer[read_bytes] = '\0';
      printf ("Input string:%s", buffer);
    }
  while (read_bytes == size);
  if (close (fd) < 0)
    {
      printf ("Can\'t close file\n");
    }
  printf ("End reading file...\n");

  int result;
  int msg_size = read_bytes;
  char name[] = "aaa.fifo";
  (void) umask (0);

  mknod (name, S_IFIFO | 0666, 0);
  printf ("Writer start\n");
  if ((fd = open (name, O_WRONLY)) < 0)
    {
      printf ("Can\'t open FIFO for writting\n");
      exit (-1);
    }
  size = write (fd, buffer, msg_size);
  if (size != msg_size)
    {
      printf ("Can\'t write all string to FIFO\n");
      exit (-1);
    }
  if (close (fd) < 0)
    {
      printf ("Writer: Can\'t close FIFO\n");
      exit (-1);
    }
  printf ("Writer exit\n");
  return 0;
}
