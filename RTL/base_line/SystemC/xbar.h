// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include "systemc.h"

SC_MODULE(XBAR) 
{
    sc_in <sc_uint<32> > North_in;
    sc_in <sc_uint<32> > East_in;
    sc_in <sc_uint<32> > West_in;
    sc_in <sc_uint<32> > South_in;
    sc_in <sc_uint<32> > Local_in;
    sc_in <sc_uint<5> > sel;
    sc_out <sc_uint<32> > Data_out;

    void logic_1();

    SC_HAS_PROCESS(XBAR);
    
    XBAR (sc_module_name name_) :
    sc_module(name_)
    {
        SC_METHOD(logic_1);
        sensitive << sel << North_in << East_in << West_in << South_in << Local_in; 
    }

};
