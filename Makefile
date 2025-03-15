build:
	@c++ main.cpp

run:
	@./a.out

clean:
	@rm -f ./a.out

build-and-run: build run
