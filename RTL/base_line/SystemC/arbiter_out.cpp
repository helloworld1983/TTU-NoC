// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include "arbiter_out.h"

// The Sequential part

void arbiter_out::arbiter_out_sequential_proc()
{
    if (reset.read() == 0)
        state = IDLE2;
    else if (clk.event() && clk.read() == 1) // At rising edge of clock, do the following:
        state = state_in.read();
} 

// Anything below here is pure Combinational

void arbiter_out::logic_1()
{
    // Initializing all Grant outputs
    grant_Y_N.write(0);
    grant_Y_E.write(0);
    grant_Y_W.write(0);
    grant_Y_S.write(0);
    grant_Y_L.write(0);
    
    switch (state.read())
    {
        case IDLE2:
            // Here it seems N has the higest priority, is it fine ?
            if (X_N_Y.read() == 1)
                state_in = North2;
            else if (X_E_Y.read() == 1)
                state_in = East2;
            else if (X_W_Y.read() == 1)
                state_in = West2;
            else if (X_S_Y.read() == 1)
                state_in = South2;
            else if (X_L_Y.read() == 1)
                state_in = Local2;
            else
                state_in = IDLE2;
            break;
            
        case North2:
            if (credit.read() != 0 && X_N_Y.read() == 1)
                grant_Y_N.write(1);
            
            if (X_N_Y.read() == 1)
                state_in = North2;
            else if (X_E_Y.read() == 1)
                state_in = East2;
            else if (X_W_Y.read() == 1)
                state_in = West2;
            else if (X_S_Y.read() == 1)
                state_in = South2;
            else if (X_L_Y.read() == 1)
                state_in = Local2;
            else
                state_in = IDLE2;
            break;
            
        case East2:
            if (credit.read() != 0 && X_E_Y.read() == 1)
                grant_Y_E.write(1);
            
            if (X_E_Y.read() == 1)
                state_in = East2;
            else if (X_W_Y.read() == 1)
                state_in = West2;
            else if (X_S_Y.read() == 1)
                state_in = South2;
            else if (X_L_Y.read() == 1)
                state_in = Local2;
            else if (X_N_Y.read() == 1)
                state_in = North2;
            else
                state_in = IDLE2;
            break;
            
        case West2:
            if (credit.read() != 0 && X_W_Y.read() == 1)
                grant_Y_W.write(1);
            
            if (X_W_Y.read() == 1)
                state_in = West2;
            else if (X_S_Y.read() == 1)
                state_in = South2;
            else if (X_L_Y.read() == 1)
                state_in = Local2;
            else if (X_N_Y.read() == 1)
                state_in = North2;
            else if (X_E_Y.read() == 1)
                state_in = East2;
            else
                state_in = IDLE2;
            break;
            
        case South2:
            if (credit.read() != 0 && X_S_Y.read() == 1)
                grant_Y_S.write(1);
            
            if (X_S_Y.read() == 1)
                state_in = South2;
            else if (X_L_Y.read() == 1)
                state_in = Local2;
            else if (X_N_Y.read() == 1)
                state_in = North2;
            else if (X_E_Y.read() == 1)
                state_in = East2;
            else if (X_W_Y.read() == 1)
                state_in = West2;
            else
                state_in = IDLE2;
            break;
            
        default: // Including Local2 and Invalid states
            if (credit.read() != 0 && X_L_Y.read() == 1)
                grant_Y_L.write(1);
            
            if (X_L_Y.read() == 1)
                state_in = Local2;
            else if (X_N_Y.read() == 1)
                state_in = North2;
            else if (X_E_Y.read() == 1)
                state_in = East2;
            else if (X_W_Y.read() == 1)
                state_in = West2;
            else if (X_S_Y.read() == 1)
                state_in = South2;
            else
                state_in = IDLE2;
            break;
    }
}

SC_MODULE_EXPORT(arbiter_out);
