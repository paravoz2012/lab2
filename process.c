#include <sys/stat.h> 
#include <stdio.h>
 #include <libakrypt.h>

char* read_from_file(char *filename, size_t* size) {
	struct file sfp;
  	ak_uint8 *ptr = NULL;
  	int error = ak_error_ok;

  	if((error = ak_file_open_to_read( &sfp, filename)) != ak_error_ok) {
    		return NULL;
  	}

  	*size = (size_t)sfp.size;
	char* buf = (char *)malloc(*size);
	
  	if(buf == NULL) {
		ak_file_close(&sfp);
      		return NULL;
    	}

  	if(ak_file_read(&sfp, buf, *size) != sfp.size) {
  		ak_file_close(&sfp);
		free(buf);
		return NULL;
	}
  
	ak_file_close(&sfp);
 	return buf;
}

void write_to_file(char* filename, char* data, size_t size) {
	struct file fs;

	if(ak_file_create_to_write(&fs, filename) != ak_error_ok) {
    	}

    	if(ak_file_write(&fs, data, size) != size) {
    	
	}
}

int main(void) {
	int error = ak_error_ok;
	ak_pointer key;
	struct bckey *pkey;
	size_t size;
	ak_uint8 iv[8] = { 0x03, 0x07, 0xae, 0xf1 };

	// init lib
	if(ak_libakrypt_create( NULL ) != ak_true) {
    		ak_libakrypt_destroy();
    		return EXIT_FAILURE;
  	}


	// import key from file
    	if((pkey = key = ak_skey_load_from_file( "key.key")) == NULL) {
		goto end;
	}

	// read data from file
	char* data = read_from_file("data.txt", &size);
	if (data == NULL) {
		printf("cannot read file");
		goto end;
	}
    
	if(error = ak_bckey_ctr(pkey, data, data, size, iv, pkey->bsize) != ak_error_ok) {
		goto end; 
		printf("error");
	}
	
	write_to_file("data.txt", data, size);
	printf("success\n");

	end:
	free(data);
	ak_bckey_destroy(pkey);
	ak_libakrypt_destroy();
	if (error != ak_error_ok) {
		return EXIT_FAILURE;
	}

 	return EXIT_SUCCESS;
}

