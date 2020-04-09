#include "analysisCode.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
  if (argc < 4)
  {
    cout << "No input, output or MC flag set" << endl;
    return 0;
  }

  analysisCode analysis(argv[1], argv[2], atoi(argv[3]) );
  analysis.Loop();

}
