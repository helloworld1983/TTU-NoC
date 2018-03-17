// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include "systemc.h"

#define HEAD  1
#define BODY  2
#define TAIL  4

SC_MODULE(LBDR) 
{
    sc_in <bool> reset;
    sc_in <bool> clk;
    sc_in <bool> empty;
    sc_in <sc_uint<3> > flit_type;
    sc_in <sc_uint<7> > cur_addr_y, cur_addr_x;
    sc_in <sc_uint<7> > dst_addr_y, dst_addr_x;
    sc_in <bool> grant_N, grant_E, grant_W, grant_S, grant_L;
    sc_out <bool> Req_N, Req_E, Req_W, Req_S, Req_L;
    
    sc_signal <sc_uint<4> > Cx;
    sc_signal <sc_uint<8> > Rxy;
    sc_signal <bool> N1, E1, W1, S1;
    sc_signal <bool> Req_N_in, Req_E_in, Req_W_in, Req_S_in, Req_L_in;
    sc_signal <bool> Req_N_FF, Req_E_FF, Req_W_FF, Req_S_FF, Req_L_FF;
    sc_signal <bool> grants;
    
    void LBDR_sequential_proc();
    void logic_1();
    void logic_2();
    void logic_3();
    void logic_4();
    
    SC_HAS_PROCESS(LBDR);
    
    LBDR (sc_module_name name_, int Rxy_rst_=60, int Cx_rst_=15) :
    sc_module(name_), Rxy_rst (Rxy_rst_), Cx_rst (Cx_rst_)
    {
        SC_METHOD(LBDR_sequential_proc);
        sensitive << clk << reset;

        SC_METHOD(logic_1);
        sensitive << grant_N << grant_E << grant_W << grant_S << grant_L;

        SC_METHOD(logic_2);
        sensitive << dst_addr_y << cur_addr_y << cur_addr_x << dst_addr_x << dst_addr_x << cur_addr_x << cur_addr_y << dst_addr_y;
        
        SC_METHOD (logic_3);
        sensitive << N1 << E1 << W1 << S1 << flit_type << empty << Req_N_FF << Req_E_FF << Req_W_FF << Req_S_FF << Req_L_FF << grants << Cx << Rxy;
        
        SC_METHOD (logic_4);
        sensitive << Req_N_FF << Req_E_FF << Req_W_FF << Req_S_FF << Req_L_FF;
        
        Cx = Cx_rst;
        Rxy = Rxy_rst;
    }

    private:
        int Cx_rst, Rxy_rst;
};

