/*
 * Project3.c
 *
 * Created: 5/16/2020 6:24:58 PM
 * Author : MrTrashCan
 */ 

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include <math.h>
#include <stdio.h>

#define A 114
#define As 107
#define B 101
#define C 191
#define Cs 180
#define D 170
#define Ds 161
#define E 152
#define F 143
#define Fs 135
#define G 128
#define Gs 120
#define REST 1
 
#define whole 8
#define half 4
#define quarter 2
#define eighth 1

typedef struct {
	int freq;
	int duration;
} note;
	
const note song[] = {{E/2, eighth}, {E/2, eighth}, {REST, quarter}, {E/2, eighth}, {REST, quarter}, {C/2, eighth}, {E/2, eighth}, {REST, quarter},  {G/2, eighth}, {REST, quarter}, {REST, half}, {G, eighth}, {REST, quarter}, {REST, half},
					 {C/2, eighth}, {REST, half}, {G, eighth}, {REST, half}, {E, eighth}, {REST, half}, {A, eighth}, {REST, quarter}, {B, eighth}, {REST, quarter}, {As, eighth}, {A, eighth}, {REST, quarter},
					 {G, eighth}, {E/2, eighth}, {G/2, eighth}, {A/2, eighth}, {REST, quarter}, {F/2, eighth}, {G/2, eighth}, {REST, quarter}, {E/2, eighth}, {REST, quarter}, {C/2, eighth}, {D/2, eighth}, {B, eighth}, {REST, half},
					 {C/2, eighth}, {REST, half}, {G, eighth}, {REST, half}, {E, eighth}, {REST, half}, {A, eighth}, {REST, quarter}, {B, eighth}, {REST, quarter}, {As, eighth}, {A, eighth}, {REST, quarter},
					 {G, eighth}, {E/2, eighth}, {G/2, eighth}, {A/2, eighth}, {REST, quarter}, {F/2, eighth}, {G/2, eighth}, {REST, quarter}, {E/2, eighth}, {REST, quarter}, {C/2, eighth}, {D/2, eighth}, {B, eighth}, {REST, half},
					 {REST, half}, {G/2, eighth}, {Fs/2, eighth}, {F/2, eighth}, {D/2, eighth}, {REST, quarter}, {E/2, eighth}, {REST, quarter}, {G, eighth}, {A, eighth}, {C/2, eighth}, {REST, quarter}, {A, eighth}, {C/2, eighth}, {D/2, eighth},
					 {REST, half}, {G/2, eighth}, {Fs/2, eighth}, {F/2, eighth}, {D/2, eighth}, {REST, quarter}, {E/2, eighth}, {REST, quarter}, {C/4, eighth}, {REST, quarter}, {C/4, eighth}, {C/4, eighth}, {REST, quarter}, {REST, half},
					 {REST, half}, {G/2, eighth}, {Fs/2, eighth}, {F/2, eighth}, {D/2, eighth}, {REST, quarter}, {E/2, eighth}, {REST, quarter}, {G, eighth}, {A, eighth}, {C/2, eighth}, {REST, quarter}, {A, eighth}, {C/2, eighth}, {D/2, eighth},
					 {REST, half}, {Ds/2, eighth}, {REST, half}, {D/2, eighth}, {REST, half}, {C/2, eighth}, {REST, quarter}, {REST, whole},
					 {REST, half}, {G/2, eighth}, {Fs/2, eighth}, {F/2, eighth}, {D/2, eighth}, {REST, quarter}, {E/2, eighth}, {REST, quarter}, {G, eighth}, {A, eighth}, {C/2, eighth}, {REST, quarter}, {A, eighth}, {C/2, eighth}, {D/2, eighth},
					 {REST, half}, {G/2, eighth}, {Fs/2, eighth}, {F/2, eighth}, {D/2, eighth}, {REST, quarter}, {E/2, eighth}, {REST, quarter}, {C/4, eighth}, {REST, quarter}, {C/4, eighth}, {C/4, eighth}, {REST, quarter}, {REST, half},
					 {REST, half}, {G/2, eighth}, {Fs/2, eighth}, {F/2, eighth}, {D/2, eighth}, {REST, quarter}, {E/2, eighth}, {REST, quarter}, {G, eighth}, {A, eighth}, {C/2, eighth}, {REST, quarter}, {A, eighth}, {C/2, eighth}, {D/2, eighth},
					 {REST, half}, {Ds/2, eighth}, {REST, half}, {D/2, eighth}, {REST, half}, {C/2, eighth}, {REST, quarter}, {REST, whole},
					 {C/2, eighth}, {C/2, eighth}, {REST, quarter}, {C/2, eighth}, {REST, quarter}, {C/2, eighth}, {D/2, eighth}, {REST, quarter}, {E/2, eighth}, {C/2, eighth}, {REST, quarter}, {A, eighth}, {G, eighth}, {REST, quarter}, {REST, half},
					 {C/2, eighth}, {C/2, eighth}, {REST, quarter}, {C/2, eighth}, {REST, quarter}, {C/2, eighth}, {D/2, eighth}, {E/2, eighth}, {REST, whole},
					 {C/2, eighth}, {C/2, eighth}, {REST, quarter}, {C/2, eighth}, {REST, quarter}, {C/2, eighth}, {D/2, eighth}, {REST, quarter}, {E/2, eighth}, {C/2, eighth}, {REST, quarter}, {A, eighth}, {G, eighth}, {REST, quarter}, {REST, half},
					 {E/2, eighth}, {E/2, eighth}, {REST, quarter}, {E/2, eighth}, {REST, quarter}, {C/2, eighth}, {E/2, eighth}, {REST, quarter}, {G/2, eighth}, {REST, quarter}, {REST, half}, {G, eighth}, {REST, quarter}, {REST, half},
					 {C/2, eighth}, {REST, half}, {G, eighth}, {REST, half}, {E, eighth}, {REST, half}, {A, eighth}, {REST, quarter}, {B, eighth}, {REST, quarter}, {As, eighth}, {A, eighth}, {REST, quarter},
					 {G, eighth}, {E/2, eighth}, {G/2, eighth}, {A/2, eighth}, {REST, quarter}, {F/2, eighth}, {G/2, eighth}, {REST, quarter}, {E/2, eighth}, {REST, quarter}, {C/2, eighth}, {D/2, eighth}, {B, eighth}, {REST, half},
					 {C/2, eighth}, {REST, half}, {G, eighth}, {REST, half}, {E, eighth}, {REST, half}, {A, eighth}, {REST, quarter}, {B, eighth}, {REST, quarter}, {As, eighth}, {A, eighth}, {REST, quarter},
					 {G, eighth}, {E/2, eighth}, {G/2, eighth}, {A/2, eighth}, {REST, quarter}, {F/2, eighth}, {G/2, eighth}, {REST, quarter}, {E/2, eighth}, {REST, quarter}, {C/2, eighth}, {D/2, eighth}, {B, eighth}, {REST, half},
					 {E/2, eighth}, {C/2, eighth}, {REST, quarter}, {G, eighth}, {REST, half}, {G, eighth}, {REST, quarter}, {A, eighth}, {F/2, eighth}, {REST, quarter}, {F/2, eighth}, {A, eighth}, {REST, quarter}, {REST, half},
					 {B, eighth}, {A/2, eighth}, {A/2, eighth}, {A/2, eighth}, {G/2, eighth}, {F/2, eighth}, {E/2, eighth}, {C/2, eighth}, {REST, quarter}, {A, eighth}, {G, eighth}, {REST, quarter}, {REST, half},
					 {E/2, eighth}, {C/2, eighth}, {REST, quarter}, {G, eighth}, {REST, half}, {G, eighth}, {REST, quarter}, {A, eighth}, {F/2, eighth}, {REST, quarter}, {F/2, eighth}, {A, eighth}, {REST, quarter}, {REST, half},
					 {B, eighth}, {F/2, eighth}, {REST, quarter}, {F/2, eighth}, {F/2, eighth}, {E/2, eighth}, {D/2, eighth}, {C/2, eighth}, {G, eighth}, {REST, quarter}, {E, eighth}, {C, eighth} , {REST, quarter}, {REST, half},
					 {C/2, eighth}, {C/2, eighth}, {REST, quarter}, {C/2, eighth}, {REST, quarter}, {C/2, eighth}, {D/2, eighth}, {REST, quarter}, {E/2, eighth}, {C/2, eighth}, {REST, quarter}, {A, eighth}, {G, eighth}, {REST, quarter}, {REST, half},
					 {C/2, eighth}, {C/2, eighth}, {REST, quarter}, {C/2, eighth}, {REST, quarter}, {C/2, eighth}, {D/2, eighth}, {E/2, eighth}, {REST, whole},
					 {C/2, eighth}, {C/2, eighth}, {REST, quarter}, {C/2, eighth}, {REST, quarter}, {C/2, eighth}, {D/2, eighth}, {REST, quarter}, {E/2, eighth}, {C/2, eighth}, {REST, quarter}, {A, eighth}, {G, eighth}, {REST, quarter}, {REST, half},
					 {E/2, eighth}, {E/2, eighth}, {REST, quarter}, {E/2, eighth}, {REST, quarter}, {C/2, eighth}, {E/2, eighth}, {REST, quarter}, {G/2, eighth}, {REST, quarter}, {REST, half}, {G, eighth}, {REST, quarter}, {REST, half},
					 {C/2, eighth}, {REST, half}, {G, eighth}, {REST, half}, {E, eighth}, {A, eighth}, {B, eighth}, {A, eighth}, {REST, quarter}, {Gs, eighth}, {As, eighth}, {Gs, eighth}, {REST, quarter}, {G, eighth}, {Fs, eighth}, {G, half}, {REST, whole}, {REST, whole}};
						 
const char characters[] = "X123A456B789C*0#D";

void play_note(const note *n);
int get_key();
int is_pressed(int r, int c);

int main(void)
{
    /* Replace with your application code */
	int key;
	lcd_init();
	lcd_puts("Super Mario Bros.");
	lcd_pos(1,0);
	lcd_puts("Main Theme");
	SET_BIT(DDRB,3);
	int s = sizeof(song)/sizeof(song[0]);
	while(1) {
		for(int i = 0; i < s; ++i) {
			play_note(&song[i]);
			key = get_key();
			if(characters[key] == '1') {
				while(1) {
					key = get_key();
					if(characters[key] == '2')
						break;
				}
			}
		}
	}
}

void play_note(const note *n)
{
	double p = 2*n->freq * 0.000005;
	int k = (int)(n->duration / p / 3);
	if(n->freq == 1) {
		for(int i = 0; i < k; ++i) {
			avr_wait(2*n->freq);
		}
	}
	else {
		for(int i = 0; i < k; ++i) {
			SET_BIT(PORTB,3);
			avr_wait(n->freq);
			CLR_BIT(PORTB,3);
			avr_wait(n->freq);
		}
	}
}

int get_key()
{
	for(int r = 0; r < 4; ++r)
		for(int c = 0; c < 4; ++c)
			if(is_pressed(r,c+4))
				return r*4+c+1;
	return 0;
}

int is_pressed(int r, int c)
{
	DDRC = 0b00000000;
	PORTC = 0b00000000;
	SET_BIT(DDRC, r);
	SET_BIT(PORTC, c);
	if (!GET_BIT(PINC, c))
		return 1;
	return 0;
}