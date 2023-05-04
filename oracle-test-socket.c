#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define DO_SYS( call, error ) if((call)==-1) { perror(error); exit(-1); }

int main(int argc, const char** argv) {
  //TODO: timeout. Use constants.
  struct sockaddr_in* local_address = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
  int server_fd;
  int server_fd2 = socket(AF_INET, SOCK_STREAM, 0);
  local_address->sin_family = AF_INET;
  inet_aton("127.0.0.1", &local_address->sin_addr);
  local_address->sin_port = htons(25000);
  bind(server_fd2, (struct sockaddr*) local_address, sizeof(*local_address));
  
  if(listen(server_fd2, 10) != 0) {
    exit(1);
  }
  struct sockaddr_in client_address;
  int size = sizeof(client_address);
  
  server_fd = accept(server_fd2, (struct sockaddr*) (&client_address), &size);
  
  long arr[5] = {10, 50, 30, 9, 1000};
  int length = 0;
  recv(server_fd, &length, 4, 0);
  char* buf = (char*) malloc(length);
  int bytes_received=0, bytes_sent=0;
  int total=0;
  while(total<length) {
    bytes_received=recv(server_fd, buf, length-total, 0);
    total+=bytes_received;
  }
  printf("%s\n", buf);
  total=0;
  long send_length = 40 << 8;
  if(send(server_fd, &send_length, 8, 0)==-1) printf("NO\n");
  send_length = send_length >> 8;
  char* send_buf = (char*) arr;
  while(total < send_length) {
    bytes_sent = send(server_fd, send_buf+total, send_length-total, 0);
    total+=bytes_sent;
  }
  close(server_fd);
  free(local_address);
  free(buf);
}