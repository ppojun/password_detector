
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define BUF_SIZE 30
#define MAX_CLIENT 10

char online_client[BUF_SIZE];
int origin_password[BUF_SIZE];
int password_length = 0;
char finded_pw[BUF_SIZE];
int choosen_number=0;
int checking_length=0;
char result_pw[BUF_SIZE];
int clnt_name[0];

	int sock;
	char message0[BUF_SIZE];
	char message[BUF_SIZE];
	char message2[BUF_SIZE];
	int str_len;
	char new_password[BUF_SIZE];
	int online_length=0;
	int i,j;
	int asci;
	int checking;
	int isTrue[BUF_SIZE];
	int asci_in[BUF_SIZE];
	int len_num[BUF_SIZE];
	int clnt_n;
	double pst=0;

	clock_t start, end;

void error_handling(char *message);
void cal();



int main(int argc, char *argv[])
{

	len_num[0]=0;


	struct sockaddr_in serv_adr;

	if(argc!=3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	//소켓을 생성
	sock=socket(PF_INET, SOCK_STREAM, 0);   
	if(sock==-1)
		error_handling("socket() error");
	//연결할 서버의 주소를 설정
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));
	//서비스 요청과 처리
	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("connect() error!");
	else
		puts("Connected...........");
	


	
	while(1) 
	{	
			printf("Do you want find your password?\n");
			fputs("\tpress y/Y to find password\n",stdout);
			fputs("\tpress q/Q to out system\n", stdout);
			scanf("%s",message2);
			//write(sock, message2, BUF_SIZE);
			if(!strcmp(message2,"y") || !strcmp(message2,"Y"))
			{
				online_length=read(sock, online_client, BUF_SIZE); // 유저수
				clnt_n=read(sock, clnt_name, BUF_SIZE);//이 클라이언트 이름
				printf("\nEntire User : %d\n", online_client[0]);
				printf("this client is %d\n", clnt_name[0]);
				printf("\n");
				printf("Receiving passwords length to be checked by this client..\n");
				password_length=read(sock, origin_password, BUF_SIZE);// 자릿수
				printf("%d numbers of password will be checking by this client\n\n",origin_password[0]);
				checking_length = origin_password[0];
				
				//checking
				
				start = clock();
			
				printf("\nAlgorithm begins...\n\n\n");
				
				if (password_length == 0)
				{
					printf("there are no password\n");
				}
				else
				{	
					if(online_client[0]==1)
					{
						cal();
					}
					else
					{
						cal();
					}
				}
			}
			if(!strcmp(message2,"q") || !strcmp(message2,"Q"))
			{	
				printf("quit\n");
				asci_in[0]=-1;
				write(sock, asci_in, BUF_SIZE);
				break;
			}

	}
	close(sock);
	return 0;
}

void cal()
{
	int temp;
	if(online_client[0]==1)
		temp=0;
	else
		temp=(online_client[0]-1)*checking_length;

		for(i=temp;i<online_client[0]*checking_length;i++)
		{	
			len_num[0]=i; //자릿수
			checking=-1;

			for(j=0;j<=9;j++)
			{
				asci_in[0]=j;	

				write(sock, len_num, BUF_SIZE);
				write(sock, asci_in, BUF_SIZE);

				printf(">>> %d 자리, %d 시도\n",len_num[0],asci_in[0]);

				checking = read(sock, isTrue, BUF_SIZE);

				if(isTrue[0] == 1)
				{
					printf(">>> Hit !\n");
					result_pw[i]=asci_in[0];
					printf("\n★ ★ ★  %d 자리 %d ★ ★ ★\n\n",len_num[0],asci_in[0]);
					break;
				}
				else
				{
					printf(">>> False....\n");
					continue;
				}
			}
			printf("\n");	
		}
		end = clock();
		pst = (double)(end-start)/CLOCKS_PER_SEC;
			printf("\n\n♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩\n\n");
			printf("    ／  ⌒ヽ				    ／⌒ヽ   \n");
			printf("　 ∩ ＾ω＾）　				　（＾ω＾∩  \n");
			printf("　 |　　 ⊂ﾉ	found your password	　 t⊃　　｜ \n");
			printf("　｜　　 _⊃				  ⊂_ 　　｜ \n");
			printf("　 し ⌒                                         ⌒ J \n");
			printf("♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩\n\n");
		printf("We'vd found password : ");
		for(j=temp;j<online_client[0]*checking_length;j++)
		{
			printf("%d ",result_pw[j]);
		}
		printf("\nWe used %f to find this password\n\n",pst);close(sock);
		temp=temp+checking_length;

}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
