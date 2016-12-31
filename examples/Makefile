CXXFLAGS     = -O2 -g -I..
LDFLAGS      = -L.. -lRequests -lcurl -lboost_system -lboost_thread

all:
	$(CXX) $(CXXFLAGS) -o requestExample  request.cpp $(LDFLAGS)
	$(CXX) $(CXXFLAGS) -o responseExample response.cpp $(LDFLAGS)
	$(CXX) $(CXXFLAGS) -o headersExample  headers.cpp $(LDFLAGS)

clean:
	rm -f core *.o *Example
