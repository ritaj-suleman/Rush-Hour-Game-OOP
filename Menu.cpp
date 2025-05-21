#include "Menu.h"
#include "GameEngine.h"
#include "Game.h"
#include "Player.h"
#include "Car.h"
#include "Board.h"
#include "constants.h"
#include "util.h"

Menu::Menu() :
		currentSelection(0), 
		menuState(0), 
		isActive(true), 
		modeSelection(0),
		nameInputMode(false), 
		nameInput(""), 
		showRoleChange(false), 
		gameEngine(nullptr) {}

Menu::Menu(GameEngine *engine) :
		gameEngine(engine), 
		currentSelection(0), 
		menuState(0), 
		isActive(true), 
		modeSelection(0), 
		nameInputMode(false), 
		nameInput(""), 
		showRoleChange(false) {}

void Menu::draw() {
	if (!isActive && !showRoleChange)
		return;

	// background
	DrawRectangle(0, 0, GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE, MENU_BG_COLOR);

	// current menu
	if (showRoleChange) {
		drawRoleChangeMenu();
	} else if (nameInputMode) {
		drawNameInputScreen();
	} else {
		switch (menuState) {
		case 0:
			showStartMenu();
			break;
		case 1:
			showModeSelectionMenu();
			break;
		}
	}
}

void Menu::showStartMenu() {
	DrawString(GRID_SIZE * CELL_SIZE / 2 - 100, 100, "RUSH HOUR", MENU_TEXT_COLOR);

	string items[2] = { "1. Start Game", "2. View Leaderboard" };
	for (int i = 0; i < 2; i++) {
		DrawString(GRID_SIZE * CELL_SIZE / 2 - 50, 200 + i * 50, items[i], MENU_TEXT_COLOR);
	}
}

void Menu::showModeSelectionMenu() {
	DrawString(GRID_SIZE * CELL_SIZE / 2 - 100, 100, "SELECT GAME MODE", MENU_TEXT_COLOR);

	string items[3] = { "1. Taxi Driver", "2. Delivery Driver", "3. Random Selection" };
	for (int i = 0; i < 3; i++) {
		DrawString(GRID_SIZE * CELL_SIZE / 2 - 50, 200 + i * 50, items[i], MENU_TEXT_COLOR);
	}
}

void Menu::drawNameInputScreen() {
	DrawString(GRID_SIZE * CELL_SIZE / 2 - 100, 150, "ENTER YOUR NAME:", MENU_TEXT_COLOR);
	DrawString(GRID_SIZE * CELL_SIZE / 2 - 50, 200, nameInput.c_str(), MENU_TEXT_COLOR);
	DrawString(GRID_SIZE * CELL_SIZE / 2 - 120, 250, "Press ENTER when done", MENU_TEXT_COLOR);
}

void Menu::showRoleChangeMenu(bool show) {
	showRoleChange = show;
}
bool Menu::isShowingRoleChange() const {
	return showRoleChange;
}

void Menu::drawRoleChangeMenu() {
	if (!showRoleChange)
		return;

	// menu background
	DrawRectangle(100, 100, 400, 300, HUD_BG_COLOR);

	DrawString(150, 150, "SELECT YOUR NEW ROLE:", colors[BLACK]);
	DrawString(150, 200, "1. Taxi Driver", colors[BLACK]);
	DrawString(150, 250, "2. Delivery Driver", colors[BLACK]);
}

void Menu::handleInput(int key) {
	if (nameInputMode) {
		// did in KeyboardCallback (game.cpp)
		return;
	}

	switch (key) {
	case '1':
		currentSelection = 0;
		selectOption();
		break;

	case '2':
		currentSelection = 1;
		selectOption();
		break;

	case '3':
		if (menuState == 1) {
			currentSelection = 2;
			selectOption();
		}
		break;
	}
}

void Menu::selectOption() {
	switch (menuState) {
	case 0: 
		if (currentSelection == 0) { 
			menuState = 1; 
		} else { 
			gameEngine->getGame()->gameState = STATE_LEADERBOARD;
			isActive = true; // keep menu active
		}
		break;

	case 1:
		if (currentSelection == 2) { 
			modeSelection = rand() % 2;
		} else {
			modeSelection = currentSelection;
		}
		nameInputMode = true; // go for  name input
		break;
	}
}

void Menu::startGame() {
	if (!gameEngine || !gameEngine->getGame() || !gameEngine->getPlayer()) {
		cout << "ERROR: Game engine, game, or player not initialized!" << endl;
		return;
	}

	cout << "Starting game in mode: " << (modeSelection == MODE_TAXI ? "Taxi" : "Delivery") << " as " << nameInput << endl;

	gameEngine->getGame()->gameMode = modeSelection;

	if (gameEngine->getPlayer()) {
		gameEngine->getPlayer()->changeRole(modeSelection);
		gameEngine->getPlayer()->name = nameInput;
	}

	isActive = false;
	nameInputMode = false;

	if (gameEngine->getGame()) {
		gameEngine->getGame()->startGame();
	}

	if (gameEngine->getBoard()) {
		gameEngine->getBoard()->cleanup();
		gameEngine->getBoard()->generateBoard();
	}

	glutPostRedisplay();

}

