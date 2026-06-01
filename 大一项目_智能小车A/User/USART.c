
#include "qudong.h"
#include "USART.h"
#include "xunji.h"

void BLEprocess(uint8_t cmd) {
  switch(cmd) {
    case 'E':  // 前进
      goForward();
      break;
    case 'H':  // 后退
      goBack();
      break;
	case 'L': //左转
	  goLeft();
	   break;
	case 'R': //右转
	  goRight();
	   break;
	 case 'S': //停止
	 stop();
	   break;
     case 'X':
	xuanzhuang();//旋转
	  break ;
		
  }
}

