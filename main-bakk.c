/*Version: auto run, data from file*/
#include <stdio.h>
#include <stdlib.h>
#include "fx-serial.h"
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include "common.h"
#include "header.pb-c.h"
#include "getdata.pb-c.h"
#include "control.pb-c.h"
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <sys/select.h>


#define BUFSIZE  1024
#define MAXSLEEP 128
struct fx_serial *ss;
time_t the_time;
FILE   *fp;
int		fd;
fd_set wset,rset;
float avge = 0; //count light's average

//room controller id 
//int Ctrl_TrainRoom1[] = {56,57,58,59,60,61,62,63,80};
//int Ctrl_TrainRoom2[] = {64,65,66,67,68,69,70,71,81};
//int Ctrl_TrainRoom3[] = {72,73,74,75,76,77,78,79,82};
//int Sterilization_Ctrl[]= {50,51,52,53,54,55};

//room sensor id
int Sensor_TrainRoom1[] = {1,2,3,4,5,6,7,8,9,10};
int Sensor_TrainRoom2[] = {11,12,13,14};
int Sensor_TrainRoom3[] = {15,16,17,18};
int Sensor_light_Room1[] = {19,20,21,22};

float room_info[10]; //save the room info

struct MsgSend
{
	Header mh;
	SensorInfo   si;
	SensorT	     st;
};

struct MsgSend MS;

//struct RMsg
//{
//	char *flag;
//	int	 len;
//	void *buf;
//};
//struct RMsg RM;

//struct IMsg 
//{
//	char *flag;
//	int len;
//	void *buf;
//}

//struct IMsg IM;


//char buf[BUFSIZE];
int  si_length;
int  st_length;
int  mh_length;

void *buf_mh;
void *buf_st;
void *buf_si;

float T1_trans(int id)
{	
	int data;
	float ret;

	sensor_get(ss,id,&data);
	ret = (float)data * 120/1000;

	return ret;

}

float H_trans(int id)
{
	int data;
	float ret;

	sensor_get(ss,id,&data);
	ret = (float)data / 10;

	return ret;
}

float Co2_trans(int id)
{
	int data;
	float ret;

	sensor_get(ss, id,&data);
	ret = (float)data * 10;

    return ret;
}

float L_trans(int id)
{
	int data;
	float ret;

	sensor_get(ss,id,&data);
	ret = (float)data * 10;

	return ret;
}

float T2_trans(int id)
{
	int data;
	float ret;

	sensor_get(ss,id,&data);
	ret = ((float)data - 30000/110)*110 / 1000;

	return ret;
}

void Calc_data(int room[],int len)
{
	int i;
	float data;

	for(i = 0; i< len; i++)
	 {
		switch(room[i])
		{
			case 1:
				data = T1_trans(room[i]);
				break;
			case 8:
			case 12:
			case 16:
				data = H_trans(room[i]);
				break;
			case 9:
			case 10:
			case 13:
			case 14:
			case 17:
			case 18:
				data = Co2_trans(room[i]);
				break;
			case 19:
			case 20:
			case 21:
			case 22:
				data = L_trans(room[i]);
				break;
			default:
				data = T2_trans(room[i]);
				break;
		} 
		room_info[i] = data;
	}
}
void Write_into_file(float room[], int len)
{
	int i;

	for(i = 0; i< len; i++)
	{
		fprintf(fp,"%.2f\t",room[i]);
	}

	fputs("\n",fp);
}

void single_sensor(float temperature,int id)
{
	MS.st.roomid = 4;
	MS.st.temperature = temperature;
	//MS.st.temperature = 14;
	
	st_length = sensor_t__get_packed_size(&MS.st);
	buf_st = malloc(st_length);
	sensor_t__pack(&MS.st,buf_st);
	//fwrite(buf_st,st_length,1,stdout);
	//putchar('\n');
}

void sensordata_pack(float T, float H, float Co2)
{
	SensorInfo *Seni;
	MS.si.roomid = 1;
	MS.si.temperature = T;
	//MS.si.temperature = 19.0;
	MS.si.humidity = H;
	//MS.si.humidity = 80.1;
	MS.si.co2 = Co2;
	//MS.si.co2 = 4500.1;
	MS.si.has_light = 1;
	MS.si.light = avge;
	//MS.si.light = 1000.1;

	si_length = sensor_info__get_packed_size(&MS.si);
	buf_si = malloc(si_length);
	sensor_info__pack(&MS.si,buf_si);
	//printf("sensor_info:%s\n",(char *)buf_si);
	
	//Seni = sensor_info__unpack(NULL,si_length,buf_si);
	//if(Seni == NULL)
	//	exit(0);
	//printf("room:%f %f %f \n",Seni->co2,Seni->temperature,Seni->light);
	//sensor_info__free_unpacked(Seni,NULL);
	//printf("%d\n",strlen(buf_si));
	//fwrite(buf_si,si_length,1,stdout);
	//putchar('\n');
}

void split_array(int len)
{
	float T_average,Co2_average;
	T_average =(room_info[2]+room_info[3]+room_info[4]+room_info[5]+room_info[6])/5;
	Co2_average =(room_info[8] + room_info[9])/2;
	
	sensordata_pack(T_average,room_info[7],Co2_average);

}


void cleanup_array(int len,int id)
{
	float Co2_average;

	Co2_average = (room_info[len-1] + room_info[len-2]) /2;
	
	MS.si.roomid = id;
	MS.si.temperature = room_info[0];
	//MS.si.temperature = 100.0;
	MS.si.humidity = room_info[1];
	//MS.si.humidity = 100.0;
	MS.si.co2 = Co2_average;
	//MS.si.co2 = 3000.1;
	MS.si.has_light = 1;
	MS.si.light = 0;
	
	si_length = sensor_info__get_packed_size(&MS.si);
	buf_si = malloc(si_length);
	sensor_info__pack(&MS.si,buf_si);


}

void makeup_data(int id,int len)
{
	
	switch(id)
	{ 
		case 1:
			split_array(len); //use to split array and use different proto to send
			break;
		case 2:
		case 3:
			cleanup_array(len,id);
			break;
	}
}

void init_msgheader(int id)
{
	
	MS.mh.message_id = 1;
	MS.mh.message_flag = id;
 
    mh_length = header__get_packed_size(&MS.mh);
	buf_mh = malloc(mh_length);
	//printf("%d\n",id);
	header__pack(&MS.mh,buf_mh);
	//printf("%d,%d\n",sizeof(buf_mh),strlen(buf_mh));
	//Header *hd;
	//hd = header__unpack(NULL,sizeof(buf_mh),buf_mh);
	//printf("id:%d flag:%d\n",hd->message_id,hd->message_flag);
	//fwrite(buf_mh,mh_length,1,stdout);
}


int safewrite(int fd, char *buf,size_t n)
{
	size_t nleft;
	size_t nwritten;;
	char *ptr;

	ptr = buf;
	nleft = n;
	while(nleft > 0)
	{
		if((nwritten = write(fd, ptr,nleft)) <= 0)
		{
			if(nwritten < 0 && errno == EINTR)
				nwritten = 0;
			else
				return(-1);
		}
		nleft -= nwritten;
		ptr += nwritten;
	} 
	return (n);
	
}

int socket_set_keepalive(int fd)
{
	int ret, error,idle,cnt,intv;
	
	/*30s without any data, send heartbeat package*/
	idle = 30;
	if(setsockopt(fd,SOL_TCP,TCP_KEEPIDLE,&idle,sizeof(idle)) != 0)
	{
		fprintf(stderr,"set keepalive idle error\n");
		return -1;
	}

	/*without any respond, 3m later resend package*/
	intv = 180;
	if(setsockopt(fd,SOL_TCP,TCP_KEEPINTVL,&idle,sizeof(intv)) != 0)
	{
		fprintf(stderr,"set keepalive intv error\n");
		return -1;
	}

	/*send 5 times, without any response, mean connect lose*/
	cnt = 5;
	if(setsockopt(fd,SOL_TCP,TCP_KEEPCNT,&cnt,sizeof(cnt)) != 0)
	{
		fprintf(stderr,"set keepalive cnt error\n");
		return -1;
	}

}

/*for test*/
void unpackmsg(char *buf)
{
	char header[100];
	char info[100];
	char flags[100];
	int  hlen,ilen;
	Header *hd;
	SensorInfo *Seni;

	printf("buf:%s\n",buf);
	sscanf(buf,"%s%2d%s%s",flags,&hlen,header,info);
	if(strcmp(flags,"MUSHROOM")== 0 )
		printf("flag correct\n");
	printf("info len: %d %d\n",hlen,strlen(info));
	printf("info:%s\n",info);
	printf("header size:%d %d\n",sizeof(buf_mh),mh_length);
	hd = header__unpack(NULL,strlen(buf_mh),buf_mh);
	if(hd == NULL)
	{ 
		printf("error header\n");
		exit(0);
	} 
	printf("header: %d %d\n",hd->message_id,hd->message_flag);
	header__free_unpacked(hd,NULL);
	if(hd->message_flag == 1)
	{ 
		printf("info len: %d %d\n",strlen(info), si_length);
		Seni = sensor_info__unpack(NULL,si_length,buf_si);
		if(Seni == NULL)
			exit(0);
		printf("room:%f %f %f \n",Seni->co2,Seni->temperature,Seni->light);
		sensor_info__free_unpacked(Seni,NULL);
	} 
	printf("=================\n");
}

void Send_data(int id)
{
	int len, ret,slen;
	void *buf,*index;

	init_msgheader(id);
	if(id == 1)
	{
		len = 8+2+mh_length+si_length;
        slen = 8+mh_length+si_length;
		buf = malloc(len);
		index = buf;
		sprintf(buf,"%d%s",slen,"MUSHROOM");
		index += strlen(buf); //move to the end
		memmove((void *)index,buf_mh,mh_length);
		index += mh_length;
		memmove((void *)index,buf_si,si_length);
        printf("%d\n",len);
		free(buf_si);
	}else if(id == 2)
	{
		len = 8+2 + mh_length +st_length;
        slen = 8+mh_length+st_length;
		buf = malloc(len+10);
		index = buf;
		sprintf(buf,"%d%s",slen,"MUSHROOM");
		index += strlen(buf); //move to the end
		memmove((void *)index,buf_mh,mh_length);
		//strcat(buf,buf_st);
		index += mh_length;
		memmove((void *)index,buf_st,st_length);
		//printf("buf length:%d %d\n",strlen(buf),st_length);
		free(buf_st);
	}    
	
	//fwrite(buf,strlen(buf),1,stdout);
	//putchar('\n');
	//printf("%d %d\n",strlen(buf),len);
	//if(FD_ISSET(fd,&wset))
	//{
		ret = safewrite(fd,buf,len);
		if(ret < 0)
		{
			printf("Send msg error,waiting for heartbeat test\n");	
		} 
//	}
	free(buf);
	free(buf_mh);

}


//void Send_data2(int id)
//{
//	int len,ret;
//	RM.flag	= malloc(9);
	//strcpy(RM.flag,"MUSHROOM");
	//init_msgheader(id);
	////char *flag = "MUSHROOM";
	//RM.buf1 = malloc(mh_length);
	//RM.buf1 = buf_mh; 
	//if(id == 1) //1 mean the sensor is full
	// {
	//	 RM.len = si_length;
	//	 RM.buf2 = malloc(si_length);
	//	 RM.buf2 = buf_si;
	//	 fwrite(RM.buf2,si_length,1,stdout);
	//	 putchar('\n');
	//	 free(buf_si);	 
	//}else if (id == 2 ) // mean the sensor is single
	//{          
	//	RM.len = st_length;
	//	RM.buf2 = malloc(st_length);
	//	strcpy(RM.buf2,buf_si);
	//	free(buf_st);
	// }  
	////len = sizeof(buf);
	////printf("buf Len:%d\n",strlen(buf));
	////buf[len+1] = '\0';
	////unpackmsg(buf);
	////free(buf_si);
	////printf("buf: %s\n",buf);
	////ret = safewrite(fd,buf,len);
	//ret = send(fd,&RM,sizeof(RM),0);
	////ret = send(fd,buf_mh,sizeof(buf_mh),0);
	//if(ret < 0)
	// {   
	//	fprintf(stderr,"Error: send buf error\n");
	//	exit(1);
	//}      
    //
	//free(RM.buf1);
	//free(RM.buf2);
	//free(buf_mh);
//}   
    //

void dumproom_info(int start, int end, int buf[])
{
	int i,j;
	j = start;
	for(i = 0; i<=(end -start);i++)
	{  
		room_info[i] = buf[j];
		j += 1;
	}
}



//This function is used to imitation
void rand_data(int id)
{
	FILE *fpp;
	int  i;
	char buf[1024];
	int realbuf[22];//string convert to intger
	char whitespace[] = " ";
	char *token;

	fpp = fopen("testdata.txt","a+");
	fgets(buf,1024,fpp);
	
	token=strtok(buf,whitespace);
	for(i = 0; i<22;i++)
	{ 
		if(token != NULL)
			realbuf[i] = atoi(token);
		token = strtok(NULL,whitespace);
	} 

	for(i =0;i <22;i++)
	  printf("%d  ",realbuf[i]);
	
	printf("\n");
	switch(id)
	{
		case 1:
			dumproom_info(4,13,realbuf);
			break;
		case 2:
			dumproom_info(14,17,realbuf);
			break;
		case 3:
			dumproom_info(18,21,realbuf);
			break;
		default:
			dumproom_info(0,3,realbuf);

	}
	fclose(fpp);
}


void Get_data(void)
{
	int  len;
	int i;

	(void)time(&the_time);
	
	fp = fopen("sensordata.txt","a+");
	if(fp == NULL)
	{
		fprintf(stderr,"Open file error\n");
		exit(1);
 	} 
	
	fputs(ctime(&the_time),fp);

	fputs("Room1 Light:\n",fp);
	len = sizeof(Sensor_light_Room1)/sizeof(Sensor_light_Room1[0]);
	//Calc_data(Sensor_light_Room1,len);
	rand_data(4);
	Write_into_file(room_info,len);
	for(i = 0; i < len; i++)
	{
		avge += room_info[i];
	}
	avge /= len;
	
	printf("room1 light %f\n",room_info[1]);
	fputs("Room1:\n",fp);
	len = sizeof(Sensor_TrainRoom1)/sizeof(Sensor_TrainRoom1[0]);
	//Calc_data(Sensor_TrainRoom1,len);
	rand_data(1);
	Write_into_file(room_info,len);
	makeup_data(1,len);	
	
	//send the first two single sensor room
	single_sensor(room_info[0],4); //room_id is 4
	Send_data(2);
	sleep(3);
	single_sensor(room_info[1],5); //room_id is 5
	Send_data(2);
	sleep(2);

	Send_data(1); //here used to send room1 data
	sleep(3);

	fputs("Room2:\n",fp);
	len = sizeof(Sensor_TrainRoom2)/sizeof(Sensor_TrainRoom2[0]);
	/* Calc_data(Sensor_TrainRoom2,len); */
	rand_data(2);
	Write_into_file(room_info,len);
	makeup_data(2,len);
	printf("here is\n");
	Send_data(1); //room 2 data
	//sleep(3);
	printf("that is\n");
	fputs("Room3:\n",fp);
	len = sizeof(Sensor_TrainRoom3)/sizeof(Sensor_TrainRoom3[0]);
	//Calc_data(Sensor_TrainRoom3,len);
	rand_data(3);
	Write_into_file(room_info,len);
	//makeup_data(3,len);
	//Send_data(1); //room 3 data
	//sleep(3);
	fputs("\n",fp);
	fclose(fp);
		
}


//void *Sensor_data(void *arg)
//{
//	while(1)
//	{
//		Get_data();
//		sleep(5); //sleep 5 mins
//	 } 
//}

/*get controll state*/
//void *Control_controller(void *arg)
//{
	//ControllerState *Cs;
	//char buffer[100];
	//int  ret,state;
    //
	//while(1)
	//{
//Rege//t:
	//	//if(FD_ISSET(fd,&rset))
	//	//{
	//		if((ret = read(fd,buffer,sizeof(buffer))) < 0)
	//		{
	//			fprintf(stderr,"cannot get the msg from server\n");
	//			continue;
	//		}
	//		//fwrite(buffer,sizeof(buffer),1,stdout);
	//		Cs = controller_state__unpack(NULL,ret,buffer);
	//		if(Cs->ctrl_id >= 55 && Cs->ctrl_id <= 82)
	//		{
	//			if(controller_set(ss,Cs->ctrl_id,Cs->ctrl_state) < 0)
	//			{
	//				printf("cannot open No.%d controller\n",Cs->ctrl_id);
	//				send(fd,"0",sizeof("0"),0);
	//			}else
	//			{
	//				controller_get(ss,Cs->ctrl_id,&state);
	//				printf("%d's status is %d\n",Cs->ctrl_id,state);
	//				send(fd,"1",sizeof("1"),0);
	//			} 
	//		}else
	//		{
	//			send(fd,"0",sizeof("0"),0);
	//			goto Reget;
	//		}
	//	controller_state__free_unpacked(Cs,NULL);
	//	sleep(2);
	//}
    //
//}   

int connect_retry(int sockfd, const struct sockaddr *addr,socklen_t alen)
{
	int nesc;

	for(nesc = 1; nesc <= MAXSLEEP; nesc <<= 1)
	{ 
		if(connect(sockfd, addr,alen) == 0)
			return(0);
		if(nesc <= MAXSLEEP/2)
			sleep(nesc);
	}


	return -1;
}

//void free_space(int signo)
//{
//	fx_serial_stop(ss);
//	close(fd);
//}

int main(int argc, const char *argv[])
{
#define OPEN 1
#define CLOSE 0
	pthread_t show_data,wait_controller;
	int err,ret,alive;

	FD_ZERO(&wset);
	FD_ZERO(&rset);
	FD_SET(fd,&wset);
	FD_SET(fd,&rset);
	
	//ss = fx_serial_start();TODO:here need to recover
	fd = client_init(7000,argv[1]);
	select(fd+1,&rset,&wset,NULL,NULL);
	
restart:
	/*set keepalive on fd*/
	alive = 1;
	if(setsockopt(fd,SOL_SOCKET,SO_KEEPALIVE,&alive,sizeof(alive)) != 0)
	{
		fprintf(stderr,"set socket option error\n");
		goto restart;
	}	

	socket_set_keepalive(fd);
	ret = connect_retry(fd,(struct sockaddr *)&clientaddr,sizeof(clientaddr));

	if(ret == -1)
	{
		printf("cannot connect to server\n");
	 	exit(1);
	}

	//signal(SIGINT,free_space);
	
	//err = pthread_create(&wait_controller,NULL,Control_controller,NULL);
	//if(err != 0)
	//{
	//	fprintf(stderr,"cannot create the thread\n");
	//	exit(1);
	//}

	while(1)
	{
		header__init(&MS.mh);
		sensor_info__init(&MS.si);
		sensor_t__init(&MS.st);
		/*TODO:here need to recover*/ 
		Get_data();
		sleep(293); //sleep 5 mins
	 } 
	//err = pthread_create(&show_data,NULL,Sensor_data,NULL);
	//if(err != 0)
	//	{
	//	fprintf(stderr,"cannot create the thread\n");
	//	exit(1);
	//}


	//pthread_join(show_data, NULL);
	//pthread_join(wait_controller, NULL);


	//while(1) getchar();
	return 0;
}
