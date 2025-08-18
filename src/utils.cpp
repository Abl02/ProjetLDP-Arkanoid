#include "utils.hpp"

#include "config.hpp" 


char bonusToChar(BRICK_CONST::bonusType bonus) {
  switch(bonus) {
    case BRICK_CONST::laser:        return 'L';
    case BRICK_CONST::bigger:       return 'B';
    case BRICK_CONST::capture:      return 'C';
    case BRICK_CONST::slow:         return 'S';
    case BRICK_CONST::interruption: return 'I';
    case BRICK_CONST::player:       return 'P';
    default:                        return '?';
  }
}

ALLEGRO_COLOR bonusToColor(char letter) {
  switch (letter) {
    case 'B': return COLORS::BLUE; // paddle size bonus
    case 'S': return COLORS::ORANGE; // ball speed slow bonus
    case 'P': return COLORS::GREY; // life bonus
    case 'C': return COLORS::GREEN; // capture ball  bonus
    case 'I': return COLORS::CYAN; // 3 ball interruption  bonus
    default:  return COLORS::YELLOW_B;
  }
}