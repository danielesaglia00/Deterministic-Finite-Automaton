#include "../include/dfa.h"

struct dfa{ 
    state* states;
    size_t n_states;

    transition* transitions;
    size_t n_transition;

    state initial_state;

    state* final_states;
    size_t n_final_states;
};

struct transition{
    char input;
    state initial_state;
    state final_state;
};

dfa* dfa_create(){
    dfa *a = malloc(sizeof(dfa));

    if(a == NULL)
        return NULL;
    
    a->states = NULL;
    a->n_states = 0;

    a->transitions = NULL;
    a->n_transition = 0;

    a->initial_state = NULL;

    a->final_states = NULL;
    a->n_final_states = 0;

    return a;
}

bool dfa_state_is_exist(dfa *a, state q){
    if(a != NULL && q != NULL){
        for(size_t i = 0; i < a->n_states; i++)
            if(strcmp(a->states[i], q))
                return false;
        return true;
    }       
    else
        return false;

}

bool dfa_state_is_final(dfa *a, state q){
    if(a != NULL && q != NULL){
        for(size_t i = 0; i < a->n_final_states; i++)
            if(strcmp(a->final_states[i], q))
                return false;
        return true;
    }       
    else
        return false;
}

bool dfa_add_state(dfa* a, state q){
    if(a != NULL && !dfa_state_is_exist(a,q)){
        a->n_states++;
    
        state *tmp = malloc(sizeof(state)*a->n_states);
        for(size_t i = 0; i < a->n_states-1; i++)
            tmp[i] = a->states[i];
        tmp[a->n_states - 1] = q;
        free(a->states);
        a->states = tmp;
        return true;
    }       
    else
        return false;
}

bool dfa_set_initial_state(dfa* a, state initial_state){
    if(dfa_state_is_exist(a, initial_state)){
        a->initial_state = initial_state;
        return true;
    }
    return false;
}

bool dfa_set_final_state(dfa* a, state q){
    if(dfa_state_is_exist(a,q) && dfa_state_is_final(a,q)){
        a->n_final_states++;
        state *tmp = malloc(sizeof(state)*a->n_final_states);
        for(size_t i = 0; i < a->n_final_states-1; i++)
            tmp[i] = a->final_states[i];
        tmp[a->n_final_states - 1] = q;
        free(a->final_states);
        a->final_states = tmp;
        return true;
    }       
    else
        return false;
}

state dfa_transition(dfa *a, char c, state qi){
    if(dfa_state_is_exist(a,qi)){
        for(size_t i = 0; i < a->n_transition; i++)
            if(!strcmp(a->transitions[i].initial_state, qi) && a->transitions[i].input == c)
                return a->transitions[i].final_state;
    }
    return NULL;
}


bool dfa_add_transition(dfa *a, char c, state qi, state qf){
     if(dfa_state_is_exist(a,qf) && dfa_transition(a,c,qi)== NULL){
        a->n_transition++;
        transition *tmp = malloc(sizeof(transition)*a->n_transition);
        for(size_t i = 0; i < a->n_transition-1; i++)
            tmp[i] = a->transitions[i];
        tmp[a->n_transition-1].initial_state = qi;
        tmp[a->n_transition-1].input = c;
        tmp[a->n_transition-1].final_state = qf;
        free(a->transitions);
        a->transitions = tmp;
        return true;
     }
     else
        return false;
}

bool dfa_exec(dfa *a, char *c){
    if(a != NULL && c != NULL && a->initial_state != NULL){
        char *pointer = c;
        state current = a->initial_state;
        if(dfa_state_is_exist(a,current)){
            while(*pointer != '\0' && current != NULL){
                current = dfa_transition(a,*pointer,current);
                pointer++;
            }
            if(dfa_state_is_final(a,current))
                return true;
        }
    }
    return false;
}

