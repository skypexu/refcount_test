all: refcount_perf
refcount_perf: main.cc refcountedobj.cpp
	$(CXX) -o $@ $^
