/*===============================================================
 *   �ļ����ƣ�server.c
 *   �������ڣ�2022��12��3��
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

/*��������� IP �� Port�ӿ�*/
char *IP = "192.168.195.128";
short Port = 8888;

/*��ǰ�û������ܺ�*/
int C_size = 0;
/*����sockfdΪȫ�ֱ������������ʹ��*/
int sockfd;

/*��������ʼ��*/
void tcp_init(char *ip, int port)
{
  printf("���ڳ�ʼ��������......\n");
  
	// 1.�����׽���
	//              ��ַ��   �׽��ֵ�����
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("socket");
		exit(-1);
	}
	printf("socket success.......\n");
	
	// 2.�󶨵�ַ�Ͷ˿�
	//  �˿�����
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

	// 3.���ü����׽���
	int ld = listen(sockfd, 10);
	if (ld < 0)
	{
		perror("listen");
		exit(-1);
	}
	printf("listen success......\n");
}


/*��ӭ���������*/
void send_HY_client(char *msg)
{
	int i = 0;
	for (; i < C_size; i++)
	{
    printf("send to %d\n",Cn[i].fds);
		send(Cn[i].fds, msg, strlen(msg), 0);
	}
}

/*������Ϣ����*/
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
                sprintf(name_buf, "��%s ��", Cn[i].name);
                break;
            }
	}
	strcat(name_buf,time_buf);
	printf("%s",name_buf);
	
	for( i = 0; i < C_size; i++)
	{
            //printf("������cfd = %d: \n",cfd);
            printf("�������ǣ�%s\n",name_buf);
            /*if(Cn[i].fds == cfd)
            {
                continue;
            }
            */
	    printf("���͵�fdsΪ: %d\n",Cn[i].fds);
	    send(Cn[i].fds,name_buf,strlen(name_buf),0);
	    send(Cn[i].fds,msg,strlen(msg),0);
	}
}

/*����Client�߳�*/
void *Client_pthread(void *arg)
{
	int connfd = *((int *)arg);

	Cn[C_size].fds = connfd; //��¼Client�ı��
	char name_buf[64] = {0};
	int ret = recv(connfd, name_buf, sizeof(name_buf), 0);
	if (ret <= 0)
	{
		printf("��ȡClient����ʧ��\n");
		exit(-1);
	}
	strcpy(Cn[C_size].name, name_buf);
	C_size++; //�����û�������һ

	char HY[100] = {0}; //��ӭ��ʾ����
	sprintf(HY, "��ӭ %s ����������......", name_buf);
	//Ⱥ����ӭ��Ϣ
	send_HY_client(HY);

	while (1)
	{
		/*buf�洢���յ�Client����Ϣ*/
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
					/*����һ�����֣������һ���û��滻����ǰ�û�*/
					Cn[i].fds = Cn[C_size - 1].fds;
					strcpy(Cn[i].name, Cn[C_size - 1].name);
				}
			}
			C_size--;
			/*���Ϊ����������ʹ��*/
			printf("��ʶΪ��%d ���û��˳���������\n", connfd);
			char q_msg[100] = {0};
			sprintf(q_msg, "���� %s �뿪�����ҡ���", q_name);
			/*Ⱥ���˳���Ϣ*/
			send_HY_client(q_msg);
			close(connfd);
			/*Client �˳� Ⱥ�ģ����������߳�*/
			return 0;
		}
		/*Ⱥ������Clien�ɹ���Ϣ*/
		send_msg_client(buf,connfd);
	}
}


/*�ȴ��ͻ������ӣ���������������*/
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
			continue; //����ѭ������������
		}
		//����ͻ��˳ɹ�������
		printf("Client Success And fd = %d\n", fd); //����
		pthread_t pid;//�����߳�
		pthread_create(&pid, 0, Client_pthread, &fd);
	}
}

/*�رշ�������socket*/
void sig_close()
{
	close(sockfd);
	printf("server end ...... \n");
	exit(0);
}

int main()
{
	/*�źų�ʼ�����˳�ʹ���˳�CTRL+C*/
	signal(SIGINT, sig_close);

	/*��������ʼ��*/
	tcp_init(IP,Port);

	/*�ȴ��ͻ�������*/
	wait_client();

	return 0;
}












