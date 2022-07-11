all:
	$(CC) -g -Wall src/bitmap.c src/linux_fb.c src/gsnap.c src/shmem.h -lm -o bin/gsnap
	$(CC) -g -Wall src/bitmap.c src/linux_fb.c src/fbshow.c src/shmem.h -lm -o bin/fbshow
	$(CC) -g -Wall src/bitmap.c src/linux_fb.c src/fbdraw.c src/shmem.h -lm -o bin/fbdraw

clean:
	rm -f bin/*
