#include "analysisCode.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
  if (argc < 8)
  {
    cout << "No input, output or MC flag set" << endl;
    return 0;
  }

  analysisCode analysis(argv[1], argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]), atoi(argv[7]) );
  analysis.Loop(false);

}
