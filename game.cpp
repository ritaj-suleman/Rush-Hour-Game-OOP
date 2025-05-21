#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "constants.h"
#include "Game.h"
#include "GameObject.h"
#include "HUD.h"
#include "InputManager.h"
#include "Score.h"
#include "Leaderboard.h"
#include "Menu.h"
#include "Building.h"
#include "Road.h"
#include "Player.h"
#include "FuelStation.h"
#include "NPCCar.h"
#include "Station.h"
#include "Obstacle.h"
#include "Package.h"
#include "Passenger.h"
#include "DeliveryCar.h"
#include "TaxiCar.h"
#include "Car.h"
#include "Board.h"
#include "GameEngine.h"

using namespace std;

void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

int xI = CELL_SIZE / 2, yI = CELL_SIZE / 2;

GameEngine *gameEngine = nullptr;

void DisplayCallback();
void TimerCallback(int value);
void KeyboardCallback(unsigned char key, int x, int y);
void KeyboardUpCallback(unsigned char key, int x, int y);
void SpecialKeysCallback(int key, int x, int y);
void SpecialUpCallback(int key, int x, int y);

void NonPrintableKeys(int key, int x, int y) {
	if (!gameEngine)
		return;

	if (gameEngine->getGame()->gameState == STATE_PLAYING) {
		if (gameEngine->getPlayer() && gameEngine->getPlayer()->car) {
			switch (key) {
			case GLUT_KEY_UP:
				gameEngine->getPlayer()->car->move(DIR_UP, gameEngine->getBoard());
				break;
			case GLUT_KEY_DOWN:
				gameEngine->getPlayer()->car->move(DIR_DOWN, gameEngine->getBoard());
				break;
			case GLUT_KEY_LEFT:
				gameEngine->getPlayer()->car->move(DIR_LEFT, gameEngine->getBoard());
				break;
			case GLUT_KEY_RIGHT:
				gameEngine->getPlayer()->car->move(DIR_RIGHT, gameEngine->getBoard());
				break;
			}
		}
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(GRID_SIZE * CELL_SIZE, TOTAL_HEIGHT);
	glutCreateWindow("Rush Hour Game");

	// Proper OpenGL setup
	glViewport(0, 0, GRID_SIZE * CELL_SIZE, TOTAL_HEIGHT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, GRID_SIZE * CELL_SIZE, TOTAL_HEIGHT, 0);
	glMatrixMode (GL_MODELVIEW);
	
	gameEngine = new GameEngine();
	gameEngine->getGame()->gameState = STATE_MENU;  
	gameEngine->getMenu()->isActive = true;         

	glutDisplayFunc(DisplayCallback);
	glutTimerFunc(16, TimerCallback, 0);
	glutSpecialFunc(NonPrintableKeys);

	glutKeyboardFunc(KeyboardCallback);
	glutKeyboardUpFunc(KeyboardUpCallback);

	glutMainLoop();
	return 0;
}

void DisplayCallback() {
	if (gameEngine) {
		gameEngine->render();
	}
}

void TimerCallback(int value) {
	if (gameEngine) {
		static int frameCount = 0;
		frameCount++;

		if (frameCount % 4 == 0 && gameEngine->getGame()->gameState == STATE_PLAYING) {
			int now = glutGet(GLUT_ELAPSED_TIME);
			gameEngine->getGame()->currentTime = (now - gameEngine->getGame()->startTime) / 1000;
			gameEngine->update();
			gameEngine->getGame()->checkTimeLimit();
		}

		glutPostRedisplay();
		glutTimerFunc(16, TimerCallback, 0); // approx 60 frames per second
	}
}

void KeyboardCallback(unsigned char key, int x, int y) {

	if (gameEngine) {
		if (gameEngine->getGame()->gameState == STATE_MENU && !gameEngine->getMenu()->nameInputMode) {
			switch (key) {
			case '1':
			case '2':
			case '3':
				gameEngine->getMenu()->handleInput(key);
				glutPostRedisplay();
				return;
			}
		}

		gameEngine->getInputManager()->handleKeyPress(key);

		Menu *menu = gameEngine->getMenu();

		if (menu && menu->nameInputMode) {
			if (key == 13) { // enter key
				if (!menu->nameInput.empty()) {
					menu->startGame();
				}
			} else if (key >= 32 && key <= 126) { // printable ASCII characters
				menu->nameInput += key;
			}
			glutPostRedisplay();
			return;
		}

		if (key == 27) {//escape key
			if (gameEngine->getGame()->gameState == STATE_PLAYING) {
				gameEngine->getGame()->pauseGame();
			} else if (gameEngine->getGame()->gameState == STATE_PAUSED) {
				gameEngine->getGame()->resumeGame();
			}
		}

		// space bar
		if (key == 32 && gameEngine->getGame()->gameState == STATE_PLAYING) {
			if (gameEngine->getPlayer() && gameEngine->getPlayer()->car) {
				if (gameEngine->getGame()->gameMode == MODE_TAXI) {
					TaxiCar *taxi = dynamic_cast<TaxiCar*>(gameEngine->getPlayer()->car);
					if (taxi) {
						if (!taxi->hasPassenger) {
							for (int i = 0; i < gameEngine->getBoard()->passengerCount; i++) {
								Passenger *p = gameEngine->getBoard()->passengers[i];
								if (p && p->isActive && taxi->checkCollision(p)) {
									if (taxi->pickupPassenger(p)) {
										p->isActive = false;
										cout << "Passenger picked up!" << endl;
										break;
									}
								}
							}
						} else {
							if (taxi->dropPassenger()) {
								cout << "Passenger dropped off!" << endl;
								// add a new passenger after a short delay
								glutTimerFunc(1000, [](int) {
									if (gameEngine) {
										gameEngine->getBoard()->addPassenger();
									}
								}, 0);
							}
						}
					}
				} else if (gameEngine->getGame()->gameMode == MODE_DELIVERY) {
					DeliveryCar *delivery = dynamic_cast<DeliveryCar*>(gameEngine->getPlayer()->car);
					if (delivery) {
						if (!delivery->hasPackage) {
							for (int i = 0; i < gameEngine->getBoard()->packageCount; i++) {
								Package *p = gameEngine->getBoard()->packages[i];
								if (p && p->isActive) {
									if (abs(p->x - delivery->x) <= 1 && abs(p->y - delivery->y) <= 1) {
										if (delivery->pickupPackage(p)) {
											p->isActive = false;
											cout << "package picked up!"
													<< endl;
											break;
										}
									}
								}
							}
						} else {
							if (delivery->deliverPackage()) {
								cout << "package dropped off!" << endl;
								// add a new package after a short delay
								glutTimerFunc(1000, [](int) {
									if (gameEngine) {
										gameEngine->getBoard()->addPackage();
									}
								}, 0);
							}
						}
					}
				}
			}
		}

		// p key for role switch
		if (key == 'p' || key == 'P') {
			if (gameEngine->getGame()->gameState == STATE_PLAYING) {
				Player *player = gameEngine->getPlayer();
				Station *station = gameEngine->getBoard()->roleChangeStation;

				if (station && station->isPlayerNear(player)) {
					gameEngine->getGame()->pauseGame();
					gameEngine->getMenu()->showRoleChangeMenu(true);
				}
			}
		}

		if (gameEngine->getMenu()->isShowingRoleChange()) {
			if (key == '1') {
				gameEngine->getPlayer()->changeRole(MODE_TAXI);
				gameEngine->getGame()->gameMode = MODE_TAXI;
				gameEngine->getBoard()->clearModeObjects();
				gameEngine->getMenu()->showRoleChangeMenu(false);
				gameEngine->getGame()->resumeGame();
			} else if (key == '2') {
				gameEngine->getPlayer()->changeRole(MODE_DELIVERY);
				gameEngine->getGame()->gameMode = MODE_DELIVERY;
				gameEngine->getBoard()->clearModeObjects();
				gameEngine->getMenu()->showRoleChangeMenu(false);
				gameEngine->getGame()->resumeGame();
			} else if (key == 27) { // ESC
				gameEngine->getMenu()->showRoleChangeMenu(false);
				gameEngine->getGame()->resumeGame();
			}
		}
	}
}

void KeyboardUpCallback(unsigned char key, int x, int y) {
	if (gameEngine) {
		gameEngine->getInputManager()->handleKeyRelease(key);
	}
}


#endif /* RushHour_CPP_ */

