#include "common.h"
bool file_test(char* filename)
{
  File test;
  test = SD.open(filename, FILE_WRITE);
  if(test)
  {
    test.close();
    return true;
  }
  else
    return false;
}
