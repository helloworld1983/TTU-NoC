// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include "systemc.h"

enum STATE_TYPE {IDLE, North, East, West, South, Local};

// Is this like the old arbiter in the router with handshaking FC ??
SC_MODULE(arbiter_in) 
{
    sc_in <bool> reset;
    sc_in <bool> clk;
    sc_in <bool> req_X_N, req_X_E, req_X_W, req_X_S, req_X_L; // From LBDR modules
    sc_out <bool> X_N, X_E, X_W, X_S, X_L; // Grants given to LBDR requests (encoded as one-hot)
    
    sc_signal <STATE_TYPE> state, state_in; // Initialization, how does it work ?!
    
    void arbiter_in_sequential_proc();
    void logic_1();
    
    SC_HAS_PROCESS(arbiter_in);
    
    arbiter_in(sc_module_name name_) :
    sc_module(name_)
    {
        SC_METHOD(arbiter_in_sequential_proc);
        sensitive << clk << reset;
        
        SC_METHOD(logic_1);
        sensitive << state << req_X_N << req_X_E << req_X_W << req_X_S << req_X_L;
    }
};

