CC = g++
FLAGS = -std=c++11
obj_files = predictors.o SingleBitBimodal.o TwoBitBimodal.o gShare.o Tournament.o

all: predictors

predictors: $(obj_files)
	$(CC) $(FLAGS) $(obj_files) -o predictors

predictors.o: predictors.cpp predictors.h
	$(CC) $(FLAGS) -c predictors.cpp

SingleBitBimodal.o: SingleBitBimodal.cpp SingleBitBimodal.h predictors.o
	$(CC) $(FLAGS) -c SingleBitBimodal.cpp

TwoBitBimodal.o: TwoBitBimodal.cpp TwoBitBimodal.h predictors.o
	$(CC) $(FLAGS) -c TwoBitBimodal.cpp

gShare.o: gShare.cpp gShare.h predictors.o
	$(CC) $(FLAGS) -c gShare.cpp
Tournament.o: Tournament.cpp Tournament.h predictors.o
	$(CC) $(FLAGS) -c Tournament.cpp

clean:
	rm -rf predictors *.o *.gch

