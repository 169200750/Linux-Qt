#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
int sockfd;
char *IP = "192.168.195.128";
short PORT = 8888;
typedef struct sockaddr SA;
char name[20];
//启动客户端，连接服务器
void init()
{
    printf("聊天室客户端开始启动\n");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(IP);
    if (connect(sockfd, (SA *)&addr, sizeof(addr)) == -1)
    {
        perror("无法连接到服务器");
        printf("客户端启动失败\n");
        exit(-1);
    }
    printf("客户端启动成功\n");
}
//开始通信
void *recv_thread(void *p)
{ //收消息
    while (1)
    {
        
        char buf[100] = {0};
        if (recv(sockfd, buf, sizeof(buf), 0) <= 0)
        {
            return NULL;
        }
        printf("%s\n", buf);
        /*
        open("aaa.jpg",O_CREAT,0666);
        
        int fd = open("aaa.jpg", O_CREAT | O_WRONLY | O_TRUNC, 0666);
        if (fd < 0)
        {
            perror("open");
            exit(-1);
        }
        int size;
        char buf[1024 * 1024] = {0};
        /*
        int ret = recv(sockfd, &size, 4, 0); //读文件大小
        printf("size : %d\n",size);
        if (ret < 0)
        {
            perror("read_size");
            exit(-1);
        }
        
        int ret = read(sockfd, buf, sizeof(buf)); //读文件内容
        printf("sockfd : %d,ret : %d\n",sockfd,ret);
        if (ret < 0)
        {
            perror("read_nr");
            exit(-1);
        }
        write(fd, buf, ret); //把读到的内容写入到文件中
        */
    }
}
void start()
{
    //发送消息
    //发消息之前，启动一个线程,用来接受服务器发送过来的消息
    pthread_t pid;
    pthread_create(&pid, 0, recv_thread, 0);
    while (1)
    {
        char buf[100] = {};
        scanf(" %s", buf);                 //接受用户输入
        send(sockfd, buf, strlen(buf), 0); //发给服务器
    }
}
void sig_close()
{
    //关闭客户端的描述符
    close(sockfd);
    exit(0);
}

int main()
{
    signal(SIGINT, sig_close); //关闭CTRL+C
    printf("请输入您的昵称:");
    scanf("%s", name);
    init();                              //连接服务器
    send(sockfd, name, strlen(name), 0); //将昵称发给服务器
    start();                             //开始通信
    return 0;
}