

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <openssl/ssl.h>

int main(void)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		printf("Socket failed, errno: %d\n", errno);
	
	const struct sockaddr addr = {
		AF_INET,
		htons(8080),
		0
	};

	if(!bind(sockfd, &addr, sizeof(addr)))
		printf("Bind failed, errno: %d\n", errno);

	if(listen(sockfd, 20) < 0)
		printf("Listen failed, errno: %d\n", errno);

	int clientfd = accept(sockfd, NULL, NULL);
	if(clientfd < 0)
		printf("Accept failed, errno: %d\n", errno);

	SSL_CTX* ctx = SSL_CTX_new(TLS_server_method());
	if(!ctx)
		printf("SSL_CTX_new failed, errno: %d\n", errno);

	SSL* ssl = SSL_new(ctx);
	if(!ssl)
		printf("SSL_new failed, errno: %d\n", errno);
	
	if(SSL_set_fd(ssl, clientfd) == 0)
		printf("SSL_set_fd failed, errno: %d\n", errno);

	if(SSL_use_certificate_chain_file(ssl, "") != 1)
		printf("SSL_use_certificate_chain_file failed, errno: %d\n", errno);

	return 0;
}

