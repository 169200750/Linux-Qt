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
//�����ͻ��ˣ����ӷ�����
void init()
{
    printf("�����ҿͻ��˿�ʼ����\n");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(IP);
    if (connect(sockfd, (SA *)&addr, sizeof(addr)) == -1)
    {
        perror("�޷����ӵ�������");
        printf("�ͻ�������ʧ��\n");
        exit(-1);
    }
    printf("�ͻ��������ɹ�\n");
}
//��ʼͨ��
void *recv_thread(void *p)
{ //����Ϣ
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
        int ret = recv(sockfd, &size, 4, 0); //���ļ���С
        printf("size : %d\n",size);
        if (ret < 0)
        {
            perror("read_size");
            exit(-1);
        }
        
        int ret = read(sockfd, buf, sizeof(buf)); //���ļ�����
        printf("sockfd : %d,ret : %d\n",sockfd,ret);
        if (ret < 0)
        {
            perror("read_nr");
            exit(-1);
        }
        write(fd, buf, ret); //�Ѷ���������д�뵽�ļ���
        */
    }
}
void start()
{
    //������Ϣ
    //����Ϣ֮ǰ������һ���߳�,�������ܷ��������͹�������Ϣ
    pthread_t pid;
    pthread_create(&pid, 0, recv_thread, 0);
    while (1)
    {
        char buf[100] = {};
        scanf(" %s", buf);                 //�����û�����
        send(sockfd, buf, strlen(buf), 0); //����������
    }
}
void sig_close()
{
    //�رտͻ��˵�������
    close(sockfd);
    exit(0);
}

int main()
{
    signal(SIGINT, sig_close); //�ر�CTRL+C
    printf("�����������ǳ�:");
    scanf("%s", name);
    init();                              //���ӷ�����
    send(sockfd, name, strlen(name), 0); //���ǳƷ���������
    start();                             //��ʼͨ��
    return 0;
}