
g++ -g -I ./include/ -c ./src/test.cpp -o obj/test.o -std=c++11

g++ -g -I ./include/ -c ./src/Dir.cpp -o obj/Dir.o -std=c++11

g++ -g -I ./include/ -c ./src/untils.cpp -o obj/untils.o -std=c++11

g++ -g -I ./include/ -c ./src/cfg.cpp -o obj/cfg.o -std=c++11

g++ -g -I ./include obj/cfg.o obj/untils.o obj/test.o obj/Dir.o src/main.cpp -o bigdata_sort -std=c++11

