#include "common.h"
#include "about.h"
void into_about()
{
  work = ABOUT_MENU;
  myGLCD.fillScr(255, 255, 255);
  show_chinese_sentence(23, 72, "\xB2\xD9\xD7\xF7", 0, 0, 0, 2);  //操作
  show_chinese_sentence(133, 72, "\xB9\xD8\xD3\xDA", 0, 0, 0, 2);  //关于
  about_menu_point = 0;
  draw_about_menu_point(about_menu_point, 255, 0, 0);
}
void draw_about_menu_point(int point, int r, int g, int b)
{
  int x1[2] = {21, 131};
  int y1 = 70;
  int x2[2] = {88, 198};
  int y2 = 105;
  myGLCD.setColor(r, g, b);
  myGLCD.drawRect(x1[point], y1, x2[point], y2);
  myGLCD.drawRect(x1[point] - 2, y1 - 2, x2[point] + 2, y2 + 2);
}
void choose_help()
{
  if(about_menu_point == 1)
  {
    draw_about_menu_point(about_menu_point, 255, 255, 255);
    about_menu_point = 0;
    draw_about_menu_point(about_menu_point, 255, 0, 0);
  }
}
void choose_ap()
{
  if(about_menu_point == 0)
  {
    draw_about_menu_point(about_menu_point, 255, 255, 255);
    about_menu_point = 1;
    draw_about_menu_point(about_menu_point, 255, 0, 0);
  }
}
void into_help()
{
  work = ABOUT_HELP;
  myGLCD.fillScr(255, 255, 255);
  show_help_menu();
  about_help_point = 0;
  draw_help_point(about_help_point, 255, 0, 0);
}
void show_help_menu()
{
  show_chinese_sentence(4, 4, "\xCD\xA8\xD3\xC3", 0, 0, 0, 1);  //通用
  show_chinese_sentence(4, 4 + 19, "\xD6\xF7\xB2\xCB\xB5\xA5", 0, 0, 0, 1);  //主菜单
  show_chinese_sentence(4, 4 + 19 * 2, "\xCE\xC4\xBC\xFE\xC1\xD0\xB1\xED", 0, 0, 0, 1);  //文件列表
  show_chinese_sentence(4, 4 + 19 * 3, "\xB5\xE7\xD7\xD3\xCA\xE9", 0, 0, 0, 1);  //电子书
  show_chinese_sentence(4, 4 + 19 * 4, "\xD4\xC4\xB6\xC1\xC9\xE8\xD6\xC3", 0, 0, 0, 1);  //阅读设置
  show_chinese_sentence(4, 4 + 19 * 5, "\xCD\xBC\xC6\xAC\xC9\xE8\xD6\xC3", 0, 0, 0, 1);  //图片设置
  show_chinese_sentence(4, 4 + 19 * 6, "\xCE\xC4\xBC\xFE\xB2\xD9\xD7\xF7", 0, 0, 0, 1);  //文件操作
}
void draw_help_point(int point, int r, int g, int b)
{
  myGLCD.setColor(r, g, b);
  myGLCD.drawRect(2, 2 + 19 * point, 69, 21 + 19 * point);
}
void change_help_point(int change)
{
  if(about_help_point + change >= 0 && about_help_point + change < 7)
  {
    draw_help_point(about_help_point, 255, 255, 255);
    about_help_point += change;
    draw_help_point(about_help_point, 255, 0, 0);
    delay(200);
  }
}
void show_help(int point)
{
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(76, 0, 219, 175);
  switch(point)
  {
    case 0: //通用
            show_english(76, 4, "UP:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 3, 4, "\xB9\xE2\xB1\xEA\xC9\xCF\xD2\xC6", 0, 0, 0, 1);  //光标上移
            show_english(76, 4 + 19, "DOWN:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 5, 4 + 19, "\xB9\xE2\xB1\xEA\xCF\xC2\xD2\xC6", 0, 0, 0, 1);  //光标下移
            show_english(76, 4 + 19 * 2, "LEFT:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 5, 4 + 19 * 2, "\xB9\xE2\xB1\xEA\xD7\xF3\xD2\xC6", 0, 0, 0, 1);  //光标左移
            show_english(76, 4 + 19 * 3, "RIGHT:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 6, 4 + 19 * 3, "\xB9\xE2\xB1\xEA\xD3\xD2\xD2\xC6", 0, 0, 0, 1);  //光标右移
            show_english(76, 4 + 19 * 4, "A:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 2, 4 + 19 * 4, "\xC8\xB7\xB6\xA8", 0, 0, 0, 1);  //确定
            show_english(76, 4 + 19 * 5, "B:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 2, 4 + 19 * 5, "\xB7\xB5\xBB\xD8", 0, 0, 0, 1);  //返回
            break;
    case 1: //主菜单
            show_chinese_sentence(76, 4, "\xCD\xBC\xB1\xEA\xCB\xB5\xC3\xF7\xA3\xBA", 0, 0, 0, 1);  //图标说明：
            show_chinese_sentence(76, 4 + 19, "\xB5\xE7\xD7\xD3\xCA\xE9", 0, 0, 0, 1);  //电子书
            show_chinese_sentence(76 + 16 * 4, 4 + 19, "\xD2\xF4\xC0\xD6", 0, 0, 0, 1);  //音乐
            show_chinese_sentence(76 + 16 * 7, 4 + 19, "\xCD\xBC\xC6\xAC", 0, 0, 0, 1);  //图片
            show_chinese_sentence(76, 4 + 19 * 2, "\xD3\xCE\xCF\xB7", 0, 0, 0, 1);  //游戏
            show_chinese_sentence(76 + 16 * 4, 4 + 19 * 2, "\xCE\xC4\xBC\xFE", 0, 0, 0, 1);  //文件
            show_chinese_sentence(76 + 16 * 7, 4 + 19 * 2, "\xB9\xD8\xD3\xDA", 0, 0, 0, 1);  //关于
            break;
    case 2: //文件列表
            show_english(76, 4, "LEFT:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 5, 4, "\xC9\xCF\xD2\xBB\xD2\xB3", 0, 0, 0, 1);  //上一页
            show_english(76, 4 + 19, "RIGHT:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 6, 4 + 19, "\xCF\xC2\xD2\xBB\xD2\xB3", 0, 0, 0, 1);  //下一页
            break;
    case 3: //电子书
            show_english(76, 4, "LEFT:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 5, 4, "\xC9\xCF\xD2\xBB\xD2\xB3", 0, 0, 0, 1);  //上一页
            show_english(76, 4 + 19, "RIGHT:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 6, 4 + 19, "\xCF\xC2\xD2\xBB\xD2\xB3", 0, 0, 0, 1);  //下一页
            show_english(76, 4 + 19 * 2, "START:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 6, 4 + 19 * 2, "\xB4\xF2\xBF\xAA\xC9\xE8\xD6\xC3", 0, 0, 0, 1);  //打开设置
            break;
    case 4: //阅读设置
            show_english(76, 4, "LEFT:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 5, 4, "\xBC\xF5\xD0\xA1\xCA\xFD\xD6\xB5", 0, 0, 0, 1);  //减小数值
            show_english(76, 4 + 19, "RIGHT:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 6, 4 + 19, "\xD4\xF6\xB4\xF3\xCA\xFD\xD6\xB5", 0, 0, 0, 1);  //增大数值
            show_chinese_sentence(76, 4 + 19 * 2, "\xB0\xB4\xD7\xA1", 0, 0, 0, 1);  //按住
            show_english(76 + 16 * 2, 4 + 19 * 2, "SELECT", 0, 0, 0, 1);
            show_chinese_sentence(76 + 16 * 2 + 8 * 6, 4 + 19 * 2, "\xBC\xD3\xBF\xEC\xB8\xC4\xB1\xE4", 0, 0, 0, 1);  //加快改变
            show_english(76, 4 + 19 * 4, "SELECT:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 7, 4 + 19 * 4, "\xD2\xC6\xB6\xAF\xB9\xE2\xB1\xEA", 0, 0, 0, 1);  //移动光标
            break;
    case 5: //图片设置
            show_english(76, 4, "LEFT:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 5, 4, "\xBC\xF5\xD0\xA1\xCA\xFD\xD6\xB5", 0, 0, 0, 1);  //减小数值
            show_english(76, 4 + 19, "RIGHT:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 6, 4 + 19, "\xD4\xF6\xB4\xF3\xCA\xFD\xD6\xB5", 0, 0, 0, 1);  //增大数值
            show_chinese_sentence(76, 4 + 19 * 2, "\xB0\xB4\xD7\xA1", 0, 0, 0, 1);  //按住
            show_english(76 + 16 * 2, 4 + 19 * 2, "SELECT", 0, 0, 0, 1);
            show_chinese_sentence(76 + 16 * 2 + 8 * 6, 4 + 19 * 2, "\xBC\xD3\xBF\xEC\xB8\xC4\xB1\xE4", 0, 0, 0, 1);  //加快改变
            show_english(76, 4 + 19 * 3, "START:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 6, 4 + 19 * 3, "\xCD\xA3\xD6\xB9\xCF\xD4\xCA\xBE", 0, 0, 0, 1);  //停止显示
            break;
    case 6: //文件操作
            show_english(76, 4, "SELECT:", 0, 0, 0, 1);
            show_chinese_sentence(76 + 8 * 7, 4, "\xC9\xBE\xB3\xFD", 0, 0, 0, 1);  //删除
            show_chinese_sentence(76, 4 + 19, "\xD6\xA7\xB3\xD6\xB5\xDD\xB9\xE9\xC9\xBE\xB3\xFD\xCE\xC4\xBC\xFE\xBC\xD0", 0, 0, 0, 1);  //支持递归删除文件夹
            break;
  }
}
void into_ap()
{
  work = ABOUT_AP;
  myGLCD.fillScr(255, 255, 255);
  show_english(4, 4, "Arduino Player beta1.0", 0, 0, 0, 1);
  show_chinese_sentence(4, 4 + 19, "\xD6\xF7\xD2\xAA\xB9\xA6\xC4\xDC\xA3\xBA", 0, 0, 0, 1);  //主要功能：
  show_english(4, 4 + 19 * 2, "1.", 0, 0, 0, 1);
  show_chinese_sentence(4 + 8 * 2, 4 + 19 * 2, "\xB5\xE7\xD7\xD3\xCA\xE9\xCF\xD4\xCA\xBE\xA1\xA2\xB7\xAD\xD2\xB3\xA1\xA2\xC9\xE8\xD6\xC3", 0, 0, 0, 1);  //电子书显示、翻页、设置
  show_english(4, 4 + 19 * 3, "2.", 0, 0, 0, 1);
  show_chinese_sentence(4 + 8 * 2, 4 + 19 * 3, "\xD2\xF4\xC0\xD6\xB2\xA5\xB7\xC5\xA1\xA2\xD4\xDD\xCD\xA3\xA1\xA2\xD1\xAD\xBB\xB7", 0, 0, 0, 1);  //音乐播放、暂停、循环
  show_english(4, 4 + 19 * 4, "3.", 0, 0, 0, 1);
  show_chinese_sentence(4 + 8 * 2, 4 + 19 * 4, "\xCD\xBC\xC6\xAC\xCF\xD4\xCA\xBE\xA1\xA2\xCB\xF5\xB7\xC5\xA1\xA2\xD0\xFD\xD7\xAA", 0, 0, 0, 1);  //图片显示、缩放、旋转
  show_english(4, 4 + 19 * 5, "4.", 0, 0, 0, 1);
  show_chinese_sentence(4 + 8 * 2, 4 + 19 * 5, "\xD6\xA7\xB3\xD6\xCD\xE2\xD6\xC3\xD3\xCE\xCF\xB7\xBD\xE2\xCE\xF6\xB2\xA2\xD4\xCB\xD0\xD0", 0, 0, 0, 1);  //支持外置游戏解析并运行
  show_english(4, 4 + 19 * 6, "5.", 0, 0, 0, 1);
  show_chinese_sentence(4 + 8 * 2, 4 + 19 * 6, "\xCE\xC4\xBC\xFE\xBC\xB0\xCE\xC4\xBC\xFE\xBC\xD0\xE4\xAF\xC0\xC0\xA1\xA2\xC9\xBE\xB3\xFD", 0, 0, 0, 1);  //文件及文件夹浏览、删除
  show_english(4 + 8 * 12, 4 + 19 * 7, "Made By ", 0, 0, 0, 1);
  show_chinese_sentence(4 + 8 * 20, 4 + 19 * 7, "\xD0\xA1\xBA\xA2\xD7\xD3", 0, 0, 0, 1);  //小孩子
  myGLCD.drawCircle(77, 163, 5);
  myGLCD.drawCircle(77, 163, 3);
  myGLCD.drawCircle(77, 163, 2);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(74, 162, 75, 164);
  show_english(4 + 8 * 10, 4 + 19 * 8, "Copyleft", 0, 0, 0, 1);
}
