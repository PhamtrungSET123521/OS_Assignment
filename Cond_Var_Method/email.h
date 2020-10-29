#ifndef EMAIL_H_
#define EMAIL_H_
#define CONTENT_MAX 500

void gen_mess(char*mess, char*_name,uint64_t _id,int _toeic_mark, float _cpa,int _credit_pass, 
	uint64_t _tutor_fee); // function generate message to pass into function "email"
#endif