#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "email.h"


void gen_mess(char*mess, char*_name,uint64_t _id,int _toeic_mark, float _cpa,int _credit_pass, 
    uint64_t _tutor_fee){
    char buffer[10];
    strcat(mess, _name);
    
    strcat(mess,"\nYour information was updated below:\n");
    strcat(mess, "Full name: ");
    strcat(mess, _name);
    
    strcat(mess, "\nYour CPA: ");
    sprintf(buffer,"%f",_cpa);
    strcat(mess,buffer);
    
    memset(buffer,0,sizeof(buffer));
    strcat(mess,"\nYour ID: ");
    sprintf(buffer, "%llu", _id);
    strcat(mess,buffer);

    memset(buffer,0,sizeof(buffer));
    strcat(mess,"\nYour Toeic Mark: ");
    sprintf(buffer, "%d", _toeic_mark);
    strcat(mess,buffer);

    memset(buffer,0,sizeof(buffer));
    strcat(mess,"\nYour Credit Pass: ");
    sprintf(buffer, "%d", _credit_pass);
    strcat(mess,buffer);

    memset(buffer,0,sizeof(buffer));
    strcat(mess,"\nYour Tutor Fee: ");
    sprintf(buffer, "%llu", _tutor_fee);
    strcat(mess,buffer);
}




