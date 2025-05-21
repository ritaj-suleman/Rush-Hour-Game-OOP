#include "sound.h"
#include <cstdlib>
using std:: string;


#define PLAY_SOUND_CMD "aplay -q "

void playSound(const string& filename) {
    string command = PLAY_SOUND_CMD + filename;
    system(command.c_str());
}
