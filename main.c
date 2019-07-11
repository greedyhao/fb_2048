/**************************************
 * 文件名：main.c
 * 文件描述：实验简易的字符界面2048游戏
 * 编辑人：王廷云
 * 编辑日期：2017-10-21
 * 修改日期：2018-2-10
**************************************/

#include <stdio.h>
#include "2048game.h"

int main(void)
{
    int gameData[NR][NR];	// 游戏数据
    int isGameOver = 0;		// 游戏结束标志位
    int key;				// 用户的按键输入

    /* 初始化游戏 */
    initGame(gameData);

    /* 显示游戏 */
    showGame(gameData);

    /* 进入游戏 */
    while (1)
    {
        /* 获取用户输入 */
		key = getInput();
		switch (key)
		{
		    case UP    : moveUp(gameData);    break;
		    case DOWN  : moveDown(gameData);  break;
    	    case LEFT  : moveLeft(gameData);  break;
		    case RIGHT : moveRight(gameData); break;
		    case EXIT  : exitGame();          break;
		    case UNKNOW: continue;
		}
		showGame(gameData);  // 每操作一次就显示结果

		/* 判断游戏是否结束 */
		isGameOver = checkGameOver(gameData);
		if (isGameOver == 1)
		{
		    fprintf(stdout, "\033[6;10H\033[31mGame Over!\033[0m");
		    exitGame();		 // 游戏满足结束条件-退出游戏
		}
    }
	
    return 0;
}

