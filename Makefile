CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lcurl

SRCS = newset.c container.c hashmap.c fetchurls.c libcurl.c dirpage.c webcrawler.c

HDRS = newset.h container.h hashmap.h fetchurls.h libcurl.h dirpage.h

OBJS = $(SRCS:.c=.o)

TARGET = webcrawler

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
