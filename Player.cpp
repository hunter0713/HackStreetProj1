#include "Player.h"
Player::Player()
{

}
Player::Player(int numShips)
  {

      Ship myShips[numShips];
      for (int i = 1; i <= numShips; i++)
      {
        Ship tempShip(i);
        myShips[i-1] = tempShip;
      }
      ownShips = myShips;
      placeShips();

  }
Player::~Player()
{

}
Board Player::getBoard(char choice)
{
  if(choice == 'o')//if choice is own board, return own board.
  {
    return(ownBoard);
  }
  else //if choice is enemy board, return enemy board.
  {
    return(enemyBoard);
  }

}
void Player::placeShips()
  {
    char tempOrient = '$';
    string tempCoord = "";
    for(int i = 0; i < numShips; i++)
    {
      cout<<"Placing Ship of Size: "<<(i+1);
      while (tempOrient != 'h' && tempOrient != 'v')
      {
      cout<<"\nPlease input an orientation (v for Vertical or h for Horizontal): ";
      cin>>tempOrient;
      if (tempOrient != 'h' && tempOrient != 'v')
        {
          cout<"Pick a valid option this time.\n";
        }
      }
      int xVal =0;
      int yVal =0;
      bool validX = true;
      bool validY = true;
      do
      {
      validX = true;
      validY = true;
      char xTemp = ' ';
      string playerShot = "";
      cout<<"Input a position for the front of the ship: ";
      cin >> playerShot;
      xTemp = playerShot.at(0);
      yVal = playerShot.at(1);

          switch (xTemp)
      	{
                 case 'a':
      		xVal = 0;
      		break;
      	         case 'b':
      		xVal = 1;
      		break;
                 case 'c':
      		xVal = 2;			//switch block transforms first char in input string from the player into integer value.
      		break;
      	         case 'd':
      		xVal = 3;
      		break;
                 case 'e':
      		xVal = 4;
      		break;
      	         case 'f':
      		xVal = 5;
      		break;
                 case 'g':
      		xVal = 6;
      		break;
      	         case 'h':
      		xVal = 7;
      		break;
      	         default:
      		cout <<"X Position Out of Bounds!\n";
          validX = false;
      		break;
        }
          switch (yVal)
      	{
                 case '1':
      		yVal = 0;
      		break;
      	         case '2':
      		yVal = 1;
      		break;
                 case '3':
      		yVal = 2;			//switch block transforms second char into integer value for grid.
      		break;
      	         case '4':
      		yVal = 3;
      		break;
                 case '5':
      		yVal = 4;
      		break;
      	         case '6':
      		yVal = 5;
      		break;
                 case '7':
      		yVal = 6;
      		break;
      	         case '8':
      		yVal = 7;
      		break;
      	         default:
      		cout <<"Y Position Out of Bounds!\n";
          validY = false;
      		break;
      	}
      }
      while (!validX || !validY);
      ownShips[i].setOrientation(tempOrient);
      ownShips[i].setPositions(xVal, yVal);
    }
  }
bool Player::fireShot(int xPos, int yPos, Player target)
{

    if(target.getBoard(o).getPos(xPos,yPos) == 's') //where s represents a ships presence.
    {
        enemyBoard.setPos(xPos,yPos, 'h');//h represents a ship turned into a hit
        return true;
    }
    else if(target.getBoard(o).getPos(xPos,yPos) == 'w')//w represents empty water
    {
      enemyBoard.setPos(xPos,yPos,'m');//m represents a miss that landed in water.
      return false;
    }
}

void Player::receiveHit(int xPos, int yPos)
{
  for (int i = 0; i < numShips; i++)
  {
    if (ownShips[i].coordCheck(xPos, yPos))
    {
      ownShips[i].addHit();
      break;
    }
  }
}

bool Player::isDead()
{
  bool tempDead = true;
  for (int i = 0; i < numShips; i++)
  {
    if (ownShips[i].isSunk() == false)
    {
      tempDead = false;
    }
  }
  return tempDead;
}
