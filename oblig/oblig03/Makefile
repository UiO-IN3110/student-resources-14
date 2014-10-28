CC = gcc
CFLAGS = -O2
LDFLAGS = -Lsimple-jpeg/ -lsimplejpeg

PROJ = denoise
OBJS = denoise.o

all : simple-jpeg $(PROJ)

denoise : $(OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

simple-jpeg :
	$(MAKE) -C simple-jpeg

obj-clean:
	$(RM) *.o

exec-clean:
	$(RM) $(PROJ)

autosave-clean:
	$(RM) *~

clean:
	$(MAKE) obj-clean
	$(MAKE) exec-clean
	$(MAKE) autosave-clean
