#include <stdlib.h>
#include "History.h"
void Assert(char *message, int actual, int expected);

void TestHistory()
{
  History h2 = History(5);
  h2.push(1);
  h2.push(2);
  h2.push(3);
  h2.push(4);
  h2.push(5);
  h2.push(6);

  Assert("b0", h2.get(0), 6);
  Assert("b1", h2.get(1), 5);
  Assert("b2", h2.get(2), 4);
  Assert("b2", h2.get(3), 3);
  Assert("b2", h2.get(4), 2);
}