// 04-fifo-reader.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  int fd;
  size_t size;
  int buf_size = 3;
  char str_buf[buf_size];
  char name[] = "bbb.fifo";

  printf ("Start reading\n");
  
  if ((fd = open (name, O_RDONLY)) < 0)
    {
      printf ("Can\'t open FIFO for reading\n");
      exit (-1);
    }
  size = read (fd, str_buf, buf_size);
  if (size < 0)
    {
      printf ("Can\'t read string from FIFO\n");
      exit (-1);
    }
  printf ("Reader exit, str_buf: %s\n", str_buf);
  if (close (fd) < 0)
    {
      printf ("Reader: Can\'t close FIFO\n");
      exit (-1);
    }
  printf ("End reading\n");
  size = sizeof(str_buf);
  printf ("Start writing\n");
  if ((fd = open (argv[1], O_WRONLY | O_CREAT, 0666)) < 0)
    {
      printf ("Can\'t open file\n");
      exit (-1);
    }
  size_t new_size = write (fd, str_buf, size);
  if (size != new_size)
    {
      printf ("Can\'t write all string\n");
      exit (-1);
    }
  if (close (fd) < 0)
    {
      printf ("Can\'t close file\n");
    }
  printf ("End writing!\n");
  return 0;
}

