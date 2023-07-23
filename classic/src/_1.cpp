#include <iostream>
#include "limittbl.h"
using namespace std;

typedef struct{
  unsigned char board[64];
  unsigned int score[3];
  unsigned int hint;
}Gameboard;

static int ScoreBoard[64] =
{
	10,  1,  3,  2,  2,  3,  1, 10,
	 1, -5, -1, -1, -1, -1, -5,  1,
	 3, -1,  0,  0,  0,  0, -1,  3,
	 2, -1,  0,  0,  0,  0, -1,  2,
	 2, -1,  0,  0,  0,  0, -1,  2,
	 3, -1,  0,  0,  0,  0, -1,  3,
	 1, -5, -1, -1, -1, -1, -5,  1,
	10,  1,  3,  2,  2,  3,  1, 10
};

void PutBoard(Gameboard &board, unsigned int index, unsigned int turn);

#define	MINVAL (-1000)
#define	MAXVAL (1000)
#define	MAXDEPTH	(20)
#define USE_SCOREBOARD 1

unsigned GetOptimal(Gameboard &board, unsigned turn, unsigned maxdepth, unsigned method)
{
	unsigned nodenum = 0;
	//<파트 1 : 오직 한가지 경우만 존재할 때 처리>
  if(!board.hint) return 64;
	if(board.hint == 1)
	{
		for( unsigned ui = 0 ; ui < 64 ; ++ui)
			if(board.board[ui] == 0)
				return ui;
	}
	Gameboard boards[MAXDEPTH];
	unsigned slot[MAXDEPTH];
	unsigned optindex[MAXDEPTH];
	int score[MAXDEPTH];
	unsigned depth = 0;
	int nodescore;

	boards[0] = board;
	slot[0] = 0;
	score[0] = (turn == 1)? MINVAL : MAXVAL;	
	for( ; ; )
	{
		//<파트 2 : 힌트값에 의해서 다음에 놓을 위치 찾기>
    while(slot[depth] < 64)
    {
      if(boards[depth].board[slot[depth]] == 0) break;
      slot[depth]++;
    }
		//<파트 3 : 노드 점수값 결정>
    if(slot[depth] < 64 || (boards[depth].hint == 0 && slot[depth] == 64))
    {
      boards[depth+1] = boards[depth];
      PutBoard(boards[depth+1], slot[depth], turn);
      depth++; turn ^= 3;
      score[depth] = (turn == 1)? MINVAL : MAXVAL;
      slot[depth] = 0;
      nodenum++;
      if(depth != maxdepth) continue;
      if(method == USE_SCOREBOARD)
      {
        nodescore = 0;
        for(unsigned r = 0 ; r < 64 ; r++)
        {
          if(boards[depth].board[r] == 1)
            nodescore += ScoreBoard[r];
          else if(boards[depth].board[r] == 2)
            nodescore -= ScoreBoard[r];
        }
      }
      else nodescore = boards[depth].score[1]-boards[depth].score[2];
    }
    else if(depth == 0) break;
    else nodescore = score[depth];
		//<파트 4 : 미니맥스 알고리즘>
    //	upward pass
    bool bFlag = false;
    if(turn == 2)	//	max check
    {
      if(score[depth-1] >= nodescore) bFlag = true;
    }
    else	//	min check
    {
      if(score[depth-1] <= nodescore) bFlag = true;
    }
    //	up a step
    depth--;
    turn ^= 3;
		//<파트 5 : 알파-베타 가지치기>
    if(!bFlag)
    {
      score[depth] = nodescore;
      optindex[depth] = slot[depth];
      if(depth > 0)
      {
        if(turn == 2)	//	max check
        {
          if(score[depth-1] >= nodescore)	bFlag = true;
        }
        else	//	min check
        {
          if(score[depth-1] <= nodescore)	bFlag = true;
        }
        if(bFlag)
        {
          depth--;
          turn ^= 3;
        }
      }
    }

		slot[depth]++;
	}
	return optindex[0];
}

void DisplayBoard(Gameboard &board)
{
	unsigned int ui, uj;
	system("cls");
	printf("     1   2   3   4   5   6   7   8   ");
	printf(" ● : ○ = %d : %d\n", board.score[1], board.score[2]);
	for(ui = 0 ; ui < 8 ; ui++)
	{
		printf("   +---+---+---+---+---+---+---+---+\n");
		printf(" %c |", ui+'a');
		for(uj = 0 ; uj < 8 ; uj++)
		{
			unsigned char v = board.board[ui*8+uj];
			if(v == 1) printf(" ● |");
			else if(v == 2)	printf(" ○ |");
			else if(v == 0)	printf(" ※ |");
			else printf("   |");
		}
		putchar('\n');
	}
	printf("   +---+---+---+---+---+---+---+---+\n");
}

void PutBoard(Gameboard &board, unsigned int index, unsigned int turn)
{
	unsigned int ui;
	unsigned int r;
	unsigned int anti = (turn ^ 0x3);
	static int dxy[8] = { -8, -7, 1, 9, 8, 7, -1, -9 };
	//<파트 1 : 돌을 놓는 로직>
  if(index != 64)
	{
		board.board[index] = turn;
		board.score[0]--;
		board.score[turn]++;
		for(ui = 0 ; ui < 8 ; ui++)
		{
			r = index + dxy[ui];
			int k;
			for( k = 1 ; k < limit[index][ui] ; ++k)
			{
				if(board.board[r] != anti) break;
				r += dxy[ui];
			}
			if(board.board[r] == turn)
			{
				while(--k)
				{
					r -= dxy[ui];
					board.board[r] = turn;
					board.score[turn]++;
					board.score[anti]--;
				}
			}
		}
	}
	//<파트 2 : 놓을 수 있는 곳을 찾는 로직>
  //	clear hint slots
	board.hint = 0;
	for(index = 0 ; index < 64 ; index++ )
	{
		if(board.board[index] != 3 && board.board[index] != 0)
			continue;
		board.board[index] = 3;
		for(ui = 0 ; ui < 8 ; ui++)
		{
			r = index + dxy[ui];
			int k;
			for( k = 1 ; k < limit[index][ui] ; k++)
			{
				if(board.board[r] != turn)
					break;
				r += dxy[ui];
			}
			if(k != 1 && board.board[r] == anti)
			{
				board.board[index] = 0;
				board.hint++;
				break;
			}
		}
	}
}
void MakeLimits()
{
	FILE *fp = fopen("limittbl.h", "w");
	unsigned limit[8];
	unsigned index, x, y;

	fprintf(fp, "unsigned limit[64][8] = \n{\n");
	for(index = 0 ; index < 64 ; index++ )
	{
		//	Get limit values of 8 axis
		x = index%8;
		y = index/8;
		limit[0] = y;
		limit[1] = (y > 7-x)?7-x:y;
		limit[2] = 7-x;
		limit[3] = (7-y > 7-x)?7-x:7-y;
		limit[4] = 7-y;
		limit[5] = (7-y > x)?x:7-y;
		limit[6] = x;
		limit[7] = (y > x)?x:y;
		fprintf(fp, "\t{ %d, %d, %d, %d, %d, %d, %d, %d }", 
			limit[0], limit[1], limit[2], limit[3], 
			limit[4], limit[5], limit[6], limit[7]);
		if(index != 63)
			fprintf(fp, ",\n");
	}
	fprintf(fp, "};");

	fclose(fp);
}
static Gameboard Initboard =
{
  {
    3, 3, 3, 3, 3, 3, 3, 3,		3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 0, 3, 3, 3,		3, 3, 3, 1, 2, 0, 3, 3,
    3, 3, 0, 2, 1, 3, 3, 3,		3, 3, 3, 0, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3,		3, 3, 3, 3, 3, 3, 3, 3
  },
  60, 2, 2, 4
};

