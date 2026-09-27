#ifndef DFA
#define DFA


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct dfa dfa;

typedef struct transition transition;

typedef char* state;

dfa* dfa_create();

bool dfa_add_state(dfa* a, state q);

bool dfa_state_is_exist(dfa *a, state q);

bool dfa_state_is_final(dfa *a, state q);

bool dfa_set_initial_state(dfa* a, state initial_state);

bool dfa_set_final_state(dfa* a, state q);

state dfa_transition(dfa *a, char c, state qi);

bool dfa_add_transition(dfa *a, char c, state qi, state qf);

bool dfa_exec(dfa *a, char *c);



#endif