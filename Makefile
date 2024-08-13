RAYLIB_DEPS=-lraylib -lgdi32 -lwinmm
INC_PATHS=-I include -L lib -Wno-narrowing -Wno-write-strings
LFLAGS=$(RAYLIB_DEPS) -ljsoncpp

# ======= Executables ==========

bin/main: src/main.cpp lib/libwfc.a lib/libtiles.a
	g++ src/main.cpp -o bin/main $(INC_PATHS) -ltiles -lwfc $(LFLAGS) 


bin/tilemap_maker: src/tilemap_maker.cpp lib/libwfc.a lib/libtiles.a
	g++ src/tilemap_maker.cpp -o bin/tilemap_maker $(INC_PATHS) -ltiles -lwfc $(LFLAGS)


bin/combine_images: src/tilemap_maker.cpp lib/libtiles.a
	g++ src/combine_images.cpp -o bin/combine_images $(INC_PATHS) -ltiles $(LFLAGS)


bin/isometric_main: src/isometric_main.cpp lib/libtiles.a
	g++ src/isometric_main.cpp -o bin/isometric_main $(INC_PATHS) -ltiles $(LFLAGS)

# ======= Libraries ==========

lib/libwfc.a: obj/wfc.o obj/rule_parser.o
	ar rvs lib/libwfc.a obj/wfc.o obj/rule_parser.o


lib/libtiles.a: obj/tilemap.o obj/tileset.o obj/tileutils.o
	ar rvs lib/libtiles.a obj/tilemap.o obj/tileset.o obj/tileutils.o

# ======= Intermediates ==========

obj/tilemap.o: src/tilemap.cpp
	g++ -c src/tilemap.cpp -o obj/tilemap.o $(INC_PATHS)


obj/tileset.o: src/tilemap.cpp
	g++ -c src/tileset.cpp -o obj/tileset.o $(INC_PATHS)


obj/rule_parser.o: src/rule_parser.cpp
	g++ -c src/rule_parser.cpp -o obj/rule_parser.o $(INC_PATHS)


obj/wfc.o: src/wfc.cpp
	g++ -c src/wfc.cpp -o obj/wfc.o $(INC_PATHS)


obj/tileutils.o: src/tileutils.cpp
	g++ -c src/tileutils.cpp -o obj/tileutils.o $(INC_PATHS)

# obj/isotilemap.o: src/isotilemap.cpp
# 	g++ -c src/isotilemap.cpp -o obj/isotilemap.o $(INC_PATHS)


# ======= Other ==========

all: bin/main bin/tilemap_maker bin/combine_images bin/isometric_main


clean:
	del obj\\tileset.o
	del obj\\tilemap.o
	del obj\\wfc.o
	del obj\\rule_parser.o
	del obj\\tileutils.o

	del lib\\libwfc.a
	del lib\\libtiles.a
	del bin\\main.exe
	del bin\\tilemap_maker.exe
