/*-------------------------------------------------------------------------------------------------
0.0- What these 2 guys built that I worked from
      Graphic LCD with Toshiba T6963 controller
      Copyright (c) Rados�aw Kwiecie�, 2007r
      http://en.radzio.dxp.pl/t6963/
      Compiler : avr-gcc
      Modified By -Gil- to work on Arduino easily : http://domoduino.tumblr.com/
0.1- Invocable class T6963
      Commands moved to T6963_commands.h
      For some reason I don't have reset hooked up and all is working fine.
0.2- rbrsidedn
      renamed SetPixel(byte,byte,byte) -> writePixel(x,y,color)
      added setPixel(x,y)
      added clearPixel(x,y)
      added createline(x1,y1,x2,y2)
      added createCircle(x,y,radius)       
r6 - Checked in with SVN
r7 - Checked in with cursor controls added
r8 - Got 6bit font width (s/b any fonth width) working.  
-----------------------------------------------------------------------------------------------*/
#ifndef T6963_h
#define T6963_h

#include "inttypes.h"
#include "T6963_Commands.h"
#include "T6963Data.h"
#include "T6963Cmd.h"

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

#define T6963_DIR_IN  0
#define T6963_DIR_OUT 1

const unsigned char T6963_CURSOR_PATTERN_SELECT=0xA0; //cursor patter select command prefix or with desired size-1.
const unsigned char T6963_DISPLAY_MODE=0x90; 


class T6963{
public:
  T6963(T6963Data *data, T6963Cmd *cmd); //Class
  
  
  void InitalizeInterface(int pixHoriz,int pixVert,int fontWidth, int sizeMem);
  //pixHoriz = Horizontal resolution
  //pixVert = Vertical Resolution
  //fontWidth = pixel width of font, determines number of columns, use hardware setting for LCD, no outputs linked to this variable.
  //sizeMem = size of memory attached to LCD in kb s/b 4,8,16,32,64 type number.
  void setDirection(int direction);
  void setOutput(unsigned char output);
  unsigned char getInput(void);
  void writeCommand(unsigned char);
  void writeData(unsigned char);
  unsigned char ReadData(void);
  void clearText(void);
  void clearCG(void);
  void clearGraphic(void);
  void WriteChar(char ch);
  void WriteString(char * str);
  void TextGoTo(unsigned char, unsigned char);
  void GraphicGoTo(unsigned char x, unsigned char y);
  void DefineCharacter(unsigned char, unsigned char *);
  void Initialize(void);
  void writePixel(unsigned char, unsigned char, unsigned char);
  unsigned char clearPixel(unsigned char,unsigned char);
  unsigned char setPixel(unsigned char,unsigned char);
  void WriteDisplayData(unsigned char);
  unsigned char checkStatus(void);
  void SetAddressPointer(unsigned int address);
  unsigned char setMode(char, char);
  unsigned char clearDispMode();
  unsigned char setDispMode(bool _text,bool _graphics, bool _cursor, bool _blink);
  unsigned char setCursorPattern(unsigned char _b);
  unsigned char setCursorPointer(unsigned char _col,unsigned char _row);
  
  void createLine(int,int,int,int);
  void createCircle(int, int, int);
  
  void setTH(unsigned int addr);
  unsigned int getTH();
  void setGH(unsigned int addr);
  unsigned int getGH();
  unsigned int sizeGA;	//(GLCD_GRAPHIC_AREA * GLCD_NUMBER_OF_LINES)
  unsigned int sizeTA;	//(GLCD_TEXT_AREA * (GLCD_NUMBER_OF_LINES/8))
  unsigned char getTextRows();
  unsigned char getTextCols();
   
private:
  T6963Data *_data;
  T6963Cmd *_cmd;
  void plot8points(int, int, int, int);
  void plot4points(int, int, int, int);
  unsigned int GLCD_NUMBER_OF_LINES;	//Veritical Resolution, Lines
  unsigned int GLCD_PIXELS_PER_LINE;	//Horizontal Resolution, pixels per line
  unsigned int _FW;		//Font Width
  unsigned int _GH;		//Graphics home
  unsigned int _TH;		//Text Home
  unsigned int _GA;		//(GLCD_PIXELS_PER_LINE / GLCD_FONT_WIDTH)
  unsigned int _TA;		//(GLCD_PIXELS_PER_LINE / GLCD_FONT_WIDTH)
  unsigned char _sizeMem;  //memory location for CGRAM (2kb required, 64kb max memory controlled by T6963, 32 possible locations)

};


#endif