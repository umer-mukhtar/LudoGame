#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
//#include "Board.h"
#include "util.h"
#include <iostream>
#include<string>
#include<cmath>
#include<fstream>

using namespace std;

int players; // global variable to record number of players
string playerNames[4]={}; // string array to store player names
int playerColors[4]={-1,-1,-1,-1}; //int array to store player colors.0 for yellow, 1 for blue, 2 for red, 3 for green, -1 for disabled
int window=1; // starts from 1st window.actually these are displays on the same window(not seperate windows)
int choice=0; // choice of assignment of colors(window3)
int spacePressed=0; // global variable to record if space is pressed
char keyPressed; // global variable to record if a printable key is pressed
int piece[4][4]={}; // initializing all pieces to zero (zero means locked)
int turn=0; //0:yellow 1:blue 2:red 3:green
int dice; // global variable for dice which is rolled
int dices[3]={}; // initilializing dice array to zero
int squares[124][2]; // to set positions of pieces
int killCount[4]={}; // initializing kill count of all 4 players to zero
int score[4]={}; // initializing score of all 4 players to zero
int block[52]={}; // if block forms on any of the 52 squares(initialized to zero)
int status[4]={-1,-1,-1,-1}; // status of all 4 players. (0 for playing. -1 for disabled. 1 for winners)
int teamMode=0; // 0 for disabled, 1 for enabled
int partnersRoll[4]={}; // TeamMode: 0 if partner is in play, if partner has all 4 pieces in home triangle and throws a six, it is =1

void initializingPieceArray() // this function runs only once to initialize piece[4][4] array's all values to -1
{
    static int countForInitializingPieceArrayFunc = 0; // counter variable for initializingPieceArray function
    if(countForInitializingPieceArrayFunc == 0)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                piece[i][j]=-1;
            }
        }
        countForInitializingPieceArrayFunc++;
    }
}

void assignValuesToSquares() // this function is being used to fill squars[52][2] with all central points of each square so later a circle can be made in place
{
    // considering 0th square to be the one directly on the safe spot of yellow and 51th square at the one below safe spot of yellow
    squares[0][0]=468; // x
    squares[0][1]=168; // y
    squares[1][0]=468;
    squares[1][1]=168+32;
    squares[2][0]=468;
    squares[2][1]=168+(2*32);
    squares[3][0]=468;
    squares[3][1]=168+(3*32);
    squares[4][0]=468;
    squares[4][1]=168+(4*32);
    squares[5][0]=468-32;
    squares[5][1]=168+(5*32);
    squares[6][0]=468-(2*32);
    squares[6][1]=168+(5*32);
    squares[7][0]=468-(3*32);
    squares[7][1]=168+(5*32);
    squares[8][0]=468-(4*32);
    squares[8][1]=168+(5*32);
    squares[9][0]=468-(5*32);
    squares[9][1]=168+(5*32);
    squares[10][0]=468-(6*32);
    squares[10][1]=168+(5*32);
    squares[11][0]=468-(6*32);
    squares[11][1]=168+(6*32);
    squares[12][0]=468-(6*32);
    squares[12][1]=168+(7*32);
    squares[13][0]=468-(5*32);
    squares[13][1]=168+(7*32);
    squares[14][0]=468-(4*32);
    squares[14][1]=168+(7*32);
    squares[15][0]=468-(3*32);
    squares[15][1]=168+(7*32);
    squares[16][0]=468-(2*32);
    squares[16][1]=168+(7*32);
    squares[17][0]=468-(1*32);
    squares[17][1]=168+(7*32);
    squares[18][0]=468-(0*32);
    squares[18][1]=168+(8*32);
    squares[19][0]=468-(0*32);
    squares[19][1]=168+(9*32);
    squares[20][0]=468-(0*32);
    squares[20][1]=168+(10*32);
    squares[21][0]=468-(0*32);
    squares[21][1]=168+(11*32);
    squares[22][0]=468-(0*32);
    squares[22][1]=168+(12*32);
    squares[23][0]=468-(0*32);
    squares[23][1]=168+(13*32);
    squares[24][0]=468+(1*32);
    squares[24][1]=168+(13*32);
    squares[25][0]=468+(2*32);
    squares[25][1]=168+(13*32);
    squares[26][0]=468+(2*32);
    squares[26][1]=168+(12*32);
    squares[27][0]=468+(2*32);
    squares[27][1]=168+(11*32);
    squares[28][0]=468+(2*32);
    squares[28][1]=168+(10*32);
    squares[29][0]=468+(2*32);
    squares[29][1]=168+(9*32);
    squares[30][0]=468+(2*32);
    squares[30][1]=168+(8*32);
    squares[31][0]=468+(3*32);
    squares[31][1]=168+(7*32);
    squares[32][0]=468+(4*32);
    squares[32][1]=168+(7*32);
    squares[33][0]=468+(5*32);
    squares[33][1]=168+(7*32);
    squares[34][0]=468+(6*32);
    squares[34][1]=168+(7*32);
    squares[35][0]=468+(7*32);
    squares[35][1]=168+(7*32);
    squares[36][0]=468+(8*32);
    squares[36][1]=168+(7*32);
    squares[37][0]=468+(8*32);
    squares[37][1]=168+(6*32);
    squares[38][0]=468+(8*32);
    squares[38][1]=168+(5*32);
    squares[39][0]=468+(7*32);
    squares[39][1]=168+(5*32);
    squares[40][0]=468+(6*32);
    squares[40][1]=168+(5*32);
    squares[41][0]=468+(5*32);
    squares[41][1]=168+(5*32);
    squares[42][0]=468+(4*32);
    squares[42][1]=168+(5*32);
    squares[43][0]=468+(3*32);
    squares[43][1]=168+(5*32);
    squares[44][0]=468+(2*32);
    squares[44][1]=168+(4*32);
    squares[45][0]=468+(2*32);
    squares[45][1]=168+(3*32);
    squares[46][0]=468+(2*32);
    squares[46][1]=168+(2*32);
    squares[47][0]=468+(2*32);
    squares[47][1]=168+(1*32);
    squares[48][0]=468+(2*32);
    squares[48][1]=168+(0*32);
    squares[49][0]=468+(2*32);
    squares[49][1]=168-(1*32);
    squares[50][0]=468+(1*32);
    squares[50][1]=168-(1*32);
    squares[51][0]=468+(0*32);
    squares[51][1]=168-(1*32);
    // now assigning squares of home column
    squares[100][0]=240+20+16+(7*32);
    squares[100][1]=100+20+16+(1*32);
    squares[101][0]=240+20+16+(7*32);
    squares[101][1]=100+20+16+(2*32);
    squares[102][0]=240+20+16+(7*32);
    squares[102][1]=100+20+16+(3*32);
    squares[103][0]=240+20+16+(7*32);
    squares[103][1]=100+20+16+(4*32);
    squares[104][0]=240+20+16+(7*32);
    squares[104][1]=100+20+16+(5*32);
    //squares[105][0]=240+20+16+(7*32);
    //squares[105][1]=100+20+16+(6*32);
    squares[106][0]=240+20+16+(1*32);
    squares[106][1]=100+20+16+(7*32);
    squares[107][0]=240+20+16+(2*32);
    squares[107][1]=100+20+16+(7*32);
    squares[108][0]=240+20+16+(3*32);
    squares[108][1]=100+20+16+(7*32);
    squares[109][0]=240+20+16+(4*32);
    squares[109][1]=100+20+16+(7*32);
    squares[110][0]=240+20+16+(5*32);
    squares[110][1]=100+20+16+(7*32);
    //squares[111][0]=240+20+16+(6*32);
    //squares[111][1]=100+20+16+(7*32);
    squares[112][0]=240+20+16+(7*32);
    squares[112][1]=100+20+16+(13*32);
    squares[113][0]=240+20+16+(7*32);
    squares[113][1]=100+20+16+(12*32);
    squares[114][0]=240+20+16+(7*32);
    squares[114][1]=100+20+16+(11*32);
    squares[115][0]=240+20+16+(7*32);
    squares[115][1]=100+20+16+(10*32);
    squares[116][0]=240+20+16+(7*32);
    squares[116][1]=100+20+16+(9*32);
    //squares[117][0]=240+20+16+(7*32);
    //squares[117][1]=100+20+16+(8*32);
    squares[118][0]=240+20+16+(13*32);
    squares[118][1]=100+20+16+(7*32);
    squares[119][0]=240+20+16+(12*32);
    squares[119][1]=100+20+16+(7*32);
    squares[120][0]=240+20+16+(11*32);
    squares[120][1]=100+20+16+(7*32);
    squares[121][0]=240+20+16+(10*32);
    squares[121][1]=100+20+16+(7*32);
    squares[122][0]=240+20+16+(9*32);
    squares[122][1]=100+20+16+(7*32);
    //squares[123][0]=240+20+16+(8*32);
    //squares[123][1]=100+20+16+(7*32);
}

void SetCanvasSize(int width, int height) { // this function sets the screen to the width and height of 720p resolution(my laptop)
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();
}

void PrintableKeys(unsigned char key, int x, int y) { // this function automatically runs when a printable key is pressed
	if (key == 27/* Escape key ASCII*/) {
        if(window==1)
        {
            exit(1); // exits the program when escape key is pressed in window 1
        }
		else
        {
            window=1; // returns to main menu
        }
	}
    if(window==1) //main menu
    {
        if(key==49) // ASCII for '1'
        {
            window=2; // enter names window
        }
        if(key==50) // ASCII for '2'
        {
            window=6; // Leaderboard window
        }
        if(key==51) //ASCII for '3'
        {
            window=4; // rules window
        }
        if(key==52) //ASCII for '4'
        {
            window=5;// instructions window
        }
    }
    if(window==2) //player's names input
    {
        static int x=0;
        while(x==0)
        { // this loop is made so that the number of players are only entered once
            if(key>=50 && key<=52)
            {
                players=key-48;
                x++; // this causes the loop to never run again
            }
            else
            {
                break; // the loop breaks if no key is being pressed
            }
        }
        while(x==1)
        {
            static int y=0;
            if((key>=65 && key<=90) || (key>=97 && key<=122)) // ASCII for capital and small alphabets
            {
                keyPressed=key;
                break;
            }
            else if(key==13)//ASCII for enter
            {
                y++;
                keyPressed=13;
                if(y==players)
                {
                    if(players==4) // then they are able to play in teams if willing
                    {
                        window=13; // go to 13th window
                    }
                    else // they are not able to play in teams
                    {
                        window=3; // go to 3rd window
                    }
                }
                break;
            }
            else
            {
                break; // breaks the loop if no key is pressed
            }
        }
    }
    if(window==3) //choice of assignment of colors
    {
        if(key==49) //ASCII for 1
        {
            choice=1;
        }
        if(key==50) //ASCII for 2
        {
            choice=2;
            window=11;
        }
    }
    if(window==13) // choice of teammode
    {
        if(key==49) //yes
        {
            teamMode=1;
            window=3;
        }
        if(key==50) // no
        {
            teamMode=0;
            window=3;
        }
    }
    if(window==12) // display randomely assigned colors
    {
        if(key==13)
        {
            window=7;
        }
    }
    if(window==11) //color by choice
    {
        if(key==97)
        {
            keyPressed='a';
        }
        if(key==98)
        {
            keyPressed='b';
        }
        if(key==99)
        {
            keyPressed='c';
        }
        if(key==100)
        {
            keyPressed='d';
        }
    }
    if(window==4) //rules
    {
        // does not react to user inputs except Esc
    }
    if(window==5) // instructions
    {
        // does not react to user inputs except Esc
    }
    if(window==6) // leaderboard
    {
        // does not react to user inputs except Esc
    }
    if(window==7) // highest roll
    {
        if(key==32)
        {
            dice=GetRandInRange(1,7);
        }
    }
    if(window==8) // game board
    {
    	if (key == 32) //Key for rolling dice
        {
            /*if(turn == 4)
            {
                turn=0;
            }*/
            spacePressed=1;
    		dice = GetRandInRange(1,7);
    	}
        if( key==97)
        {
            keyPressed='a';
        }
        if(key==98)
        {
            keyPressed='b';
        }
        if(key==99)
        {
            keyPressed='c';
        }
        if(key==100)
        {
            keyPressed='d';
        }
        if(key == 110) // if no possible moves
        {
            turn++; // next turn
            dice = GetRandInRange(1,7);  // new dice number
            for(int x=0;x<3;x++)
            {
                dices[x]=0;
            }
        }
    }
    if(window==9) // end window
    {
        if(key==13)
        {
            window=6; // it says press enter to view leaderboard
        }
    }
	glutPostRedisplay();
}

void window1() // this function is used to display main menu
{
    DrawStringHead(610,500,"LUDO",colors[BLACK]);
    DrawStringHead(610-40,500-27,"MAIN MENU",colors[BLACK]);
    DrawString(570,400,"1) Play Game",colors[BLACK]);
    DrawString(570,400-20,"2) Leaderboard",colors[BLACK]);
    DrawString(570,400-40,"3) Rules",colors[BLACK]);
    DrawString(570,400-60,"4) Instructions",colors[BLACK]);
    DrawStringSmall(570,400-100,"Press the respective numeric key",colors[BLACK]);
    //select option by presing the respective number key
    //DrawString(610-200,500-37,,colors[BLACK]);
    //DrawStringHead(520,480,"MAIN MENU",colors[BLACK]);
    glutPostRedisplay();
}

void window2() // this function is used to take player's names input from the user
{
    DrawString(510,500,"Please enter the number of players",colors[BLACK]);
    string playersString; // to display the number of players on screen using DrawString function
    playersString = players + 48; // e.g if players are 2, then int of 2 is ASCII 2+48 which is '2' in string
    if(players==0)
    {
        DrawString(630,480,"___",colors[BLACK]); // Dash as a replacement for numbers beforehand
    }
    else
    {
        DrawString(635,470,playersString,colors[BLACK]);
        DrawString(440,410,"Please enter your names one by one (by pressing the enter)",colors[BLACK]);
        /*DrawString(440,390,playerNames[0],colors[BLACK]);
        DrawString(440,380,playerNames[1],colors[BLACK]);
        DrawString(440,370,playerNames[2],colors[BLACK]);
        DrawString(440,360,playerNames[3],colors[BLACK]);*/
        static int i=0;
        if(i<players)
        {
            if(keyPressed==0) // NULL
            {
                // do nothing
            }
            else if(keyPressed==13)
            {
                i++;
            }
            else if(keyPressed!=13) // when some alphabet keys are pressed
            {
                playerNames[i]+=keyPressed;
            }// when this for loop breaks, the window should move on to the next one
            DrawString(620,380,playerNames[0],colors[BLACK]); // prints name of player 0
            DrawString(620,360,playerNames[1],colors[BLACK]);// prints name of player 1
            DrawString(620,340,playerNames[2],colors[BLACK]);// prints name of player 2
            DrawString(620,320,playerNames[3],colors[BLACK]);//prints name of player 3
            keyPressed=0;
        }
    }
    glutPostRedisplay();
}

void window12() // displays the randomely assigned colors
{
    /*test data
    players=2;
    playerNames[0]="ABC";
    playerNames[1]="DEF";
    playerColors[0]=1;
    playerColors[1]=2;*/
    for(int i=0;i<players;i++)
    {
        DrawString(400,500,"These colors were randomely assigned to you",colors[BLACK]);
        if(i==0) // player 0
        {
            DrawString(400,460,playerNames[i],colors[BLACK]);
            if(playerColors[i]==0)
            {
                DrawString(500,460,"Yellow",colors[OLIVE]);
            }
            if(playerColors[i]==1)
            {
                DrawString(500,460,"Blue",colors[BLUE]);
            }
            if(playerColors[i]==2)
            {
                DrawString(500,460,"Red",colors[RED]);
            }
            if(playerColors[i]==3)
            {
                DrawString(500,460,"Green", colors[LIME]);
            }
        }
        if(i==1) // player 1
        {
            DrawString(400,430,playerNames[i],colors[BLACK]);
            if(playerColors[i]==0)
            {
                DrawString(500,430,"Yellow",colors[OLIVE]);
            }
            if(playerColors[i]==1)
            {
                DrawString(500,430,"Blue",colors[BLUE]);
            }
            if(playerColors[i]==2)
            {
                DrawString(500,430,"Red",colors[RED]);
            }
            if(playerColors[i]==3)
            {
                DrawString(500,430,"Green", colors[LIME]);
            }
        }
        if(i==2) // player 2
        {
            DrawString(400,400,playerNames[i],colors[BLACK]);
            if(playerColors[i]==0)
            {
                DrawString(500,400,"Yellow",colors[OLIVE]);
            }
            if(playerColors[i]==1)
            {
                DrawString(500,400,"Blue",colors[BLUE]);
            }
            if(playerColors[i]==2)
            {
                DrawString(500,400,"Red",colors[RED]);
            }
            if(playerColors[i]==3)
            {
                DrawString(500,400,"Green", colors[LIME]);
            }
        }
        if(i==3) // player 3
        {
            DrawString(400,370,playerNames[i],colors[BLACK]);
            if(playerColors[i]==0)
            {
                DrawString(500,370,"Yellow",colors[OLIVE]);
            }
            if(playerColors[i]==1)
            {
                DrawString(500,370,"Blue",colors[BLUE]);
            }
            if(playerColors[i]==2)
            {
                DrawString(500,370,"Red",colors[RED]);
            }
            if(playerColors[i]==3)
            {
                DrawString(500,370,"Green", colors[LIME]);
            }
        }
        //DrawString(100,100,playerNames[i],colors[BLACK]);
        DrawString(400,340,"Press Enter to conitnue",colors[BLACK]);
    }
    glutPostRedisplay();
}

void window3() // this function is used to ask for choice of colors from user
{
    DrawString(380,500,"How do you want to be assigned colors?",colors[BLACK]);
    DrawString(380,470,"1) Randomly" ,colors[BLACK]);
    DrawString(380,450,"2) Based on choice",colors[BLACK]);
    DrawStringSmall(380,430,"Press the respective numeric key",colors[BLACK]);
    if(choice == 1)
    {
        if(players==2) // 2 players can only have opposite colors
        {
            playerColors[0] = GetRandInRange(0, 4);
            if(playerColors[0]<=1)
            {
                playerColors[1] = playerColors[0]+2; // if playerColors[0] is 0 then other will get 2. if it is 1, then other will get 3
            }
            else
            {
                playerColors[1] = playerColors[0]-2; // if playercolors[0] is 2 then other will get 0, if it is 3 then other will get 1
            }
        }
        else // if players are 3 or 4, they will get any random color
        {
            playerColors[0] = GetRandInRange(0, 4);
            if(players==3)
            {
                do{
                    playerColors[1] = GetRandInRange(0, 4);
                }while(playerColors[1]==playerColors[0]); // does not allow same colors
                do{
                    playerColors[2] = GetRandInRange(0, 4);
                }while(playerColors[2] == playerColors[0] || playerColors[2]==playerColors[1]); // doesnt allow same colors
            }
            if(players==4)
            {
                do{
                    playerColors[1] = GetRandInRange(0, 4);
                }while(playerColors[1]==playerColors[0]) ;// does not allow same colors
                do{
                    playerColors[2] = GetRandInRange(0, 4);
                }while(playerColors[2] == playerColors[0] || playerColors[2]==playerColors[1]) ;// doesnt allow same colors
                do{
                    playerColors[3] = GetRandInRange(0, 4);
                }while(playerColors[3] == playerColors[0] || playerColors[3]==playerColors[1] || playerColors[3]==playerColors[2]); // doesnt allow same colors
            }
        }
        window=12;
    }
    else; // change of window is in PrintableKeys function
    glutPostRedisplay();
}

void window13() // this function asks the players if they want to play in teams
{
    DrawString(400,500,"Do you want to play in teams? (Opposite colors will be of the same team)",colors[BLACK]);
    DrawString(400,470,"1) Yes",colors[BLACK]);
    DrawString(400,450,"2) No",colors[BLACK]);
    DrawStringSmall(400,430,"Press the respective numeric key",colors[BLACK]);
}

void window11() // this function lets user pick color by choice
{
    static int x=0;
    DrawStringHead(490,650-50,"Pick a color",colors[BLACK]);
    DrawRectangle(450, 550-30-50-100, 100, 100, colors[OLIVE]);
    DrawRectangle(450, 550-30-50, 100, 100, colors[BLUE]);
    DrawRectangle(450+100, 550-30-50, 100, 100, colors[RED]);
    DrawRectangle(450+100, 550-30-50-100, 100, 100, colors[LIME]);
    DrawString(450+50, 550-30-50-100+50, "a", colors[BLACK]);
    DrawString(450+50, 550-30-50+50, "b", colors[BLACK]);
    DrawString(450+100+50, 550-30-50+50,"c", colors[BLACK]);
    DrawString(450+100+50, 550-30-50-100+50,"d", colors[BLACK]);
    DrawString(450+50, 550-30-50-150, playerNames[x], colors[BLACK]);
    if(players==2) // in case of 2 players, they can only have opposing colors
    {
        if(keyPressed>=97 && keyPressed<=100)
        {
            playerColors[0]=keyPressed-97;
            if(keyPressed<=98) // a and b
            {
                playerColors[1]=keyPressed-97+2; // if 0 chooses a then 1 gets c. if 0 chooses b then 1 gets d
                keyPressed=0;
                window=7;
            }
            else if(keyPressed>=99) // c and d
            {
                playerColors[1]=keyPressed-97-2; // if 0 chooses c then 1 gets a. if 0 chooses d then 1 gets b
                keyPressed=0;
                window=7;
            }
        }
    }
    else
    {
        if(x<players)
        {
            if(keyPressed>=97 && keyPressed<=100)
            {
                if(x==0)
                {
                    playerColors[0]=keyPressed-97;
                    x++;
                    keyPressed=0;
                }
                else if(x==1)
                {
                    if(playerColors[0]!=keyPressed-97)
                    {
                        playerColors[1]=keyPressed-97;
                        x++;
                        keyPressed=0;
                    }
                }
                else if(x==2)
                {
                    if(playerColors[0]!=keyPressed-97 && playerColors[1]!=keyPressed-97)
                    {
                        playerColors[2]=keyPressed-97;
                        x++;
                        keyPressed=0;
                    }
                }
                else if(x==3)
                {
                    for(int j=0;j<4;j++)
                    {
                        if(playerColors[0]!=j && playerColors[1]!=j && playerColors[2]!=j)
                        {
                            playerColors[3]=j;
                            x++;
                        }
                    }
                    keyPressed=0;
                }
                else
                {
                    keyPressed=0;
                }
            }
        }
        else // if x==players move on to the next window
        {
            window=7;
        }
    }
    glutPostRedisplay();
}

void window4() // this function is used to display the rules of the game
{
    DrawStringHead(550,600,"RULES",colors[BLACK]);
    DrawString(200,570,"1) Each player will have 4 Ludo pieces of that color placed in the corresponding starting square.",colors[BLACK]);
    DrawString(200,550-5,"2) A player must throw a 6 to move a piece from the starting square onto the first square on the track.",colors[BLACK]);
    DrawString(200,530-10,"3) A player will keep on throwing the dice if Six comes.",colors[BLACK]);
    DrawString(200,510-15,"4) Three consecutive sixes will result in loss of turn and all his numbers in that turn will be discarded.",colors[BLACK]);
    DrawString(200,490-20,"5) A piece moves in a clockwise direction around the track given by the number thrown.",colors[BLACK]);
    DrawString(200,470-25,"6) If a piece lands on a piece of a different color, the piece jumped upon is returned to its starting circle.",colors[BLACK]);
    DrawString(200,450-30,"7) An extra turn is given to the player that removes the opponent's piece",colors[BLACK]);
    DrawString(200,430-35,"8) If a piece lands upon a piece of the same color, this forms a block.",colors[BLACK]);
    DrawString(220,410-40,"This block cannot be passed or landed on by any opposing piece.",colors[BLACK]);
    DrawString(200,390-45,"9) When a piece has circumnavigated the board, it proceeds up the home column.",colors[BLACK]);
    DrawString(200,370-50,"10) A player is not be allowed to enter into his Home column until he has removed at least one opposing piece.",colors[BLACK]);
    DrawString(200,350-55,"11) A piece can only be moved onto the home triangle by an exact throw.",colors[BLACK]);
    DrawString(200,330-60,"12) An extra turn is given to the player whose piece makes it to the home triangle.",colors[BLACK]);
    DrawString(200,310-65,"13) The first person to move all 4 pieces into the home triangle wins.",colors[BLACK]);
    DrawString(200,290-70,"14) Scoring criteria:",colors[BLACK]);
    DrawString(250,270-75,"a) A player receives 1 point for each square crossed.",colors[BLACK]);
    DrawString(250,250-80,"b) A player receives 2 points for creating a block.",colors[BLACK]);
    DrawString(250,230-85,"c) A player receives 10 points if removes an opponent's piece.",colors[BLACK]);
    DrawString(250,210-90,"d) A player receives 15 points if moves a piece into the home column.",colors[BLACK]);
    glutPostRedisplay();
}

void window5() // this function is used to display the instructions on how to play the game
{
    DrawStringHead(550,600,"INSTRUCTIONS",colors[BLACK]);
    DrawString(200,570,"1) Each player will roll the dice by using the spacebar key",colors[BLACK]);
    DrawString(200,550-5,"2) If dice rolls 6, the player will be given an extra roll which will also be done using the spacebar key.",colors[BLACK]);
    DrawString(200,530-10,"3) A player will select the piece to be moved based on its character using 'a', 'b', 'c', or 'd' keys.",colors[BLACK]);
    DrawString(200,510-15,"4) If there is no possible move, the player may press 'n' to move the turn to the next player",colors[BLACK]);
    DrawString(200,490-20,"5) Press Esc to return to the main menu",colors[BLACK]);
    glutPostRedisplay();
}

void updateLeaderboardArraysFromFile(string leaderboardNames[],string leaderboardScores[]) // updates the arrays from the file highscore.txt
{
    ifstream leaderboard;
    leaderboard.open("highscores.txt");
    for(int i=0;i<10;i++)
    {
        leaderboard >> leaderboardNames[i] >> leaderboardScores[i];
    }
    /*for(int x=0;x<10;x++)
    {
        cout<<leaderboardNames[x]<<" "<<leaderboardScores[x]<<endl;
    }*/
    leaderboard.close();
}

void window6() // this function displays the leaderboard
{
    string leaderboardNames[10]; // stores leaderboardnames in string array
    string leaderboardScores[10]; // stores leaderboardscores in string array
    updateLeaderboardArraysFromFile(leaderboardNames,leaderboardScores);
    DrawStringHead(350+200,500,"LEADERBOARD",colors[BLACK]);
    for(int i=0;i<10;i++)
    {
        DrawString(350+200,460-(i*30),leaderboardNames[i],colors[BLACK]);
        DrawString(480+200,460-(i*30),leaderboardScores[i],colors[BLACK]);
    }
    glutPostRedisplay();
}

void drawDiceForFirstRolls(int diceNum, int index) // draws dices for first rolls
{
    if(index==0)
    {
        //    DrawString(250+(0*200),250,playerNames[0],colors[BLACK]);
        DrawRoundRect(1120-870, 600-230, 44, 44, colors[SANDY_BROWN], 10);
        if(diceNum==1)
        {
            DrawCircle(1120+22-870, 600+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==2)
        {
            DrawCircle(1120+10-5+22-870, 600+10-5+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+5+22-870, 600-10+5+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==3)
        {
            DrawCircle(1120+22-870, 600+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10+22-870, 600+10+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+22-870, 600-10+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==4)
        {
            DrawCircle(1120+10-3+22-870, 600+10-3+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+3+22-870, 600-10+3+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10-3+22-15-870, 600+10-3+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+3+22+15-870, 600-10+3+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==5)
        {
            DrawCircle(1120+22-870, 600+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10+22-870, 600+10+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+22-870, 600-10+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+22-870, 600+10+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10+22-870, 600-10+22-230, 5, colors[BLACK]);
        }
        else //if diceNum==6
        {
            DrawCircle(1120+10-3+22-15-1-870, 600+10-3+22+5-230, 5, colors[BLACK]); // top left
            DrawCircle(1120+10-3+22+1-870, 600+10-3+22+5-230, 5, colors[BLACK]); // top right
            DrawCircle(1120-10+3+22-1-870, 600-10+5+22+5-230, 5, colors[BLACK]); // middle left
            DrawCircle(1120-10+3+22+15+1-870, 600-10+5+22+5-230, 5, colors[BLACK]); // middle right
            DrawCircle(1120-10+3+22-1-870, 600-10+3+22-5-230, 5, colors[BLACK]); // bottom left
            DrawCircle(1120-10+3+22+15+1-870, 600-10+3+22-5-230, 5, colors[BLACK]); // bottom right
        }
    }
    if(index==1)
    {
        DrawRoundRect(1120-670, 600-230, 44, 44, colors[SANDY_BROWN], 10);
        if(diceNum==1)
        {
            DrawCircle(1120+22-670, 600+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==2)
        {
            DrawCircle(1120+10-5+22-670, 600+10-5+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+5+22-670, 600-10+5+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==3)
        {
            DrawCircle(1120+22-670, 600+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10+22-670, 600+10+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+22-670, 600-10+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==4)
        {
            DrawCircle(1120+10-3+22-670, 600+10-3+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+3+22-670, 600-10+3+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10-3+22-15-670, 600+10-3+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+3+22+15-670, 600-10+3+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==5)
        {
            DrawCircle(1120+22-670, 600+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10+22-670, 600+10+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+22-670, 600-10+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+22-670, 600+10+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10+22-670, 600-10+22-230, 5, colors[BLACK]);
        }
        else //if diceNum==6
        {
            DrawCircle(1120+10-3+22-15-1-670, 600+10-3+22+5-230, 5, colors[BLACK]); // top left
            DrawCircle(1120+10-3+22+1-670, 600+10-3+22+5-230, 5, colors[BLACK]); // top right
            DrawCircle(1120-10+3+22-1-670, 600-10+5+22+5-230, 5, colors[BLACK]); // middle left
            DrawCircle(1120-10+3+22+15+1-670, 600-10+5+22+5-230, 5, colors[BLACK]); // middle right
            DrawCircle(1120-10+3+22-1-670, 600-10+3+22-5-230, 5, colors[BLACK]); // bottom left
            DrawCircle(1120-10+3+22+15+1-670, 600-10+3+22-5-230, 5, colors[BLACK]); // bottom right
        }
    }
    if(index==2)
    {
        DrawRoundRect(1120-470, 600-230, 44, 44, colors[SANDY_BROWN], 10);
        if(diceNum==1)
        {
            DrawCircle(1120+22-470, 600+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==2)
        {
            DrawCircle(1120+10-5+22-470, 600+10-5+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+5+22-470, 600-10+5+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==3)
        {
            DrawCircle(1120+22-470, 600+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10+22-470, 600+10+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+22-470, 600-10+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==4)
        {
            DrawCircle(1120+10-3+22-470, 600+10-3+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+3+22-470, 600-10+3+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10-3+22-15-470, 600+10-3+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+3+22+15-470, 600-10+3+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==5)
        {
            DrawCircle(1120+22-470, 600+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10+22-470, 600+10+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+22-470, 600-10+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+22-470, 600+10+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10+22-470, 600-10+22-230, 5, colors[BLACK]);
        }
        else //if diceNum==6
        {
            DrawCircle(1120+10-3+22-15-1-470, 600+10-3+22+5-230, 5, colors[BLACK]); // top left
            DrawCircle(1120+10-3+22+1-470, 600+10-3+22+5-230, 5, colors[BLACK]); // top right
            DrawCircle(1120-10+3+22-1-470, 600-10+5+22+5-230, 5, colors[BLACK]); // middle left
            DrawCircle(1120-10+3+22+15+1-470, 600-10+5+22+5-230, 5, colors[BLACK]); // middle right
            DrawCircle(1120-10+3+22-1-470, 600-10+3+22-5-230, 5, colors[BLACK]); // bottom left
            DrawCircle(1120-10+3+22+15+1-470, 600-10+3+22-5-230, 5, colors[BLACK]); // bottom right
        }
    }
    if(index==3)
    {
        DrawRoundRect(1120-270, 600-230, 44, 44, colors[SANDY_BROWN], 10);
        if(diceNum==1)
        {
            DrawCircle(1120+22-270, 600+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==2)
        {
            DrawCircle(1120+10-5+22-270, 600+10-5+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+5+22-270, 600-10+5+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==3)
        {
            DrawCircle(1120+22-270, 600+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10+22-270, 600+10+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+22-270, 600-10+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==4)
        {
            DrawCircle(1120+10-3+22-270, 600+10-3+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+3+22-270, 600-10+3+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10-3+22-15-270, 600+10-3+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+3+22+15-270, 600-10+3+22-230, 5, colors[BLACK]);
        }
        else if(diceNum==5)
        {
            DrawCircle(1120+22-270, 600+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10+22-270, 600+10+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+22-270, 600-10+22-230, 5, colors[BLACK]);
            DrawCircle(1120-10+22-270, 600+10+22-230, 5, colors[BLACK]);
            DrawCircle(1120+10+22-270, 600-10+22-230, 5, colors[BLACK]);
        }
        else //if diceNum==6
        {
            DrawCircle(1120+10-3+22-15-1-270, 600+10-3+22+5-230, 5, colors[BLACK]); // top left
            DrawCircle(1120+10-3+22+1-270, 600+10-3+22+5-230, 5, colors[BLACK]); // top right
            DrawCircle(1120-10+3+22-1-270, 600-10+5+22+5-230, 5, colors[BLACK]); // middle left
            DrawCircle(1120-10+3+22+15+1-270, 600-10+5+22+5-230, 5, colors[BLACK]); // middle right
            DrawCircle(1120-10+3+22-1-270, 600-10+3+22-5-230, 5, colors[BLACK]); // bottom left
            DrawCircle(1120-10+3+22+15+1-270, 600-10+3+22-5-230, 5, colors[BLACK]); // bottom right
        }
    }
    //DrawSquare( 1140-20 , 620-20 , 40, colors[SANDY_BROWN]);
    /*DrawRoundRect(1120, 600-230, 44, 44, colors[SANDY_BROWN], 10);
    if(diceNum==1)
    {
        DrawCircle(1120+22, 600+22-230, 5, colors[BLACK]);
    }
    else if(diceNum==2)
    {
        DrawCircle(1120+10-5+22, 600+10-5+22-230, 5, colors[BLACK]);
        DrawCircle(1120-10+5+22, 600-10+5+22-230, 5, colors[BLACK]);
    }
    else if(diceNum==3)
    {
        DrawCircle(1120+22, 600+22-230, 5, colors[BLACK]);
        DrawCircle(1120+10+22, 600+10+22-230, 5, colors[BLACK]);
        DrawCircle(1120-10+22, 600-10+22-230, 5, colors[BLACK]);
    }
    else if(diceNum==4)
    {
        DrawCircle(1120+10-3+22, 600+10-3+22-230, 5, colors[BLACK]);
        DrawCircle(1120-10+3+22, 600-10+3+22-230, 5, colors[BLACK]);
        DrawCircle(1120+10-3+22-15, 600+10-3+22-230, 5, colors[BLACK]);
        DrawCircle(1120-10+3+22+15, 600-10+3+22-230, 5, colors[BLACK]);
    }
    else if(diceNum==5)
    {
        DrawCircle(1120+22, 600+22-230, 5, colors[BLACK]);
        DrawCircle(1120+10+22, 600+10+22-230, 5, colors[BLACK]);
        DrawCircle(1120-10+22, 600-10+22-230, 5, colors[BLACK]);
        DrawCircle(1120-10+22, 600+10+22-230, 5, colors[BLACK]);
        DrawCircle(1120+10+22, 600-10+22-230, 5, colors[BLACK]);
    }
    else //if diceNum==6
    {
        DrawCircle(1120+10-3+22-15-1, 600+10-3+22+5-230, 5, colors[BLACK]); // top left
        DrawCircle(1120+10-3+22+1, 600+10-3+22+5-230, 5, colors[BLACK]); // top right
        DrawCircle(1120-10+3+22-1, 600-10+5+22+5-230, 5, colors[BLACK]); // middle left
        DrawCircle(1120-10+3+22+15+1, 600-10+5+22+5-230, 5, colors[BLACK]); // middle right
        DrawCircle(1120-10+3+22-1, 600-10+3+22-5-230, 5, colors[BLACK]); // bottom left
        DrawCircle(1120-10+3+22+15+1, 600-10+3+22-5-230, 5, colors[BLACK]); // bottom right
    }*/
    glutPostRedisplay();
}

void window7() //this is to assign turn with respect to the highest roll
{
    /* test data
    players=2;
    playerNames[0]="ABC";
    playerNames[1]="CED";
    playerColors[0]=2;
    playerColors[1]=3;
    */
    static int firstRolls[4]={};
    DrawString(400,650,"The player with the highest roll will get the first turn",colors[BLACK]);
    DrawString(550,620,"Roll dice one by one",colors[BLACK]);
    static int i=0;
    static int rollAgain=0; // will be used to show roll again message if more than one highest rolls occur
    if(rollAgain==1)
    {
        DrawString(580,590,"Roll again",colors[BLACK]);
    }
    DrawString(250+(0*200),250,playerNames[0],colors[BLACK]); // printing player names that exist
    DrawString(250+(1*200),250,playerNames[1],colors[BLACK]);
    DrawString(250+(2*200),250,playerNames[2],colors[BLACK]);
    DrawString(250+(3*200),250,playerNames[3],colors[BLACK]);
    if(firstRolls[0]!=0) // printing dices that are rolled ONLY
    {
        drawDiceForFirstRolls(firstRolls[0], 0);
    }
    if(firstRolls[1]!=0)
    {
        drawDiceForFirstRolls(firstRolls[1], 1);
    }
    if(firstRolls[2]!=0)
    {
        drawDiceForFirstRolls(firstRolls[2], 2);
    }
    if(firstRolls[3]!=0)
    {
        drawDiceForFirstRolls(firstRolls[3], 3);
    }
    if(i<players)
    {
        if(dice!=0)
        {
            firstRolls[i]=dice; // to record first rolls
            dice=0;
            i++;
        }
    }
    else // i==players now
    {
        // now finding the highest roll
        static int counter=0; /// to find the number of players who rolled the highest number
        static int highestRoll=0;
        static int index; // to keep track of the color which rolls highest
        for(int i=0;i<players;i++)
        {
            if(firstRolls[i]>highestRoll)
            {
                highestRoll=firstRolls[i];
                index=i;
            }
        }
        for(int j=0;j<players;j++)
        {
            if(highestRoll==firstRolls[j])
            {
                counter++;
            }
        }
        if(counter==1) // there was only one highest roll
        {
            turn=playerColors[index]; // first turn goes to the player who rolled highest
            window=8;
        }
        else // more than 1 highest rolls occured. the players should now roll again
        {
            rollAgain=1;
            counter=0;
            highestRoll=0;
            i=0;
            for(int x=0;x<players;x++)
            {
                firstRolls[x]=0; // they will have to roll again
            }
        }
    }
    glutPostRedisplay();
}

// window8 is inside GameDisplay function

void updateLeaderboard() // updates the leaderboard if any one beats the highscores
{
    /*test data
    playerNames[1]="ABC";
    playerColors[1]=3;
    score[3]=500;*/
    string leaderboardNames[10]; // stores leaderboardnames in string array
    int leaderboardScores[10]; // stores leaderboardscores in INT array
    ifstream leaderboard;
    leaderboard.open("highscores.txt");
    for(int i=0;i<10;i++)
    {
        leaderboard >> leaderboardNames[i] >> leaderboardScores[i];
    }
    leaderboard.close();
    // now the data has been stored in the arrays
    int lowestScore=leaderboardScores[0];
    int index=0;; // index of the lowest score
    for(static int j=0;j<4;j++)
    {
        for(int i=0;i<10;i++)
        {
            if(leaderboardScores[i]<lowestScore) // this finds lowest score in the array of scores
            {
                lowestScore=leaderboardScores[i];
                index=i;
            }
        } // this loop should run to check for every player's score(e.g if player 2 scores more than player 1 and player 1 is at lowest, then it should be updated with player 2)
        if(score[j]>lowestScore)
        {
            for(int x=0;x<4;x++)
            {
                if(playerColors[x]==j)
                {
                    leaderboardNames[index]=playerNames[x]; // replaces the index of name array with lowest score
                    leaderboardScores[index]=score[j]; // replaces the index of score array with lowest score
                }
            }
            index=0;
            lowestScore=leaderboardScores[0];
        }
    }
    // now the arrays have been updated.
    ofstream leaderboardUpdate;
    leaderboardUpdate.open("highscores.txt");
    for(int k=0;k<10;k++)
    {
        leaderboardUpdate << leaderboardNames[k] << " " << leaderboardScores[k] << endl; // updates the highscore.txt file
    }
    leaderboardUpdate.close();
}

string intToString(int intVal) // this function converts int numbers to string
{
    string stringVal;
    int tempNum=intVal;
    int digits=0;
    do{
        tempNum/=10;
        digits++;
    }while(tempNum!=0);
    int m=0;
    do{
        tempNum=(intVal/pow(10,digits-1))-(10*static_cast<int>(intVal/pow(10,digits)));
        stringVal+=tempNum+48;
        digits--;
        m++;
    }while(digits!=0);
    // no comments as all this logic was created using the help of pen and paper
    // should just know that it converts any int value to string
    return stringVal;
}

void window9() // this function displays the end game (GAME OVER) window
{
    /*test data
    players=2;
    playerNames[0]="ABC";
    playerNames[1]="DEF";
    playerColors[0]=0;
    playerColors[1]=3;
    score[0]=300;
    score[3]=19;*/
    DrawStringHead(550,500,"GAME OVER",colors[BLACK]);
    for(int i=0;i<players;i++)
    {
        string tempScore; // a temporary variable to store scores to display them in string form
        if(playerColors[i]==0) // yellow
        {
            DrawString(550,460,playerNames[i],colors[BLACK]);
            tempScore=intToString(score[0]);
            DrawString(650,460,tempScore,colors[BLACK]);
        }
        if(playerColors[i]==1) //blue
        {
            DrawString(550,430,playerNames[i],colors[BLACK]);
            tempScore=intToString(score[1]);
            DrawString(650,430,tempScore,colors[BLACK]);
            //DrawString(650,460,score[1],colors[BLACK]);
        }
        if(playerColors[i]==2) // red
        {
            DrawString(550,400,playerNames[i],colors[BLACK]);
            tempScore=intToString(score[2]);
            DrawString(650,400,tempScore,colors[BLACK]);
            //DrawString(650,460,score[2],colors[BLACK]);
        }
        if(playerColors[i]==3) // green
        {
            DrawString(550,370,playerNames[i],colors[BLACK]);
            tempScore=intToString(score[3]);
            DrawString(650,370,tempScore,colors[BLACK]);
            //DrawString(650,460,score[3],colors[BLACK]);
        }
    }
    DrawString(550,340,"Press Enter to view leaderboard",colors[BLACK]);
    glutPostRedisplay();
}

void writeTurn() // this function writes the colour whose turn it is
{
    if(turn==0)
    {
        DrawString( 1085, 450, "Yellow's Turn", colors[BLACK]);
    }
    else if(turn==1)
    {
        DrawString( 1093, 450, "Blue's Turn", colors[BLACK]);
    }
    else if(turn==2)
    {
        DrawString( 1098, 450, "Red's Turn", colors[BLACK]);
    }
    else //turn==3
    {
        DrawString( 1090, 450, "Green's Turn", colors[BLACK]);
    }
    glutPostRedisplay();
}

void drawPieces(); //prototype

void drawBoard() // this function draws the board
{
    DrawLine( 1000 , 0 ,  1000 , 720-1 , 10 , colors[BLACK] ); // seperation line
	DrawRoundRect(241-0, 101-0, 520, 520, colors[SANDY_BROWN], 20); //outer board
	DrawRectangle(240-1+20-2, 100-1+20-2, 520-40+4, 520-40+4, colors[BLACK]); // line
	DrawRectangle(240-1+20, 100-1+20, 520-40, 520-40, colors[BURLY_WOOD]); // inner board

	// THROUGHOUT THE DISPLAY, 32x32 IS THE SIZE OF A SINGLE BLOCK ON WHICH A PIECE MOVES
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<3;j++)
		{
			DrawSquare( 432+20+(j*32)+1 , 100+20+(i*32)+1 ,32,colors[BLACK]);
			DrawSquare( 432+20+(j*32)+1 , 100+20+(i*32)+1 ,30,colors[WHITE]);
		}
	}//vertical line of boxes


	for(int i=0;i<15;i++)
	{
		for(int j=0;j<3;j++)
		{
			DrawSquare( 240+20+(i*32)+1 , 292+20+(j*32)+1 ,32,colors[BLACK]);
			DrawSquare( 240+20+(i*32)+1 , 292+20+(j*32)+1 ,30,colors[WHITE]);
		}
	}//horizontal line of boxes

	//horizontal line
	DrawLine(240 + 20, 292 + 20, 240 + 20 + 480, 292 + 20, 2, colors[BLACK]);
	//vertical lines
	DrawLine(240 + 20+192, 100 + 20-1, 240 + 20+192, 100 + 20+480, 2, colors[BLACK]);
	//drawing homes and their pieces
	/*DrawCircle(240+20+96, 100+20+96, 65, colors[OLIVE]); // actually yellow
	DrawCircle(240+20+96-24, 100+20+96-24, 12, colors[DARK_GOLDEN_ROD]); // darker yellow shade one can say
	DrawCircle(240+20+96-24, 100+20+96+24, 12, colors[DARK_GOLDEN_ROD]);
	DrawCircle(240+20+96+24, 100+20+96+24, 12, colors[DARK_GOLDEN_ROD]);
	DrawCircle(240+20+96+24, 100+20+96-24, 12, colors[DARK_GOLDEN_ROD]);

	DrawCircle(240+20+96+292, 100+20+96, 65, colors[LIME]); // lighter green shade
	DrawCircle(240+20+96+292-24, 100+20+96-24, 12, colors[GREEN]);
	DrawCircle(240+20+96+292-24, 100+20+96+24, 12, colors[GREEN]);
	DrawCircle(240+20+96+292+24, 100+20+96+24, 12, colors[GREEN]);
	DrawCircle(240+20+96+292+24, 100+20+96-24, 12, colors[GREEN]);

	DrawCircle(240+20+96, 100+20+96+292, 65, colors[BLUE]); // lighter blue shade
	DrawCircle(240+20+96-24, 100+20+96+292-24, 12, colors[DARK_BLUE]);
	DrawCircle(240+20+96-24, 100+20+96+292+24, 12, colors[DARK_BLUE]);
	DrawCircle(240+20+96+24, 100+20+96+292+24, 12, colors[DARK_BLUE]);
	DrawCircle(240+20+96+24, 100+20+96+292-24, 12, colors[DARK_BLUE]);

	DrawCircle(240+20+96+292, 100+20+96+292, 65, colors[RED]);
	DrawCircle(240+20+96+292-24, 100+20+96+292-24, 12, colors[FIREBRICK]);// darker red shade
	DrawCircle(240+20+96+292-24, 100+20+96+292+24, 12, colors[FIREBRICK]);
	DrawCircle(240+20+96+292+24, 100+20+96+292+24, 12, colors[FIREBRICK]);
	DrawCircle(240+20+96+292+24, 100+20+96+292-24, 12, colors[FIREBRICK]);*/

    DrawCircle(240+20+96, 100+20+96, 65, colors[OLIVE]); // actually yellow
	DrawCircle(240+20+96-24, 100+20+96-24, 12, colors[MISTY_ROSE]); // white( if the piece has left the starting circle)
	DrawCircle(240+20+96-24, 100+20+96+24, 12, colors[MISTY_ROSE]);
	DrawCircle(240+20+96+24, 100+20+96+24, 12, colors[MISTY_ROSE]);
	DrawCircle(240+20+96+24, 100+20+96-24, 12, colors[MISTY_ROSE]);

	DrawCircle(240+20+96+292, 100+20+96, 65, colors[LIME]);
	DrawCircle(240+20+96+292-24, 100+20+96-24, 12, colors[MISTY_ROSE]);
	DrawCircle(240+20+96+292-24, 100+20+96+24, 12, colors[MISTY_ROSE]);
	DrawCircle(240+20+96+292+24, 100+20+96+24, 12, colors[MISTY_ROSE]);
	DrawCircle(240+20+96+292+24, 100+20+96-24, 12, colors[MISTY_ROSE]);

	DrawCircle(240+20+96, 100+20+96+292, 65, colors[BLUE]);
	DrawCircle(240+20+96-24, 100+20+96+292-24, 12, colors[MISTY_ROSE]);
	DrawCircle(240+20+96-24, 100+20+96+292+24, 12, colors[MISTY_ROSE]);
	DrawCircle(240+20+96+24, 100+20+96+292+24, 12, colors[MISTY_ROSE]);
	DrawCircle(240+20+96+24, 100+20+96+292-24, 12, colors[MISTY_ROSE]);

	DrawCircle(240+20+96+292, 100+20+96+292, 65, colors[RED]);
	DrawCircle(240+20+96+292-24, 100+20+96+292-24, 12, colors[MISTY_ROSE]);
	DrawCircle(240+20+96+292-24, 100+20+96+292+24, 12, colors[MISTY_ROSE]);
	DrawCircle(240+20+96+292+24, 100+20+96+292+24, 12, colors[MISTY_ROSE]);
	DrawCircle(240+20+96+292+24, 100+20+96+292-24, 12, colors[MISTY_ROSE]);
	// now drawing yellow boxes
	DrawSquare( 240+20+192+1 , 100+20+32 ,30,colors[OLIVE]);
	for(int i=1;i<6;i++)
	{
		DrawSquare( 240+20+32+192+1 , 100+20+(32*i) ,30,colors[OLIVE]);
	}
	// now drawing green boxes
	DrawSquare( 240+20+192+1+(7*32) , 100+20+(6*32) ,30,colors[LIME]);
	for(int i=7;i>2;i--)
	{
		DrawSquare( 240+20+192+1+(i*32) , 100+20+(7*32) ,30,colors[LIME]);
	}
	// now drawing red boxes
	DrawSquare(240+20+(8*32),100+20+(13*32),31,colors[RED]);
	for(int i=13;i>8;i--)
	{
		DrawSquare(240+20+(7*32),100+20+(i*32),31,colors[RED]);
	}
	// now drawing blue boxes
	DrawSquare(240+20+32,100+20+(8*32),31,colors[BLUE]);
	for(int i=1;i<6;i++)
	{
		DrawSquare(240+20+(i*32),100+20+(7*32),31,colors[BLUE]);
	}
	// now drawing central triangles
	DrawTriangle(240+20+(32*6), 100+20+(32*6), 240+20+(32*9), 100+20+(32*6), 240+20+(32*7.5), 100+20+(32*7.5), colors[OLIVE]);
	DrawTriangle(240+20+(32*9), 100+20+(32*6), 240+20+(32*9), 100+20+(32*9), 240+20+(32*7.5), 100+20+(32*7.5), colors[LIME]);
	DrawTriangle(240+20+(32*6), 100+20+(32*9), 240+20+(32*9), 100+20+(32*9), 240+20+(32*7.5), 100+20+(32*7.5), colors[RED]);
	DrawTriangle(240+20+(32*6), 100+20+(32*6), 240+20+(32*6), 100+20+(32*9), 240+20+(32*7.5), 100+20+(32*7.5), colors[BLUE]);
	// now drawing additional safe spots(other than coloured ones)
	DrawSquare(240+20+(32*8),100+20+(2*32),31,colors[DIM_GRAY]);//yellow
	DrawSquare(240+20+(32*6),100+20+(12*32),31,colors[DIM_GRAY]);//red
	DrawSquare(240+20+(32*2),100+20+(6*32),31,colors[DIM_GRAY]);//blue
	DrawSquare(240+20+(32*12),100+20+(8*32),31,colors[DIM_GRAY]);//green

    drawPieces();
    glutPostRedisplay();
}

void drawPiecesStart() // this function draws the pieces ONLY when they are in the starting circle
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(i==0) // 1st player
            {
                if(piece[i][j]==-1) // i is the player, j is the piece number, -1 means the piece is locked
                {
                    if(j==0) // 1st piece
                    {
                        DrawCircle(240+20+96-24, 100+20+96-24, 12, colors[DARK_GOLDEN_ROD]); // darker yellow shade one can say
                        DrawString(240+20+96-24-5,100+20+96-24-5 , "a", colors[BLACK]);
                    }
                    else if(j==1) // 2nd piece
                    {
                        DrawCircle(240+20+96-24, 100+20+96+24, 12, colors[DARK_GOLDEN_ROD]);
                        DrawString(240+20+96-24-5,100+20+96+24-5 , "b", colors[BLACK]);
                    }
                    else if(j==2) // 3rd piece
                    {
                        DrawCircle(240+20+96+24, 100+20+96+24, 12, colors[DARK_GOLDEN_ROD]);
                        DrawString(240+20+96+24-5,100+20+96+24-5 , "c", colors[BLACK]);
                    }
                    else
                    {
                        DrawCircle(240+20+96+24, 100+20+96-24, 12, colors[DARK_GOLDEN_ROD]);
                        DrawString(240+20+96+24-5,100+20+96-24-5 , "d", colors[BLACK]);
                    }
                }
            }
            else if(i==1) // blue
            {
                if(piece[i][j]==-1)
                {
                    if(j==0)
                    {
                        //DrawCircle(240+20+96+292-24, 100+20+96-24, 12, colors[DARK_BLUE]);
                        //DrawString(240+20+96+292-24-5,100+20+96-24-5 , "a", colors[BLACK]);
                        DrawCircle(240+20+96-24, 100+20+96+292-24, 12, colors[DARK_BLUE]);// darker red shade
                        DrawString(240+20+96-24-5,100+20+96+292-24-5 , "a", colors[BLACK]);
                    }
                    else if(j==1)
                    {
                        //DrawCircle(240+20+96+292-24, 100+20+96+24, 12, colors[DARK_BLUE]);
                        //DrawString(240+20+96+292-24-5,100+20+96+24-5 , "b", colors[BLACK]);
                        DrawCircle(240+20+96-24, 100+20+96+292+24, 12, colors[DARK_BLUE]);
                        DrawString(240+20+96-24-5,100+20+96+292+24-5 , "b", colors[BLACK]);
                    }
                    else if(j==2)
                    {
                        //DrawCircle(240+20+96+292+24, 100+20+96+24, 12, colors[DARK_BLUE]);
                        //DrawString(240+20+96+292+24-5,100+20+96+24-5 , "c", colors[BLACK]);
                        DrawCircle(240+20+96+24, 100+20+96+292+24, 12, colors[DARK_BLUE]);
                        DrawString(240+20+96+24-5,100+20+96+292+24-5 , "c", colors[BLACK]);
                    }
                    else
                    {
                        //DrawCircle(240+20+96+292+24, 100+20+96-24, 12, colors[DARK_BLUE]);
                        //DrawString(240+20+96+292+24-5,100+20+96-24-5 , "d", colors[BLACK]);
                        DrawCircle(240+20+96+24, 100+20+96+292-24, 12, colors[DARK_BLUE]);
                        DrawString(240+20+96+24-5,100+20+96+292-24-5 , "d", colors[BLACK]);
                    }
                }
            }
            else if(i==2) //red
            {
                if(piece[i][j]==-1)
                {
                    if(j==0)
                    {
                        DrawCircle(240+20+96+292-24, 100+20+96+292-24, 12, colors[FIREBRICK]);// darker red shade
                        DrawString(240+20+96+292-24-5,100+20+96+292-24-5 , "a", colors[BLACK]);
                        //DrawCircle(240+20+96-24, 100+20+96+292-24, 12, colors[FIREBRICK]);
                        //DrawString(240+20+96-24-5,100+20+96+292-24-5 , "a", colors[BLACK]);
                    }
                    else if(j==1)
                    {
                        DrawCircle(240+20+96+292-24, 100+20+96+292+24, 12, colors[FIREBRICK]);
                        DrawString(240+20+96+292-24-5,100+20+96+292+24-5 , "b", colors[BLACK]);
                        //DrawCircle(240+20+96-24, 100+20+96+292+24, 12, colors[FIREBRICK]);
                        //DrawString(240+20+96-24-5,100+20+96+292+24-5 , "b", colors[BLACK]);
                    }
                    else if(j==2)
                    {
                        //DrawCircle(240+20+96+24, 100+20+96+292+24, 12, colors[FIREBRICK]);
                        //DrawString(240+20+96+24-5,100+20+96+292+24-5 , "c", colors[BLACK]);
                        DrawCircle(240+20+96+292+24, 100+20+96+292+24, 12, colors[FIREBRICK]);
                        DrawString(240+20+96+292+24-5,100+20+96+292+24-5 , "c", colors[BLACK]);
                    }
                    else
                    {
                        DrawCircle(240+20+96+292+24, 100+20+96+292-24, 12, colors[FIREBRICK]);
                        DrawString(240+20+96+292+24-5,100+20+96+292-24-5 , "d", colors[BLACK]);
                        //DrawCircle(240+20+96+24, 100+20+96+292-24, 12, colors[FIREBRICK]);
                        //DrawString(240+20+96+24-5,100+20+96+292-24-5 , "d", colors[BLACK]);
                    }
                }
            }
            else //green
            {
                if(piece[i][j]==-1)
                {
                    if(j==0)
                    {
                        DrawCircle(240+20+96+292-24, 100+20+96-24, 12, colors[GREEN]);
                        DrawString(240+20+96+292-24-5,100+20+96-24-5 , "a", colors[BLACK]);
                        //DrawCircle(240+20+96-24, 100+20+96+292-24, 12, colors[FIREBRICK]);
                        //DrawString(240+20+96-24-5,100+20+96+292-24-5 , "a", colors[BLACK]);
                    }
                    else if(j==1)
                    {
                        DrawCircle(240+20+96+292-24, 100+20+96+24, 12, colors[GREEN]);
                        DrawString(240+20+96+292-24-5,100+20+96+24-5 , "b", colors[BLACK]);
                        //DrawCircle(240+20+96-24, 100+20+96+292+24, 12, colors[FIREBRICK]);
                        //DrawString(240+20+96-24-5,100+20+96+292+24-5 , "b", colors[BLACK]);
                    }
                    else if(j==2)
                    {
                        //DrawCircle(240+20+96+24, 100+20+96+292+24, 12, colors[FIREBRICK]);
                        //DrawString(240+20+96+24-5,100+20+96+292+24-5 , "c", colors[BLACK]);
                        DrawCircle(240+20+96+292+24, 100+20+96+24, 12, colors[GREEN]);
                        DrawString(240+20+96+292+24-5,100+20+96+24-5 , "c", colors[BLACK]);
                    }
                    else
                    {
                        DrawCircle(240+20+96+292+24, 100+20+96-24, 12, colors[GREEN]);
                        DrawString(240+20+96+292+24-5,100+20+96-24-5 , "d", colors[BLACK]);
                        //DrawCircle(240+20+96+24, 100+20+96+292-24, 12, colors[FIREBRICK]);
                        //DrawString(240+20+96+24-5,100+20+96+292-24-5 , "d", colors[BLACK]);
                    }
                }
            }
        }
    }
    glutPostRedisplay();
}

void drawPieces() // this function draws the pieces ONLY when they are NOT in the starting circle
{
    //drawing position of pieces
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(piece[i][j]!=-1 && piece[i][j]!=-2)
            {
                if(i==0)
                {
                    DrawCircle(squares[piece[i][j]][0], squares[piece[i][j]][1],12, colors[DARK_GOLDEN_ROD]);
                    if(j==0)
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "a", colors[BLACK]);
                    }
                    else if(j==1)
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "b", colors[BLACK]);
                    }
                    else if(j==2)
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "c", colors[BLACK]);
                    }
                    else
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "d", colors[BLACK]);
                    }
                }
                else if(i==1)
                {
                    DrawCircle(squares[piece[i][j]][0], squares[piece[i][j]][1],12, colors[DARK_BLUE]);
                    if(j==0)
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "a", colors[BLACK]);
                    }
                    else if(j==1)
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "b", colors[BLACK]);
                    }
                    else if(j==2)
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "c", colors[BLACK]);
                    }
                    else
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "d", colors[BLACK]);
                    }

                }
                else if(i==2)
                {
                    DrawCircle(squares[piece[i][j]][0], squares[piece[i][j]][1],12, colors[FIREBRICK]);
                    if(j==0)
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "a", colors[BLACK]);
                    }
                    else if(j==1)
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "b", colors[BLACK]);
                    }
                    else if(j==2)
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "c", colors[BLACK]);
                    }
                    else
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "d", colors[BLACK]);
                    }
                }
                else //i==3
                {
                    DrawCircle(squares[piece[i][j]][0], squares[piece[i][j]][1],12, colors[GREEN]);
                    if(j==0)
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "a", colors[BLACK]);
                    }
                    else if(j==1)
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "b", colors[BLACK]);
                    }
                    else if(j==2)
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "c", colors[BLACK]);
                    }
                    else
                    {
                        DrawString(squares[piece[i][j]][0]-5, squares[piece[i][j]][1]-5, "d", colors[BLACK]);
                    }
                }
            }
        }
    }
    glutPostRedisplay();
}

void drawPiecesHomeTriangle() // this function draws only those pieces which are in home triangle
{
    //pieces are difficult to be seen visually when overlapping so in home triangle every piece has its unique place where it goes
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(piece[i][j]==-2) //piece is in home triangle
            {
                if(i==0) // yellow
                {
                    if(j==0)
                    {
                        DrawCircle(240+20+(32*7)+16, 100+20+(32*7), 12, colors[DARK_GOLDEN_ROD]);
                        DrawString(240+20+(32*7)+16-5, 100+20+(32*7)-5, "a", colors[BLACK]);
                    }
                    else if(j==1)
                    {
                        DrawCircle(240+20+(32*6)+16+12, 100+20+(32*6)+12, 12, colors[DARK_GOLDEN_ROD]);
                        DrawString(240+20+(32*6)+16+12-5, 100+20+(32*6)+12-5, "b", colors[BLACK]);
                    }
                    else if(j==2)
                    {
                        DrawCircle(240+20+(32*6)+16+12+20, 100+20+(32*6)+12, 12, colors[DARK_GOLDEN_ROD]);
                        DrawString(240+20+(32*6)+16+12-5+20, 100+20+(32*6)+12-5, "c", colors[BLACK]);
                    }
                    else //if j==3
                    {
                        DrawCircle(240+20+(32*6)+16+12+40, 100+20+(32*6)+12, 12, colors[DARK_GOLDEN_ROD]);
                        DrawString(240+20+(32*6)+16+12-5+40, 100+20+(32*6)+12-5, "d", colors[BLACK]);
                    }
                }
                else if(i==1) //BLUE
                {
                    if(j==0)
                    {
                        DrawCircle(240+20+(32*6)+16+13, 100+20+(32*6)+12+38, 12, colors[DARK_BLUE]);
                        DrawString(240+20+(32*6)+16+13-5, 100+20+(32*6)+12+38-5, "a", colors[BLACK]);
                    }
                    else if(j==1)
                    {
                        DrawCircle(240+20+(32*6)+13, 100+20+(32*6)+12+38+20, 12, colors[DARK_BLUE]);
                        DrawString(240+20+(32*6)+13-5, 100+20+(32*6)+12+38-5+20, "b", colors[BLACK]);
                    }
                    else if(j==2)
                    {
                        DrawCircle(240+20+(32*6)+13, 100+20+(32*6)+12+38, 12, colors[DARK_BLUE]);
                        DrawString(240+20+(32*6)+13-5, 100+20+(32*6)+12+38-5, "c", colors[BLACK]);
                    }
                    else //if j==3
                    {
                        DrawCircle(240+20+(32*6)+13, 100+20+(32*6)+12+38-20, 12, colors[DARK_BLUE]);
                        DrawString(240+20+(32*6)+13-5, 100+20+(32*6)+12+38-5-20, "d", colors[BLACK]);
                    }
                }
                else if(i==2)//red
                {
                    if(j==0)
                    {
                        DrawCircle(240+20+(32*7)+16, 100+20+(32*8), 12, colors[FIREBRICK]);
                        DrawString(240+20+(32*7)+16-5, 100+20+(32*8)-5, "a", colors[BLACK]);
                    }
                    else if(j==1)
                    {
                        DrawCircle(240+20+(32*6)+16+12, 100+20+(32*8)+12+10, 12, colors[FIREBRICK]);
                        DrawString(240+20+(32*6)+16+12-5, 100+20+(32*8)+12-5+10, "b", colors[BLACK]);
                    }
                    else if(j==2)
                    {
                        DrawCircle(240+20+(32*6)+16+12+20, 100+20+(32*8)+12+10, 12, colors[FIREBRICK]);
                        DrawString(240+20+(32*6)+16+12-5+20, 100+20+(32*8)+12+10-5, "c", colors[BLACK]);
                    }
                    else //if j==3
                    {
                        DrawCircle(240+20+(32*6)+16+12+40, 100+20+(32*8)+12+10, 12, colors[FIREBRICK]);
                        DrawString(240+20+(32*6)+16+12-5+40, 100+20+(32*8)+12+10-5, "d", colors[BLACK]);
                    }
                }
                else //i==3 green
                {
                    if(j==0)
                    {
                        DrawCircle(240+20+(32*6)+16+13+37, 100+20+(32*6)+12+38, 12, colors[GREEN]);
                        DrawString(240+20+(32*6)+16+13-5+37, 100+20+(32*6)+12+38-5, "a", colors[BLACK]);
                    }
                    else if(j==1)
                    {
                        DrawCircle(240+20+(32*7)+13+40, 100+20+(32*6)+12+38+20, 12, colors[GREEN]);
                        DrawString(240+20+(32*7)+13-5+40, 100+20+(32*6)+12+38-5+20, "b", colors[BLACK]);
                    }
                    else if(j==2)
                    {
                        DrawCircle(240+20+(32*7)+13+40, 100+20+(32*6)+12+38, 12, colors[GREEN]);
                        DrawString(240+20+(32*7)+13-5+40, 100+20+(32*6)+12+38-5, "c", colors[BLACK]);
                    }
                    else //if j==3
                    {
                        DrawCircle(240+20+(32*7)+13+40, 100+20+(32*6)+12+38-20, 12, colors[GREEN]);
                        DrawString(240+20+(32*7)+13-5+40, 100+20+(32*6)+12+38-5-20, "d", colors[BLACK]);
                    }
                }
            }
        }
    }
    glutPostRedisplay();
}

void drawDice(int diceNum) // this function creates the animated dice using the argument of the dice number passed to it
{
    //DrawSquare( 1140-20 , 620-20 , 40, colors[SANDY_BROWN]);
    DrawRoundRect(1120, 600-230, 44, 44, colors[SANDY_BROWN], 10);
    if(diceNum==1)
    {
        DrawCircle(1120+22, 600+22-230, 5, colors[BLACK]);
    }
    else if(diceNum==2)
    {
        DrawCircle(1120+10-5+22, 600+10-5+22-230, 5, colors[BLACK]);
        DrawCircle(1120-10+5+22, 600-10+5+22-230, 5, colors[BLACK]);
    }
    else if(diceNum==3)
    {
        DrawCircle(1120+22, 600+22-230, 5, colors[BLACK]);
        DrawCircle(1120+10+22, 600+10+22-230, 5, colors[BLACK]);
        DrawCircle(1120-10+22, 600-10+22-230, 5, colors[BLACK]);
    }
    else if(diceNum==4)
    {
        DrawCircle(1120+10-3+22, 600+10-3+22-230, 5, colors[BLACK]);
        DrawCircle(1120-10+3+22, 600-10+3+22-230, 5, colors[BLACK]);
        DrawCircle(1120+10-3+22-15, 600+10-3+22-230, 5, colors[BLACK]);
        DrawCircle(1120-10+3+22+15, 600-10+3+22-230, 5, colors[BLACK]);
    }
    else if(diceNum==5)
    {
        DrawCircle(1120+22, 600+22-230, 5, colors[BLACK]);
        DrawCircle(1120+10+22, 600+10+22-230, 5, colors[BLACK]);
        DrawCircle(1120-10+22, 600-10+22-230, 5, colors[BLACK]);
        DrawCircle(1120-10+22, 600+10+22-230, 5, colors[BLACK]);
        DrawCircle(1120+10+22, 600-10+22-230, 5, colors[BLACK]);
    }
    else //if diceNum==6
    {
        DrawCircle(1120+10-3+22-15-1, 600+10-3+22+5-230, 5, colors[BLACK]); // top left
        DrawCircle(1120+10-3+22+1, 600+10-3+22+5-230, 5, colors[BLACK]); // top right
        DrawCircle(1120-10+3+22-1, 600-10+5+22+5-230, 5, colors[BLACK]); // middle left
        DrawCircle(1120-10+3+22+15+1, 600-10+5+22+5-230, 5, colors[BLACK]); // middle right
        DrawCircle(1120-10+3+22-1, 600-10+3+22-5-230, 5, colors[BLACK]); // bottom left
        DrawCircle(1120-10+3+22+15+1, 600-10+3+22-5-230, 5, colors[BLACK]); // bottom right
    }
    glutPostRedisplay();
}

void writeNames() // this function writes names of players who are playing next to their color
{
    for(int i=0;i<players;i++)
    {
        if(playerColors[i]==0) // yellow
        {
            for(int x=0;playerNames[i][x]!='\0';x++) // divides playerNames[i] single string to characters .
            {// '\0' refers to the NULL character. It is present at the end of string so it lets know that the string has ended
                string playerNamesStringArray[15]; // this string is being used as a character array to store characters of playerNames[i] string 1 by 1
                playerNamesStringArray[x]=playerNames[i][x];
                DrawString(450+(x*18),50,playerNamesStringArray[x],colors[BLACK]); // this function then displays those characters 1 by 1 as the for loop runs
            }
            //DrawString(450,50,playerNames[i],colors[BLACK]);
        }
        if(playerColors[i]==1) //blue
        {
            for(int x=0;playerNames[i][x]!='\0';x++)
            {
                string playerNamesStringArray[15];
                playerNamesStringArray[x]=playerNames[i][x];
                DrawString(120,100+520-220-(x*18),playerNamesStringArray[x],colors[BLACK]);
            }
        }
        if(playerColors[i]==2) // red
        {
            for(int x=0;playerNames[i][x]!='\0';x++)
            {
                string playerNamesStringArray[15];
                playerNamesStringArray[x]=playerNames[i][x];
                DrawString(450+(x*18),100+520+50,playerNamesStringArray[x],colors[BLACK]);
            }
            //DrawString(450,100+520+50,playerNames[i],colors[BLACK]);
        }
        if(playerColors[i]==3) // green
        {
            for(int x=0;playerNames[i][x]!='\0';x++)
            {
                string playerNamesStringArray[15];
                playerNamesStringArray[x]=playerNames[i][x];
                DrawString(240+520+120,100+520-220-(x*18),playerNamesStringArray[x],colors[BLACK]);
            }
        }
    }
    glutPostRedisplay();
}

void homeColumnStatus() // this function displays a cross on home columns if they are closed
{
    for(int i=0;i<4;i++)
    {
        if(status[i]!=-1) // either playing or won
        {
            if(killCount[i]==0)
            {
                //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
            	//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );
                if(i==0)
                {
                    DrawCircle(484+16,152+16,10,colors[SANDY_BROWN]);
                    DrawCircle(484+16,152+16,7,colors[OLIVE]);
                }
                if(i==1)
                {
                    DrawCircle(308,360,10,colors[SANDY_BROWN]);
                    DrawCircle(308,360,7,colors[BLUE]);
                }
                if(i==2)
                {
                    DrawCircle(484+16,552,10,colors[SANDY_BROWN]);
                    DrawCircle(484+16,552,7,colors[RED]);
                }
                if(i==3)
                {
                    DrawCircle(692,360,10,colors[SANDY_BROWN]);
                    DrawCircle(692,360,7,colors[LIME]);
                }
            }
            else
            {
                // display nothing
            }
        }
    }
}

int checkForHomeColumn(int diceNum) //check if the piece is eligible and also can move to home triangle
{
    if(turn==0 && killCount[turn]>0) // if kills are zero then the piece will move along the board instead of going in the home column
    {
        if(piece[turn][keyPressed-97]+dices[diceNum]>50)
        {
            piece[turn][keyPressed-97]+=49+dices[diceNum]; // this logic was created with the help of pen and paper
            return 1;
        }
    }
    else if(turn==1 && killCount[turn]>0)
    {
        if(piece[turn][keyPressed-97]+dices[diceNum]>11 && piece[turn][keyPressed-97]<=11)
        {
            piece[turn][keyPressed-97]+=94+dices[diceNum]; // this logic was created with the help of pen and paper
            return 1;
        }
    }
    else if(turn==2 && killCount[turn]>0)
    {
        if(piece[turn][keyPressed-97]+dices[diceNum]>24 && piece[turn][keyPressed-97]<=24)
        {
            piece[turn][keyPressed-97]+=87+dices[diceNum]; // this logic was created with the help of pen and paper
            return 1;
        }
    }
    else if(turn==3 && killCount[turn]>0)
    {
        if(piece[turn][keyPressed-97]+dices[diceNum]>37 && piece[turn][keyPressed-97]<=37)
        {
            piece[turn][keyPressed-97]+=80+dices[diceNum]; // this logic was created with the help of pen and paper
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

void checkForKill() // check if a piece is killing another piece
{
    //piece[turn][keyPressed-97]
    if(teamMode==0)
    {
        for(int i=0;i<4;i++) // colours
        {
            if(turn!=i) // not the same colors
            {
                for(int j=0;j<4;j++) // pieces
                {
                    if((piece[turn][keyPressed-97]==piece[i][j]) && piece[i][j]!=-1 && piece[i][j]!=-2 && piece[i][j]!=0 && piece[i][j]!=8 && piece[i][j]!=13 &&  piece[i][j]!=21 && piece[i][j]!=26 && piece[i][j]!=34 && piece[i][j]!=39 && piece[i][j]!=47 && piece[i][j]<52) // all these are safe spots where a piece cannot be removed
                    {// one piece kills another
                        killCount[turn]++;
                        score[turn]+=10;
                        piece[i][j]=-1; // move back to the starting circle
                        turn--; // gives the player another turn
                    }
                }
            }
        }
    }
    if(teamMode==1) // teammates are unable to remove each other's pieces from the board
    {
        for(int i=0;i<4;i++) // colours
        {
            if(turn<=1)
            {
                if(turn!=i && i!=turn+2) // not the same colors or same teams
                {
                    for(int j=0;j<4;j++) // pieces
                    {
                        if((piece[turn][keyPressed-97]==piece[i][j]) && piece[i][j]!=-1 && piece[i][j]!=-2 && piece[i][j]!=0 && piece[i][j]!=8 && piece[i][j]!=13 &&  piece[i][j]!=21 && piece[i][j]!=26 && piece[i][j]!=34 && piece[i][j]!=39 && piece[i][j]!=47 && piece[i][j]<52) // all these are safe spots where a piece cannot be removed
                        {// one piece kills another
                            killCount[turn]++;
                            score[turn]+=10;
                            piece[i][j]=-1; // move back to the starting circle
                            turn--; // gives the player another turn
                        }
                    }
                }
            }
            if(turn>=2)
            {
                if(turn!=i && i!=turn-2) // not the same colors or same teams
                {
                    for(int j=0;j<4;j++) // pieces
                    {
                        if((piece[turn][keyPressed-97]==piece[i][j]) && piece[i][j]!=-1 && piece[i][j]!=-2 && piece[i][j]!=0 && piece[i][j]!=8 && piece[i][j]!=13 &&  piece[i][j]!=21 && piece[i][j]!=26 && piece[i][j]!=34 && piece[i][j]!=39 && piece[i][j]!=47 && piece[i][j]<52) // all these are safe spots where a piece cannot be removed
                        {// one piece kills another
                            killCount[turn]++;
                            score[turn]+=10;
                            piece[i][j]=-1; // move back to the starting circle
                            turn--; // gives the player another turn
                        }
                    }
                }
            }
        }
    }
}

void blocksFormed() // checks if a block is formed and displays it
{
    if(teamMode==0)
    {
        for(int i=0;i<4;i++) //turns
        {
            for(int j=0;j<4;j++)
            {
                for(int k=0;k<4;k++)
                {
                    if((piece[i][j]==piece[i][k] && j!=k) && piece[i][j]!=-1 && piece[i][j]!=-2 && piece[i][j]!=0 && piece[i][j]!=8 && piece[i][j]!=13 &&  piece[i][j]!=21 && piece[i][j]!=26 && piece[i][j]!=34 && piece[i][j]!=39 && piece[i][j]!=47 && piece[i][j]<100) // other pieces
                    {
                        if(i==0)
                        {
                            DrawSquare(squares[piece[i][j]][0]-13,squares[piece[i][j]][1]-13,26,colors[DARK_GOLDEN_ROD]);
                            if (j==0)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(j==1)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);

                            }
                            else if(j==2)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else //if j==3
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                            if(k==0)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(k==1)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);
                            }
                            else if(k==2)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else // if k==3
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                        }
                        else if(i==1)
                        {
                            DrawSquare(squares[piece[i][j]][0]-13,squares[piece[i][j]][1]-13,26,colors[DARK_BLUE]);
                            if (j==0)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(j==1)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);

                            }
                            else if(j==2)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else //if j==3
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                            if(k==0)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(k==1)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);
                            }
                            else if(k==2)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else // if k==3
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                        }
                        else if(i==2)
                        {
                            DrawSquare(squares[piece[i][j]][0]-13,squares[piece[i][j]][1]-13,26,colors[FIREBRICK]);
                            if (j==0)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(j==1)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);

                            }
                            else if(j==2)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else //if j==3
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                            if(k==0)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(k==1)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);
                            }
                            else if(k==2)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else // if k==3
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                        }
                        else //if i==4
                        {
                            DrawSquare(squares[piece[i][j]][0]-13,squares[piece[i][j]][1]-13,26,colors[GREEN]);
                            if (j==0)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(j==1)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);

                            }
                            else if(j==2)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else //if j==3
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                            if(k==0)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(k==1)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);
                            }
                            else if(k==2)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else // if k==3
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                        }
                        /*if (j==0)
                        {
                            DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                        }
                        else if(j==1)
                        {
                            DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);

                        }
                        else if(j==2)
                        {
                            DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                        }
                        else //if j==3
                        {
                            DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                        }
                        if(k==0)
                        {
                            DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                        }
                        else if(k==1)
                        {
                            DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);
                        }
                        else if(k==2)
                        {
                            DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                        }
                        else // if k==3
                        {
                            DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                        }*/
                        block[piece[i][j]]=1;
                    }
                }
            }
        }
    }
    if(teamMode==1)
    {
        for(int i=0;i<4;i++) // this for loop is for same colored block
        {
            for(int j=0;j<4;j++)
            {
                for(int k=0;k<4;k++)
                {
                    if((piece[i][j]==piece[i][k] && j!=k) && piece[i][j]!=-1 && piece[i][j]!=-2 && piece[i][j]!=0 && piece[i][j]!=8 && piece[i][j]!=13 &&  piece[i][j]!=21 && piece[i][j]!=26 && piece[i][j]!=34 && piece[i][j]!=39 && piece[i][j]!=47 && piece[i][j]<100) // other pieces
                    {
                        if(i==0)
                        {
                            DrawSquare(squares[piece[i][j]][0]-13,squares[piece[i][j]][1]-13,26,colors[DARK_GOLDEN_ROD]);
                            if (j==0)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(j==1)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);

                            }
                            else if(j==2)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else //if j==3
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                            if(k==0)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(k==1)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);
                            }
                            else if(k==2)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else // if k==3
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                        }
                        else if(i==1)
                        {
                            DrawSquare(squares[piece[i][j]][0]-13,squares[piece[i][j]][1]-13,26,colors[DARK_BLUE]);
                            if (j==0)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(j==1)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);

                            }
                            else if(j==2)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else //if j==3
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                            if(k==0)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(k==1)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);
                            }
                            else if(k==2)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else // if k==3
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                        }
                        else if(i==2)
                        {
                            DrawSquare(squares[piece[i][j]][0]-13,squares[piece[i][j]][1]-13,26,colors[FIREBRICK]);
                            if (j==0)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(j==1)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);

                            }
                            else if(j==2)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else //if j==3
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                            if(k==0)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(k==1)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);
                            }
                            else if(k==2)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else // if k==3
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                        }
                        else //if i==4
                        {
                            DrawSquare(squares[piece[i][j]][0]-13,squares[piece[i][j]][1]-13,26,colors[GREEN]);
                            if (j==0)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(j==1)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);

                            }
                            else if(j==2)
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else //if j==3
                            {
                                DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                            if(k==0)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                            }
                            else if(k==1)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);
                            }
                            else if(k==2)
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                            }
                            else // if k==3
                            {
                                DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                            }
                        }
                        block[piece[i][j]]=1;
                    }
                }
            }
        }
        for(int i=0;i<4;i++) // this for loop is for different coloured blocks
        {
            for(int j=0;j<4;j++)
            {
                for(int k=0;k<4;k++)
                {
                    if(i<=1)
                    {
                        if((piece[i][j]==piece[i+2][k]) && piece[i][j]!=-1 && piece[i][j]!=-2 && piece[i][j]!=0 && piece[i][j]!=8 && piece[i][j]!=13 &&  piece[i][j]!=21 && piece[i][j]!=26 && piece[i][j]!=34 && piece[i][j]!=39 && piece[i][j]!=47 && piece[i][j]<100) // other pieces
                        {
                            if(i==0)
                            {
                                DrawSquare(squares[piece[i][j]][0]-13,squares[piece[i][j]][1]-13,26,colors[FIREBRICK]);
                                DrawRectangle(squares[piece[i][j]][0]-13,squares[piece[i][j]][1]-13,26/2,26,colors[DARK_GOLDEN_ROD]); // tested this logic. if you overlap a half rectangle on a square, it looks like there are 2 half rectangles
                                if (j==0)
                                {
                                    DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                                }
                                else if(j==1)
                                {
                                    DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);
                                }
                                else if(j==2)
                                {
                                    DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                                }
                                else //if j==3
                                {
                                    DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                                }
                                if(k==0)
                                {
                                    DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                                }
                                else if(k==1)
                                {
                                    DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);
                                }
                                else if(k==2)
                                {
                                    DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                                }
                                else // if k==3
                                {
                                    DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                                }
                            }
                            else if(i==1)
                            {
                                DrawSquare(squares[piece[i][j]][0]-13,squares[piece[i][j]][1]-13,26,colors[GREEN]);
                                DrawRectangle(squares[piece[i][j]][0]-13,squares[piece[i][j]][1]-13,26/2,26,colors[DARK_BLUE]);
                                //DrawSquare(squares[piece[i][j]][0]-13,squares[piece[i][j]][1]-13,26,colors[DARK_BLUE]);
                                if (j==0)
                                {
                                    DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                                }
                                else if(j==1)
                                {
                                    DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);

                                }
                                else if(j==2)
                                {
                                    DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                                }
                                else //if j==3
                                {
                                    DrawString(squares[piece[i][j]][0]-12,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                                }
                                if(k==0)
                                {
                                    DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "a", colors[BLACK]);
                                }
                                else if(k==1)
                                {
                                    DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "b", colors[BLACK]);
                                }
                                else if(k==2)
                                {
                                    DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "c", colors[BLACK]);
                                }
                                else // if k==3
                                {
                                    DrawString(squares[piece[i][j]][0]+1,squares[piece[i][j]][1]-13+5 , "d", colors[BLACK]);
                                }
                            }
                            block[piece[i][j]]=1;
                        }
                    }
                }
            }
        }
    }
    glutPostRedisplay();
}

void moveFromBlock(int diceNum) // if a piece moves from the block, this function breaks the block
{
    if(piece[turn][keyPressed-97]-dices[diceNum]<0) // the block was before the 0th position
    {
        if(block[52+piece[turn][keyPressed-97]-dices[diceNum]]==1) // this logic was created with the help of pen and paper
        {
            block[52+piece[turn][keyPressed-97]-dices[diceNum]]=0;
            score[turn]+=2;
        }
    }
    else if(piece[turn][keyPressed-97]-dices[diceNum]>=0) // the block was after 0th position(i.e. yellow's starting square)
    {
        if(block[piece[turn][keyPressed-97]-dices[diceNum]]==1)
        {
            block[piece[turn][keyPressed-97]-dices[diceNum]]=0;
            score[turn]+=2;
        }
    }
}

int colorAtBlock(int x) // returns the number of color at the block(0,1,2,3)
{
    for(int a=0;a<4;a++)
    {
        for(int b=0;b<4;b++)
        {
            if(piece[a][b]==x)
            {
                return a;
            }
        }
    }
}

int checkForBlock(int diceNum) // checks whether a block exists in the path of the piece
{
    // returns 0 if the pathway is open. returns 1 if the pathway is closed by a block
    int blockCounter=0;
    if(teamMode==0)
    {
        if(piece[turn][keyPressed-97]+dices[diceNum]<52)
        {
            for(int i=piece[turn][keyPressed-97]+1;i<=(piece[turn][keyPressed-97]+dices[diceNum]);i++)
            {
                if(block[i]==1 && colorAtBlock(i)!=turn) // colorAtBlock(i)!=turn allows only the same color to cross the block
                {
                    blockCounter++;
                }
            }
        }
        else if((piece[turn][keyPressed-97]+dices[diceNum])>=52 && (piece[turn][keyPressed-97]+dices[diceNum])<100)
        {
            for(int i=piece[turn][keyPressed-97]+1;i<=(piece[turn][keyPressed-97]+dices[diceNum]);i++)
            {
                if(i<52)
                {
                    if(block[i]==1 && colorAtBlock(i)!=turn) // colorAtBlock(i)!=turn allows only the same color to cross the block
                    {
                        blockCounter++;
                    }
                }
                if(i>=52)
                {
                    if(block[i-52]==1 && colorAtBlock(i-52)!=turn) // colorAtBlock(i-52)!=turn allows only the same color to cross the block
                    {
                        blockCounter++;
                    }
                }
            } // this function started creating issues when pieces crossed yellow's home cirlcle. so all this logic was created to remove those issues
        }
    }
    if(teamMode==1)
    {
        if(turn<=1)
        {
            if(piece[turn][keyPressed-97]+dices[diceNum]<52)
            {
                for(int i=piece[turn][keyPressed-97]+1;i<=(piece[turn][keyPressed-97]+dices[diceNum]);i++)
                {
                    if(block[i]==1 && colorAtBlock(i)!=turn && colorAtBlock(i)!=(turn+2)) // colorAtBlock(i)!=turn allows only the same color to cross the block
                    {
                        blockCounter++;
                    }
                }
            }
            else if((piece[turn][keyPressed-97]+dices[diceNum])>=52 && (piece[turn][keyPressed-97]+dices[diceNum])<100)
            {
                for(int i=piece[turn][keyPressed-97]+1;i<=(piece[turn][keyPressed-97]+dices[diceNum]);i++)
                {
                    if(i<52)
                    {
                        if(block[i]==1 && colorAtBlock(i)!=turn && colorAtBlock(i)!=(turn+2)) // colorAtBlock(i)!=turn allows only the same color to cross the block
                        {
                            blockCounter++;
                        }
                    }
                    if(i>=52)
                    {
                        if(block[i-52]==1 && colorAtBlock(i-52)!=turn && colorAtBlock(i-52)!=(turn+2)) // colorAtBlock(i-52)!=turn allows only the same color to cross the block
                        {
                            blockCounter++;
                        }
                    }
                } // this function started creating issues when pieces crossed yellow's home cirlcle. so all this logic was created to remove those issues
            }
        }
        if(turn>=2)
        {
            if(piece[turn][keyPressed-97]+dices[diceNum]<52)
            {
                for(int i=piece[turn][keyPressed-97]+1;i<=(piece[turn][keyPressed-97]+dices[diceNum]);i++)
                {
                    if(block[i]==1 && colorAtBlock(i)!=turn && colorAtBlock(i)!=(turn-2)) // colorAtBlock(i)!=turn allows only the same color to cross the block
                    {
                        blockCounter++;
                    }
                }
            }
            else if((piece[turn][keyPressed-97]+dices[diceNum])>=52 && (piece[turn][keyPressed-97]+dices[diceNum])<100)
            {
                for(int i=piece[turn][keyPressed-97]+1;i<=(piece[turn][keyPressed-97]+dices[diceNum]);i++)
                {
                    if(i<52)
                    {
                        if(block[i]==1 && colorAtBlock(i)!=(turn-2) && colorAtBlock(i)!=(turn-2)) // colorAtBlock(i)!=turn allows only the same color to cross the block
                        {
                            blockCounter++;
                        }
                    }
                    if(i>=52)
                    {
                        if(block[i-52]==1 && colorAtBlock(i-52)!=(turn-2) && colorAtBlock(i-52)!=(turn-2)) // colorAtBlock(i-52)!=turn allows only the same color to cross the block
                        {
                            blockCounter++;
                        }
                    }
                } // this function started creating issues when pieces crossed yellow's home cirlcle. so all this logic was created to remove those issues
            }
        }
    }
    if(blockCounter>0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkForHomeTriangle_Six() //this function puts the piece in home triangle ONLY when the piece is out of the home column on the first block before it. As then the piece needs a 6 to move to home triangle
{
    if(turn == 0 && killCount[turn]>0 && piece[turn][keyPressed-97]==50 )
    {
        return 1;
    }
    if(turn == 1 && killCount[turn]>0 && piece[turn][keyPressed-97]==11 )
    {
        return 1;
    }
    if(turn == 2 && killCount[turn]>0 && piece[turn][keyPressed-97]==24 )
    {
        return 1;
    }
    if(turn == 3 && killCount[turn]>0 && piece[turn][keyPressed-97]==37 )
    {
        return 1;
    }
    return 0; // did not move to home triangle( actually it will move along the board agiain)
}

void limitHomeThrow(int diceNum) // a piece enters home triangle only on exact throw
{
    if(turn ==0)
    {
        if(piece[turn][keyPressed-97]+dices[diceNum]==105)
        {
            piece[turn][keyPressed-97]=-2;
            score[turn]+=dices[diceNum];
            turn--; // gives an extra turn
        }
        else if(piece[turn][keyPressed-97]+dices[diceNum]<105)
        {
            piece[turn][keyPressed-97]+=dices[diceNum];
            score[turn]+=dices[diceNum];
        }
        else
        {
            // do nothing
        }
    }
    else if(turn == 1)
    {
        if(piece[turn][keyPressed-97]+dices[diceNum]==111)
        {
            piece[turn][keyPressed-97]=-2;
            score[turn]+=dices[diceNum];
            turn--; // gives an extra turn
        }
        else if(piece[turn][keyPressed-97]+dices[diceNum]<111)
        {
            piece[turn][keyPressed-97]+=dices[diceNum];
            score[turn]+=dices[diceNum];
        }
        else
        {
            // do nothing
        }
    }
    else if(turn == 2)
    {
        if(piece[turn][keyPressed-97]+dices[diceNum]==117)
        {
            piece[turn][keyPressed-97]=-2;
            score[turn]+=dices[diceNum];
            turn--; // gives an extra turn
        }
        else if(piece[turn][keyPressed-97]+dices[diceNum]<117)
        {
            piece[turn][keyPressed-97]+=dices[diceNum];
            score[turn]+=dices[diceNum];
        }
        else
        {
            // do nothing
        }
    }
    else if(turn == 3)
    {
        if(piece[turn][keyPressed-97]+dices[diceNum]==123)
        {
            piece[turn][keyPressed-97]=-2;
            score[turn]+=dices[diceNum];
            turn--; // gives an extra turn
        }
        else if(piece[turn][keyPressed-97]+dices[diceNum]<123)
        {
            piece[turn][keyPressed-97]+=dices[diceNum];
            score[turn]+=dices[diceNum];
        }
        else
        {
            // do nothing
        }
    }
}

void checkForWinners() // checks if there are any winners after the last turn and gives winner status=1;
{
    for(int i=0;i<4;i++)
    {
        int count=0;
        for(int j=0;j<4;j++)
        {
            if(piece[i][j]==-2) // in home triangle
            {
                count++;
            }
        }
        if(count==4) // all 4 pieces in home triangle
        {
            status[i]=1; // the COLOR i has won
        }
    }
}

void setStatus() // this function only runs once to set the status of playing colors to zero
{
    static int i=0;
    if(i==0)
    {
        for(int x=0;x<4;x++)
        {
            if(playerColors[x]>=0)
            {
                status[playerColors[x]]=0; // in play
            }
        }
        i++;
    }
}

void nextTurn() // this function selects which color is getting the next turn
{
    for(;;)
    {
        if(turn >= 4) // there is no 4th player. turn statrts from zero again
        {
            turn=0;
        }
        if (status[turn]==1 || status[turn]==-1) // turn++ if a color is disabled or has won
        {
            turn++;
            continue;
        }
        else
        {
            break;
        }
    }
}

//TeamMode functions are created starting from here
/// FOR TURN+2(This means when 0th and 1st players gives theur turn to 2nd and 3rd player respectively)
// therefore all these functions are named TeamPlus

int checkForHomeColumnTeamPlus(int diceNum) //check if the piece is eligible and also can move to home triangle
{
    if(turn+2==0 && killCount[turn+2]>0) // if kills are zero then the piece will move along the board instead of going in the home column
    {
        if(piece[turn+2][keyPressed-97]+dices[diceNum]>50)
        {
            piece[turn+2][keyPressed-97]+=49+dices[diceNum]; // this logic was created with the help of pen and paper
            return 1;
        }
    }
    else if(turn+2==1 && killCount[turn+2]>0)
    {
        if(piece[turn+2][keyPressed-97]+dices[diceNum]>11 && piece[turn+2][keyPressed-97]<=11)
        {
            piece[turn+2][keyPressed-97]+=94+dices[diceNum]; // this logic was created with the help of pen and paper
            return 1;
        }
    }
    else if(turn+2==2 && killCount[turn+2]>0)
    {
        if(piece[turn+2][keyPressed-97]+dices[diceNum]>24 && piece[turn+2][keyPressed-97]<=24)
        {
            piece[turn+2][keyPressed-97]+=87+dices[diceNum]; // this logic was created with the help of pen and paper
            return 1;
        }
    }
    else if(turn+2==3 && killCount[turn+2]>0)
    {
        if(piece[turn+2][keyPressed-97]+dices[diceNum]>37 && piece[turn+2][keyPressed-97]<=37)
        {
            piece[turn+2][keyPressed-97]+=80+dices[diceNum]; // this logic was created with the help of pen and paper
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

void checkForKillTeamPlus() // check if a piece is killing another piece
{
    //piece[turn][keyPressed-97]
        for(int i=0;i<4;i++) // colours
        {
            if(turn+2<=1)
            {
                if(turn+2!=i && i!=turn+2+2) // not the same colors or same teams
                {
                    for(int j=0;j<4;j++) // pieces
                    {
                        if((piece[turn+2][keyPressed-97]==piece[i][j]) && piece[i][j]!=-1 && piece[i][j]!=-2 && piece[i][j]!=0 && piece[i][j]!=8 && piece[i][j]!=13 &&  piece[i][j]!=21 && piece[i][j]!=26 && piece[i][j]!=34 && piece[i][j]!=39 && piece[i][j]!=47 && piece[i][j]<52) // all these are safe spots where a piece cannot be removed
                        {// one piece kills another
                            killCount[turn+2]++;
                            score[turn+2]+=10;
                            piece[i][j]=-1; // move back to the starting circle
                            turn--; // gives the player another turn
                        }
                    }
                }
            }
            if(turn+2>=2)
            {
                if(turn+2!=i && i!=turn+2-2) // not the same colors or same teams
                {
                    for(int j=0;j<4;j++) // pieces
                    {
                        if((piece[turn+2][keyPressed-97]==piece[i][j]) && piece[i][j]!=-1 && piece[i][j]!=-2 && piece[i][j]!=0 && piece[i][j]!=8 && piece[i][j]!=13 &&  piece[i][j]!=21 && piece[i][j]!=26 && piece[i][j]!=34 && piece[i][j]!=39 && piece[i][j]!=47 && piece[i][j]<52) // all these are safe spots where a piece cannot be removed
                        {// one piece kills another
                            killCount[turn+2]++;
                            score[turn+2]+=10;
                            piece[i][j]=-1; // move back to the starting circle
                            turn--; // gives the player another turn
                        }
                    }
                }
            }
        }
}

void moveFromBlockTeamPlus(int diceNum) // if a piece moves from the block, this function breaks the block
{
    if(piece[turn+2][keyPressed-97]-dices[diceNum]<0) // the block was before the 0th position
    {
        if(block[52+piece[turn+2][keyPressed-97]-dices[diceNum]]==1) // this logic was created with the help of pen and paper
        {
            block[52+piece[turn+2][keyPressed-97]-dices[diceNum]]=0;
            score[turn+2]+=2;
        }
    }
    else if(piece[turn+2][keyPressed-97]-dices[diceNum]>=0) // the block was after 0th position(i.e. yellow's starting square)
    {
        if(block[piece[turn+2][keyPressed-97]-dices[diceNum]]==1)
        {
            block[piece[turn+2][keyPressed-97]-dices[diceNum]]=0;
            score[turn+2]+=2;
        }
    }
}

int checkForBlockTeamPlus(int diceNum) // checks whether a block exists in the path of the piece
{
    // returns 0 if the pathway is open. returns 1 if the pathway is closed by a block
    int blockCounter=0;
        if(turn+2<=1)
        {
            if(piece[turn+2][keyPressed-97]+dices[diceNum]<52)
            {
                for(int i=piece[turn+2][keyPressed-97]+1;i<=(piece[turn+2][keyPressed-97]+dices[diceNum]);i++)
                {
                    if(block[i]==1 && colorAtBlock(i)!=turn+2 && colorAtBlock(i)!=(turn+2+2)) // colorAtBlock(i)!=turn allows only the same color to cross the block
                    {
                        blockCounter++;
                    }
                }
            }
            else if((piece[turn+2][keyPressed-97]+dices[diceNum])>=52 && (piece[turn+2][keyPressed-97]+dices[diceNum])<100)
            {
                for(int i=piece[turn+2][keyPressed-97]+1;i<=(piece[turn+2][keyPressed-97]+dices[diceNum]);i++)
                {
                    if(i<52)
                    {
                        if(block[i]==1 && colorAtBlock(i)!=turn+2 && colorAtBlock(i)!=(turn+2+2)) // colorAtBlock(i)!=turn+2 allows only the same color to cross the block
                        {
                            blockCounter++;
                        }
                    }
                    if(i>=52)
                    {
                        if(block[i-52]==1 && colorAtBlock(i-52)!=turn+2 && colorAtBlock(i-52)!=(turn+2+2)) // colorAtBlock(i-52)!=turn+2 allows only the same color to cross the block
                        {
                            blockCounter++;
                        }
                    }
                } // this function started creating issues when pieces crossed yellow's home cirlcle. so all this logic was created to remove those issues
            }
        }
        if(turn+2>=2)
        {
            if(piece[turn+2][keyPressed-97]+dices[diceNum]<52)
            {
                for(int i=piece[turn+2][keyPressed-97]+1;i<=(piece[turn+2][keyPressed-97]+dices[diceNum]);i++)
                {
                    if(block[i]==1 && colorAtBlock(i)!=turn+2 && colorAtBlock(i)!=(turn+2-2)) // colorAtBlock(i)!=turn+2 allows only the same color to cross the block
                    {
                        blockCounter++;
                    }
                }
            }
            else if((piece[turn+2][keyPressed-97]+dices[diceNum])>=52 && (piece[turn+2][keyPressed-97]+dices[diceNum])<100)
            {
                for(int i=piece[turn+2][keyPressed-97]+1;i<=(piece[turn+2][keyPressed-97]+dices[diceNum]);i++)
                {
                    if(i<52)
                    {
                        if(block[i]==1 && colorAtBlock(i)!=(turn+2-2) && colorAtBlock(i)!=(turn+2-2)) // colorAtBlock(i)!=turn+2 allows only the same color to cross the block
                        {
                            blockCounter++;
                        }
                    }
                    if(i>=52)
                    {
                        if(block[i-52]==1 && colorAtBlock(i-52)!=(turn+2-2) && colorAtBlock(i-52)!=(turn+2-2)) // colorAtBlock(i-52)!=turn+2 allows only the same color to cross the block
                        {
                            blockCounter++;
                        }
                    }
                } // this function started creating issues when pieces crossed yellow's home cirlcle. so all this logic was created to remove those issues
            }
        }
    if(blockCounter>0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkForHomeTriangle_SixTeamPlus() //this function puts the piece in home triangle ONLY when the piece is out of the home column on the first block before it. As then the piece needs a 6 to move to home triangle
{
    if(turn+2 == 0 && killCount[turn+2]>0 && piece[turn+2][keyPressed-97]==50 )
    {
        return 1;
    }
    if(turn+2 == 1 && killCount[turn+2]>0 && piece[turn+2][keyPressed-97]==11 )
    {
        return 1;
    }
    if(turn+2 == 2 && killCount[turn+2]>0 && piece[turn+2][keyPressed-97]==24 )
    {
        return 1;
    }
    if(turn+2 == 3 && killCount[turn+2]>0 && piece[turn+2][keyPressed-97]==37 )
    {
        return 1;
    }
    return 0; // did not move to home triangle( actually it will move along the board agiain)
}

void limitHomeThrowTeamPlus(int diceNum) // a piece enters home triangle only on exact throw
{
    if(turn+2 ==0)
    {
        if(piece[turn+2][keyPressed-97]+dices[diceNum]==105)
        {
            piece[turn+2][keyPressed-97]=-2;
            score[turn+2]+=dices[diceNum];
            turn--; // gives an extra turn
        }
        else if(piece[turn+2][keyPressed-97]+dices[diceNum]<105)
        {
            piece[turn+2][keyPressed-97]+=dices[diceNum];
            score[turn+2]+=dices[diceNum];
        }
        else
        {
            // do nothing
        }
    }
    else if(turn+2 == 1)
    {
        if(piece[turn+2][keyPressed-97]+dices[diceNum]==111)
        {
            piece[turn+2][keyPressed-97]=-2;
            score[turn+2]+=dices[diceNum];
            turn--; // gives an extra turn
        }
        else if(piece[turn+2][keyPressed-97]+dices[diceNum]<111)
        {
            piece[turn+2][keyPressed-97]+=dices[diceNum];
            score[turn+2]+=dices[diceNum];
        }
        else
        {
            // do nothing
        }
    }
    else if(turn+2 == 2)
    {
        if(piece[turn+2][keyPressed-97]+dices[diceNum]==117)
        {
            piece[turn+2][keyPressed-97]=-2;
            score[turn+2]+=dices[diceNum];
            turn--; // gives an extra turn
        }
        else if(piece[turn+2][keyPressed-97]+dices[diceNum]<117)
        {
            piece[turn+2][keyPressed-97]+=dices[diceNum];
            score[turn+2]+=dices[diceNum];
        }
        else
        {
            // do nothing
        }
    }
    else if(turn+2 == 3)
    {
        if(piece[turn+2][keyPressed-97]+dices[diceNum]==123)
        {
            piece[turn+2][keyPressed-97]=-2;
            score[turn+2]+=dices[diceNum];
            turn--; // gives an extra turn
        }
        else if(piece[turn+2][keyPressed-97]+dices[diceNum]<123)
        {
            piece[turn+2][keyPressed-97]+=dices[diceNum];
            score[turn+2]+=dices[diceNum];
        }
        else
        {
            // do nothing
        }
    }
}

////////////////////////////////////////////////
// FOR TURN-2 (This means when 2nd and 3rd players gives theur turn to 0th and 1st players respectively)
// therefore all these functions are named TeamMinus

int checkForHomeColumnTeamMinus(int diceNum) //check if the piece is eligible and also can move to home triangle
{
    if(turn-2==0 && killCount[turn-2]>0) // if kills are zero then the piece will move along the board instead of going in the home column
    {
        if(piece[turn-2][keyPressed-97]+dices[diceNum]>50)
        {
            piece[turn-2][keyPressed-97]+=49+dices[diceNum]; // this logic was created with the help of pen and paper
            return 1;
        }
    }
    else if(turn-2==1 && killCount[turn-2]>0)
    {
        if(piece[turn-2][keyPressed-97]+dices[diceNum]>11 && piece[turn-2][keyPressed-97]<=11)
        {
            piece[turn-2][keyPressed-97]+=94+dices[diceNum]; // this logic was created with the help of pen and paper
            return 1;
        }
    }
    else if(turn-2==2 && killCount[turn-2]>0)
    {
        if(piece[turn-2][keyPressed-97]+dices[diceNum]>24 && piece[turn-2][keyPressed-97]<=24)
        {
            piece[turn-2][keyPressed-97]+=87+dices[diceNum]; // this logic was created with the help of pen and paper
            return 1;
        }
    }
    else if(turn-2==3 && killCount[turn-2]>0)
    {
        if(piece[turn-2][keyPressed-97]+dices[diceNum]>37 && piece[turn-2][keyPressed-97]<=37)
        {
            piece[turn-2][keyPressed-97]+=80+dices[diceNum]; // this logic was created with the help of pen and paper
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

void checkForKillTeamMinus() // check if a piece is killing another piece
{
    //piece[turn][keyPressed-97]
        for(int i=0;i<4;i++) // colours
        {
            if(turn-2<=1)
            {
                if(turn-2!=i && i!=turn-2+2) // not the same colors or same teams
                {
                    for(int j=0;j<4;j++) // pieces
                    {
                        if((piece[turn-2][keyPressed-97]==piece[i][j]) && piece[i][j]!=-1 && piece[i][j]!=-2 && piece[i][j]!=0 && piece[i][j]!=8 && piece[i][j]!=13 &&  piece[i][j]!=21 && piece[i][j]!=26 && piece[i][j]!=34 && piece[i][j]!=39 && piece[i][j]!=47 && piece[i][j]<52) // all these are safe spots where a piece cannot be removed
                        {// one piece kills another
                            killCount[turn-2]++;
                            score[turn-2]+=10;
                            piece[i][j]=-1; // move back to the starting circle
                            turn--; // gives the player another turn
                        }
                    }
                }
            }
            if(turn-2>=2)
            {
                if(turn-2!=i && i!=turn-2-2) // not the same colors or same teams
                {
                    for(int j=0;j<4;j++) // pieces
                    {
                        if((piece[turn-2][keyPressed-97]==piece[i][j]) && piece[i][j]!=-1 && piece[i][j]!=-2 && piece[i][j]!=0 && piece[i][j]!=8 && piece[i][j]!=13 &&  piece[i][j]!=21 && piece[i][j]!=26 && piece[i][j]!=34 && piece[i][j]!=39 && piece[i][j]!=47 && piece[i][j]<52) // all these are safe spots where a piece cannot be removed
                        {// one piece kills another
                            killCount[turn-2]++;
                            score[turn-2]+=10;
                            piece[i][j]=-1; // move back to the starting circle
                            turn--; // gives the player another turn
                        }
                    }
                }
            }
        }
}

void moveFromBlockTeamMinus(int diceNum) // if a piece moves from the block, this function breaks the block
{
    if(piece[turn-2][keyPressed-97]-dices[diceNum]<0) // the block was before the 0th position
    {
        if(block[52+piece[turn-2][keyPressed-97]-dices[diceNum]]==1) // this logic was created with the help of pen and paper
        {
            block[52+piece[turn-2][keyPressed-97]-dices[diceNum]]=0;
            score[turn-2]+=2;
        }
    }
    else if(piece[turn-2][keyPressed-97]-dices[diceNum]>=0) // the block was after 0th position(i.e. yellow's starting square)
    {
        if(block[piece[turn-2][keyPressed-97]-dices[diceNum]]==1)
        {
            block[piece[turn-2][keyPressed-97]-dices[diceNum]]=0;
            score[turn-2]+=2;
        }
    }
}

int checkForBlockTeamMinus(int diceNum) // checks whether a block exists in the path of the piece
{
    // returns 0 if the pathway is open. returns 1 if the pathway is closed by a block
    int blockCounter=0;
        if(turn-2<=1)
        {
            if(piece[turn-2][keyPressed-97]+dices[diceNum]<52)
            {
                for(int i=piece[turn-2][keyPressed-97]+1;i<=(piece[turn-2][keyPressed-97]+dices[diceNum]);i++)
                {
                    if(block[i]==1 && colorAtBlock(i)!=turn-2 && colorAtBlock(i)!=(turn-2+2)) // colorAtBlock(i)!=turn allows only the same color to cross the block
                    {
                        blockCounter++;
                    }
                }
            }
            else if((piece[turn-2][keyPressed-97]+dices[diceNum])>=52 && (piece[turn-2][keyPressed-97]+dices[diceNum])<100)
            {
                for(int i=piece[turn-2][keyPressed-97]+1;i<=(piece[turn-2][keyPressed-97]+dices[diceNum]);i++)
                {
                    if(i<52)
                    {
                        if(block[i]==1 && colorAtBlock(i)!=turn-2 && colorAtBlock(i)!=(turn-2+2)) // colorAtBlock(i)!=turn-2 allows only the same color to cross the block
                        {
                            blockCounter++;
                        }
                    }
                    if(i>=52)
                    {
                        if(block[i-52]==1 && colorAtBlock(i-52)!=turn-2 && colorAtBlock(i-52)!=(turn-2+2)) // colorAtBlock(i-52)!=turn-2 allows only the same color to cross the block
                        {
                            blockCounter++;
                        }
                    }
                } // this function started creating issues when pieces crossed yellow's home cirlcle. so all this logic was created to remove those issues
            }
        }
        if(turn-2>=2)
        {
            if(piece[turn-2][keyPressed-97]+dices[diceNum]<52)
            {
                for(int i=piece[turn-2][keyPressed-97]+1;i<=(piece[turn-2][keyPressed-97]+dices[diceNum]);i++)
                {
                    if(block[i]==1 && colorAtBlock(i)!=turn-2 && colorAtBlock(i)!=(turn-2-2)) // colorAtBlock(i)!=turn-2 allows only the same color to cross the block
                    {
                        blockCounter++;
                    }
                }
            }
            else if((piece[turn-2][keyPressed-97]+dices[diceNum])>=52 && (piece[turn-2][keyPressed-97]+dices[diceNum])<100)
            {
                for(int i=piece[turn-2][keyPressed-97]+1;i<=(piece[turn-2][keyPressed-97]+dices[diceNum]);i++)
                {
                    if(i<52)
                    {
                        if(block[i]==1 && colorAtBlock(i)!=(turn-2-2) && colorAtBlock(i)!=(turn-2-2)) // colorAtBlock(i)!=turn-2 allows only the same color to cross the block
                        {
                            blockCounter++;
                        }
                    }
                    if(i>=52)
                    {
                        if(block[i-52]==1 && colorAtBlock(i-52)!=(turn-2-2) && colorAtBlock(i-52)!=(turn-2-2)) // colorAtBlock(i-52)!=turn-2 allows only the same color to cross the block
                        {
                            blockCounter++;
                        }
                    }
                } // this function started creating issues when pieces crossed yellow's home cirlcle. so all this logic was created to remove those issues
            }
        }
    if(blockCounter>0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkForHomeTriangle_SixTeamMinus() //this function puts the piece in home triangle ONLY when the piece is out of the home column on the first block before it. As then the piece needs a 6 to move to home triangle
{
    if(turn-2 == 0 && killCount[turn-2]>0 && piece[turn-2][keyPressed-97]==50 )
    {
        return 1;
    }
    if(turn-2 == 1 && killCount[turn-2]>0 && piece[turn-2][keyPressed-97]==11 )
    {
        return 1;
    }
    if(turn-2 == 2 && killCount[turn-2]>0 && piece[turn-2][keyPressed-97]==24 )
    {
        return 1;
    }
    if(turn-2 == 3 && killCount[turn-2]>0 && piece[turn-2][keyPressed-97]==37 )
    {
        return 1;
    }
    return 0; // did not move to home triangle( actually it will move along the board agiain)
}

void limitHomeThrowTeamMinus(int diceNum) // a piece enters home triangle only on exact throw
{
    if(turn-2 ==0)
    {
        if(piece[turn-2][keyPressed-97]+dices[diceNum]==105)
        {
            piece[turn-2][keyPressed-97]=-2;
            score[turn-2]+=dices[diceNum];
            turn--; // gives an extra turn
        }
        else if(piece[turn-2][keyPressed-97]+dices[diceNum]<105)
        {
            piece[turn-2][keyPressed-97]+=dices[diceNum];
            score[turn-2]+=dices[diceNum];
        }
        else
        {
            // do nothing
        }
    }
    else if(turn-2 == 1)
    {
        if(piece[turn-2][keyPressed-97]+dices[diceNum]==111)
        {
            piece[turn-2][keyPressed-97]=-2;
            score[turn-2]+=dices[diceNum];
            turn--; // gives an extra turn
        }
        else if(piece[turn-2][keyPressed-97]+dices[diceNum]<111)
        {
            piece[turn-2][keyPressed-97]+=dices[diceNum];
            score[turn-2]+=dices[diceNum];
        }
        else
        {
            // do nothing
        }
    }
    else if(turn-2 == 2)
    {
        if(piece[turn-2][keyPressed-97]+dices[diceNum]==117)
        {
            piece[turn-2][keyPressed-97]=-2;
            score[turn-2]+=dices[diceNum];
            turn--; // gives an extra turn
        }
        else if(piece[turn-2][keyPressed-97]+dices[diceNum]<117)
        {
            piece[turn-2][keyPressed-97]+=dices[diceNum];
            score[turn-2]+=dices[diceNum];
        }
        else
        {
            // do nothing
        }
    }
    else if(turn-2 == 3)
    {
        if(piece[turn-2][keyPressed-97]+dices[diceNum]==123)
        {
            piece[turn-2][keyPressed-97]=-2;
            score[turn-2]+=dices[diceNum];
            turn--; // gives an extra turn
        }
        else if(piece[turn-2][keyPressed-97]+dices[diceNum]<123)
        {
            piece[turn-2][keyPressed-97]+=dices[diceNum];
            score[turn-2]+=dices[diceNum];
        }
        else
        {
            // do nothing
        }
    }
}

/////////////////////////////////////////////////
// End of teamMode functions

void GameDisplay() { // main game display function. All other functions are called through it
	glClearColor(255.0/255/*Red Component*/, 255.0/255	/*Green Component*/,
			254.0/255/*Blue Component*/, 1.0 /*Alpha component*/); // background colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
    if(window!=1)
    {
        DrawStringSmall( 1055, 20, "Press Esc to return to main menu", colors[BLACK]);
    }
    else
    {
        DrawStringSmall( 1095, 20, "Press Esc to exit", colors[BLACK]);
    }
    if(window==1) // all window functions are linked to this GameDisplay function for seperate displays
    {
        window1();
    }
    if(window==2)
    {
        window2();
    }
    if(window==3)
    {
        window3();
    }
    if(window==13)
    {
        window13();
    }
    if(window==12)
    {
        window12();
    }
    if(window==11)
    {
        window11();
    }
    if(window==4)
    {
        window4();
    }
    if(window==5)
    {
        window5();
    }
    if (window==6)
    {
        window6();
    }
    if(window==7)
    {
        window7();
    }
    if(window==8)
    {
        if(teamMode==0) // this runs when there is no teammode
        {
            setStatus(); // sets status of the 4 colors
            drawBoard(); // draws the  wooden board
            drawPiecesStart();// draws pieces in starting circle
            drawPiecesHomeTriangle(); // draws pieces only in home triangle
            writeTurn(); // writes whos turn it is in the right column
            writeNames(); // writes names of the players playing the game
            blocksFormed(); // draws any block if they are formed
            homeColumnStatus(); // draws status of home columns
            DrawCircle(0, 0, 14, colors[MISTY_ROSE]); // to cover up when home-triangle pieces jump to corner(co-ordinates for 105,111,117 and 123 are (0,0))
            if (spacePressed==1) // dice got rolled
            {
                static int sixCount=0;
                static int x=0;
                //string diceNum; // to display the number of dice on screen using DrawString function
                //diceNum = dice + 48; // e.g if dice gives 2, then int of 2 is ASCII 2+48 which is '2' in string
                drawDice(dice);
                if(dice==6)
                {
                    sixCount++;
                    dices[x]=6;
                    x++;
                    if(sixCount==3)
                    {
                        for(int z=0;z<3;z++)
                        {
                            dices[z]=0;
                        }
                        x=0;
                        sixCount=0;
                        turn++; // turn gets skipped on 3 consecutive sixes
                    }
                    spacePressed=0;
                }
                else
                {
                    if(sixCount==0) // this if statement will only run when a person gets a single roll meaning only a single numeric less than 6
                    {
                        static int y=0;
                        dices[y]=dice; //dices[0] as y=0
                        int count=0;
                        for(int i=0;i<4;i++)
                        {
                            if(piece[turn][i]==-1 || piece[turn][i]==-2)
                            {
                                count++;
                            }
                        }
                        if(count==4)
                        {
                            spacePressed=0; // turn gets skipped if all pieces are in starting circle
                            turn++;
                            for(int z=0;z<3;z++)
                            {
                                dices[z]=0; // assigning all dices back to zero
                            }
                        }
                        else
                        {
                            DrawString( 1055, 330, "Select piece to move", colors[BLACK]);
                        }
                        if(keyPressed==0)
                        {
                            // do nothing
                        }
                        else if(piece[turn][keyPressed-97]!=-1 && piece[turn][keyPressed-97]!=-2 && checkForBlock(y)==0) //&&keyPressed !=0
                        {
                            if(piece[turn][keyPressed-97]>=100) // it is already in home column
                            {
                                limitHomeThrow(y);
                            }
                            else if(checkForHomeColumn(y)==1)
                            {
                                //the function will return 1 if the piece is eligible and is going to home column
                                // it will return 0 otherwise
                                score[turn]+=dices[y];
                                score[turn]+=15;
                            }
                            else if(piece[turn][keyPressed-97]+dices[y]>51) // our MAIN board is being ranged from 0-51
                            {
                                piece[turn][keyPressed-97]=piece[turn][keyPressed-97]+dices[y]-52; // this logic was created with help of pen and paper for example subtracting 52 from 52 will give 0
                                score[turn]+=dices[y];
                            } // it will start it back again from position[0][0]
                            else
                            {
                                piece[turn][keyPressed-97]+=dices[y];
                                score[turn]+=dices[y];                                                   //MOVEMENT DONE HERE
                            }
                            //checkForHomeColumn(y);
                            moveFromBlock(y);
                            checkForKill();
                            for(int z=0;z<3;z++)
                            {
                                dices[z]=0; // assigning all dices back to zero
                            }
                            spacePressed=0;
                            turn++;
                            y=0;
                        }
                        else if(piece[turn][keyPressed-97]==-1 && count!=4) // the key user pressed was not moveable
                        {
                            //DrawString( 900, 200, "AGAIN!", colors[BLACK]);
                            spacePressed=1;
                            // turn != ++
                        }
                    }// end if statement of (if there were no sixes)
                    else // this statement will run when there are sixes too to be moved
                    {
                            dices[x]=dice;
                            static int y=0;
                            DrawString( 1055, 330, "Select piece to move", colors[BLACK]);
                            if(dices[y]==0) // assuming if the 2nd roll was !=6 so the 3rd roll was 0. so it should move to the next turn
                            {
                                turn++;
                                sixCount=0;
                                x=0;
                                for(int z=0;z<3;z++)
                                {
                                    dices[z]=0; // assigning all dices back to zero
                                }
                                spacePressed=0;
                                y=0;
                            }
                            if(keyPressed==0)
                            {
                                // do nothing
                            }
                            else if(dices[y]==6 && piece[turn][keyPressed-97]!=-2 && checkForBlock(y)==0)// && some key is pressed
                            {
                                if(piece[turn][keyPressed-97]==-1) // 97 is the ASCII for 'a', so if a user enters a, it directs towards 0th piece i.e. 'a' piece
                                {
                                    if(turn==0) //movement also done here but on safe spots
                                    {
                                        piece[turn][keyPressed-97]=0;//starting position of yellow
                                    }
                                    else if(turn==1)
                                    {
                                        piece[turn][keyPressed-97]=13; // starting position of blue
                                    }
                                    else if(turn==2)
                                    {
                                        piece[turn][keyPressed-97]=26;//starting position of red
                                    }
                                    else
                                    {
                                        piece[turn][keyPressed-97]=39;//starting position of green
                                    }
                                    //turn++;
                                    y++;
                                }
                                else // piece is on the board squares
                                {
                                    if(checkForHomeTriangle_Six()==1)
                                    {
                                        // the function will return true when the piece is eligible and is going to home triangle
                                        // otherwise it will return false
                                        piece[turn][keyPressed-97]=-2;
                                        score[turn]+=dices[y];
                                        score[turn]+=15; // because actually, the piece crossed the home column to get into home triangle
                                    }
                                    else if(checkForHomeColumn(y)==1)
                                    {
                                        //the function will return 1 if the piece is eligible and is going to home column
                                        // it will return 0 otherwise
                                        score[turn]+=15;
                                        score[turn]+=dices[y];
                                    }
                                    else if(piece[turn][keyPressed-97]+dices[y]>51) // our board is being ranged from 0-51
                                    {
                                        piece[turn][keyPressed-97]=piece[turn][keyPressed-97]+dices[y]-52; // this logic was created with help of pen and paper
                                        score[turn]+=dices[y];
                                    } // it will start it back again from position[0][0]
                                    else
                                    {
                                        piece[turn][keyPressed-97]+=dices[y];                                           //MOVEMENT DONE HERE
                                        score[turn]+=dices[y];
                                    }
                                    //checkForHomeColumn(y);
                                    moveFromBlock(y);
                                    checkForKill();
                                    //turn++;
                                    y++;
                                }
                            }
                            else if(dices[y]!=6 && dices[y]!=0 && piece[turn][keyPressed-97]!=-1 && piece[turn][keyPressed-97]!=-2 && checkForBlock(y)==0) // if dices[y]!=6 (1-5) && some key is pressed
                            {
                                if(piece[turn][keyPressed-97]>=100) // it is already in home column
                                {
                                    limitHomeThrow(y);
                                }
                                else if(checkForHomeColumn(y)==1)
                                {
                                    //the function will return 1 if the piece is eligible and is going to home column
                                    // it will return 0 otherwise
                                    score[turn]+=15;
                                    score[turn]+=dices[y];
                                }
                                else if(piece[turn][keyPressed-97]+dices[y]>51) // our board is being ranged from 0-51
                                {
                                    piece[turn][keyPressed-97]=piece[turn][keyPressed-97]+dices[y]-52; // this logic was created with help of pen and paper
                                    score[turn]+=dices[y];
                                } // it will start it back again from position[0][0]
                                else
                                {
                                    piece[turn][keyPressed-97]+=dices[y];                                               //MOVEMENT DONE HERE
                                    score[turn]+=dices[y];
                                }
                                //checkForHomeColumn(y);
                                moveFromBlock(y);
                                checkForKill();
                                turn++;
                                sixCount=0;
                                x=0;
                                for(int z=0;z<3;z++)
                                {
                                    dices[z]=0; // assigning all dices back to zero
                                }
                                spacePressed=0;
                                y=0;
                            }
                    }
                }
                /*if(turn == 4)
                {
                    turn=0;
                }*/
                checkForWinners(); // checks if someone has won and makes their status 1 if they have won
                int count=0;
                for(int i=0;i<4;i++)
                {
                    if(status[i]==1 || status[i]==-1)
                    {
                        count++;
                    }
                }
                if(count==3) // only 1 player has been left
                {
                    updateLeaderboard();
                    window=9; // end game window
                }
                /* test data
                piece[2][0]=-2;
                piece[2][1]=-2;
                piece[2][2]=-2;
                piece[2][3]=-2;
                */
                nextTurn();
                /*if(turn==1)
                {
                    turn++;
                }
                if(turn==3)
                {
                    turn=0;
                }*/
                keyPressed=0;
            }
        }
        if(teamMode==1) // this runs when there is teammode
        {
            setStatus(); // sets status of the 4 colors to zero
            drawBoard(); // draws the  wooden board
            drawPiecesStart();// draws pieces in starting circle
            drawPiecesHomeTriangle(); // draws pieces only in home triangle
            writeTurn(); // writes whos turn it is in the right column
            writeNames(); // writes names of the players playing the game
            blocksFormed(); // draws any block if they are formed
            homeColumnStatus(); // draws status of home columns
            DrawCircle(0, 0, 14, colors[MISTY_ROSE]); // to cover up when home-triangle pieces jump to corner(co-ordinates for 105,111,117 and 123 are (0,0))
            if (spacePressed==1) // dice got rolled
            {
                static int sixCount=0;
                static int x=0;
                drawDice(dice);
                if(status[turn]==0) // player is in play
                {
                    if(dice==6)
                    {
                        sixCount++;
                        dices[x]=6;
                        x++;
                        if(sixCount==3)
                        {
                            for(int z=0;z<3;z++)
                            {
                                dices[z]=0;
                            }
                            x=0;
                            sixCount=0;
                            turn++; // turn gets skipped on 3 consecutive sixes
                        }
                        spacePressed=0;
                    }
                    else
                    {
                        if(sixCount==0) // this if statement will only run when a person gets a single roll meaning only a single numeric less than 6
                        {
                            static int y=0;
                            dices[y]=dice; //dices[0] as y=0
                            int count=0;
                            for(int i=0;i<4;i++)
                            {
                                if(piece[turn][i]==-1 || piece[turn][i]==-2)
                                {
                                    count++;
                                }
                            }
                            if(count==4)
                            {
                                spacePressed=0; // turn gets skipped if all pieces are in starting circle
                                turn++;
                                for(int z=0;z<3;z++)
                                {
                                    dices[z]=0; // assigning all dices back to zero
                                }
                            }
                            else
                            {
                                DrawString( 1055, 330, "Select piece to move", colors[BLACK]);
                            }
                            if(keyPressed==0)
                            {
                                // do nothing
                            }
                            else if(piece[turn][keyPressed-97]!=-1 && piece[turn][keyPressed-97]!=-2 && checkForBlock(y)==0) //&&keyPressed !=0
                            {
                                if(piece[turn][keyPressed-97]>=100) // it is already in home column
                                {
                                    limitHomeThrow(y);
                                }
                                else if(checkForHomeColumn(y)==1)
                                {
                                    //the function will return 1 if the piece is eligible and is going to home column
                                    // it will return 0 otherwise
                                    score[turn]+=dices[y];
                                    score[turn]+=15;
                                }
                                else if(piece[turn][keyPressed-97]+dices[y]>51) // our MAIN board is being ranged from 0-51
                                {
                                    piece[turn][keyPressed-97]=piece[turn][keyPressed-97]+dices[y]-52; // this logic was created with help of pen and paper for example subtracting 52 from 52 will give 0
                                    score[turn]+=dices[y];
                                } // it will start it back again from position[0][0]
                                else
                                {
                                    piece[turn][keyPressed-97]+=dices[y];
                                    score[turn]+=dices[y];                                                   //MOVEMENT DONE HERE
                                }
                                //checkForHomeColumn(y);
                                moveFromBlock(y);
                                checkForKill();
                                for(int z=0;z<3;z++)
                                {
                                    dices[z]=0; // assigning all dices back to zero
                                }
                                spacePressed=0;
                                turn++;
                                y=0;
                            }
                            else if(piece[turn][keyPressed-97]==-1 && count!=4) // the key user pressed was not moveable
                            {
                                //DrawString( 900, 200, "AGAIN!", colors[BLACK]);
                                spacePressed=1;
                                // turn != ++
                            }
                        }// end if statement of (if there were no sixes)
                        else // this statement will run when there are sixes too to be moved
                        {
                                dices[x]=dice;
                                static int y=0;
                                DrawString( 1055, 330, "Select piece to move", colors[BLACK]);
                                if(dices[y]==0) // assuming if the 2nd roll was !=6 so the 3rd roll was 0. so it should move to the next turn
                                {
                                    turn++;
                                    sixCount=0;
                                    x=0;
                                    for(int z=0;z<3;z++)
                                    {
                                        dices[z]=0; // assigning all dices back to zero
                                    }
                                    spacePressed=0;
                                    y=0;
                                }
                                if(keyPressed==0)
                                {
                                    // do nothing
                                }
                                else if(dices[y]==6 && piece[turn][keyPressed-97]!=-2 && checkForBlock(y)==0)// && some key is pressed
                                {
                                    if(piece[turn][keyPressed-97]==-1) // 97 is the ASCII for 'a', so if a user enters a, it directs towards 0th piece i.e. 'a' piece
                                    {
                                        if(turn==0) //movement also done here but on safe spots
                                        {
                                            piece[turn][keyPressed-97]=0;//starting position of yellow
                                        }
                                        else if(turn==1)
                                        {
                                            piece[turn][keyPressed-97]=13; // starting position of blue
                                        }
                                        else if(turn==2)
                                        {
                                            piece[turn][keyPressed-97]=26;//starting position of red
                                        }
                                        else
                                        {
                                            piece[turn][keyPressed-97]=39;//starting position of green
                                        }
                                        //turn++;
                                        y++;
                                    }
                                    else // piece is on the board squares
                                    {
                                        if(checkForHomeTriangle_Six()==1)
                                        {
                                            // the function will return true when the piece is eligible and is going to home triangle
                                            // otherwise it will return false
                                            piece[turn][keyPressed-97]=-2;
                                            score[turn]+=dices[y];
                                            score[turn]+=15; // because actually, the piece crossed the home column to get into home triangle
                                        }
                                        else if(checkForHomeColumn(y)==1)
                                        {
                                            //the function will return 1 if the piece is eligible and is going to home column
                                            // it will return 0 otherwise
                                            score[turn]+=15;
                                            score[turn]+=dices[y];
                                        }
                                        else if(piece[turn][keyPressed-97]+dices[y]>51) // our board is being ranged from 0-51
                                        {
                                            piece[turn][keyPressed-97]=piece[turn][keyPressed-97]+dices[y]-52; // this logic was created with help of pen and paper
                                            score[turn]+=dices[y];
                                        } // it will start it back again from position[0][0]
                                        else
                                        {
                                            piece[turn][keyPressed-97]+=dices[y];                                           //MOVEMENT DONE HERE
                                            score[turn]+=dices[y];
                                        }
                                        //checkForHomeColumn(y);
                                        moveFromBlock(y);
                                        checkForKill();
                                        //turn++;
                                        y++;
                                    }
                                }
                                else if(dices[y]!=6 && dices[y]!=0 && piece[turn][keyPressed-97]!=-1 && piece[turn][keyPressed-97]!=-2 && checkForBlock(y)==0) // if dices[y]!=6 (1-5) && some key is pressed
                                {
                                    if(piece[turn][keyPressed-97]>=100) // it is already in home column
                                    {
                                        limitHomeThrow(y);
                                    }
                                    else if(checkForHomeColumn(y)==1)
                                    {
                                        //the function will return 1 if the piece is eligible and is going to home column
                                        // it will return 0 otherwise
                                        score[turn]+=15;
                                        score[turn]+=dices[y];
                                    }
                                    else if(piece[turn][keyPressed-97]+dices[y]>51) // our board is being ranged from 0-51
                                    {
                                        piece[turn][keyPressed-97]=piece[turn][keyPressed-97]+dices[y]-52; // this logic was created with help of pen and paper
                                        score[turn]+=dices[y];
                                    } // it will start it back again from position[0][0]
                                    else
                                    {
                                        piece[turn][keyPressed-97]+=dices[y];                                               //MOVEMENT DONE HERE
                                        score[turn]+=dices[y];
                                    }
                                    //checkForHomeColumn(y);
                                    moveFromBlock(y);
                                    checkForKill();
                                    turn++;
                                    sixCount=0;
                                    x=0;
                                    for(int z=0;z<3;z++)
                                    {
                                        dices[z]=0; // assigning all dices back to zero
                                    }
                                    spacePressed=0;
                                    y=0;
                                }
                        }
                    }
                }
                else if(status[turn]==1) // player has all 4 pieces in home triangle
                {
                    if(partnersRoll[turn]==0)
                    {
                        if(dice==6)
                        {
                            partnersRoll[turn]=1;
                            dice=0;
                            spacePressed=0;
                        }
                        else
                        {
                            //partnersRoll[turn] will remain zero
                            dice=0;
                            spacePressed=0;
                        }
                        turn++;
                    }
                    else // if partnersRoll[turn]==1
                    {
                        if(turn<=1)
                        {
                            if(dice==6)
                            {
                                sixCount++;
                                dices[x]=6;
                                x++;
                                if(sixCount==3)
                                {
                                    for(int z=0;z<3;z++)
                                    {
                                        dices[z]=0;
                                    }
                                    x=0;
                                    sixCount=0;
                                    turn++; // turn gets skipped on 3 consecutive sixes
                                }
                                spacePressed=0;
                            }
                            else
                            {
                                if(sixCount==0) // this if statement will only run when a person gets a single roll meaning only a single numeric less than 6
                                {
                                    static int y=0;
                                    dices[y]=dice; //dices[0] as y=0
                                    int count=0;
                                    for(int i=0;i<4;i++)
                                    {
                                        if(piece[turn+2][i]==-1 || piece[turn+2][i]==-2)
                                        {
                                            count++;
                                        }
                                    }
                                    if(count==4)
                                    {
                                        spacePressed=0; // turn gets skipped if all pieces are in starting circle
                                        turn++;
                                        for(int z=0;z<3;z++)
                                        {
                                            dices[z]=0; // assigning all dices back to zero
                                        }
                                    }
                                    else
                                    {
                                        DrawString( 1055, 330, "Select piece to move", colors[BLACK]);
                                    }
                                    if(keyPressed==0)
                                    {
                                        // do nothing
                                    }
                                    else if(piece[turn+2][keyPressed-97]!=-1 && piece[turn+2][keyPressed-97]!=-2 && checkForBlockTeamPlus(y)==0) //&&keyPressed !=0
                                    {
                                        if(piece[turn+2][keyPressed-97]>=100) // it is already in home column
                                        {
                                            limitHomeThrowTeamPlus(y);
                                        }
                                        else if(checkForHomeColumnTeamPlus(y)==1)
                                        {
                                            //the function will return 1 if the piece is eligible and is going to home column
                                            // it will return 0 otherwise
                                            score[turn+2]+=dices[y];
                                            score[turn+2]+=15;
                                        }
                                        else if(piece[turn+2][keyPressed-97]+dices[y]>51) // our MAIN board is being ranged from 0-51
                                        {
                                            piece[turn+2][keyPressed-97]=piece[turn+2][keyPressed-97]+dices[y]-52; // this logic was created with help of pen and paper for example subtracting 52 from 52 will give 0
                                            score[turn+2]+=dices[y];
                                        } // it will start it back again from position[0][0]
                                        else
                                        {
                                            piece[turn+2][keyPressed-97]+=dices[y];
                                            score[turn+2]+=dices[y];                                                   //MOVEMENT DONE HERE
                                        }
                                        //checkForHomeColumn(y);
                                        moveFromBlockTeamPlus(y);
                                        checkForKillTeamPlus();
                                        for(int z=0;z<3;z++)
                                        {
                                            dices[z]=0; // assigning all dices back to zero
                                        }
                                        spacePressed=0;
                                        turn++;
                                        y=0;
                                    }
                                    else if(piece[turn+2][keyPressed-97]==-1 && count!=4) // the key user pressed was not moveable
                                    {
                                        //DrawString( 900, 200, "AGAIN!", colors[BLACK]);
                                        spacePressed=1;
                                        // turn != ++
                                    }
                                }// end if statement of (if there were no sixes)
                                else // this statement will run when there are sixes too to be moved
                                {
                                        dices[x]=dice;
                                        static int y=0;
                                        DrawString( 1055, 330, "Select piece to move", colors[BLACK]);
                                        if(dices[y]==0) // assuming if the 2nd roll was !=6 so the 3rd roll was 0. so it should move to the next turn
                                        {
                                            turn++;
                                            sixCount=0;
                                            x=0;
                                            for(int z=0;z<3;z++)
                                            {
                                                dices[z]=0; // assigning all dices back to zero
                                            }
                                            spacePressed=0;
                                            y=0;
                                        }
                                        if(keyPressed==0)
                                        {
                                            // do nothing
                                        }
                                        else if(dices[y]==6 && piece[turn+2][keyPressed-97]!=-2 && checkForBlockTeamPlus(y)==0)// && some key is pressed
                                        {
                                            if(piece[turn+2][keyPressed-97]==-1) // 97 is the ASCII for 'a', so if a user enters a, it directs towards 0th piece i.e. 'a' piece
                                            {
                                                if(turn+2==0) //movement also done here but on safe spots
                                                {
                                                    piece[turn+2][keyPressed-97]=0;//starting position of yellow
                                                }
                                                else if(turn+2==1)
                                                {
                                                    piece[turn+2][keyPressed-97]=13; // starting position of blue
                                                }
                                                else if(turn+2==2)
                                                {
                                                    piece[turn+2][keyPressed-97]=26;//starting position of red
                                                }
                                                else
                                                {
                                                    piece[turn+2][keyPressed-97]=39;//starting position of green
                                                }
                                                //turn++;
                                                y++;
                                            }
                                            else // piece is on the board squares
                                            {
                                                if(checkForHomeTriangle_SixTeamPlus()==1)
                                                {
                                                    // the function will return true when the piece is eligible and is going to home triangle
                                                    // otherwise it will return false
                                                    piece[turn+2][keyPressed-97]=-2;
                                                    score[turn+2]+=dices[y];
                                                    score[turn+2]+=15; // because actually, the piece crossed the home column to get into home triangle
                                                }
                                                else if(checkForHomeColumnTeamPlus(y)==1)
                                                {
                                                    //the function will return 1 if the piece is eligible and is going to home column
                                                    // it will return 0 otherwise
                                                    score[turn+2]+=15;
                                                    score[turn+2]+=dices[y];
                                                }
                                                else if(piece[turn+2][keyPressed-97]+dices[y]>51) // our board is being ranged from 0-51
                                                {
                                                    piece[turn+2][keyPressed-97]=piece[turn+2][keyPressed-97]+dices[y]-52; // this logic was created with help of pen and paper
                                                    score[turn+2]+=dices[y];
                                                } // it will start it back again from position[0][0]
                                                else
                                                {
                                                    piece[turn+2][keyPressed-97]+=dices[y];                                           //MOVEMENT DONE HERE
                                                    score[turn+2]+=dices[y];
                                                }
                                                //checkForHomeColumn(y);
                                                moveFromBlockTeamPlus(y);
                                                checkForKillTeamPlus();
                                                //turn++;
                                                y++;
                                            }
                                        }
                                        else if(dices[y]!=6 && dices[y]!=0 && piece[turn+2][keyPressed-97]!=-1 && piece[turn+2][keyPressed-97]!=-2 && checkForBlockTeamPlus(y)==0) // if dices[y]!=6 (1-5) && some key is pressed
                                        {
                                            if(piece[turn+2][keyPressed-97]>=100) // it is already in home column
                                            {
                                                limitHomeThrowTeamPlus(y);
                                            }
                                            else if(checkForHomeColumnTeamPlus(y)==1)
                                            {
                                                //the function will return 1 if the piece is eligible and is going to home column
                                                // it will return 0 otherwise
                                                score[turn+2]+=15;
                                                score[turn+2]+=dices[y];
                                            }
                                            else if(piece[turn+2][keyPressed-97]+dices[y]>51) // our board is being ranged from 0-51
                                            {
                                                piece[turn+2][keyPressed-97]=piece[turn+2][keyPressed-97]+dices[y]-52; // this logic was created with help of pen and paper
                                                score[turn+2]+=dices[y];
                                            } // it will start it back again from position[0][0]
                                            else
                                            {
                                                piece[turn+2][keyPressed-97]+=dices[y];                                               //MOVEMENT DONE HERE
                                                score[turn+2]+=dices[y];
                                            }
                                            //checkForHomeColumn(y);
                                            moveFromBlockTeamPlus(y);
                                            checkForKillTeamPlus();
                                            turn++;
                                            sixCount=0;
                                            x=0;
                                            for(int z=0;z<3;z++)
                                            {
                                                dices[z]=0; // assigning all dices back to zero
                                            }
                                            spacePressed=0;
                                            y=0;
                                        }
                                }
                            }
                        }
                        if(turn>=2)
                        {
                            if(dice==6)
                            {
                                sixCount++;
                                dices[x]=6;
                                x++;
                                if(sixCount==3)
                                {
                                    for(int z=0;z<3;z++)
                                    {
                                        dices[z]=0;
                                    }
                                    x=0;
                                    sixCount=0;
                                    turn++; // turn gets skipped on 3 consecutive sixes
                                }
                                spacePressed=0;
                            }
                            else
                            {
                                if(sixCount==0) // this if statement will only run when a person gets a single roll meaning only a single numeric less than 6
                                {
                                    static int y=0;
                                    dices[y]=dice; //dices[0] as y=0
                                    int count=0;
                                    for(int i=0;i<4;i++)
                                    {
                                        if(piece[turn-2][i]==-1 || piece[turn-2][i]==-2)
                                        {
                                            count++;
                                        }
                                    }
                                    if(count==4)
                                    {
                                        spacePressed=0; // turn gets skipped if all pieces are in starting circle
                                        turn++;
                                        for(int z=0;z<3;z++)
                                        {
                                            dices[z]=0; // assigning all dices back to zero
                                        }
                                    }
                                    else
                                    {
                                        DrawString( 1055, 330, "Select piece to move", colors[BLACK]);
                                    }
                                    if(keyPressed==0)
                                    {
                                        // do nothing
                                    }
                                    else if(piece[turn-2][keyPressed-97]!=-1 && piece[turn-2][keyPressed-97]!=-2 && checkForBlockTeamMinus(y)==0) //&&keyPressed !=0
                                    {
                                        if(piece[turn-2][keyPressed-97]>=100) // it is already in home column
                                        {
                                            limitHomeThrowTeamMinus(y);
                                        }
                                        else if(checkForHomeColumnTeamMinus(y)==1)
                                        {
                                            //the function will return 1 if the piece is eligible and is going to home column
                                            // it will return 0 otherwise
                                            score[turn-2]+=dices[y];
                                            score[turn-2]+=15;
                                        }
                                        else if(piece[turn-2][keyPressed-97]+dices[y]>51) // our MAIN board is being ranged from 0-51
                                        {
                                            piece[turn-2][keyPressed-97]=piece[turn-2][keyPressed-97]+dices[y]-52; // this logic was created with help of pen and paper for example subtracting 52 from 52 will give 0
                                            score[turn-2]+=dices[y];
                                        } // it will start it back again from position[0][0]
                                        else
                                        {
                                            piece[turn-2][keyPressed-97]+=dices[y];
                                            score[turn-2]+=dices[y];                                                   //MOVEMENT DONE HERE
                                        }
                                        //checkForHomeColumn(y);
                                        moveFromBlockTeamMinus(y);
                                        checkForKillTeamMinus();
                                        for(int z=0;z<3;z++)
                                        {
                                            dices[z]=0; // assigning all dices back to zero
                                        }
                                        spacePressed=0;
                                        turn++;
                                        y=0;
                                    }
                                    else if(piece[turn-2][keyPressed-97]==-1 && count!=4) // the key user pressed was not moveable
                                    {
                                        //DrawString( 900, 200, "AGAIN!", colors[BLACK]);
                                        spacePressed=1;
                                        // turn != ++
                                    }
                                }// end if statement of (if there were no sixes)
                                else // this statement will run when there are sixes too to be moved
                                {
                                        dices[x]=dice;
                                        static int y=0;
                                        DrawString( 1055, 330, "Select piece to move", colors[BLACK]);
                                        if(dices[y]==0) // assuming if the 2nd roll was !=6 so the 3rd roll was 0. so it should move to the next turn
                                        {
                                            turn++;
                                            sixCount=0;
                                            x=0;
                                            for(int z=0;z<3;z++)
                                            {
                                                dices[z]=0; // assigning all dices back to zero
                                            }
                                            spacePressed=0;
                                            y=0;
                                        }
                                        if(keyPressed==0)
                                        {
                                            // do nothing
                                        }
                                        else if(dices[y]==6 && piece[turn-2][keyPressed-97]!=-2 && checkForBlockTeamMinus(y)==0)// && some key is pressed
                                        {
                                            if(piece[turn-2][keyPressed-97]==-1) // 97 is the ASCII for 'a', so if a user enters a, it directs towards 0th piece i.e. 'a' piece
                                            {
                                                if(turn-2==0) //movement also done here but on safe spots
                                                {
                                                    piece[turn-2][keyPressed-97]=0;//starting position of yellow
                                                }
                                                else if(turn-2==1)
                                                {
                                                    piece[turn-2][keyPressed-97]=13; // starting position of blue
                                                }
                                                else if(turn-2==2)
                                                {
                                                    piece[turn-2][keyPressed-97]=26;//starting position of red
                                                }
                                                else
                                                {
                                                    piece[turn-2][keyPressed-97]=39;//starting position of green
                                                }
                                                //turn++;
                                                y++;
                                            }
                                            else // piece is on the board squares
                                            {
                                                if(checkForHomeTriangle_SixTeamMinus()==1)
                                                {
                                                    // the function will return true when the piece is eligible and is going to home triangle
                                                    // otherwise it will return false
                                                    piece[turn-2][keyPressed-97]=-2;
                                                    score[turn-2]+=dices[y];
                                                    score[turn-2]+=15; // because actually, the piece crossed the home column to get into home triangle
                                                }
                                                else if(checkForHomeColumnTeamMinus(y)==1)
                                                {
                                                    //the function will return 1 if the piece is eligible and is going to home column
                                                    // it will return 0 otherwise
                                                    score[turn-2]+=15;
                                                    score[turn-2]+=dices[y];
                                                }
                                                else if(piece[turn-2][keyPressed-97]+dices[y]>51) // our board is being ranged from 0-51
                                                {
                                                    piece[turn-2][keyPressed-97]=piece[turn-2][keyPressed-97]+dices[y]-52; // this logic was created with help of pen and paper
                                                    score[turn-2]+=dices[y];
                                                } // it will start it back again from position[0][0]
                                                else
                                                {
                                                    piece[turn-2][keyPressed-97]+=dices[y];                                           //MOVEMENT DONE HERE
                                                    score[turn-2]+=dices[y];
                                                }
                                                //checkForHomeColumn(y);
                                                moveFromBlockTeamMinus(y);
                                                checkForKillTeamMinus();
                                                //turn++;
                                                y++;
                                            }
                                        }
                                        else if(dices[y]!=6 && dices[y]!=0 && piece[turn-2][keyPressed-97]!=-1 && piece[turn-2][keyPressed-97]!=-2 && checkForBlockTeamMinus(y)==0) // if dices[y]!=6 (1-5) && some key is pressed
                                        {
                                            if(piece[turn-2][keyPressed-97]>=100) // it is already in home column
                                            {
                                                limitHomeThrowTeamMinus(y);
                                            }
                                            else if(checkForHomeColumnTeamMinus(y)==1)
                                            {
                                                //the function will return 1 if the piece is eligible and is going to home column
                                                // it will return 0 otherwise
                                                score[turn-2]+=15;
                                                score[turn-2]+=dices[y];
                                            }
                                            else if(piece[turn-2][keyPressed-97]+dices[y]>51) // our board is being ranged from 0-51
                                            {
                                                piece[turn-2][keyPressed-97]=piece[turn-2][keyPressed-97]+dices[y]-52; // this logic was created with help of pen and paper
                                                score[turn-2]+=dices[y];
                                            } // it will start it back again from position[0][0]
                                            else
                                            {
                                                piece[turn-2][keyPressed-97]+=dices[y];                                               //MOVEMENT DONE HERE
                                                score[turn-2]+=dices[y];
                                            }
                                            //checkForHomeColumn(y);
                                            moveFromBlockTeamMinus(y);
                                            checkForKillTeamMinus();
                                            turn++;
                                            sixCount=0;
                                            x=0;
                                            for(int z=0;z<3;z++)
                                            {
                                                dices[z]=0; // assigning all dices back to zero
                                            }
                                            spacePressed=0;
                                            y=0;
                                        }
                                }
                            }
                        }
                    }
                }
                checkForWinners(); // checks if someone has won and makes their status 1 if they have won
                int count=0;
                if(status[0]==1 && status[2]==1)
                {
                    count++;
                }
                if(status[1]==1 && status[3]==1)
                {
                    count++;
                }
                if(count==1) // 1 team has won
                {
                    updateLeaderboard();
                    window=9; // end game window
                }
                if(turn==4) // next turn function for team mode
                {
                    turn=0;
                }
                // no nextTurn() because in teammode, all 4 players keep rolling the dice until the game ends
                keyPressed=0;
            }
        }
    }
    if(window==9)
    {
        window9();
    }
	glutSwapBuffers(); // do not modify this line..
}

void Timer(int m)
{
    glutTimerFunc(1000.0, Timer, 0);
    glutPostRedisplay();
}

int main(int argc, char*argv[])
{
    initializingPieceArray();
    assignValuesToSquares();
	int width = 1280, height = 720; // i have set my window in accordance with my laptop i.e. 720p
	InitRandomizer(); // seed the random number generator (util)
	glutInit(&argc, argv); // initialize the graphics library
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("LUDO"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	glutTimerFunc(1000.0, Timer, 0);
	glutMainLoop();
	return 1;
}

#endif
/* Old code to run some tests
int start(string names[])
{
	int players;
	cout<<"How many players want to play? ";
	for(;;)
	{
		cin>>players;
		if(players<=1 || players>4)
		{
			cout<<"Invalid input. Please try again: ";
		}
		else
		{
			break;
		}
	}
	cin.ignore(20,'\n');
	cout<<"Please enter your respective names: ";
	for(int i=0;i<players;i++)
	{
		getline(cin,names[i]);
	}
	return players;
}

Old codes
if(dice==6)
{
    DrawString( 900, 400, "Select piece to move(a,b,c,d)", colors[BLACK]);
    if(keyPressed==0)
    {
        // do nothing
    }
    else
    {
        if(piece[turn][keyPressed-97]==-1) // 97 is the ASCII for 'a', so if a user enters a, it directs towards 0th piece i.e. 'a' piece
        {
            if(turn==0)
            {
                piece[turn][keyPressed-97]=0;//starting position of yellow
            }
            else if(turn==1)
            {
                piece[turn][keyPressed-97]=13; // starting position of blue
            }
            else if(turn==2)
            {
                piece[turn][keyPressed-97]=26;//starting position of red
            }
            else
            {
                piece[turn][keyPressed-97]=39;//starting position of green
            }
            turn++;
        }
        else
        {
            piece[turn][keyPressed-97]+=dice;
            turn++;
        }
    spacePressed=0;
    }
}
else // if dice == 1-5
{
    int count=0;
    for(int i=0;i<4;i++)
    {
        if(piece[turn][i]==-1)
        {
            count++;
        }
    }
    if(count==4)
    {
        spacePressed=0;
        turn++;
    }
    DrawString( 900, 400, "Select piece to\n move(a,b,c,d)", colors[BLACK]);
    if(keyPressed==0)
    {
        // do nothing
    }
    else if(piece[turn][keyPressed-97]!=-1) //&&keyPressed !=0
    {
        piece[turn][keyPressed-97]+=dice;
        spacePressed=0;
        turn++;
    }
    else if(piece[turn][keyPressed-97]==-1 && count!=4) // the key user pressed was not moveable
    {
        DrawString( 900, 200, "AGAIN!", colors[BLACK]);
        spacePressed=1;
        // turn != ++
    }
}*/
