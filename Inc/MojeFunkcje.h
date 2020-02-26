#include "i2c-lcd.h"
#include "tim.h"
#include "arm_math.h"
#include "math_helper.h"
#include "bh1750.h"
#include "stdio.h"
#include "string.h"

#define MAX_zadana (1200)
#define MIN_zadana (0)

void ZadajPWM(uint16_t WartoscWejsciowa, uint16_t WartoscOdczytu, arm_pid_instance_f32 * Regulator);
void ZmierzLUX(uint16_t * WartoscOdczytu);
void MakeLCDgreatAgain(uint16_t WartoscWejsciowa, uint16_t WartoscOdczytu);
