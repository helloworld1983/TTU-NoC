// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include "allocator.h"

// The Sequential part

void allocator::allocator_sequential_proc()
{
    if (reset.read() == 0)
    {
        // We start with all full cradit
        credit_counter_N_out = 3;
        credit_counter_E_out = 3;
        credit_counter_W_out = 3;
        credit_counter_S_out = 3;
        credit_counter_L_out = 3;
    }
    
    else if (clk.event() && clk.read() == 1) // At rising edge of clock, do the following:
    {
        credit_counter_N_out = credit_counter_N_in.read();
        credit_counter_E_out = credit_counter_E_in.read();
        credit_counter_W_out = credit_counter_W_in.read();
        credit_counter_S_out = credit_counter_S_in.read();
        credit_counter_L_out = credit_counter_L_in.read();
    }
}


// Anything below here is pure Combinational

void allocator::logic_1()
{
    bool grant_N_N_tmp;
    bool grant_N_E_tmp;
    bool grant_N_W_tmp;
    bool grant_N_S_tmp;
    bool grant_N_L_tmp;
    bool grant_E_N_tmp;
    bool grant_E_E_tmp;
    bool grant_E_W_tmp;
    bool grant_E_S_tmp;
    bool grant_E_L_tmp;
    bool grant_W_N_tmp;
    bool grant_W_E_tmp;
    bool grant_W_W_tmp;
    bool grant_W_S_tmp;
    bool grant_W_L_tmp;
    bool grant_S_N_tmp;
    bool grant_S_E_tmp;
    bool grant_S_W_tmp;
    bool grant_S_S_tmp;
    bool grant_S_L_tmp;
    bool grant_L_N_tmp;
    bool grant_L_E_tmp;
    bool grant_L_W_tmp;
    bool grant_L_S_tmp;
    bool grant_L_L_tmp;

    bool grant_N_tmp;
    bool grant_E_tmp;
    bool grant_W_tmp;
    bool grant_S_tmp;
    bool grant_L_tmp;

    grant_N_N_tmp = grant_N_N_sig.read() & !empty_N.read();
    grant_N_E_tmp = grant_N_E_sig.read() & !empty_E.read();
    grant_N_W_tmp = grant_N_W_sig.read() & !empty_W.read();
    grant_N_S_tmp = grant_N_S_sig.read() & !empty_S.read();
    grant_N_L_tmp = grant_N_L_sig.read() & !empty_L.read();
    
    grant_E_N_tmp = grant_E_N_sig.read() & !empty_N.read();
    grant_E_E_tmp = grant_E_E_sig.read() & !empty_E.read();
    grant_E_W_tmp = grant_E_W_sig.read() & !empty_W.read();
    grant_E_S_tmp = grant_E_S_sig.read() & !empty_S.read();
    grant_E_L_tmp = grant_E_L_sig.read() & !empty_L.read();
    
    grant_W_N_tmp = grant_W_N_sig.read() & !empty_N.read();
    grant_W_E_tmp = grant_W_E_sig.read() & !empty_E.read();
    grant_W_W_tmp = grant_W_W_sig.read() & !empty_W.read();
    grant_W_S_tmp = grant_W_S_sig.read() & !empty_S.read();
    grant_W_L_tmp = grant_W_L_sig.read() & !empty_L.read();
    
    grant_S_N_tmp = grant_S_N_sig.read() & !empty_N.read();
    grant_S_E_tmp = grant_S_E_sig.read() & !empty_E.read();
    grant_S_W_tmp = grant_S_W_sig.read() & !empty_W.read();
    grant_S_S_tmp = grant_S_S_sig.read() & !empty_S.read();
    grant_S_L_tmp = grant_S_L_sig.read() & !empty_L.read();
    
    grant_L_N_tmp = grant_L_N_sig.read() & !empty_N.read();
    grant_L_E_tmp = grant_L_E_sig.read() & !empty_E.read();
    grant_L_W_tmp = grant_L_W_sig.read() & !empty_W.read();
    grant_L_S_tmp = grant_L_S_sig.read() & !empty_S.read();
    grant_L_L_tmp = grant_L_L_sig.read() & !empty_L.read();

    grant_N_N.write (grant_N_N_tmp);
    grant_N_E.write (grant_N_E_tmp);
    grant_N_W.write (grant_N_W_tmp);
    grant_N_S.write (grant_N_S_tmp);
    grant_N_L.write (grant_N_L_tmp);
    grant_E_N.write (grant_E_N_tmp);
    grant_E_E.write (grant_E_E_tmp);
    grant_E_W.write (grant_E_W_tmp);
    grant_E_S.write (grant_E_S_tmp);
    grant_E_L.write (grant_E_L_tmp);
    grant_W_N.write (grant_W_N_tmp);
    grant_W_E.write (grant_W_E_tmp);
    grant_W_W.write (grant_W_W_tmp);
    grant_W_S.write (grant_W_S_tmp);
    grant_W_L.write (grant_W_L_tmp);
    grant_S_N.write (grant_S_N_tmp);
    grant_S_E.write (grant_S_E_tmp);
    grant_S_W.write (grant_S_W_tmp);
    grant_S_S.write (grant_S_S_tmp);
    grant_S_L.write (grant_S_L_tmp);
    grant_L_N.write (grant_L_N_tmp);
    grant_L_E.write (grant_L_E_tmp);
    grant_L_W.write (grant_L_W_tmp);
    grant_L_S.write (grant_L_S_tmp);
    grant_L_L.write (grant_L_L_tmp);

    grant_N_tmp = (grant_N_N_sig.read() & !empty_N.read()) | (grant_N_E_sig.read() & !empty_E.read()) | (grant_N_W_sig.read() & !empty_W.read()) | (grant_N_S_sig.read() & !empty_S.read()) | (grant_N_L_sig.read() & !empty_L.read());
    grant_E_tmp = (grant_E_N_sig.read() & !empty_N.read()) | (grant_E_E_sig.read() & !empty_E.read()) | (grant_E_W_sig.read() & !empty_W.read()) | (grant_E_S_sig.read() & !empty_S.read()) | (grant_E_L_sig.read() & !empty_L.read());
    grant_W_tmp = (grant_W_N_sig.read() & !empty_N.read()) | (grant_W_E_sig.read() & !empty_E.read()) | (grant_W_W_sig.read() & !empty_W.read()) | (grant_W_S_sig.read() & !empty_S.read()) | (grant_W_L_sig.read() & !empty_L.read());
    grant_S_tmp = (grant_S_N_sig.read() & !empty_N.read()) | (grant_S_E_sig.read() & !empty_E.read()) | (grant_S_W_sig.read() & !empty_W.read()) | (grant_S_S_sig.read() & !empty_S.read()) | (grant_S_L_sig.read() & !empty_L.read());
    grant_L_tmp = (grant_L_N_sig.read() & !empty_N.read()) | (grant_L_E_sig.read() & !empty_E.read()) | (grant_L_W_sig.read() & !empty_W.read()) | (grant_L_S_sig.read() & !empty_S.read()) | (grant_L_L_sig.read() & !empty_L.read());

    grant_N.write (grant_N_tmp);
    grant_E.write (grant_E_tmp);
    grant_W.write (grant_W_tmp);
    grant_S.write (grant_S_tmp);
    grant_L.write (grant_L_tmp);
}

// This process handles the credit counters.
void allocator::logic_2()
{
    //Initializing credit counters with their previous values.
    credit_counter_N_in = credit_counter_N_out.read();
    credit_counter_E_in = credit_counter_E_out.read();
    credit_counter_W_in = credit_counter_W_out.read();
    credit_counter_S_in = credit_counter_S_out.read();
    credit_counter_L_in = credit_counter_L_out.read();
    
    if (credit_in_N.read()==1 && grant_N.read()==1)
        credit_counter_N_in = credit_counter_N_out.read();
    else if (credit_in_N.read()==1 && (credit_counter_N_out.read() < 3))
        credit_counter_N_in = credit_counter_N_out.read() + 1;
    else if (grant_N.read()==1 && credit_counter_N_out.read() > 0)
        credit_counter_N_in = credit_counter_N_out.read() - 1;
    
    if (credit_in_E.read() == 1 && grant_E.read() == 1 )
        credit_counter_E_in = credit_counter_E_out.read();
    else if (credit_in_E.read() == 1 && credit_counter_E_out.read() < 3)
        credit_counter_E_in = credit_counter_E_out.read() + 1;
    else if (grant_E.read() == 1 && credit_counter_E_out.read() > 0)
        credit_counter_E_in = credit_counter_E_out.read() - 1;
    
    if (credit_in_W.read() == 1 && grant_W.read() == 1)
        credit_counter_W_in = credit_counter_W_out.read();
    else if (credit_in_W.read() == 1 && credit_counter_W_out.read() < 3)
        credit_counter_W_in = credit_counter_W_out.read() + 1;
    else if (grant_W.read() == 1 && credit_counter_W_out.read() > 0)
        credit_counter_W_in = credit_counter_W_out.read() - 1;
    
    if (credit_in_S.read() == 1 && grant_S.read() == 1)
        credit_counter_S_in = credit_counter_S_out.read();
    else if (credit_in_S.read() == 1 && credit_counter_S_out.read() < 3)
        credit_counter_S_in = credit_counter_S_out.read() + 1;
    else if (grant_S.read() == 1 && credit_counter_S_out.read() > 0)
        credit_counter_S_in = credit_counter_S_out.read() - 1;
    
    if (credit_in_L.read() == 1 && grant_L.read() == 1)
        credit_counter_L_in = credit_counter_L_out.read();
    else if (credit_in_L.read()== 1 && credit_counter_L_out.read() < 3)
        credit_counter_L_in = credit_counter_L_out.read() + 1;
    else if (grant_L.read()== 1 && credit_counter_L_out.read() > 0)
        credit_counter_L_in = credit_counter_L_out.read() - 1;
}

void allocator::logic_3()
{
    valid_N.write(grant_N.read());
    valid_E.write(grant_E.read());
    valid_W.write(grant_W.read());
    valid_S.write(grant_S.read());
    valid_L.write(grant_L.read());
}

SC_MODULE_EXPORT(allocator);

