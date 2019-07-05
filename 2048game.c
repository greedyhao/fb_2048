/********************************************
 * 文件名：2048game.c
 * 文件描述: 2048游戏项目里所有功能函数的实现
 * 编辑人：王廷云
 * 编辑日期：2017-10-21
 * 修改日期：2018-2-14
********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "2048game.h"
#include "framebuffer.h"

/*
 * 函数名：initGame
 * 功能：初始化2048游戏，该函数会对游戏界面数据进行初始化
 *       并产生两个随机数
 * 参数：需要初始化的游戏数据
 * 返回值：无
*/
void initGame(int data[NR][NR])
{
    int x, y;

    init_fb();

    /* 配置终端显示设置 */
	printf("\033[2J");			 // 清屏
    system("stty -icanon");      // 关闭缓冲
    system("stty -echo");        // 关闭回显
    fprintf(stdout,"\033[?25l"); // 隐藏光标
	fflush(stdout);				 // 刷新

    /* 初始化游戏数据 */
    for (y = 0; y < NR; y++)
    {
        for (x = 0; x < NR; x++)
		{
		    data[y][x] = 0;		 // 所有数据清零
		}
    }

    /* 游戏上随机产生两个数 */
    srand(time(NULL));           // 设置随机数种子
    getRand(data);
    getRand(data);
}

/*
 * 函数名：showGame
 * 功能：显示游戏界面
 * 参数：需要显示的游戏数据
 * 返回值：无
*/
void showGame(int data[NR][NR])
{
    int x, y;

	/* 打印游戏提示信息 */
	fprintf(stdout, "\033[1;1H");	// 定位到第一行第一列
    fprintf(stdout, "欢迎来到\033[32m2048\033[0m游戏！");
    fprintf(stdout, "(\033[33m按'q'退出游戏)\033[0m\n");

	/* 打印所有数据 */
    for (y = 0; y < NR; y++)
    {
        for (x = 0; x < NR; x++)
		{
	    	if (data[y][x] == 0)
	    	{
                Display_Pic(GAME_NUM_0, x*GAME_NUM_PIX, y*GAME_NUM_PIX);
	        	fprintf(stdout, "%5d", data[y][x]);
	    	}
	    	else
	    	{
				switch (data[y][x])	// 根据不同数字打印不同颜色
				{
				case 2   : fprintf(stdout, "\033[32m%5d\033[0m", \
				    		       data[y][x]); 
                            Display_Pic(GAME_NUM_2, x*GAME_NUM_PIX, y*GAME_NUM_PIX);
                            break;
				case 4   : fprintf(stdout, "\033[32m%5d\033[0m", \
				    		       data[y][x]);
                            Display_Pic(GAME_NUM_4, x*GAME_NUM_PIX, y*GAME_NUM_PIX);
                            break;
				case 8   : fprintf(stdout, "\033[32m%5d\033[0m", \
				    		       data[y][x]);
                            Display_Pic(GAME_NUM_8, x*GAME_NUM_PIX, y*GAME_NUM_PIX);
                            break;
				case 16  : fprintf(stdout, "\033[35m%5d\033[0m", \
				    		       data[y][x]);
                            Display_Pic(GAME_NUM_16, x*GAME_NUM_PIX, y*GAME_NUM_PIX);
                            break;
				case 32  : fprintf(stdout, "\033[35m%5d\033[0m", \
				    		       data[y][x]);
                            Display_Pic(GAME_NUM_32, x*GAME_NUM_PIX, y*GAME_NUM_PIX);
                            break;
				case 64  : fprintf(stdout, "\033[33m%5d\033[0m", \
				    		       data[y][x]);
                            Display_Pic(GAME_NUM_64, x*GAME_NUM_PIX, y*GAME_NUM_PIX);
                            break;
				case 128 : fprintf(stdout, "\033[33m%5d\033[0m", \
				    		       data[y][x]);
                            Display_Pic(GAME_NUM_128, x*GAME_NUM_PIX, y*GAME_NUM_PIX);
                            break;
				case 256 : fprintf(stdout, "\033[34m%5d\033[0m", \
				    		       data[y][x]);
                            Display_Pic(GAME_NUM_256, x*GAME_NUM_PIX, y*GAME_NUM_PIX);
                            break;
				case 512 : fprintf(stdout, "\033[34m%5d\033[0m", \
				    		       data[y][x]);
                            Display_Pic(GAME_NUM_512, x*GAME_NUM_PIX, y*GAME_NUM_PIX);
                            break;
				case 1024: fprintf(stdout, "\033[34m%5d\033[0m", \
				    		       data[y][x]);
                            Display_Pic(GAME_NUM_1024, x*GAME_NUM_PIX, y*GAME_NUM_PIX);
                            break;
				case 2048: fprintf(stdout, "\033[36m%5d\033[0m", \
							       data[y][x]);
                            Display_Pic(GAME_NUM_2048, x*GAME_NUM_PIX, y*GAME_NUM_PIX);
                            break;
				}
	    	}
		}
		fputc('\n', stdout);
    }

    /* 打印游戏结果 */
	fprintf(stdout, "当前最高纪录：\033[1;35m%d\033[0m", maxScore(data));
    fflush(stdout);
}

/*
 * 函数名：moveUp
 * 功能：把游戏数据上移
 * 参数：需要上移的游戏数据
 * 返回值：无
*/
void moveUp(int data[NR][NR])
{
    int x, y;
    int idx;
    int isChange = 0;	// 可移动标记位

    /* 先累加 */
    for (x = 0; x <= NR-1; x++)
    {
        for (y = 0; y < NR-1; y++)
		{
		    if (data[y][x] == 0)
		    {
		        continue;
		    }
		    /* 查找是否可加，能加则加 */
		    for (idx = y+1; idx <= NR-1; idx++)
		    {
		        if (data[idx][x] == 0)
				{
				    continue;
				}
				else if (data[idx][x] != data[y][x])
				{
				    break;
				}
				else
				{
				    data[y][x]  += data[idx][x];
				    data[idx][x] = 0;
				    isChange = 1;
				    break;
				}
		    }
		}
    }

    /* 累加完后移动 */
    for (x = 0; x <= NR-1; x++)
    {
        for (y = 1; y <= NR-1; y++)
		{
		    if (data[y][x] == 0)
		    {
		        continue;
		    }

		    /* 寻找移动点 */
    	    idx = y-1;
		    while (data[idx][x] == 0 && idx >= 0)
		    {
		        idx--;
		    }

    	    if (data[idx+1][x] == 0)
		    {
		        data[idx+1][x] = data[y][x];
		        data[y][x] = 0;
		        isChange = 1;
		    }
		}
    }

	/* 成功移动之后需要随即产生一个数 */
    if (isChange == 1)
    {
        getRand(data);
    }
}

/*
 * 函数名：moveDown
 * 功能：把游戏数据下移
 * 参数：需要下移的游戏数据
 * 返回值：无
*/
void moveDown(int data[NR][NR])
{
    int x, y;
    int idx;
    int isChange = 0;   // 可移动标记位

    /* 先累加 */
    for (x = 0; x <= NR-1; x++)
    {
        for (y = NR-1; y >= 1; y--)
    	{
    	    if (data[y][x] == 0)
    	    {
    	        continue;
    	    }
    	    /* 查找是否可加，能加则加 */
    	    for (idx = y-1; idx >= 0; idx--)
    	    {
    	        if (data[idx][x] == 0)
        		{
        		    continue;
        		}
        		else if (data[idx][x] != data[y][x])
        		{
        		    break;
        		}
        		else
        		{
        		    data[y][x]  += data[idx][x];
        		    data[idx][x] = 0;
        		    isChange = 1;
        		    break;
        		}
    	    }
    	}
    }
    /* 累加完后移动 */
    for (x = 0; x <= NR-1; x++)
    {
        for (y = NR-2; y >= 0; y--)
    	{
    	    if (data[y][x] == 0)
    	    {
    	        continue;
    	    }
    	    /* 寻找移动点 */
    	    idx = y+1;
    	    while (data[idx][x] == 0 && idx <= NR-1)
    	    {
    	        idx++;
    	    }

    	    if (data[idx-1][x] == 0)
    	    {
        		data[idx-1][x] = data[y][x];
        		data[y][x] = 0;
        		isChange = 1;
    	    }
    	}
    }

    /* 成功移动之后需要随即产生一个数 */
    if (isChange == 1)
    {
        getRand(data);
    }
}

/*
 * 函数名：moveRight
 * 功能：把游戏数据右移
 * 参数：需要右移的游戏数据
 * 返回值：无
*/
void moveRight(int data[NR][NR])
{
    int x, y;
    int idx;
    int isChange = 0;   // 可移动标记位

    /* 先累加 */
    for (y = 0; y < NR; y++)
    {
        for (x = NR-1; x >= 0; x--)
    	{
    	    if (data[y][x] == 0)
    	    {
    	        continue;
    	    }
    	    /* 查找是否可加，能加则加 */
    	    for (idx = x-1; idx >= 0; idx--)
    	    {
    	        if (data[y][idx] == 0)
        		{
        		    continue;
        		}
        		else if (data[y][idx] != data[y][x])
        		{
        		    break;
        		}
        		else
        		{
        		    data[y][x]  += data[y][x];
        		    data[y][idx] = 0;
        		    isChange = 1;
        		    break;
        		}
    	    }
    	}
    }
    /* 累加完后移动 */
    for (y = 0; y < NR; y++)
    {
        for (x = NR-2; x >= 0; x--)
    	{
    	    if (data[y][x] == 0)
    	    {
    	        continue;
    	    }
    	    /* 寻找移动点 */
    	    idx = x+1;
    	    while (data[y][idx] == 0 && idx <= NR-1)
    	    {
    	        idx++;
    	    }

      	    if (data[y][idx-1] == 0)
    	    {
    	        data[y][idx-1] = data[y][x];
    	        data[y][x] = 0;
    	        isChange = 1;
    	    }
    	}
    }

    /* 成功移动之后需要随即产生一个数 */
    if (isChange == 1)
    {
        getRand(data);
    }
}

/*
 * 函数名：moveLeft
 * 功能：把游戏数据左移
 * 参数：需要左移的游戏数据
 * 返回值：无
*/
void moveLeft(int data[NR][NR])
{
    int x, y;
    int idx;
    int isChange = 0;   // 可移动标记位

    /* 先累加 */
    for (y = 0; y <= NR-1; y++)
    {
        for (x = 0; x < NR-1; x++)
    	{
    	    if (data[y][x] == 0)
    	    {
    	        continue;
    	    }
    	    /* 查看是否可加，能加则加 */
    	    for (idx = x+1; idx <= NR-1; idx++)
    	    {
    	        if (data[y][idx] == 0)
        		{
        		    continue;
        		}
        		else if (data[y][idx] != data[y][x])
        		{
        		    break;
        		}
        		else
        		{
        		    data[y][x]  += data[y][idx];
        		    data[y][idx] = 0;
        		    isChange = 1;
        		    break;
        		}
    	    }
    	}
    }
    /* 累加完后移动 */
    for (y = 0; y <= NR-1; y++)
    {
        for (x = 1; x <= NR-1; x++)
    	{
    	    if (data[y][x] == 0)
    	    {
    	        continue;
    	    }
    	    /* 寻找移动点 */
    	    idx = x-1;
    	    while (data[y][idx] == 0 && idx >= 0)
    	    {
    	        idx--;
    	    }

    	    if (data[y][idx+1] == 0)
    	    {
    	        data[y][idx+1] = data[y][x];
    	        data[y][x] = 0;
    	        isChange = 1;
    	    }
    	}
    }

    /* 成功移动之后需要随即产生一个数 */
    if (isChange == 1)
    {
        getRand(data);
    }
}
/*
 * 函数名：checkGameOver
 * 功能：检查游戏是否结束
 * 参数：需要检查的游戏数据
 * 返回值：游戏结束返回1，没有结束返回0
*/
int checkGameOver(int data[NR][NR])
{
    int x, y;

    /* 判断有无空位0 */
    for (y = 0; y < NR; y++)
    {
        for (x = 0; x < NR; x++)
    	{
    	    if (data[y][x] == 0)
    	    {
    	        return 0;
    	    }
    	}
    }
    /* 判断各行是否可加 */
    for (y = 0; y < NR; y++)
    {
        for (x = 0; x < NR-1; x++)
    	{
    	    if (data[y][x] == data[y][x+1])
    	    {
    	        return 0;
    	    }
    	}
    }
    /* 判断各列是否可加 */
    for (x = 0; x < NR; x++)
    {
        for (y = 0; y < NR-1; y++)
    	{
    	    if (data[y][x] == data[y+1][x])
    	    {
    	       return 0;
    	    }
    	}
    }
    /* 游戏结束 */
    return 1;
}

/*
 * 函数名：getInput
 * 功能：获取用户按键输入
 * 参数：无
 * 返回值：返回用户输入的对应按键
*/
int getInput(void)
{
    char ch;
    int key;

    ch = fgetc(stdin);

    if (ch == '\033' && fgetc(stdin) == '[')    // 方向键
    {
        ch = fgetc(stdin);
    	switch (ch)
    	{
    	    case 'A': key = UP;     break;
    	    case 'B': key = DOWN;   break;
    	    case 'C': key = RIGHT;  break;
    	    case 'D': key = LEFT;   break;
    	}
    }
    else if (ch == 'q') // 退出键
	   key = EXIT;
    else                // 其它键
	   key = UNKNOW;

    return key;
}

/*
 * 函数名：getRand
 * 功能：在游戏数据中产生一个随机数，2的概率为80%，4的概率为20%
 * 参数：需要产生随机数的游戏数据
 * 返回值：无
*/
void getRand(int data[NR][NR])
{
    int x, y;
    int idx;  /* 随机种子索引 */
    int seedLib[] = {2,2,2,4,2,2,2,4,2,2};

    /* 全局查找是否有空位产生随机数 */
    while (1)
    {
        /* 随即定位 */
        x = rand() % NR;
        y = rand() % NR;

        /* 定位的位置有数了 */
        if (data[y][x] != 0)
    	    continue;

        /* 空白位置产生数 */
        idx = rand() % 10;
    	data[y][x] = seedLib[idx];

        return;
    }
}

/*
 * 函数名：maxScore
 * 功能：获取游戏最高分
 * 参数：需要获取最高分的游戏数据
 * 返回值：返回游戏数据中的最大值
*/
int maxScore(int data[NR][NR])
{
    int x, y;
    int maxValue = 0;

    for (y = 0; y < NR; y++)
    {
        for (x = 0; x < NR; x++)
    	{
    	    if (maxValue < data[y][x])
    	    {
    	        maxValue = data[y][x];
    	    }
    	}
    }

    return maxValue;
}

/*
 * 函数名：exitGame
 * 功能：配置退出游戏前的一些终端配置
 * 参数：无
 * 返回值：无
*/
void exitGame(void)
{
    close_fb();
    system("stty icanon");          // 恢复缓冲
    system("stty echo");            // 恢复回显
    fprintf(stdout, "\033[?25h");   // 显示鼠标
    fputc('\n', stdout);            // 让终端提示符下一行显示
    exit(0);                        // 退出游戏
}
