main: main.o
	g++  main.cpp -o main

main.o: 
	g++ -c main.cpp 

run: main
	./main

clean:
	rm main
	rm -f *.o
	rm hueFile1.raw
	rm hueFile2.raw
	rm intensityFile1.raw
	rm intensityFile2.raw
	rm saturationFile1.raw
	rm saturationFile2.raw

