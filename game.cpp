//============================================================================||
// Name        : Pedra Preciosa A Dança (Gem Jive)                            ||
// Author      : Hiyam Rehan and Imama Sarwar                                 ||
// Version     : 2024                                                         ||
// Copyright   : (c) Reserved                                                 ||
// Description : A Candy Crush inspired game made in C++ and OpenGL library.  ||
//============================================================================||

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cmath> // for basic math functions such as cos, sin, sqrt
#include <GL/glut.h>
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */

int gameBoard[9][9];

void Menu();
void ModeChoice();
void GameBoardInitialize();
void SetCanvasSize(int, int);
void DrawGameBoard();
int ScoreUpdate(int);
int*** HintLogic();
void HintLogic2();
void CheckMatches(int, int, int, int, int, int);
void SwapGems(int, int, int, int);
void DrawProgressBar(int, int);
void DecreaseProgressBar(int);
void Timer(int);
void TTDrawProgressBar(int, int, int, int);
void TTGameDisplay();
void GameDisplay();
void MouseClicked(int, int, int, int);
void TimeTrialMode();
void NormalMode();
void PrintableKeys(unsigned char, int, int);

// --- MAIN FUNCTION ---
int main(int argc, char*argv[]) {

	string PlayerName="Hiyam";
	cout << "Enter your name to proceed: ";
	cin >> PlayerName;

	int width = 570, height = 840;
	
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Gem Jive"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

        glutDisplayFunc(Menu);
	glutKeyboardFunc(PrintableKeys);

	glutMainLoop();
	return 1;
}

// --- DRAWS MENU AT START OF GAME ---
void Menu() {
	glClearColor(154.0/255, 206.0/255, 183.0/255, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	DrawRectangle(70,125,410,60,colors[TEAL]);

	DrawString(160, 750, " pedra preciosa A dança", colors[MISTY_ROSE]);
	DrawString(70, 650, " Welcome to a world of Gem-tastic fun", colors[MISTY_ROSE]);
        DrawString(45, 600, "Benvenuto in un mondo di divertimento fantastic", colors[TEAL]);
	DrawString(200, 150, "Press S to Start", colors[WHITE]);

	DrawTriangle(250, 405, 300, 405, 275, 455, colors[GOLD]);
        DrawSquare(220, 350, 40, colors[POWDER_BLUE]);
        DrawRoundRect(285, 350, 43, 43, colors[WHITE], 10);
	DrawString(200, 150, "Press S to Start", colors[WHITE]);

	glutSwapBuffers();
}

// --- FOR SELECTING OF GAME MODE --- // either Normal or Time Trial
void ModeChoice() {
	glClearColor(154.0/255, 206.0/255, 183.0/255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	DrawString(150, 770, "Press N for Normal Mode", colors[TEAL]);
	DrawString(150, 730, "Press T for Time-Trial Mode", colors[TEAL]);
	
	DrawString(170, 670, "HOW TO PLAY?", colors[BLACK]);
	DrawString(70, 630, "Slide adjacent gems to form chains.", colors[WHITE]);
	DrawString(70, 600, "No match? They'll snap back!", colors[WHITE]);	
	DrawString(70, 570, "Build chains to boost your score.", colors[WHITE]);
	DrawString(70, 540, "and fill up the progress bar. XD", colors[WHITE]);
	DrawString(70, 510, "Need a break? Press 'P' OR", colors[WHITE]);
	DrawString(70, 480, "Hit the Pause Button to freeze the action ;).", colors[WHITE]);
	DrawString(70, 450, "Race against the clock in Time Trial mode", colors[WHITE]);
	DrawString(70, 420, "AND Make those chains count!!", colors[WHITE]);	
	DrawString(70, 390, "Stuck? Press 'H' or click the hint button for a clue", colors[WHITE]);
	DrawString(70, 360, "but watch out—it'll cost you points!", colors[WHITE]);
	
	DrawTriangle(250, 220, 300, 220, 275, 275, colors[GOLD]);
        DrawSquare(220, 170, 42, colors[POWDER_BLUE]);
        DrawRoundRect(285, 170, 43, 43, colors[WHITE], 10);
	glutSwapBuffers();
}

// --- INITIALIZES THE GAMEBOARD WITH RANDOM VALUES ---
void GameBoardInitialize() {

	// To randomize gems
    int randNum;

	// 1 = Blue circle gem
	// 2 = Misty rose round rectangle gem
	// 3 = Sea green square gem
	// 4 = Red triangle gem
	// 5 = Yellow inverted triangle gem
	// 6 = Green round rectangle gem

	for (int i = 0; i < 9; i++) {
		int prevGem = -1; // Variable to store the previous generated gem
		int consecutiveCountHorizontal = 0; // Counts consecutive gems horizontally
                int consecutiveCountVertical = 0; // Counts consecutive gems vertically

		for (int j = 0; j < 9; j++) {			
            do {
                randNum = rand() % 6 + 1;
            } while ((randNum == prevGem && (consecutiveCountHorizontal >= 2 || consecutiveCountVertical >= 2)) || 
                     (i >= 2 && randNum == gameBoard[i - 1][j] && randNum == gameBoard[i - 2][j]) ||
                     (j >= 2 && randNum == gameBoard[i][j - 1] && randNum == gameBoard[i][j - 2]));    //ensures that 3 same type of gems don't appear consecutively
                     
            // Reset consecutive count if a different gem is generated
            // Reset consecutive counts if a different gem is generated
            if (randNum != prevGem) {
                consecutiveCountHorizontal = 0;
                consecutiveCountVertical = 0;
            } 

			else {
                // Update consecutive counts
                if (j >= 1 && randNum == gameBoard[i][j - 1]) {
                    consecutiveCountHorizontal++;
                } else {
                    consecutiveCountHorizontal = 0;
                }
                
                if (i >= 1 && randNum == gameBoard[i - 1][j]) {
                    consecutiveCountVertical++;
                } else {
                    consecutiveCountVertical = 0;
                }
            }

                        gameBoard[i][j] = randNum; // After conditions are checked, gameBoard[i][j] is assigned the random value
			prevGem = randNum;
		}
	}
}

// --- FOR CREATING WINDOW ---
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

// --- FOR DRAWING GAME BOARD ON SCREEN ACCORDING TO ARRAY ---
void DrawGameBoard() {
	// Values to generalize process
    int gemSize = 40;
    int spacing = 10;
    int startX = 80;
    int startY = 670;
    int x,y;
	
	for (int i = 0; i < 9; i++) {
		x = startX;
		y = startY - i * (gemSize + spacing); // y changes for each index of i

		for (int j = 0; j < 9; j++) {			
			switch (gameBoard[i][j]) {
			case 1: // 1 = Blue circle gem
				DrawCircle(x, y, gemSize / 2, colors[BLUE]);
				break;

			case 2: // 2 = Misty rose round rectangle gem
				DrawRoundRect(x - gemSize / 2, y - gemSize / 2, gemSize, gemSize, colors[MISTY_ROSE], gemSize / 4);
				break;

			case 3: // 3 = Sea green square gem
				DrawSquare(x - gemSize / 2, y - gemSize / 2, gemSize, colors[SEA_GREEN]);
				break;

			case 4: // 4 = Red triangle gem
				DrawTriangle(x - gemSize / 2, y - gemSize / 2, x + gemSize / 2, y - gemSize / 2, x, y + gemSize / 2, colors[RED]);
				break;

			case 5: // 5 = Yellow inverted triangle gem
				DrawTriangle(x - gemSize / 2, y + gemSize / 2, x + gemSize / 2, y + gemSize / 2, x, y - gemSize / 2, colors[YELLOW]);
				break;

			case 6: // 6 = Green round rectangle gem
				DrawRoundRect(x - gemSize / 2, y - gemSize / 2, gemSize, gemSize, colors[GREEN], gemSize / 3);
				break;
			}

			// Changes value of x every time gem is placed
			x += gemSize + spacing;
		}	
	}
}

// --- SCORING LOGIC ---
int ScoreUpdate(int hintflag = 0) {
    static int score = 0; // Score changes everytime this function is called

	/* Check if value is passed in hintflag, meaning
	function was called through HintLogic */
	if (hintflag != 0) { 
		if (score >= 20) {
			score -= 20; // Decrease score if hint is used
			return score;
		}
		else {	// If score is less than 20, do nothing
			return score;
		}
	}

	// Conditions for score updating 
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {

			// Initially checks for chain of 3 (vertical)
			if (gameBoard[i][j] ==  gameBoard[i+1][j] &&
				gameBoard[i+1][j] ==  gameBoard[i+2][j]) {
					
				// If chain of 3 is present, check if chain of 5 is made
				if (gameBoard[i+2][j] ==  gameBoard[i+3][j] &&
				gameBoard[i+3][j] ==  gameBoard[i+4][j]) {

					score += 50;
					return score;

				}

				// Otherwise, check if chain of 4 is made
				else if (gameBoard[i+2][j] ==  gameBoard[i+3][j]) {

					score += 30;
					return score;

				}

				// Otherwise, return score for 3 chain 
				else {
					score += 10;
					return score;
				}

			}

			// Initially checks for chain of 3 (horizontal)
			else if (gameBoard[i][j] ==  gameBoard[i][j+1] &&
					gameBoard[i][j+1] ==  gameBoard[i][j+2]) {

				// If chain of 3 is present, check if chain of 5 is made
				if (gameBoard[i][j+2] ==  gameBoard[i][j+3] &&
					gameBoard[i][j+3] ==  gameBoard[i][j+4]) {

					score += 50;
					return score;

				}

				// Otherwise, check if chain of 4 is made
				else if (gameBoard[i][j+2] ==  gameBoard[i][j+3]) {

					score += 30;
					return score;

				}

				// Otherwise, return score for 3 chain 
				else {
					score += 10;
					return score;
				}

			}
		}	
	}
	
	// If no match, just return the score
	return score;
}

// --- LOGIC FOR FINDING X Y COORIDINATES OF EACH GEM ---
int*** HintLogic() {
	// Middle coords of first gem
    int x1 = 80, y1 = 140;
    int*** hint = new int**[2]; // i in hint[i][j][k] (0 = x-coord, 1 = y-coord)

    for (int i = 0; i < 2; i++) {
		y1=140;
        hint[i] = new int*[9]; // j in hint[i][j][k]
        for (int j = 0; j < 9; j++) {
            hint[i][j] = new int[9]; // k in hint[i][j][k]
            for (int k = 0; k < 9; k++) {
                hint[i][j][k] = (i == 0) ? x1 : y1;
				
                x1 += 50;
            }
            x1 = 80;
            y1 += 40;
        }
		
    }

    return hint;
}

// --- HINT LOGIC THAT ACTUALLY HELPS THE USER ---
void HintLogic2() {
	int score;
	score = ScoreUpdate(1);

	if (score < 20) {
		cout << "You cannot afford a hint. :(" << endl;
		return;
	}

	else {
		for(int i = 0; i < 9 ; i++) {
			for(int j = 0; j < 9; j++) {
				////////////////////////////////for vertical matches////////////////////////////
				
				if(gameBoard[i][j] == gameBoard[i+1][j]) {   //if two vertically consecutive gems are there
					if(j != 0 && (gameBoard[i+2][j-1] == gameBoard[i+1][j])) {  //check if in the next row there is another same gem on the left

						cout << "HINT: Swap gem (" << (i + 2) + 1 << ", " << (j - 1) + 1 << ") ";
						cout << "with gem (" << (i + 2) + 1 << ", " << j + 1 << ")\n" << endl;
						glutPostRedisplay();

						return;
					}

					if (gameBoard[i+2][j+1] == gameBoard[i+1][j]) {   //otherwise check if in the next row there is another same gem on the right

						cout << "HINT: Swap gem (" << (i + 2) + 1 << ", " << (j + 1) + 1 << ") ";
						cout << "with gem (" << (i + 2) + 1 << ", " << j + 1 << ")\n" << endl;
						glutPostRedisplay();
						
						return;
					}

					if (i != 0 && (gameBoard[i-1][j+1] == gameBoard[i][j]))  {     //or check if in the previous row there is another same gem on the right

						cout << "HINT: Swap gem (" << (i - 1) + 1 << ", " << (j + 1) + 1 << ") ";
						cout << "with gem (" << (i - 1) + 1 << ", " << j + 1 << ")\n" << endl;
						glutPostRedisplay();

						return;
					}

					if (i !=0 && j != 0 && (gameBoard[i-1][j-1] == gameBoard[i][j])) {   //otherwise check if in the previous row there is another same gem on the left

						cout << "HINT: Swap gem (" << (i - 1) + 1 << ", " << (j - 1) + 1 << ") ";
						cout << "with gem (" << (i - 1) + 1 << ", " << j + 1 << ")\n" << endl;
						glutPostRedisplay();

						return;
					}
				}

				/////////////////////////horizontal matches/////////////////////////
				
				else if(gameBoard[i][j] == gameBoard[i][j+1]) {      //check if two horizontally same gems are there
					if(gameBoard[i][j+3]==gameBoard[i][j+1]) {   //now check if there is a same gem on the right of same row

						cout << "HINT: Swap gem (" << i + 1 << ", " << (j + 3) + 1 << ") ";
						cout << "with gem (" << i + 1 << ", " << (j + 2) + 1 << ")\n" << endl;
						glutPostRedisplay();

						return;
					}
			
					if(j>=2 && gameBoard[i][j-2] == gameBoard[i][j]) {   //now check if there is a same gem on the left of same row

						cout << "HINT: Swap gem (" << i + 1 << ", " << (j - 2) + 1 << ") ";
						cout << "with gem (" << i + 1 << ", " << (j - 1) + 1 << ")\n" << endl;
						glutPostRedisplay();

						return;
					}
				}
			}
		}
	}
}

// --- LOGIC FOR CHECKING FOR A 3 GEM CHAIN + DROPPING LOGIC ---
void CheckMatches(int startX, int startY, int endX, int endY, int valX, int valY) {
	static int score = 0; // Score changes every time the function is called
	
	bool noMatch = true; // Check for later
	srand(time(0));
	
	// For Vertical Matches
	for(int i=0;i<9;i++){
       	for(int j=0;j<9;j++) { 
			// Checks for chain of 3 vertical gems
			if(gameBoard[i][j] == gameBoard[i+1][j] && gameBoard[i+1][j] == gameBoard[i+2][j]) {

				score=ScoreUpdate();
				noMatch = false; // So that horizontal match isn't checked

				// Gem dropping logic
				int n = i+2; // n starts from 2
				for (int k = 1; k <= i; k++) { //k starts from 1 so that checking at i=0 isnt made 
					gameBoard[n][j]=gameBoard[i-k][j];  //the last gem of the chain is replaced by the gem on the top of the place from where chain is starting
					n--;    //so that the next gem falls on the 2nd gem of the chain 
				}
				
				// Randomize top 3 gem values
				do {
					gameBoard[0][j]=rand()%6+1;
					gameBoard[1][j]=rand()%6+1;
					gameBoard[2][j]=rand()%6+1;
					// do-while loop ensures the three random gems don't accidentally make a chain
				} while (gameBoard[0][j] == gameBoard[1][j] && gameBoard[1][j] == gameBoard[2][j] &&
						gameBoard[0][j] == gameBoard[0][j+1] && gameBoard[0][j+1] == gameBoard[0][j+2]);
				
				glutPostRedisplay();
				goto out; // to break out of two loops simultaneously
			}
     	}
   	}

	out:

	// For Horizontal Matches
	if (noMatch == true) { // If no vertical match is found, check for horizontal match
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++) { 
				// Checks for chain of 3 horizontal gems
				if(gameBoard[i][j]==gameBoard[i][j+1] && gameBoard[i][j+1]==gameBoard[i][j+2]) {
					
					score = ScoreUpdate();
					noMatch = false; // So that gem doesn't get swapped back
					
					// Gem dropping logic
					int n = 0; // n starts at zero
					for (int k = 1; k <= i; k++) {
						gameBoard[i-n][j] = gameBoard[i-n-1][j];
						gameBoard[i-n][j+1] = gameBoard[i-n-1][j+1];
						gameBoard[i-n][j+2] = gameBoard[i-n-1][j+2];
						
						n++;
					}
					
					do {
						gameBoard[0][j] = rand()%6 + 1;
						gameBoard[0][j+1] = rand()%6 + 1;
						gameBoard[0][j+2] = rand()%6 + 1;
						// do-while loop ensures the three random gems don't accidentally make a chain
					} while (gameBoard[0][j] == gameBoard[1][j] && gameBoard[1][j] == gameBoard[2][j] &&
						gameBoard[0][j] == gameBoard[0][j+1] && gameBoard[0][j+1] == gameBoard[0][j+2]);

					glutPostRedisplay();
					goto out2;
				}
			}
		}
	}

	out2:

	int temp = 0; // temp variable for swapping

	if (noMatch == true) { // If no match is made, swap gem to their original position.
		if (valX == 1 && startY == endY) {
			cout << "No match made, switched to original position." << endl;
			temp = gameBoard[startY][startX];
			gameBoard[startY][startX] = gameBoard[endY][endX];
			gameBoard[endY][endX] = temp;
		} 

		else if (valX == -1 && startY == endY) {
			cout << "No match made, switched to original position." << endl;
			temp = gameBoard[startY][startX];
			gameBoard[startY][startX] = gameBoard[endY][endX];
			gameBoard[endY][endX] = temp;
		}

		else if (valY == 1 && startX == endX) {
			cout << "No match made, switched to original position." << endl;
			temp = gameBoard[startY][startX];
			gameBoard[startY][startX] = gameBoard[endY][endX];
			gameBoard[endY][endX] = temp;
		}
			
		else if (valY == -1 && startX == endX) {
			cout << "No match made, switched to original position." << endl;
			temp = gameBoard[startY][startX];
			gameBoard[startY][startX] = gameBoard[endY][endX];
			gameBoard[endY][endX] = temp;
		}
	} 

	glutPostRedisplay();
}

// --- LOGIC TO SWAP ADJACENT GEMS ---
void SwapGems(int startX, int startY, int endX, int endY) {
	/* These values store the difference of the value
	where mouse was clicked vs. the value where mouse
	was released. */
	int valX = endX - startX;
	int valY = endY - startY;

	int temp = 0; // temp variable for swapping
	
	// Checks whether gems are adjacent and only then allows swapping.
	if (valX == 1 && startY == endY) {
		// Gem swapped to the right.
		temp = gameBoard[endY][endX];
		gameBoard[endY][endX] = gameBoard[startY][startX];
		gameBoard[startY][startX] = temp;
	} 

	else if (valX == -1 && startY == endY) {
		// Gem swapped to the left
		temp = gameBoard[endY][endX];
		gameBoard[endY][endX] = gameBoard[startY][startX];
		gameBoard[startY][startX] = temp;
	}

	else if (valY == 1 && startX == endX) {
		// Gem swapped down.
		temp = gameBoard[endY][endX];
		gameBoard[endY][endX] = gameBoard[startY][startX];
		gameBoard[startY][startX] = temp;
	}
		
	else if (valY == -1 && startX == endX) {
		// Gem swapped up.
		temp = gameBoard[endY][endX];
		gameBoard[endY][endX] = gameBoard[startY][startX];
		gameBoard[startY][startX] = temp;
	}
	
	glutPostRedisplay();
	
	// Call function to check if a match is being made.
	CheckMatches(startX, startY, endX, endY, valX, valY);
}

// --- FOR DRAWING PROGRESS BAR (NORMAL MODE) ---
void DrawProgressBar(int levelScore , int levelThreshold) { 
	// Total width + height of progress bar
    int barWidth = 570;
    int barHeight = 20;

	// Values set to 0 instead of passing zero (for clarity)
    int barX = 0;
    int barY = 0;
	
	// Clear the previous progress bar
	DrawRectangle(0, 0, 570, 20, colors[BLACK]);

	glColor3f(0.0f, 1.0f, 0.0f); // Green color

	// Draws a rectangle with coordinates
	glBegin(GL_QUADS);
	glVertex2i(barX, barY);
	glVertex2i(barX + (levelScore * barWidth) / levelThreshold, barY);
	glVertex2i(barX + (levelScore * barWidth) / levelThreshold, barY + barHeight);
	glVertex2i(barX, barY + barHeight);
	glEnd();

}	

// --- DECREASES VALUE OF PROGRESS BAR (TIME TRIAL MODE) ---
void DecreaseProgressBar(int value) {
    // Decrease the levelScore variable by 1
    value -= 1;

    // Call TTGameDisplay function again to update the display
    glutPostRedisplay();
}

// --- TIMER FUNCTION TO CALL A FUNCTION EVERY SECOND ---
void Timer(int value) {
    // Decrease the levelScore variable by 1
    DecreaseProgressBar(value);

    // Call Timer function again after 1 second
    glutTimerFunc(1000, Timer, 0);
}

// --- FOR DRAWING PROGRESS BAR (TIME TRIAL MODE) ---
void TTDrawProgressBar(int levelScore, int levelThreshold, int level, int elapsedTime) {
	// Total width + height of progress bar
    int barWidth = 570;
    int barHeight = 20;

	// Values set to 0 instead of passing zero (for clarity)
    int barX = 0;
    int barY = 0;

    // Clear the previous progress bar
    DrawRectangle(0, 0, 570, 20, colors[BLACK]);

    // Calculate the remaining time
    int remainingTime = (levelThreshold - levelScore) * 3 - elapsedTime; // Assuming 10 seconds per point and subtracting elapsed time
    int filledWidth = (remainingTime * barWidth) / (levelThreshold * 3);
    if(filledWidth<=0)
    {
    cout<<"Oh NO!!!!!! You losttt :("<<endl;
    cout<<"Game Ended!!"<<endl;
    exit(1);
    }
    // Draw the filled portion of the progress bar based on the remaining time
    glColor3f(1.0f, 0.0f, 0.0f); // Red color

	// Draws a rectangle with coordinates
    glBegin(GL_QUADS);
    glVertex2i(barX, barY);
    glVertex2i(barX + filledWidth, barY);
    glVertex2i(barX + filledWidth, barY + barHeight);
    glVertex2i(barX, barY + barHeight);
    glEnd();

     
    // Updates elapsed time
    //elapsedTime += 2; // Assuming 2 seconds elapsed after each chain

    //
}

// --- FUNCTION CALLED FOR DISPLAYING ELEMENTS ON SCREEN (TIME TRIAL MODE) ---
void TTGameDisplay() {
    int score = ScoreUpdate(); // For getting score everytime GameDisplay is called
    static int levelThreshold, level, levelScore, resetScore, realLevel, elapsedTime = 0;

    // Update elapsed time
    elapsedTime += 2; // Assuming 2 seconds elapsed after each chain

	/* Logic for updating levels, adjusting each level threshold,
	and adjusting levelScore to pass into DrawProgressBar function */
    if (score >= 0 && score < 100) {
        levelThreshold = 100;
        levelScore = 50;
        level = 0;
    } else if (score >= 100 && score < 250) {
        levelThreshold = 210;
        levelScore = score % levelThreshold;
        level = 1;
    } else if (score >= 250 && score < 450) {
        levelThreshold = 430;
        levelScore = score % levelThreshold;
        level = 2;
    } else if (score >= 450 && score < 700) {
        levelThreshold = 690;
        levelScore = score % levelThreshold;
        level = 3;
    } else if (score >= 700 && score < 1000) {
        levelThreshold = 1000;
       levelScore = score % levelThreshold;
        level = 4;
    } else if (score >= 1000 && score < 1350) {
        levelThreshold = 1350;
        levelScore = score % levelThreshold;
        level = 5;
    }

	// Changes BG color according to level
    switch(level) {
		case 0:
		    glClearColor(238.0/255, 195.0/255, 248.0/255, 1); // Default background color
            break;
        case 1:
            glClearColor(130.0/255, 41.0/255, 169.0/255, 0.8);
            break;
        case 2:
            glClearColor(154.0/255, 226.0/255, 255.0/255, 0.86);
            break;
        case 3:
            glClearColor(65.0/255, 186.0/255, 218.0/255, 1);
            break;
        case 4:
            glClearColor(139.0/255, 81.0/255, 81.0/255, 1);
            break;
        case 5:
            glClearColor(238.0/255, 195.0/255, 248.0/255, 1); // Default background color
            break;
	default:
	    glClearColor(238.0/255, 195.0/255, 248.0/255, 1); // Default background color
            break;
	}

	// Logic for Game Screen
    glClear(GL_COLOR_BUFFER_BIT);
    DrawString(10, 800, "Score: " + to_string(score), colors[BLACK]);
    DrawString(350, 800, "Hiyam", colors[BLACK]);
    
    realLevel = level + 1; // So that level starts from 1 instead of 0
    DrawString(10, 755, "Level: " + to_string(realLevel), colors[BLACK]);
    DrawGameBoard();
    // glutTimerFunc(2000, DecreaseProgressBar, 0); // For decreasing progress bar every second
   TTDrawProgressBar(levelScore, levelThreshold, level, elapsedTime); // Different porgress bar for time trial
glutTimerFunc(1000, Timer, 0);
    // Logic to draw the Pause Button
    DrawRoundRect(450, 50, 75, 75, colors[BLUE], 10);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(((450 + 525 - 10) / 2), ((50 + 125 - 10) / 2));
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'P');

    // Logic to draw Hint Button
    DrawRoundRect(40, 50, 75, 75, colors[BLUE], 10);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(((40 + 115 - 20) / 2), ((50 + 125 - 15) / 2));
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'H');

    glutSwapBuffers();
}

// --- FUNCTION CALLED FOR DISPLAYING ELEMENTS ON SCREEN (NORMAL MODE) ---
void GameDisplay() {
    int score = ScoreUpdate(); // For getting score everytime GameDisplay is called
    static int levelThreshold, level, levelScore, resetScore, realLevel;

	/* Logic for updating levels, adjusting each level threshold,
	and adjusting levelScore to pass into DrawProgressBar function */
	if (score >= 0 && score <= 100) {
        levelThreshold = 100;
        levelScore = score;
        level = 0;
    } else if (score > 100 && score < 250) {
        levelThreshold = 150;
        levelScore = score - 100;
        level = 1;
    } else if (score >= 250 && score < 450) {
        levelThreshold = 200;
        levelScore = score - 250; 
        level = 2;
    } else if (score >= 450 && score < 700) {
        levelThreshold = 250;
        levelScore = score - 450; 
        level = 3;
    } else if (score >= 700 && score < 1000) {
        levelThreshold = 300;
        levelScore = score - 700; 
        level = 4;
    } else if (score > 1001) {
        levelThreshold = 350;
        levelScore = score - 1001; 
        level = 5;
    }

	// Changes BG color according to level
    switch(level) {
	case 0:
	    glClearColor(238.0/255, 195.0/255, 248.0/255, 1); 
            break;
        case 1:
            glClearColor(130.0/255, 41.0/255, 169.0/255, 0.8);
            break;
        case 2:
            glClearColor(154.0/255, 226.0/255, 255.0/255, 0.86);
            break;
        case 3:
            glClearColor(65.0/255, 186.0/255, 218.0/255, 1);
            break;
        case 4:
            glClearColor(139.0/255, 81.0/255, 81.0/255, 1);
            break;
        case 5:
            glClearColor(238.0/255, 195.0/255, 248.0/255, 1); 
            break;
	default:
	    glClearColor(238.0/255, 195.0/255, 248.0/255, 1); 
            break;
    }

	// Logic for Game Screen
    glClear(GL_COLOR_BUFFER_BIT);
    DrawString(10, 800, "Score: " + to_string(score), colors[BLACK]);
    DrawString(350, 800, "Hiyam", colors[BLACK]);
    
    realLevel = level + 1; // So that level starts from 1 instead of 0
    DrawString(10, 760, "Level: " + to_string(realLevel), colors[BLACK]);
    DrawGameBoard();
    DrawProgressBar(levelScore, levelThreshold);

    // Logic to draw the Pause Button
    DrawRoundRect(450, 50, 75, 75, colors[BLUE], 10);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(((450 + 525 - 10) / 2), ((50 + 125 - 10) / 2));
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'P');

	// Logic to draw Hint Button
    DrawRoundRect(40, 50, 75, 75, colors[BLUE], 10);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(((40 + 115 - 20) / 2), ((50 + 125 - 15) / 2));
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'H');

    glutSwapBuffers();
}

// --- WRAPPER FUNCTION FOR GAME DISPLAY ---
/* (Used so that a value can be passed in the function) */

// --- DRAGGING LOGIC AND BUTTON LOGIC ---
void MouseClicked(int button, int state, int x, int y) {
	// Stores initial position of mouse click
    static int startX = 0;
    static int startY = 0;

	// Stores final position of  mouse release
	static int endX = 0;
	static int endY = 0;

	string s = ""; // Value to input for unpausing game
    bool hintClicked=false;
	
	// Detects if Mouse left button is clicked
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// For Pause Button
		if ((x >= 450 && x < 526) && (y >= 606 && y < 671)) { // Condition for Pause button coorinates
			glClearColor(238.0 / 255, 195.0 / 255, 248.0 / 255, 1); 
			glClear(GL_COLOR_BUFFER_BIT); 
			DrawString(200, 400, "Game Paused!!", colors[BLACK]);
			cout << "Press any key to continue: "<<endl; // Displays in terminal
			glutSwapBuffers();
			cin >> s; 
			glutPostRedisplay(); // When input is taken, glutPostRedisplay will redraw the game screen 
             
        }

        // For Hint button
		if ((x >= 40 && x < 116) && (y >= 606 && y < 671)) {
			GameDisplay();
		
			HintLogic2();
		}

		/* For Swapping functionality. This stores START position of 
		where the mouse was clicked on the gameboard. */
		if ((x >= 60 && x < 501) && (y >= 125 && y < 491)) { // Coords for game area

			// This logic translates x & y coords into index i & j in the gameBoard array.
			int row = (y - 125) / (40); // detects i in gameboard[i][j]
			int col = (x - 60) / (50); // detects j in gameBoard[i][j]

			/* x = col and y = row . it's swapped beacause x becomes column placement
			and y becomes row placement in an array viewpoint. */

			startX = col;
			startY = row;
		}
	}

	// Detects if Mouse click is released
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		/* This stores END position of where the mouse was clicked 
		on the gameboard. */
		if ((x >= 60 && x < 501) && (y >= 125 && y < 491)) { // Coords for game area
			int row = (y - 125) / (40); // detects i in gameboard[i][j]
			int col = (x - 60) / (50); // detects j in gameboard[i][j]

			endX = col;
			endY = row;

			SwapGems(startX, startY, endX, endY); // SwapGems is called when mouse is released.
		}
	}
}

// --- ENABLES TIME TRIAL MODE ---
void TimeTrialMode() {
	glutSwapBuffers(); // Used to clear previous menu screen
	glutPostRedisplay();

	GameBoardInitialize(); // Initializes the GameBoard
	
	glutDisplayFunc(TTGameDisplay); // Display the game
glutTimerFunc(1000, Timer, 0);
	// Called for functionality purposes
	glutKeyboardFunc(PrintableKeys);
	glutMouseFunc(MouseClicked);
	
	glutMainLoop();
}

// --- ENABLES NORMAL GAME MODE ---
void NormalMode() {
	glutSwapBuffers(); // Used to clear previous menu screen
	glutPostRedisplay();

	GameBoardInitialize(); // Initializes the GameBoard

	glutDisplayFunc(GameDisplay); // Display the game

	// Called for functionality purposes
	glutKeyboardFunc(PrintableKeys); 
	glutMouseFunc(MouseClicked);

	glutMainLoop(); 
}

// --- CHECKS FOR KEYS PRESSED ON KEYBOARD ---
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	string s = ""; // Value to input for unpausing game

	if (key == 'p' || key == 'P') { // Alternative: When P is pressed, the game will pause
		glClearColor(238.0 / 255, 195.0 / 255, 248.0 / 255, 1); 
		glClear(GL_COLOR_BUFFER_BIT); 
		DrawString(200, 400, "Game Paused!!", colors[BLACK]);
		cout << "Press any key to continue: "<<endl; // Displays in terminal
		glutSwapBuffers();
		cin >> s; 
		glutPostRedisplay(); // When input is taken, glutPostRedisplay will redraw the game screen 
             
    }

	if (key == 's' || key == 'S') { // Starts the game
		ModeChoice();            
	}
	if (key == 't' || key == 'T') { // Enables Time Trial
		TimeTrialMode();
	}
	else if(key=='n'||key=='N') { // Enables Normal Mode
		NormalMode();
	}

}

#endif /* AsteroidS_CPP_ */

