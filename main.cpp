#include <iostream>
#include <sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <unistd.h>

using namespace std;


int main() {
  struct sockaddr_in server_addr, client_addr;
  memset(&server_addr, 0, sizeof(sockaddr_in));
  memset(&client_addr, 0, sizeof(sockaddr_in));
  socklen_t clilen = sizeof(client_addr);

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(3001);;

  int server_socket_fd, client_socket_fd;

  if ((server_socket_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    cout << "Error while creating socket for server :(" << endl;
    return 0;
  }

  if (bind(server_socket_fd, (const sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
    cout << "Error while binding server socket to server address on PORT: 3001" << endl;
    return 0;
  }

  if(listen(server_socket_fd, 5) == -1){
    cout << "Some error while server wants to listen" << endl;
    return 0;
  }

  if((client_socket_fd = accept(server_socket_fd, (sockaddr *) &client_addr, (socklen_t *) &clilen)) == -1){
    cout << "Some error while accepting and creating connections" << endl;
    return 0;
  }

  cout << client_socket_fd << endl;
  const char message[]  = "hello_from_the_server_bitch";
  write(client_socket_fd, message, sizeof(message));

  close(server_socket_fd);
  close(client_socket_fd);

  return 0;
}
