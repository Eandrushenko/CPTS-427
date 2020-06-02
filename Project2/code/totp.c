#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/bn.h>
#include <openssl/hmac.h>
#include <stdint.h>
#include <byteswap.h>

#define RUN  0
#define TEST  1

/////////////////////
// This code based off TOTP RFC 6238 implementation
// https://tools.ietf.org/html/rfc6238
/////////////////////


int64_t compute_totp(int64_t *time, char *seed){
	unsigned char hash[64];
	int hashLen = 0;
	int64_t bytetime = bswap_64(time);
	// compute the MAC
	HMAC(EVP_sha512(), seed, strlen(seed), (char *)&bytetime, 8, hash, &hashLen);

	// compute the offset - 
	int offset = hash[hashLen - 1] & 0xf;
	
	int binary = (((hash[offset] & 0x7f) << 24) | ((hash[offset + 1] & 0xff) << 16) | ((hash[offset + 2] & 0xff) << 8) | (hash[offset + 3] & 0xff));

	// perfrom modulus
	binary = binary % 100000000;

	return binary; 
}

int32_t main (int argc, char *argv[])
{
	int8_t argsok = 0; 
	int8_t mode=0;
	int64_t t_int = 0;
	unsigned char seed[] = "\x31\x32\x33\x34\x35\x36\x37\x38\x39\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x30\x31\x32\x33\x34";

	if (argc > 1){
		if(strncmp(argv[1], "run", 3)==0){
			mode = RUN; 
			argsok=1;
		}
		else if (strncmp(argv[1], "test", 4)==0){
			argsok=1;
			mode = TEST; 
		}
	}
	if(!argsok){
		perror("'./totp test' or './totp run'\n");
		exit(1);
	}
	if (mode == RUN){

		//compute time segment based on current time/period
		time(&t_int);
		t_int /= 30;
		printf("Time: %016llx, OTP: %d\n", t_int, compute_totp(t_int, seed));
	}
	else{
		t_int = 0x0000000000000001;
		printf("Time: 0000000%llx, OTP: %d\n", t_int, compute_totp(t_int, seed));
		t_int = 0x00000000023523EC; 
		printf("Time: 0%llx, OTP: %d\n", t_int, compute_totp(t_int, seed));
		t_int = 0x00000000023523ED;
		printf("Time: 0%llx, OTP: %d\n", t_int, compute_totp(t_int, seed));
		t_int = 0x000000000273EF07;
		printf("Time: 0%llx, OTP: %d\n", t_int, compute_totp(t_int, seed));
		t_int = 0x0000000003F940AA;
		printf("Time: 0%llx, OTP: %d\n", t_int, compute_totp(t_int, seed));
		t_int = 0x0000000027BC86AA;
		printf("Time: %llx, OTP: %d\n", t_int, compute_totp(t_int, seed));
	}

	return 0;
}

