CC = g++
TARGET = BattleShip
SOURCES = Main.cpp Game.cpp Player.cpp Map.cpp Ship.cpp Aircraft.cpp BattleShip.cpp Cruiser.cpp Destroyer.cpp
LDFLAGS = -lncurses

all:
	$(CC) -std=c++11 -o $(TARGET) $(SOURCES) $(LDFLAGS)
clean:
	rm -rf *.o $(TARGET)
