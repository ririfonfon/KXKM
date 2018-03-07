const byte adr = 13;

#define __TO_10(U1, U2) (uint16_t)( (uint16_t)( (uint8_t)(U1) << 8 + (uint8_t)(U2) ) >> 6)
#define _TO_10(U1, U2) (uint16_t)( (uint8_t)(U1) * 4 + (uint8_t)(U2) / 64)
#define TO_10(U1, U2) ((_TO_10(U1,U2)*_TO_10(U1,U2))/1024)

inline uint16_t u8_to_10_gamma(uint8_t u1, uint8_t u2) {
  uint16_t to10 = u1 * 4 + (u2 + 1) / 64;
  return (to10 * to10) / 1024;
}

inline uint16_t u8_to_12_gamma(uint8_t u1, uint8_t u2) {
  uint16_t to10 = u1 * 16 + (u2 + 1) / 16;
  return (to10 * to10) / (4096);
}
