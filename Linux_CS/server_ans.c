/*===============================================================
 *   文件名称：server.c
 *   创建日期：2022年12月3日
 *================================================================*/

#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>

struct client
{
	char name[20];
	int fds;
} Cn[100];

/*定义服务器 IP 与 Port接口*/
char *IP = "192.168.195.128";
short Port = 8888;

/*当前用户数量总和*/
int C_size = 0;
/*定义sockfd为全局变量，方便后期使用*/
int sockfd;

/*服务器初始化*/
void tcp_init(char *ip, int port)
{
  printf("正在初始化服务器......\n");
  
	// 1.创建套接字
	//              地址族   套接字的类型
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("socket");
		exit(-1);
	}
	printf("socket success.......\n");
	
	// 2.绑定地址和端口
	//  端口重用
	int opt = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	struct sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(port);
	myaddr.sin_addr.s_addr = inet_addr(ip);
	int bfd = bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr));
	if (bfd < 0)
	{
		perror("bind");
		exit(-1);
	}
	printf("bind success.....\n");

	// 3.设置监听套接字
	int ld = listen(sockfd, 10);
	if (ld < 0)
	{
		perror("listen");
		exit(-1);
	}
	printf("listen success......\n");
}


/*欢迎函数已完成*/
void send_HY_client(char *msg)
{
	int i = 0;
	for (; i < C_size; i++)
	{
    printf("send to %d\n",Cn[i].fds);
		send(Cn[i].fds, msg, strlen(msg), 0);
	}
}

/*发送信息函数*/
void send_msg_client(char *msg,int cfd)
{
	int i;
	char name_buf[100] = {0};
	time_t t = time(0);
	char time_buf[32] = {0};
	strftime(time_buf,sizeof(time_buf),"%Y-%m-%d %H:%M:%S : ",localtime(&t));
	//char ans_buf[100] = {0};
	for(i = 0; i < C_size; i++)
	{
            if(Cn[i].fds == cfd)
            {
                //strcpy(name_buf,Cn[i].name);
                sprintf(name_buf, "【%s 】", Cn[i].name);
                break;
            }
	}
	strcat(name_buf,time_buf);
	printf("%s",name_buf);
	
	for( i = 0; i < C_size; i++)
	{
            //printf("发送者cfd = %d: \n",cfd);
            printf("发送者是：%s\n",name_buf);
            /*if(Cn[i].fds == cfd)
            {
                continue;
            }
            */
	    printf("发送到fds为: %d\n",Cn[i].fds);
	    send(Cn[i].fds,name_buf,strlen(name_buf),0);
	    send(Cn[i].fds,msg,strlen(msg),0);
	}
}

/*创建Client线程*/
void *Client_pthread(void *arg)
{
	int connfd = *((int *)arg);

	Cn[C_size].fds = connfd; //记录Client的标记
	char name_buf[64] = {0};
	int ret = recv(connfd, name_buf, sizeof(name_buf), 0);
	if (ret <= 0)
	{
		printf("读取Client名称失败\n");
		exit(-1);
	}
	strcpy(Cn[C_size].name, name_buf);
	C_size++; //在线用户数量加一

	char HY[100] = {0}; //欢迎提示数组
	sprintf(HY, "欢迎 %s 进入聊天室......", name_buf);
	//群发欢迎消息
	send_HY_client(HY);

	while (1)
	{
		/*buf存储接收到Client的信息*/
		char buf[100] = {0};
		int c_fd = recv(connfd, buf, sizeof(buf), 0);
		if (c_fd == 0)
		{
      printf("Client connfd = %d Quit\n",connfd);
			char q_name[20] = {0};
			int i = 0;
			for (i = 0; i < C_size; i++)
			{
				if (Cn[i].fds == connfd)
				{
					strcpy(q_name, Cn[i].name);
					/*拷贝一份名字，用最后一个用户替换掉当前用户*/
					Cn[i].fds = Cn[C_size - 1].fds;
					strcpy(Cn[i].name, Cn[C_size - 1].name);
				}
			}
			C_size--;
			/*这句为服务器调试使用*/
			printf("标识为：%d 的用户退出在线聊天\n", connfd);
			char q_msg[100] = {0};
			sprintf(q_msg, "欢送 %s 离开聊天室……", q_name);
			/*群发退出消息*/
			send_HY_client(q_msg);
			close(connfd);
			/*Client 退出 群聊，结束服务线程*/
			return 0;
		}
		/*群发接收Clien成功消息*/
		send_msg_client(buf,connfd);
	}
}


/*等待客户机连接，启动服务器服务*/
void wait_client()
{
	printf("server start now ......\n");
	while (1)
	{
		struct sockaddr_in fromaddr;
		socklen_t len = sizeof(fromaddr);
		int fd = accept(sockfd, (struct sockaddr *)&fromaddr, &len);
		if (fd == -1)
		{
			printf("Client connect error......\n");
			continue; //继续循环，处理连接
		}
		//如果客户端成功连接上
		printf("Client Success And fd = %d\n", fd); //测试
		pthread_t pid;//启动线程
		pthread_create(&pid, 0, Client_pthread, &fd);
	}
}

/*关闭服务器的socket*/
void sig_close()
{
	close(sockfd);
	printf("server end ...... \n");
	exit(0);
}

int main()
{
	/*信号初始化，退出使用退出CTRL+C*/
	signal(SIGINT, sig_close);

	/*服务器初始化*/
	tcp_init(IP,Port);

	/*等待客户机连接*/
	wait_client();

	return 0;
}












