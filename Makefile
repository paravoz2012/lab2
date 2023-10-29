gen_key:
	gcc gen_key.c -o gen_key -lakrypt-base -lakrypt -Wl,-R/usr/local/lib

process:
	gcc process.c -o process -lakrypt-base -lakrypt -Wl,-R/usr/local/lib

clean:
	rm -rf process gen_key

all: gen_key process
