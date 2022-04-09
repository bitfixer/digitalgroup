dgtape: src/dgtape.cpp
	g++ -o bin/dgtape src/dgtape.cpp

dgrom: src/dgrom.cpp
	g++ -o bin/dgrom src/dgrom.cpp

dglength: src/dglength.cpp
	g++ -o bin/dglength src/dglength.cpp

wav: audio
	ffmpeg -f f32le -ar 44100 -ac 1 -i bin/dgprog.raw bin/dgprog.wav

audio: dgtape prog
	bin/dgtape bin/dgprog.bin bin/dgprog.raw

prog: dgtape dglength
	zasm/zasm -uwy --reqcolon src/dgprog.asm bin/dgprog_1.bin
	bin/dglength bin/dgprog_1.bin bin/dgprog.bin

clean:
	rm -rf bin/*