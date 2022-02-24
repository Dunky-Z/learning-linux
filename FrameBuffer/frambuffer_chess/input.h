#ifndef __INPUT_H
#define __INPUT_H

#define KEYBOARDMODE 0
#define CHARMODE 1

void input_init(void);

int input_choice_mode(int mode);

int input_kb_mode(void);

int input_char_mode(void);

void input_recover(void);

#endif