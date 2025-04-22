#include <cstd>

// Write a 
uint32_t HEX_VAL = 0xFADE1234;
uint32_t HAX_VAL_SWAP = 0x3412DEFA;
uint8_t LE_CHECK = 0x34;

u32 swap32(u32 val)
{
  const uint32_t FIRST_MASK = 0xFF000000;
  const uint32_t SECOND_MASK = 0x00FF0000;
  const uint32_t THIRD_MASK = 0x0000FF00;
  const uint32_t FOURTH_MASK = 0x000000FF;

  uint32_t first = FIRST_MASK & val;
  uint32_t second = SECOND_MASK & val;
  uint32_t third = THIRD_MASK & val;
  uint32_t fourth = FOURTH_MASK & val;
  
  first = first >> 24u;
  second = second >> 8u;
  third = third << 8u;
  fourth = fourth << 24u;
  uint32_t ret_val = fourth | third | second | first;

  return ret_val;
}

// Function: isLE()
// Returns: 1 if the platform is Little Endian
//          0 otherwise
int isLE()
{
  uint32_t sample_val = HEX_VAL;
  uint8_t* first_val = (uint8_t*)&sample_val;

  if(first_val == LE_CHECK)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// Network byte order is Big Endian
uint32_t htonl(uint32_t input)
{
  if(isLE())
  {
    return swap32(input);
  }
  else
  {
    return input;
  }
}