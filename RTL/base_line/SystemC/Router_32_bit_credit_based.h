// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include "FIFO_one_hot_credit_based.h"
#include "LBDR.h"
#include "allocator.h"
#include "xbar.h"

SC_MODULE(router_credit_based) 
{
    sc_in <bool> reset;
    sc_in <bool> clk;
    
    sc_in <sc_uint<32> > RX_N, RX_E, RX_W, RX_S, RX_L;
    sc_in <bool> credit_in_N, credit_in_E, credit_in_W, credit_in_S, credit_in_L;
    sc_in <bool> valid_in_N, valid_in_E, valid_in_W, valid_in_S, valid_in_L;
    
    sc_out <bool> valid_out_N, valid_out_E, valid_out_W, valid_out_S, valid_out_L;
    sc_out <bool> credit_out_N, credit_out_E, credit_out_W, credit_out_S, credit_out_L;
    
    sc_out <sc_uint<32> > TX_N, TX_E, TX_W, TX_S, TX_L;
    
    sc_signal <sc_uint<32> > FIFO_D_out_N, FIFO_D_out_E, FIFO_D_out_W, FIFO_D_out_S, FIFO_D_out_L;
    
    sc_signal <sc_uint<3> > LBDR_N_flit_type, LBDR_E_flit_type, LBDR_W_flit_type, LBDR_S_flit_type, LBDR_L_flit_type;
    
    sc_signal <sc_uint<7> > LBDR_cur_addr_y, LBDR_cur_addr_x;
    sc_signal <sc_uint<7> > LBDR_N_dst_addr_y, LBDR_E_dst_addr_y, LBDR_W_dst_addr_y, LBDR_S_dst_addr_y, LBDR_L_dst_addr_y;
    sc_signal <sc_uint<7> > LBDR_N_dst_addr_x, LBDR_E_dst_addr_x, LBDR_W_dst_addr_x, LBDR_S_dst_addr_x, LBDR_L_dst_addr_x;
    
    sc_signal <bool> Grant_NN, Grant_NE, Grant_NW, Grant_NS, Grant_NL;
    sc_signal <bool> Grant_EN, Grant_EE, Grant_EW, Grant_ES, Grant_EL;
    sc_signal <bool> Grant_WN, Grant_WE, Grant_WW, Grant_WS, Grant_WL;
    sc_signal <bool> Grant_SN, Grant_SE, Grant_SW, Grant_SS, Grant_SL;
    sc_signal <bool> Grant_LN, Grant_LE, Grant_LW, Grant_LS, Grant_LL;
    
    sc_signal <bool> Req_NN, Req_EN, Req_WN, Req_SN, Req_LN;
    sc_signal <bool> Req_NE, Req_EE, Req_WE, Req_SE, Req_LE;
    sc_signal <bool> Req_NW, Req_EW, Req_WW, Req_SW, Req_LW;
    sc_signal <bool> Req_NS, Req_ES, Req_WS, Req_SS, Req_LS;
    sc_signal <bool> Req_NL, Req_EL, Req_WL, Req_SL, Req_LL;
    
    sc_signal <bool> empty_N, empty_E, empty_W, empty_S, empty_L;
    
    sc_signal <sc_uint<5> > Xbar_sel_N, Xbar_sel_E, Xbar_sel_W, Xbar_sel_S, Xbar_sel_L;
    
    FIFO_credit_based *FIFO_N, *FIFO_E, *FIFO_W, *FIFO_S, *FIFO_L;
    LBDR *LBDR_N, *LBDR_E, *LBDR_W, *LBDR_S, *LBDR_L;
    allocator *allocator_unit;
    XBAR *XBAR_N, *XBAR_E, *XBAR_W, *XBAR_S, *XBAR_L;
    
    void logic_1();
    void logic_2();
    
    SC_HAS_PROCESS(router_credit_based);
    
    router_credit_based (sc_module_name name_, int current_address_=5, int Rxy_rst_=60, int Cx_rst_=15, int NoC_size_x_=4) :
    sc_module(name_), current_address (current_address_), Rxy_rst (Rxy_rst_), Cx_rst (Cx_rst_), NoC_size_x (NoC_size_x_), 
    Grant_NN (0), Grant_EE (0), Grant_WW (0), Grant_SS (0), Grant_LL (0), Req_NN (0), Req_EE (0), Req_WW (0), Req_SS (0), Req_LL (0)
    {
        // Instantiation of modules (5 modules, 1 per each input port)
        // All the FIFOs
        FIFO_N = new FIFO_credit_based ("FIFO_N");
        (*FIFO_N) (reset, clk, RX_N, valid_in_N, Grant_NN, Grant_EN, Grant_WN, Grant_SN, Grant_LN, credit_out_N, empty_N, FIFO_D_out_N);
        
        FIFO_E = new FIFO_credit_based ("FIFO_E");
        (*FIFO_E) (reset, clk, RX_E, valid_in_E, Grant_NE, Grant_EE, Grant_WE, Grant_SE, Grant_LE, credit_out_E, empty_E, FIFO_D_out_E);
        
        FIFO_W = new FIFO_credit_based ("FIFO_W");
        (*FIFO_W) (reset, clk, RX_W, valid_in_W, Grant_NW, Grant_EW, Grant_WW, Grant_SW, Grant_LW, credit_out_W, empty_W, FIFO_D_out_W);
        
        FIFO_S = new FIFO_credit_based ("FIFO_S");
        (*FIFO_S) (reset, clk, RX_S, valid_in_S, Grant_NS, Grant_ES, Grant_WS, Grant_SS, Grant_LS, credit_out_S, empty_S, FIFO_D_out_S);
        
        FIFO_L = new FIFO_credit_based ("FIFO_L");
        (*FIFO_L) (reset, clk, RX_L, valid_in_L, Grant_NL, Grant_EL, Grant_WL, Grant_SL, Grant_LL, credit_out_L, empty_L, FIFO_D_out_L);
        
        // All the LBDRs
        LBDR_N = new LBDR ("LBDR_N", Rxy_rst, Cx_rst);
        (*LBDR_N) (reset, clk, empty_N,
                   LBDR_N_flit_type,
                   LBDR_cur_addr_y,
                   LBDR_cur_addr_x,
                   LBDR_N_dst_addr_y,
                   LBDR_N_dst_addr_x,
                   Grant_NN, Grant_EN, Grant_WN, Grant_SN, Grant_LN,
                   Req_NN, Req_NE, Req_NW, Req_NS, Req_NL);
        
        LBDR_E = new LBDR ("LBDR_E", Rxy_rst, Cx_rst);
        (*LBDR_E) (reset, clk, empty_E,
                   LBDR_E_flit_type,
                   LBDR_cur_addr_y,
                   LBDR_cur_addr_x,
                   LBDR_E_dst_addr_y,
                   LBDR_E_dst_addr_x,
                   Grant_NE, Grant_EE, Grant_WE, Grant_SE, Grant_LE,
                   Req_EN, Req_EE, Req_EW, Req_ES, Req_EL);
        
        LBDR_W = new LBDR ("LBDR_W", Rxy_rst, Cx_rst);
        (*LBDR_W) (reset, clk, empty_W,
                   LBDR_W_flit_type,
                   LBDR_cur_addr_y,
                   LBDR_cur_addr_x,
                   LBDR_W_dst_addr_y,
                   LBDR_W_dst_addr_x,
                   Grant_NW, Grant_EW, Grant_WW, Grant_SW, Grant_LW,
                   Req_WN, Req_WE, Req_WW, Req_WS, Req_WL);
        
        LBDR_S = new LBDR ("LBDR_S", Rxy_rst, Cx_rst);
        (*LBDR_S) (reset, clk, empty_S,
                   LBDR_S_flit_type,
                   LBDR_cur_addr_y,
                   LBDR_cur_addr_x,
                   LBDR_S_dst_addr_y,
                   LBDR_S_dst_addr_x,
                   Grant_NS, Grant_ES, Grant_WS, Grant_SS, Grant_LS,
                   Req_SN, Req_SE, Req_SW, Req_SS, Req_SL);
        
        LBDR_L = new LBDR ("LBDR_L", Rxy_rst, Cx_rst);
        (*LBDR_L) (reset, clk, empty_L,
                   LBDR_L_flit_type,
                   LBDR_cur_addr_y,
                   LBDR_cur_addr_x,
                   LBDR_L_dst_addr_y,
                   LBDR_L_dst_addr_x,
                   Grant_NL, Grant_EL, Grant_WL, Grant_SL, Grant_LL,
                   Req_LN, Req_LE, Req_LW, Req_LS, Req_LL);
        
        // Switch Allocator
        allocator_unit = new allocator ("allocator_unit");
        allocator_unit -> reset (reset);
        allocator_unit -> clk (clk);
        allocator_unit -> credit_in_N (credit_in_N);
        allocator_unit -> credit_in_E (credit_in_E);
        allocator_unit -> credit_in_W (credit_in_W);
        allocator_unit -> credit_in_S (credit_in_S);
        allocator_unit -> credit_in_L (credit_in_L);
        allocator_unit -> req_N_N (Req_NN);
        allocator_unit -> req_N_E (Req_NE);
        allocator_unit -> req_N_W (Req_NW);
        allocator_unit -> req_N_S (Req_NS);
        allocator_unit -> req_N_L (Req_NL);
        allocator_unit -> req_E_N (Req_EN);
        allocator_unit -> req_E_E (Req_EE);
        allocator_unit -> req_E_W (Req_EW);
        allocator_unit -> req_E_S (Req_ES);
        allocator_unit -> req_E_L (Req_EL);
        allocator_unit -> req_W_N (Req_WN);
        allocator_unit -> req_W_E (Req_WE);
        allocator_unit -> req_W_W (Req_WW);
        allocator_unit -> req_W_S (Req_WS);
        allocator_unit -> req_W_L (Req_WL);
        allocator_unit -> req_S_N (Req_SN);
        allocator_unit -> req_S_E (Req_SE);
        allocator_unit -> req_S_W (Req_SW);
        allocator_unit -> req_S_S (Req_SS);
        allocator_unit -> req_S_L (Req_SL);
        allocator_unit -> req_L_N (Req_LN);
        allocator_unit -> req_L_E (Req_LE);
        allocator_unit -> req_L_W (Req_LW);
        allocator_unit -> req_L_S (Req_LS);
        allocator_unit -> req_L_L (Req_LL);
        allocator_unit -> empty_N (empty_N);
        allocator_unit -> empty_E (empty_E);
        allocator_unit -> empty_W (empty_W);
        allocator_unit -> empty_S (empty_S);
        allocator_unit -> empty_L (empty_L);
        allocator_unit -> valid_N (valid_out_N);
        allocator_unit -> valid_E (valid_out_E);
        allocator_unit -> valid_W (valid_out_W);
        allocator_unit -> valid_S (valid_out_S);
        allocator_unit -> valid_L (valid_out_L);
        allocator_unit -> grant_N_N (Grant_NN);
        allocator_unit -> grant_N_E (Grant_NE);
        allocator_unit -> grant_N_W (Grant_NW);
        allocator_unit -> grant_N_S (Grant_NS);
        allocator_unit -> grant_N_L (Grant_NL);
        allocator_unit -> grant_E_N (Grant_EN);
        allocator_unit -> grant_E_E (Grant_EE);
        allocator_unit -> grant_E_W (Grant_EW);
        allocator_unit -> grant_E_S (Grant_ES);
        allocator_unit -> grant_E_L (Grant_EL);
        allocator_unit -> grant_W_N (Grant_WN);
        allocator_unit -> grant_W_E (Grant_WE);
        allocator_unit -> grant_W_W (Grant_WW);
        allocator_unit -> grant_W_S (Grant_WS);
        allocator_unit -> grant_W_L (Grant_WL);
        allocator_unit -> grant_S_N (Grant_SN);
        allocator_unit -> grant_S_E (Grant_SE);
        allocator_unit -> grant_S_W (Grant_SW);
        allocator_unit -> grant_S_S (Grant_SS);
        allocator_unit -> grant_S_L (Grant_SL);
        allocator_unit -> grant_L_N (Grant_LN);
        allocator_unit -> grant_L_E (Grant_LE);
        allocator_unit -> grant_L_W (Grant_LW);
        allocator_unit -> grant_L_S (Grant_LS);
        allocator_unit -> grant_L_L (Grant_LL);
        
        // All the XBARs
        
        XBAR_N = new XBAR ("XBAR_N");
        (*XBAR_N) (FIFO_D_out_N, FIFO_D_out_E, FIFO_D_out_W, FIFO_D_out_S, FIFO_D_out_L, Xbar_sel_N, TX_N);
        
        XBAR_E = new XBAR ("XBAR_E");
        (*XBAR_E) (FIFO_D_out_N, FIFO_D_out_E, FIFO_D_out_W, FIFO_D_out_S, FIFO_D_out_L, Xbar_sel_E, TX_E);
        
        XBAR_W = new XBAR ("XBAR_W");
        (*XBAR_W) (FIFO_D_out_N, FIFO_D_out_E, FIFO_D_out_W, FIFO_D_out_S, FIFO_D_out_L, Xbar_sel_W, TX_W);
        
        XBAR_S = new XBAR ("XBAR_S");
        (*XBAR_S) (FIFO_D_out_N, FIFO_D_out_E, FIFO_D_out_W, FIFO_D_out_S, FIFO_D_out_L, Xbar_sel_S, TX_S);
        
        XBAR_L = new XBAR ("XBAR_L");
        (*XBAR_L) (FIFO_D_out_N, FIFO_D_out_E, FIFO_D_out_W, FIFO_D_out_S, FIFO_D_out_L, Xbar_sel_L, TX_L);
        
        SC_METHOD(logic_1);
        sensitive << Grant_NN << Grant_NE << Grant_NW << Grant_NS << Grant_NL
        << Grant_EN << Grant_EE << Grant_EW << Grant_ES << Grant_EL
        << Grant_WN << Grant_WE << Grant_WW << Grant_WS << Grant_WL
        << Grant_SN << Grant_SE << Grant_SW << Grant_SS << Grant_SL
        << Grant_LN << Grant_LE << Grant_LW << Grant_LS << Grant_LL;
        
        SC_METHOD(logic_2);
        sensitive << FIFO_D_out_N << FIFO_D_out_E << FIFO_D_out_W << FIFO_D_out_S << FIFO_D_out_L;
    }

    private: 
        int current_address;
        int Rxy_rst;
        int Cx_rst;
        int NoC_size_x;
};
