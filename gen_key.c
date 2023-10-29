 #include <stdio.h>
 #include <libakrypt.h>

 int main( void )
{
	struct bckey key;
	ak_oid oid = NULL;
	char keylabel[64];
	char *password = NULL;
	size_t size;

	printf("Enter the password's length: ");
	scanf("%lu", &size);
	password = (char *)malloc(sizeof(char) * size);

	printf("Enter the password: ");
	scanf("%s", password);

  	if( ak_libakrypt_create( NULL ) != ak_true ) {
    		ak_libakrypt_destroy();
    		return EXIT_FAILURE;
  	}


	oid = ak_oid_find_by_name("kuznechik");
	ak_bckey_create_oid( &key, oid);
  	ak_bckey_set_key_from_password( &key, password, size, password, size );

	/* экпортируем ключ в файл (в der-кодировке) */
    	ak_snprintf(keylabel, sizeof( keylabel),
                                            "keylabel-%s-%03u", oid->name[0], key.key.number[0] );
    	ak_skey_set_label( (ak_skey)&key, keylabel, 0 );
    	if( ak_skey_export_to_file_with_password( &key,
                   password, size, "key.key", 0, asn1_der_format ) == ak_error_ok )
      	printf("key exported to %s file\n\n", "key.key");
   	
	/* удаляем ключ */
    	ak_bckey_destroy( &key );
	free(password);


 	return EXIT_SUCCESS;
}

