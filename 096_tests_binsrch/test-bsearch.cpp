#include "function.h"

using namespace std;

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
