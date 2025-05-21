# Compiler Flags
CXXFLAGS = -g3 -Wall -fmessage-length=0 #-Werror

# Object files: Add all the .cpp files here
OBJS = util.o game.o Board.o Car.o DeliveryCar.o TaxiCar.o Game.o GameObject.o HUD.o \
       InputManager.o  Score.o Leaderboard.o Menu.o Building.o Road.o Player.o \
       FuelStation.o NPCCar.o Station.o Obstacle.o Package.o Passenger.o GameEngine.o \
       constants.o sound.o

# Libraries (linked with the program)
LIBS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib \
       -lglut -lGLU -lGL -lX11 -lfreeimage -pthread

# Target executable
TARGET = game

# Link all object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

# Rule to create .o files from .cpp files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Default rule to build the target
all: $(TARGET)

# Clean rule to remove object files and the target executable
clean:
	rm -f $(OBJS) $(TARGET)


