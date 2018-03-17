// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include <systemc.h>

SC_MODULE(FIFO_credit_based) 
{
    sc_in <bool> reset;
    sc_in <bool> clk;
    sc_in <sc_uint<32> > RX;
    sc_in <bool> valid_in;
    sc_in <bool> read_en_N;
    sc_in <bool> read_en_E;
    sc_in <bool> read_en_W;
    sc_in <bool> read_en_S;
    sc_in <bool> read_en_L;
    sc_out <bool> credit_out;
    sc_out <bool> empty_out;
    sc_out <sc_uint<32> > Data_out;

    sc_signal <sc_uint<4> > read_pointer, read_pointer_in,  write_pointer, write_pointer_in;
    sc_signal <bool> full, empty;
    sc_signal <bool> read_en, write_en;
    
    sc_signal <sc_uint<32> > FIFO_MEM_1, FIFO_MEM_1_in;
    sc_signal <sc_uint<32> > FIFO_MEM_2, FIFO_MEM_2_in;
    sc_signal <sc_uint<32> > FIFO_MEM_3, FIFO_MEM_3_in;
    sc_signal <sc_uint<32> > FIFO_MEM_4, FIFO_MEM_4_in;
    
    void FIFO_sequential_proc();
    void logic_1();
    void logic_2();
    void logic_3();
    void logic_8();
    void logic_4();
    void logic_5();
    void logic_6();
    void logic_7();
    
    SC_HAS_PROCESS(FIFO_credit_based);
    
    FIFO_credit_based(sc_module_name name_) :
    sc_module(name_)
    {
        SC_METHOD(FIFO_sequential_proc);
        sensitive << clk << reset;
        
        SC_METHOD(logic_1);
        sensitive << RX << write_pointer << FIFO_MEM_1 << FIFO_MEM_2 << FIFO_MEM_3 << FIFO_MEM_4;
        
        SC_METHOD (logic_2);
        sensitive << read_pointer << FIFO_MEM_1 << FIFO_MEM_2 << FIFO_MEM_3 << FIFO_MEM_4;
        
        SC_METHOD (logic_3);
        sensitive << read_en_N << read_en_E << read_en_W << read_en_S << read_en_L << empty;
        
        SC_METHOD (logic_8);
        sensitive << empty;

        SC_METHOD (logic_4);
        sensitive << write_en << write_pointer;
        
        SC_METHOD (logic_5);
        sensitive << read_en << empty << read_pointer;
        
        SC_METHOD (logic_6);
        sensitive << full << valid_in;
        
        SC_METHOD (logic_7);
        sensitive << write_pointer << read_pointer;
    }
    
};
