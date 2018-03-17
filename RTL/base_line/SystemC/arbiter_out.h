// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include "systemc.h"

enum STATE_TYPE2 {IDLE2, North2, East2, West2, South2, Local2};

// Is this like the old arbiter in the router with handshaking FC ??
SC_MODULE(arbiter_out) 
{
    sc_in <bool> reset;
    sc_in <bool> clk;
    sc_in <bool> X_N_Y, X_E_Y, X_W_Y, X_S_Y, X_L_Y; // From Arbiter_in modules
    sc_in <sc_uint<2> > credit;
    sc_out <bool> grant_Y_N, grant_Y_E, grant_Y_W, grant_Y_S, grant_Y_L; // Grants given to Arbiter_in requests (encoded as one-hot)
    
    sc_signal <STATE_TYPE2> state, state_in; // Initialization, how does it work ?!
    
    void arbiter_out_sequential_proc();
    void logic_1();
    
    SC_HAS_PROCESS(arbiter_out);
    
    arbiter_out(sc_module_name name_) :
    sc_module(name_)
    {
        SC_METHOD(arbiter_out_sequential_proc);
        sensitive << clk << reset;
        
        SC_METHOD(logic_1);
        sensitive << state << X_N_Y << X_E_Y << X_W_Y << X_S_Y << X_L_Y << credit;
    }
};

