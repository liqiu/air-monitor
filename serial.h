#ifndef SERIAL_H
#define SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

int open_port(void);
void read_port(int fd);
int parse_data(int* pm1p0, int* pm2p5, int* pm10);

#ifdef __cplusplus
}
#endif

#endif
