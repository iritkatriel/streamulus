
#include <cstdlib>

#include "operator_subscribe_test.hpp"

int main(int argc , char *argv[]) {

  streamulus::operator_subscribe_unit_tests subscribeTests;
  subscribeTests.Run();

  return 0;

}
