CXXFLAGS     = -O2 -g -I.
LDFLAGS      = -L. -lRequests -lcurl -lboost_system -lboost_thread
LIB_REQUESTS = libRequests.a

SRCS=Headers.cpp \
     Request.cpp \
     Response.cpp

OBJS=$(SRCS:.cpp=.o)

all: $(LIB_REQUESTS)
	$(CXX) $(CXXFLAGS) -o headersTest HeadersTest.cpp  $(LDFLAGS)
	$(CXX) $(CXXFLAGS) -o requestTest RequestTest.cpp  $(LDFLAGS)
	$(CXX) $(CXXFLAGS) -o loadTest    LoadTest.cpp     $(LDFLAGS)
	$(MAKE) -C examples all

$(LIB_REQUESTS): $(OBJS)
	$(AR) rcs $@ $^

test: all
	@for test in *Test; do \
		./$$test; \
		if [ $$? != 0 ]; then \
			break; \
		fi; \
	done

clean:
	rm -f core *.o *Test $(LIB_REQUESTS)
	$(MAKE) -C examples clean
