#include "common.h"
#include "button.h"
#include "menu.h"
#include "book.h"
#include "music.h"
#include "image.h"
#include "file.h"
#include "about.h"
void press_button()
{
  if(digitalRead(btnUP) == LOW)
    press_btnUP();
  if(digitalRead(btnDOWN) == LOW)
    press_btnDOWN();
  if(digitalRead(btnLEFT) == LOW)
    press_btnLEFT();
  if(digitalRead(btnRIGHT) == LOW)
    press_btnRIGHT();
  if(digitalRead(btnA) == LOW)
    press_btnA();
  if(digitalRead(btnB) == LOW)
    press_btnB();
  if(digitalRead(btnSTART) == LOW)
    press_btnSTART();
  if(digitalRead(btnSELECT) == LOW)
    press_btnSELECT();
}
void press_btnUP()
{
  switch(work)
  {
    case MAIN_MENU:change_main_menu_point(0, -1); break;
    case BOOK_MENU:
    case MUSIC_MENU:
    case IMAGE_MENU:
    case GAME_MENU:
    case FILE_MENU:
                    change_file_list_point(-1); break;
    case BOOK_SHOW:last_book(book_name); break;
    case BOOK_CONFIG:if(in_pallet)
                     {
                       change_pallet_point(-1);
                       delay(200);
                     }
                     break;
    case MUSIC_PLAY:change_next_music(-1); break;
    case IMAGE_SHOW:change_image_point(-1); break;
    case ABOUT_HELP:change_help_point(-1); break;
  }
}
void press_btnDOWN()
{
  switch(work)
  {
    case MAIN_MENU:change_main_menu_point(0, 1); break;
    case BOOK_MENU:
    case MUSIC_MENU:
    case IMAGE_MENU:
    case GAME_MENU:
    case FILE_MENU:
                    change_file_list_point(1); break;
    case BOOK_SHOW:next_book(book_name); break;
    case BOOK_CONFIG:if(in_pallet)
                     {
                       change_pallet_point(1);
                       delay(200);
                     }
                     break;
    case MUSIC_PLAY:change_next_music(1); break;
    case IMAGE_SHOW:change_image_point(1); break;
    case ABOUT_HELP:change_help_point(1); break;
  }
}
void press_btnLEFT()
{
  switch(work)
  {
    case MAIN_MENU:change_main_menu_point(-1, 0); break;
    case BOOK_MENU:
    case MUSIC_MENU:
    case IMAGE_MENU:
    case GAME_MENU:
    case FILE_MENU:
                    change_file_list_point(-9); break;
    case BOOK_SHOW:last_book(book_name); break;
    case BOOK_CONFIG:if(in_pallet)
                     {
                       if(digitalRead(btnSELECT) == LOW)
                         change_temp_rgb(temp_point, book_config_point, -10);
                       else
                         change_temp_rgb(temp_point, book_config_point, -1);
                     }
                     else
                     {
                       switch(book_config_point)
                       {
                         case 2: change_dot(-1); break;
                         case 3: change_offset(-1); break;
                       }
                     }
                     break;
    case MUSIC_PLAY:change_next_music(-1); break;
    case IMAGE_SHOW:switch(image_point)
                    {
                      case 0: change_image_mode(-1); break;
                      case 1: if(digitalRead(btnSELECT) == LOW)
                                change_image_left(-10);
                              else
                                change_image_left(-1);
                              break;
                      case 2: if(digitalRead(btnSELECT) == LOW)
                                change_image_top(-10);
                              else
                                change_image_top(-1);
                              break;
                    }
                    break;
    case FILE_DELETE: choose_no(); break;
    case ABOUT_MENU: choose_help(); break;
  }
}
void press_btnRIGHT()
{
  switch(work)
  {
    case MAIN_MENU:change_main_menu_point(1, 0); break;
    case BOOK_MENU:
    case MUSIC_MENU:
    case IMAGE_MENU:
    case GAME_MENU:
    case FILE_MENU:
                    change_file_list_point(9); break;
    case BOOK_SHOW:next_book(book_name); break;
    case BOOK_CONFIG:if(in_pallet)
                     {
                       if(digitalRead(btnSELECT) == LOW)
                         change_temp_rgb(temp_point, book_config_point, 10);
                       else
                         change_temp_rgb(temp_point, book_config_point, 1);
                     }
                     else
                     {
                       switch(book_config_point)
                       {
                         case 2: change_dot(1); break;
                         case 3: change_offset(1); break;
                       }
                     }
                     break;
    case MUSIC_PLAY:change_next_music(1); break;
    case IMAGE_SHOW:switch(image_point)
                    {
                      case 0: change_image_mode(1); break;
                      case 1: if(digitalRead(btnSELECT) == LOW)
                                change_image_left(10);
                              else
                                change_image_left(1);
                              break;
                      case 2: if(digitalRead(btnSELECT) == LOW)
                                change_image_top(10);
                              else
                                change_image_top(1);
                              break;
                    }
                    break;
    case FILE_DELETE: choose_yes(); break;
    case ABOUT_MENU: choose_ap(); break;
  }
}
void press_btnA()
{
  switch(work)
  {
    case MAIN_MENU:into_menu(); break;
    case BOOK_MENU:{
                     strcpy(book_name, "book/");
                     strcat(book_name, file_list[file_list_point]);
                     into_book(book_name, 0);
                     break;
                   }
    case BOOK_CONFIG:if(!in_pallet)
                     {
                       switch(book_config_point)
                       {
                         case 0: case 1:{
                                          draw_book_config_point(book_config_point, 255, 255, 255);
                                          show_pallet(book_config_point);
                                          break;
                                        }
                         case 4:{
                                  txtbr = temp_r[0];
                                  txtbg = temp_g[0];
                                  txtbb = temp_b[0];
                                  txtfr = temp_r[1];
                                  txtfg = temp_g[1];
                                  txtfb = temp_b[1];
                                  txtdot = temp_dot;
                                  txt_now_offset = txt_max_offset * temp_offset_rate / 100;
                                  if(txt_now_offset >= txt_max_offset)
                                    txt_now_offset -= 20;
                                }
                         case 5:exit_book_config(); break;
                       }
                     }
                     else if(temp_point == 3)
                     {
                       myGLCD.setColor(temp_r[book_config_point], temp_g[book_config_point], temp_b[book_config_point]);
                       myGLCD.fillRect(146, 2 + 66 * book_config_point, 209, 2 + 66 * book_config_point + 63);
                       in_pallet = false;
                       draw_book_config_point(book_config_point, 255, 0, 0);
                     }
                     break;
    case MUSIC_MENU:{
                      strcpy(music_name, file_list[file_list_point]);
                      into_music(music_name);
                      break;
                    }
    case MUSIC_PLAY: stop_music(); break;
    case IMAGE_MENU:{
                      strcpy(image_name, "image/");
                      strcat(image_name, file_list[file_list_point]);
                      into_image(image_name);
                      break;
                    }
    case IMAGE_SHOW:switch(image_point)
                    {
                      case 3: image_update(); break;
                      case 4: image_left_spin(); break;
                      case 5: image_right_spin(); break;
                      case 6: image_next(-1); break;
                      case 7: image_next(1); break;
                    }
                    break;
    case FILE_MENU: file_into(); break;
    case FILE_DELETE: if(file_delete_point == 0)
                        file_no_delete();
                      else
                        file_yes_delete();
                      break;
    case ABOUT_MENU:if(about_menu_point == 0)
                      into_help();
                    else
                      into_ap();
                    break;
    case ABOUT_HELP:show_help(about_help_point); break;
  }
}
void press_btnB()
{
  switch(work)
  {
    case BOOK_MENU:
    case MUSIC_MENU:
    case IMAGE_MENU:
    case GAME_MENU:
    case ABOUT_MENU:
                   exit_menu(); break;
    case BOOK_SHOW:exit_book(); break;
    case BOOK_CONFIG:if(in_pallet)
                     {
                       in_pallet = false;
                       myGLCD.setColor(255, 255, 255);
                       myGLCD.fillRect(146, 2 + 66 * book_config_point, 209, 2 + 66 * book_config_point + 63);
                       draw_book_config_point(book_config_point, 255, 0, 0);
                     }
                     break;
    case MUSIC_PLAY:exit_music(); break;
    case IMAGE_SHOW:exit_image(); break;
    case FILE_MENU: file_back(); break;
    case FILE_DELETE:file_no_delete(); break;
    case ABOUT_HELP: 
    case ABOUT_AP:
                  into_about(); break;
  }
}
void press_btnSTART()
{
  switch(work)
  {
    case BOOK_SHOW:into_book_config(); break;
    case MUSIC_PLAY:change_music_state(); break;
  }
}
void press_btnSELECT()
{
  switch(work)
  {
    case BOOK_CONFIG:if(!in_pallet)
                     {
                       change_book_config_point();
                       delay(200);
                     }
                     break;
    case MUSIC_PLAY:change_music_mode(); break;
    case FILE_MENU: into_file_delete(); break;
  }
}

