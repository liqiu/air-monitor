#include "serial.h"

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

static unsigned char rx_buffer[256];
static int rx_length;

int open_port(void)
{
  int fd; 
  struct termios options;

  fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
    perror("open_port: Unable to open /dev/ttyAMA0 - ");
  }
  else
    fcntl(fd, F_SETFL, 0);

  tcgetattr(fd, &options);
  cfsetospeed(&options, B9600);
  options.c_cflag |= CLOCAL | CREAD;
  // 8N1
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;
  
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(fd, TCIFLUSH);
  tcsetattr(fd, TCSANOW, &options);

  return (fd);
}

void read_port(int fd)
{
  rx_length = read(fd, (void*)rx_buffer, 255);
  if (rx_length < 0)
  {
  }
  else if (rx_length == 0)
  {
  }
  else
  {  
    int i;
    rx_buffer[rx_length] = '\0';
    printf("%i bytes read:", rx_length);
    for (i = 0; i < rx_length; i++)
    {
      int low = rx_buffer[i] & 0x0f;
      int high = (rx_buffer[i] & 0xf0) >> 4;
      printf("%X%X ", high, low);  
    }
    printf("\n");
  }
}

#define DATA_START_POS 4
int parse_data(int* pm1p0, int* pm2p5, int* pm10)
{
//  *pm1p0 = *pm2p5 = *pm10 = -1;
  if (rx_length != 32)
    return -1;
  // 0x42, 0x4d
  if (rx_buffer[0] != 66 || rx_buffer[1] != 77)
    return -1; 

  *pm1p0 = rx_buffer[DATA_START_POS] * 256 + rx_buffer[DATA_START_POS+1];
  *pm2p5 = rx_buffer[DATA_START_POS+2] * 256 + rx_buffer[DATA_START_POS+3];
  *pm10 = rx_buffer[DATA_START_POS+4] * 256 + rx_buffer[DATA_START_POS+5];
  printf("PM1.0: %i PM2.5: %i PM10: %i\n", *pm1p0, *pm2p5, *pm10);
  return 0;
}
/*
int main(int argc, char** argv)
{
  int pm1p0, pm2p5, pm10;
  int fd = open_port();
  while(1)
  {
    read_port(fd);
    if (!parse_data(&pm1p0, &pm2p5, &pm10))
      printf("PM1.0: %i PM2.5: %i PM10: %i\n", pm1p0, pm2p5, pm10);
    usleep(800000);
  }
  close(fd);
}
*/

