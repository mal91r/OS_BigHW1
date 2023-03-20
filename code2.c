// calculating
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isGood (char x)
{
  return x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z' || x >= '0' && x <= '9';
}

int func (char string[], int n)
{
  int cntGood = 0, cnt = 0;
  for (int i = 0; i < n; i++)
    {
      if (isGood (string[i]))
	{
	  cntGood++;
	}
      else
	{
	  if (cntGood > 0)
	    {
	      cnt++;
	    }
	  cntGood = 0;
	}
    }
  if (cntGood > 0)
    {
      cnt++;
    }
  return cnt;
}


int main ()
{
  int fd;
  size_t size;
  int buf_size = 20;
  char str_buf[buf_size];
  char name[] = "aaa.fifo";
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

  printf ("Start calculating\n");
  int msg_size = sizeof (str_buf);
  int answer = func (str_buf, msg_size);
  printf ("%d\n", answer);

  char str[100];
  sprintf (str, "%d", answer);
  printf ("End calculating\n");

  int result;
  msg_size = sizeof (str);

  (void) umask (0);

  char name2[] = "bbb.fifo";
  mknod (name2, S_IFIFO | 0666, 0);
  printf ("Start writing\n");
  if ((fd = open (name2, O_WRONLY)) < 0)
    {
      printf ("Can\'t open FIFO for writting\n");
      exit (-1);
    }
  size = write (fd, str, msg_size);
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

