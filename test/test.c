#include <stdio.h>
#include "dfa.h"

int main(){

    dfa *a = dfa_create();

    dfa_add_state(a, "q0");
    dfa_add_state(a, "q1");
    dfa_add_state(a, "q2");

    dfa_set_initial_state(a, "q0");
    dfa_set_final_state(a, "q2");

    dfa_add_transition(a,'0',"q0","q1");
    dfa_add_transition(a,'1',"q1","q2");
    dfa_add_transition(a,'0',"q2","q1");

    char w[32];

    printf("Inserire stringa: ");
    scanf("%s",w);

    bool result = dfa_exec(a, w);

    if(result)
        printf("Stringa valida");
    else
        printf("Stringa non valida");

    return 0;
}

