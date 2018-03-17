// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include "arbiter_in.h"

// The Sequential part

void arbiter_in::arbiter_in_sequential_proc()
{
    if (reset.read()==0)
        state.write(IDLE);
    else if (clk.event() && clk.read() == 1) // At rising edge of clock, do the following:
        state.write(state_in.read());
}


// Anything below here is pure Combinational

void arbiter_in::logic_1()
{
    // Initializing all Grant outputs
    X_N.write(0);
    X_E.write(0);
    X_W.write(0);
    X_S.write(0);
    X_L.write(0);

    switch (state.read())
    {
        case IDLE: // In the arbiter for hand-shaking FC router, L had the  highest priority (L, N, E, W, S)
            // Here it seems N has the higest priority, is it fine ?
            if (req_X_N.read() == 1)
            {
                state_in = North;
                X_N.write(1);
            }
            
            else if (req_X_E.read() == 1)
            {
                state_in = East;
                X_E.write(1);
            }
            
            else if (req_X_W.read() == 1)
            {
                state_in = West;
                X_W.write(1);
            }
            
            else if (req_X_S.read() == 1)
            {
                state_in = South;
                X_S.write(1);
            }
            
            else if (req_X_L.read() == 1)
            {
                state_in = Local;
                X_L.write(1);
            }
            
            else
                state_in = state.read();
            
            break;
            
        case North:
            if (req_X_N.read() == 1)
            {
                state_in = North;
                X_N.write(1);
            }
            
            else if (req_X_E.read() == 1)
            {
                state_in = East;
                X_E.write(1);
            }
            
            else if (req_X_W.read() == 1)
            {
                state_in = West;
                X_W.write(1);
            }
            
            else if (req_X_S.read() == 1)
            {
                state_in = South;
                X_S.write(1);
            }
            
            else if (req_X_L.read() == 1)
            {
                state_in = Local;
                X_L.write(1);
            }
            
            else
                state_in = state.read();
            
            break;
            
        case East:
            if (req_X_E.read() == 1)
            {
                state_in = East;
                X_E.write(1);
            }
            
            else if (req_X_W.read() == 1)
            {
                state_in = West;
                X_W.write(1);
            }
            
            else if (req_X_S.read() == 1)
            {
                state_in = South;
                X_S.write(1);
            }
            
            else if (req_X_L.read() == 1)
            {
                state_in = Local;
                X_L.write(1);
            }
            
            else if (req_X_N.read() == 1)
            {
                state_in = North;
                X_N.write(1);
            }
            
            else
                state_in = state.read();
            
            break;
            
        case West:
            if (req_X_W.read() == 1)
            {
                state_in = West;
                X_W.write(1);
            }
            
            else if (req_X_S.read() == 1)
            {
                state_in = South;
                X_S.write(1);
            }
            
            else if (req_X_L.read() == 1)
            {
                state_in = Local;
                X_L.write(1);
            }
            
            else if (req_X_N.read() == 1)
            {
                state_in = North;
                X_N.write(1);
            }
            
            else if (req_X_E.read() == 1)
            {
                state_in = East;
                X_E.write(1);
            }
            
            else
                state_in = state.read();
            
            break;
            
        case South:
            if (req_X_S.read() == 1)
            {
                state_in = South;
                X_S.write(1);
            }
            
            else if (req_X_L.read() == 1)
            {
                state_in = Local;
                X_L.write(1);
            }
            
            else if (req_X_N.read() == 1)
            {
                state_in = North;
                X_N.write(1);
            }
            
            else if (req_X_E.read() == 1)
            {
                state_in = East;
                X_E.write(1);
            }
            
            else if (req_X_W.read() == 1)
            {
                state_in = West;
                X_W.write(1);
            }
            
            else
                state_in = state.read();
            
            break;
            
        default: // Including Local and Invalid states
            if (req_X_L.read() == 1)
            {
                state_in = Local;
                X_L.write(1);
            }
            
            else if (req_X_N.read() == 1)
            {
                state_in = North;
                X_N.write(1);
            }
            
            else if (req_X_E.read() == 1)
            {
                state_in = East;
                X_E.write(1);
            }
            
            else if (req_X_W.read() == 1)
            {
                state_in = West;
                X_W.write(1);
            }
            
            else if (req_X_S.read() == 1)
            {
                state_in = South;
                X_S.write(1);
            }
            
            else
                state_in = state.read();
            
            break;
    }
}

SC_MODULE_EXPORT(arbiter_in);
