FROM gcc:latest

WORKDIR /workspace

RUN apt-get update && apt-get install -y \
	build-essential \
	cmake \
	gdb \
	valgrind \
	lldb \
	clang-format \
	clang-tidy \
	cppcheck \
	doxygen \
	graphviz \
	git \
	&& rm -rf /var/lib/apt/lists/*
