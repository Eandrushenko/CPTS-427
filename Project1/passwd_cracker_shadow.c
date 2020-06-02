#include <crypt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define SHDW_LINE_LEN 256
#define WORD_LEN 80

void removenewline(char *str)
{
	if (str == NULL)
	{
		return;
	}
	int length = strlen(str);
	if (str[length-1] == '\n');
	{
		str[length-1] = '/0';
	}
}

int main(){

	char *user[5];
	char *salt[5];
	char *hash[5];

	FILE *shadow;
	FILE *dict;

	shadow = fopen("/etc/shadow", "r");
	if(shadow == NULL){
		fprintf(stderr, "Cannot open shadow file \n");
		exit(1);
	}

	dict   = fopen("/etc/dictionaries-common/words", "r");
	if(dict == NULL){
		fprintf(stderr, "Cannot open dict file\n");
		exit(1);
	}

	char shdw_line[SHDW_LINE_LEN];
	int num_accounts = 0;
	while(fgets(shdw_line, SHDW_LINE_LEN, shadow)!=NULL){
		char *token = strtok(shdw_line, ":");
		printf("ID: %s\n", token);
		user[num_accounts] = token;
		char *shdw_hash = strtok(NULL, ":");
		if(strcmp(shdw_hash, "*")!=0 && strcmp(shdw_hash, "!")!=0){
			token = strtok(shdw_hash, "$");
			token = strtok(NULL, "$");
			salt[num_accounts] = token;
			printf("  salt: %s\n", token);
			token = strtok(NULL, "$");
			hash[num_accounts] = token;
			printf("  hash: %s\n", token);
			printf("num_accounts = %d\n", num_accounts);
			num_accounts++;
			//////////////////////
			// Part A: 
			//  These values need to 
			//  be stored in an array
			//////////////////////
			
		}
	}
	printf("%s - %s - %s\n", user[0], salt[0], hash[0]);
	printf("%s - %s - %s\n", user[1], salt[1], hash[1]);
	printf("%s - %s - %s\n", user[2], salt[2], hash[2]);
	printf("%s - %s - %s\n", user[3], salt[3], hash[3]);
	printf("%s - %s - %s\n", user[4], salt[4], hash[4]);
	char *hashy;
	char word[WORD_LEN];
	while(fgets(word, WORD_LEN, dict)!=NULL){
		for(int i=0; i<num_accounts; i++){
			//////////////////////
			// Part B: 
			//  For each account, compute
			//  the hash for that dictionary
			//  word and the users known salt
			//  as shown below:
			//     hash = crypt("password", "$6$_____");
			//  then check if the password is 
			//  the same as that users entry 
			//  from  /etc/shadow, if so
			//  you've successfully cracked it,
			//  print the password and userid
			//////////////////////
			removenewline(word);
			hashy = crypt(word, salt[4]);
			//printf("hashy = %s\n", hashy);
			if (!(strcmp(hashy, hash[4])))
			{
				printf("word = %s \n", word);
			}
		}
	}
	printf("hashy = %s\n", hashy);
	printf("true hash = %s\n", hash[4]);
}

