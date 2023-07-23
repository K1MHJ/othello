#include <cstdlib>
#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <ncurses.h>
#include <pthread.h>

using namespace std;

void wait(uint32_t msec);
char* monitor_input();
char* inText;

void *funcKeyInput(void *arg)
{
  while (true) {
    int ch = getch();
    if (ch == 'q') break;
  }
  cout << "Exit" << endl;
  pthread_exit(NULL);
}
int ____main()
{
  pthread_t thid;
  if(pthread_create(&thid, NULL, funcKeyInput, NULL) != 0){
    fprintf(stderr, "pthread create error\n");
    exit(1);
  }
  
  if(pthread_join(thid, NULL) != 0){
    fprintf(stderr, "pthread join error\n");
    exit(1);
  }
  
  return (EXIT_SUCCESS);

  initscr();
  noecho(); //キーが入力されても表示しない
  curs_set(0);//カーソルを非表示
  keypad(stdscr, TRUE); // xtermでマウスイベントの取得に必要
  mousemask(REPORT_MOUSE_POSITION, NULL);//マウスイベントを取得
  MEVENT e;
  int px = 2;
  while (true) {
    int ch = getch();
    if (ch == 'q') break;
    if (ch == KEY_MOUSE) {
      if (getmouse(&e) == OK) {
        clear();
        px = e.x;
        if (px < 2)px = 2;
        if (px > 77)px = 77;
        mvprintw(23, px - 2, "-----");
        refresh();
      }
    }
  }
  endwin();
  return (EXIT_SUCCESS);
}
int __main()
{
  initscr();

  start_color();
  init_pair(1, COLOR_RED, COLOR_BLUE); //색번호1을 빨간 글자/파란 배경으로 한다.
  bkgd(COLOR_PAIR(1)); //색1을 디폴트로 한다.
  
  erase();
  move(10,20);
  addstr("Hello world");
  refresh();
  timeout(-1);

  for(int i =0;i<3;i++){
    //cout << i << endl;
    wait(1000); 
    inText=monitor_input();
    if(!strcmp(inText,"exit")){
      break;
    }
  }
  endwin();
  return (EXIT_SUCCESS);
}

char* monitor_input()
{
  int fd = 0;
  fd_set rfds;
  struct timeval tv;
  int retval;
  char* inputval;
  FD_ZERO(&rfds);
  FD_SET(fd, &rfds);
  tv.tv_sec = 0;
  tv.tv_usec = 1000;
  retval = select(fd+1, &rfds, NULL, NULL, &tv);
  if(retval < 0){
    perror("select()");
  }
  else if(retval > 0){
    scanf("%s", inputval);
    printf("input: %s\n", inputval);
  }
  return inputval;
}
void wait(uint32_t msec)
{
  int fd = 0;
  fd_set rfds;
  struct timeval tv;
  int retval;
  FD_ZERO(&rfds);
  FD_SET(fd, &rfds);
  tv.tv_sec = (int)(msec / 1000);
  tv.tv_usec = (msec % 1000) * 1000;
  retval = select(fd, &rfds, NULL, NULL, &tv);
  if(retval < 0){
    perror("select()");
  }
  else if(retval > 0){
  }
  else{
  }
}
