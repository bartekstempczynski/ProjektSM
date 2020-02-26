#include <Brzozowe_Funkcje.h>






/**
 *  @brief Ta funkcja odczytuje natezenie swiatla z czujnika BH1750, nie przyjmuje zadnych argumentow

 *  @retval Wartosc natezenia wyrazona w LUX
 */
void ZmierzLUX(uint16_t *WartoscOdczytu)
{
	float Pomiar_f;
	BH1750_ReadLight(&Pomiar_f); //ODCZYT WARTOSCI DO PRZEKAZANEJ ZMIENNEJ
	//int lol = Pomiar_f;
	*WartoscOdczytu = Pomiar_f;
}


/**
 *  @brief Ta funkcja ma na celu odswiezac wyswietlacz LCD poprzez usuniecie wszystkich
 *  znakow i ponowne zapisanie ich z czestotliowscia uzalezniona od zegara przez ktory bedzie wywolywana
 *
 *  @param WartoscWejsciowa Pierwszy argument typu int bedacy wartoscia zadana z zakresu 0-99999999
 *  @param WartoscOdczytu Drugi argument typu int bedacy wartoscia odczytana z czujnika z zakresu 0-99999999
 *
 *  @retval brak
 */
void MakeLCDgreatAgain(uint16_t WartoscWejsciowa, uint16_t WartoscOdczytu)
{
	uint8_t size;
	lcd_clear();
	lcd_put_cur(0, 0); // od tego miejsca zaczynamy wprowadzac znaki

	char WiadomoscDoWyswietlenia[16];

	size = sprintf(&WiadomoscDoWyswietlenia, "Zadana: %d", WartoscWejsciowa);

	if(size > 15) lcd_send_string("Wiadomosc zbyt dluga");
	else lcd_send_string(WiadomoscDoWyswietlenia); // wysylanie wiadomosci

	lcd_put_cur(1, 0); // zmiana miejsca wpisywania tekstu na druga linie
	size = sprintf(&WiadomoscDoWyswietlenia, "Odczyt: %d", WartoscOdczytu);

	if(size > 15) lcd_send_string("Wiadomosc zbyt dluga");
	else lcd_send_string(WiadomoscDoWyswietlenia); // wysylanie wiadomosci

}


/**
 *  @brief Funkcja ta, przyjmuje 3 argumenty na podstawie ktorych przeprowadza obliczenia
 *  i zadaje odpowiednie wypelnienie PWMa w celu osiagniecia wartosci zadanej
 *
 *  @param WartoscWejsciowa argument uint16_t - wartosc zadawana przez uzytkownika
 *  @param WartoscOdczytu  argument uint16_t - wartoscia odczytana z czujnika BH1750
 *  @param Regulator wskaznik na regulator
 *
 *  @retval brak
 */
void ZadajPWM(uint16_t WartoscWejsciowa, uint16_t WartoscOdczytu, arm_pid_instance_f32 * Regulator)
{	uint16_t x = WartoscWejsciowa;
	if(WartoscWejsciowa > MAX_zadana) x = MAX_zadana;
	else if(WartoscWejsciowa < MIN_zadana) x = MIN_zadana;
	uint16_t PWM;
	PWM = arm_pid_f32(Regulator, x - WartoscOdczytu); //obliczanie wypelnienia dzieki funkcji z biblioteki cmsis
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, PWM); //Zadaje wypelnienie PWM
}
