#include "framebuffer.h"
#include "2048game.h"

intel_pjt_t intel_pjt;

int Get_ts_info()
{
	int x,y;

	read(intel_pjt.ts,&intel_pjt.event.touch,sizeof(intel_pjt.event.touch)); //这个函数默认是堵塞的

	if(intel_pjt.event.touch.type == EV_ABS && intel_pjt.event.touch.code == ABS_X) x=intel_pjt.event.touch.value;
	if(intel_pjt.event.touch.type == EV_ABS && intel_pjt.event.touch.code == ABS_Y) y=intel_pjt.event.touch.value;

	if(intel_pjt.event.touch.type == EV_KEY && intel_pjt.event.touch.code == BTN_TOUCH && intel_pjt.event.touch.value == 0)
	{
		intel_pjt.ts_info.flag_press = 0;
	}
	if(intel_pjt.event.touch.type == EV_KEY && intel_pjt.event.touch.code == BTN_TOUCH && intel_pjt.event.touch.value == 1) //手没离开
	{
		intel_pjt.ts_info.flag_press = 1;
	}

	intel_pjt.ts_info.ts_x = x*800/1024;
	intel_pjt.ts_info.ts_y = y*480/600;
    
}

int Display_Pic(char * pic_path, int dis_x, int dis_y)
{
	if (dis_x > 800 || dis_x < 0 ||
		dis_y > 480 || dis_y < 0)
	{
		perror("error input");
		return -1;
	}

	int bmp = open(pic_path,O_RDONLY);//打开图片
	if(bmp == -1)
	{
		printf("opening %s\n", pic_path);
		perror("打开图片失败!");
	}

	int *rend_p = intel_pjt.lcd_mmap + 800*dis_y + dis_x;

	//获取图片的宽和高
	int w,h;//存放宽和高
	lseek(bmp,18,SEEK_SET);
	read(bmp,&w,4);
	read(bmp,&h,4);
	// printf("w:%d --- h:%d\n",w,h);

	//判断图片的宽的字节数是不是4的倍数
	int skip;//补数
	if(w*3%4 != 0)
	{
		skip = 4 - ((w*3)%4);
	}
	else //如果是4的倍数，则补数为0
	{
		skip = 0;
	}

	// printf("补数为：%d\n",skip);
	//重新跳图片的前54个字节之后再去读图片的像素点
	int  read_num;
	read_num = (w*h*3)+(skip*h);
	char rgb[read_num];
	lseek(bmp,54,SEEK_SET);
	read(bmp,rgb,read_num);//读取数据的时候，除了前54字节之外，所有的数据都要去读（像素点+系统补的字节数）

	int x,y,num = 0;
	for(y=0; y<h; y++)
	{
		for(x=0; x<w; x++,num+=3)
		{
			*(rend_p + 800*(h-1-y)+x) = rgb[num] <<0 | rgb[num+1] <<8 | rgb[num+2] <<16;   

		}

		num+=skip;//跳过系统补的字节数，在进行映射指针的像素点赋值
	}

	close(bmp);

	return 0;
}

int init_fb()
{
	printf("初始化项目！\n");

	intel_pjt.lcd = open(LCD_DEV_PATH, O_RDWR);
	if (intel_pjt.lcd == -1)
	{
		perror("lcd open failed!");
	}

	intel_pjt.ts = open(TS_DEV_PATH, O_RDONLY);
	if (intel_pjt.ts == -1)
	{
		perror("touch screen open failed!");
	}
	
	intel_pjt.lcd_mmap = mmap(NULL, MMAP_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, intel_pjt.lcd ,0);
	if (!intel_pjt.lcd_mmap)
	{
		perror("mmap failed!");
	}
	
	Display_Pic(UI_GAME_PIC_PATH,0,0);
    Display_Pic(UI_PICT_L_PIC_PATH,600,300);
    Display_Pic(UI_PICT_L_PIC_PATH,600,200);
    Display_Pic(UI_PICT_L_PIC_PATH,700,300);
    Display_Pic(UI_PICT_L_PIC_PATH,500,300);

	return 0;
}


int close_fb()
{
	printf("结束释放项目！\n");

	close(intel_pjt.lcd);
	close(intel_pjt.ts);
	munmap(intel_pjt.lcd_mmap, MMAP_LENGTH);
}

