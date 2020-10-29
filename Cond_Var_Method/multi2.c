/*
Date: 29/10/2020
Content: Synch Multithread using condition variable
Author: Pham Quoc Trung
Student ID: 20172875
*/	
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include "email.h"

#define MAX 30
#define MAX_LENGTH 300
#define MAIL "phamtrung123521@gmail.com"
// defined the student struct
struct student{
	char name[MAX];
	uint64_t id;
	int toeic_mark;
	float cpa;
	int credit_pass;
	uint64_t tutor_fee;
};

//declare global struct variable

struct student student1;

//declare mutex variable
pthread_mutex_t a_mutex;
pthread_mutexattr_t attr;

//declare cond variable
pthread_cond_t get_done = PTHREAD_COND_INITIALIZER;

//declare check variable, when update process successful, assign check = 1
int check = 0;
//Function Prototype
void*update(void*data); //Function for thread 1
void*send_email(void*data); // Function for thread 2


int main(){
	int i;
	pthread_t thread1;
	pthread_t thread2;

//Initialize the mutex variable
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	if(pthread_mutex_init(&a_mutex, &attr) != 0){
		perror("Mutex create error!\n");
		exit(EXIT_FAILURE);
	}
//Create thread 1 to update information
	if(pthread_create(&thread1, NULL, update, NULL) != 0){
		perror("Thread create error!\n");
		exit(EXIT_FAILURE);
	}
	sleep(1);

//Create thread 2 to send email
	if(pthread_create(&thread2, NULL, send_email, NULL) != 0){
		perror("Thread create error!\n");
		exit(EXIT_FAILURE);
	}
// Main thread waiting
	for(i=0; i<5; ++i){
		printf("Main thread waiting %d second...\n",i);
		sleep(1);
	}
// Wait sending email jod terminate
	if(pthread_join(thread2,NULL) != 0){
		perror("Send email wait error.\n");
		exit(EXIT_FAILURE);
	}
//Destroy mutex variable
	pthread_mutex_destroy(&a_mutex);
//Destroy cond variable
	pthread_cond_destroy(&get_done);
	printf("Complete The Process.\n");
	return 0;
}

//function for thread 1 to update information

void*update(void*data){
	printf("\n------------------------------\nUpdate Process Start\n");
	pthread_mutex_lock(&a_mutex);
	printf("Thread %u lock\n", pthread_self());
	printf("Student Name: %s\n",strcpy(student1.name, "Pham Quoc Trung"));
	printf("Student ID: %llu\n", student1.id = 20172875);
	printf("Student CPA: %f\n",student1.cpa = 3.32);
	printf("Student Toeic Mark: %d\n", student1.toeic_mark = 700);
	printf("Student All Credit Passed: %d\n", student1.credit_pass = 100);
	printf("Student Tutor Fee: %llu\n", student1.tutor_fee = 12000000);
	check ++;
	sleep(1);
	printf("Thread %u unlock\n", pthread_self());
	printf("Update Process Complete!\n------------------------------\n");
	pthread_mutex_unlock(&a_mutex);
	printf("Thread %u signal.\n", pthread_self());
	pthread_cond_signal(&get_done);
}	

//function for thread 2 to send email

void*send_email(void*data){
	pthread_mutex_lock(&a_mutex);
	printf("Sending Email\n");
	printf("Thread %u lock.\n", pthread_self());
	while(1){
		if(check == 1){
			char cmd[100];  			// to hold the command.
		    char body[300] = "Hi ";   	 // email body.
		    //Generate message
		    gen_mess(body, student1.name, student1.id, student1.toeic_mark, student1.cpa,
				student1.credit_pass, student1.tutor_fee);
		    pthread_mutex_unlock(&a_mutex);

		    //Send Email
		    char tempFile[100];     // name of tempfile.
		    strcpy(tempFile,tempnam("/tmp","sendmail")); // generate temp file name.
		    FILE *fp1 = fopen(tempFile,"w"); // open it for writing.
		    fprintf(fp1,"%s\n",body);		// write body to it.  	
		    fclose(fp1);       				// close file
		    sprintf(cmd,"sendmail %s < %s",MAIL,tempFile); // prepare command.
		    system(cmd);     				// execute it.
		    printf("Thread %u unlock.\n", pthread_self());
		 	printf("Email sent successfully\n");
			pthread_exit(NULL);
		}
		else{
			pthread_cond_wait(&get_done, &a_mutex);
		}
	}	
}
