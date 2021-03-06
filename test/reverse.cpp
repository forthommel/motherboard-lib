#include "TDCControl.h"
#include "TDCSetup.h"

int main(int argc, char* argv[])
{
  PPSTimingMB::TDCSetup s;

  // dump the register content before reversing it
  std::cout << "--- Before reversing the register:" << std::endl;
  s.DumpRegister(2);
  std::vector<uint8_t> s_vec = s.GetBytesVector();

  PPSTimingMB::TDCSetup s_rev(s_vec, true);
  // dump the register content after reversing it
  std::cout << "--- After reversing the register:" << std::endl;
  s_rev.DumpRegister();

  return 0;
}
