#include "common.h"
#include "file.h"
#include "menu.h"
void file_into()
{
  char filename[128];
  File entry;
  if(!file_amount)
    return;
  if(strlen(workdirname) == 1)
    sprintf(filename, "%s%s", workdirname, file_list[file_list_point]);
  else
    sprintf(filename, "%s/%s", workdirname, file_list[file_list_point]);
  entry = SD.open(filename);
  if(entry.isDirectory())
  {
      entry.close();
      draw_file_list_point(file_list_point, 255, 255, 255);  //光标
      strcpy(workdirname, filename);
      file_amount = get_file_amount(workdirname, workdircase);  //文件数量
      file_offset = 0;
      read_file_list(workdirname, file_offset, workdircase);  //载入文件列表
      show_file_menu();  //显示文件列表
      if(file_amount)
      {
        file_list_point = 0;
        myGLCD.setColor(0, 0, 255);
        myGLCD.drawRect(210, 2, 218, 173);
        draw_file_list_point(file_list_point, 255, 0, 0);  //光标
      }
      else
        show_chinese_sentence(111, 4, "\xBF\xD5\xCE\xC4\xBC\xFE\xBC\xD0", 0, 0, 0, 1);  //空文件夹
  }
  return;
}
void file_back()
{
  if(strcmp(workdirname, "/") == 0)
  {
    exit_menu();
    return;
  }
  else
  {
    draw_file_list_point(file_list_point, 255, 255, 255);  //光标
    back_dir();
    file_amount = get_file_amount(workdirname, workdircase);  //文件数量
    file_offset = 0;
    read_file_list(workdirname, file_offset, workdircase);  //载入文件列表
    show_file_menu();  //显示文件列表
    file_list_point = 0;
    draw_file_list_point(file_list_point, 255, 0, 0);  //光标
  }
}
void back_dir()
{
  int i;
  for(i = strlen(workdirname) - 1; i >= 0; i--)
  {
    if(workdirname[i] == '/')
    {
      if(i == 0)
        workdirname[1] = '\0';
      else
        workdirname[i] = '\0';
      break;
    }
  }
}
void into_file_delete()
{
  if(file_amount)
  {
    draw_file_list_point(file_list_point, 255, 255, 255);
    show_file_delete();
    work = FILE_DELETE;
    file_delete_point = 0;
    myGLCD.setColor(255, 0, 0);
    myGLCD.drawRect(8, 138, 43, 157);
  }
}
void show_file_delete()
{
  show_chinese_sentence(10, 120, "\xC8\xB7\xB6\xA8\xC9\xBE\xB3\xFD\xA3\xBF", 0, 0, 0, 1);  //确定删除？
  show_chinese_sentence(10, 140, "\xC8\xA1\xCF\xFB", 0, 0, 0, 1);  //取消
  show_chinese_sentence(50, 140, "\xC8\xB7\xB6\xA8", 0, 0, 0, 1);  //确定
}
void choose_yes()
{
  if(file_delete_point == 0)
  {
    file_delete_point = 1;
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRect(8, 138, 43, 157);
    myGLCD.setColor(255, 0, 0);
    myGLCD.drawRect(48, 138, 83, 157);
  }
}
void choose_no()
{
  if(file_delete_point == 1)
  {
    file_delete_point = 0;
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRect(48, 138, 83, 157);
    myGLCD.setColor(255, 0, 0);
    myGLCD.drawRect(8, 138, 43, 157);
  }
}
void file_yes_delete()
{
  char deletefilename[128];
  File entry;
  work = FILE_MENU;
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(8, 120, 90, 157);
  if(strlen(workdirname) == 1)
    sprintf(deletefilename, "%s%s", workdirname, file_list[file_list_point]);
  else
    sprintf(deletefilename, "%s/%s", workdirname, file_list[file_list_point]);
  entry = SD.open(deletefilename);
  if(entry.isDirectory())
  {
    entry.close();
    rm_rf(deletefilename);
  }
  else
  {
    entry.close();
    SD.remove(deletefilename);
  }
  file_amount = get_file_amount(workdirname, workdircase);  //文件数量
  file_offset = 0;
  read_file_list(workdirname, file_offset, workdircase);  //载入文件列表
  show_file_menu();  //显示文件列表
  if(file_amount)
  {
    file_list_point = 0;
    myGLCD.setColor(0, 0, 255);
    myGLCD.drawRect(210, 2, 218, 173);
    draw_file_list_point(file_list_point, 255, 0, 0);  //光标
  }
  else
    show_chinese_sentence(111, 4, "\xBF\xD5\xCE\xC4\xBC\xFE\xBC\xD0", 0, 0, 0, 1);  //空文件夹
}
void file_no_delete()
{
  work = FILE_MENU;
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(8, 120, 90, 157);
  draw_file_list_point(file_list_point, 255, 0, 0);
}
void rm_rf(char* dirname)
{
  File dir, entry;
  char nextdirname[128];
  if(get_file_amount(dirname, BOTH_FILE_DIR) == 0)
    SD.rmdir(dirname);
  else
  {
    dir = SD.open(dirname);
    dir.rewindDirectory();
    while(true)
    {
      entry = dir.openNextFile();
      if(!entry)
        break;
      sprintf(nextdirname, "%s/%s", dirname, entry.name());
      if(entry.isDirectory())
      {
        entry.close();
        rm_rf(nextdirname);
      }
      else
      {
        entry.close();
        SD.remove(nextdirname);
      }
    }
    dir.close();
    SD.rmdir(dirname);
  }
}

