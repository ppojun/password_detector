//2016118035 황규민
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/* Multicasting : process 기반 다중접속 서버 모델을 구현한다. 
Multicasting의 핵심은 connection이 하나 생성될 때마다 process를 생성하여, 해당 client에 대해 service를 제공하는 것이다.*/
#define BUF_SIZE 30
int new_password[BUF_SIZE]; //설정된 비밀번호 저장 배열
char origin_password[BUF_SIZE]; 
int input[BUF_SIZE];
char ans[BUF_SIZE];
int online_client;
int success=0;//맞춘 횟수 표시용
int password_length; // 비밀번호 길이를 표시
int user; // client 수를 표시
int count; //비밀번호 자릿수 표시
int cln_list[BUF_SIZE]; // 접속중인 클라이언트 pid 저장
int try_password[BUF_SIZE]; // client가 try한 정보
int try_index[BUF_SIZE]; //client가 보내온 password의 자릿수
int hint_length[BUF_SIZE]; // client에게 보내줄 비밀번호 길이 정보
int hint_user[BUF_SIZE]; // client에게 보내줄 유저수 정보
int result[BUF_SIZE]; //맞았는지 틀렸는지 보내줄 정보
char happy[BUF_SIZE]="HIT ! You conquer the Security";

void init(int array[]);
void split_password(int array[]); 
int check_password(int try_password,int try_index);
int clnt_name[BUF_SIZE];
int total_user;

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}

void read_childproc(int sig)
{
	pid_t pid;
	int status;
	pid=waitpid(-1,&status,WNOHANG); //sig_child 부분이다.

	//printf("removed proc id: %d \n", pid); //제거된 process id를 출력해주는 statement이다.
}

int main(int argc, char* argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	
	pid_t pid,pid1,pid2,pid3,pid4,pid5,pid6,pid7,pid8,pid9,pid10,pid11,pid12,pid13,pid14,pid15,pid16,pid17,pid18,pid19,pid20;
	struct sigaction act;
	socklen_t adr_sz;
	int str_len, state;
	int str_len1;
	int buf[BUF_SIZE];
	int i,j;

	if(argc!=2)
	{
		printf("Usage: %s<port>\n",argv[0]);
		exit(1);
	}
	
	// signal handler 구현 부분 //
	act.sa_handler = read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	state = sigaction(SIGCHLD, &act, 0); 
	// signal handler 구현 부분 //

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	
	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");
	
	printf("\n\n\n");
	printf("┌──────────────────────────────────────────────────────────────────┐\n");
	printf("|          n ,, n                                  n,,n            |\n");
	printf("│	　(,,・v・)	PassWord Detector	  (ﾟｰﾟ*)   	   │\n");
	printf("│	～(_ u,u ) 				　cuuc,,)~         │\n");
	printf("│								   │\n");
	printf("└──────────────────────────────────────────────────────────────────┘\n");
	printf("\n");//sleep(2);
	printf("──────────────────────────────────────────────────────────────────────────\n\n");
	printf("    This is PassWord Detector System !\n");//sleep(1);
	printf("    If you want to break the locking system, then you must use this program !\n");//sleep(1);
	printf("    And then You can easier conquer Security.\n");//sleep(1);
	printf("    This program gives sharing password dection through multicasting\n");//sleep(1);
	printf("    we can save to your spending half of time\n");//sleep(1);
	printf("    Have a relex and Find your Password !\n\n");//sleep(1);
	printf("──────────────────────────────────────────────────────────────────────────\n\n");

	fputs("Press y/Y to find password\n",stdout);
	fputs("Press q/Q to out system\n",stdout);
	scanf("%s",ans);
	printf("\n");
	//init(new_password);
	for(int i=0; i<BUF_SIZE;i++)
		new_password[i]=-1;

	if(!strcmp(ans,"y")|| !strcmp(ans,"Y"))
	{
		printf("Please enter your password length\n");
		scanf("%d",&password_length);
		printf("\n");
		printf("Length:%d\n",password_length);
		printf("\n");
		printf("Please Enter the password\n");
		for(i=0;i<password_length;i++)
		{
			printf("pw[%d] : ",i);
			scanf("%d",&new_password[i]);	
		}
		printf("Password is ★  ");
		for(i=0;i<password_length;i++){
			printf("%d",new_password[i]);
		}
		printf(" ★\n");
		printf("Input total user ");
		scanf("%d",&total_user);
	}
	else
	{
		printf("Terminated !\n");
		exit(1);
	}

	while(1) // client와 계속해서 통신할 수 있도록 while loop 구현.
	{

		adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
		

		if(clnt_sock == -1) 
			continue;
		else
		{	
			puts("new User Entered...");
			user++;
			printf("Current Users : %d\n",user);
			//printf("Client %d id is %d\n\n",user,clnt_sock);
		
			//printf("This Program is start at least 2 Users...\nWait a seconds....\n");
		}
			//write(clnt_sock, buf, str_len);
			//memcpy(new_password,buf,sizeof(int)*BUF_SIZE); //버퍼를 비밀번호 배열로 복사
			system("clear");
			printf("Waiting for Clients response... !\n\n");
			printf("New password is ★  ");
			for(i=0;i<password_length;i++)
			{
				printf("%d",new_password[i]);
			}
			printf(" ★\n");
					
			hint_length[0] = password_length/total_user;
			hint_user[0]= user;
			clnt_name[0]=clnt_sock;
			write(clnt_sock,hint_user,BUF_SIZE-1);
			write(clnt_sock,clnt_name,BUF_SIZE-1);
			printf("\n");

			//printf(">>>test user :%d\n",hint_user[0]);
			//write(clnt_sock,hint_user[1],sizeof(hint_user[1]));
			//write(clnt_sock,hint_length[0],sizeof(hint_user[0]));
			sleep(5);
			write(clnt_sock,hint_length,BUF_SIZE-1); // 비밀번호 길이
			//printf(">>>test length :%d\n",hint_length[0]);
			//client가 맞추려는 자릿수, 비밀번호

			printf("Now the Algorithm will be running !\n\n");
			init(result);
			for(i=0; i<hint_length[0];i++)
			{
				printf("   자리 시도\n");
				for(j=0; j<=9;i++)				
				{

					init(try_index);
					init(try_password);
	
					str_len = read(clnt_sock, try_index, BUF_SIZE);
					str_len1 = read(clnt_sock, try_password, BUF_SIZE);

					printf(">>> %d  %d \n", try_index[0],try_password[0]);
		
					result[0]=check_password(try_password[0],try_index[0]);
			
					write(clnt_sock,result,BUF_SIZE);
					if(success==hint_length[0])
						break;
				}
			}
			success=0;
			system("clear");
			printf("♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩\n\n");
			printf("    ／  ⌒ヽ				    ／⌒ヽ   \n");
			printf("　 ∩ ＾ω＾）　				　（＾ω＾∩  \n");
			printf("　 |　　 ⊂ﾉ	found your password	　 t⊃　　｜ \n");
			printf("　｜　　 _⊃				  ⊂_ 　　｜ \n");
			printf("　 し ⌒                                         ⌒ J \n");
			printf("♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩♩\n\n");
		
			printf("Wait for Clients selection....\n");
			str_len1 = read(clnt_sock, try_password, BUF_SIZE);
			if(try_password[0]==-1)
			{
				close(clnt_sock);
				puts("client disconnected...");
				return 0;
			}
			else
				printf("wait for client select...\n");
	}
	close(serv_sock);
	return 0;
}
void init(int array[])
{
	for(int i=0; i<=BUF_SIZE; i++)
		array[i]=-1;
}
int check_password(int try_password,int try_index)
{
	if(new_password[try_index]==try_password)
	{	
		success++;	
		return 1;	
	}
	else
		return 0;		
}

