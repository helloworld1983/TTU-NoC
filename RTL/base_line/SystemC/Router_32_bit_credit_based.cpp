// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include "Router_32_bit_credit_based.h"

// All the Xbar select_signals
void router_credit_based::logic_1()
{
    sc_uint<5> Xbar_sel_N_tmp, Xbar_sel_E_tmp, Xbar_sel_W_tmp, Xbar_sel_S_tmp, Xbar_sel_L_tmp;

    bool Grant_NN_tmp = Grant_NN.read();
    bool Grant_EN_tmp = Grant_EN.read();
    bool Grant_WN_tmp = Grant_WN.read();
    bool Grant_SN_tmp = Grant_SN.read();
    bool Grant_LN_tmp = Grant_LN.read();

    bool Grant_NE_tmp = Grant_NE.read();
    bool Grant_EE_tmp = Grant_EE.read();
    bool Grant_WE_tmp = Grant_WE.read();
    bool Grant_SE_tmp = Grant_SE.read();
    bool Grant_LE_tmp = Grant_LE.read();

    bool Grant_NW_tmp = Grant_NW.read();
    bool Grant_EW_tmp = Grant_EW.read();
    bool Grant_WW_tmp = Grant_WW.read();
    bool Grant_SW_tmp = Grant_SW.read();
    bool Grant_LW_tmp = Grant_LW.read();

    bool Grant_NS_tmp = Grant_NS.read();
    bool Grant_ES_tmp = Grant_ES.read();
    bool Grant_WS_tmp = Grant_WS.read();
    bool Grant_SS_tmp = Grant_SS.read();
    bool Grant_LS_tmp = Grant_LS.read();

    bool Grant_NL_tmp = Grant_NL.read();
    bool Grant_EL_tmp = Grant_EL.read();
    bool Grant_WL_tmp = Grant_WL.read();
    bool Grant_SL_tmp = Grant_SL.read();
    bool Grant_LL_tmp = Grant_LL.read();

    Xbar_sel_N_tmp[4] = Grant_NN_tmp;
    Xbar_sel_N_tmp[3] = Grant_NE_tmp;
    Xbar_sel_N_tmp[2] = Grant_NW_tmp;
    Xbar_sel_N_tmp[1] = Grant_NS_tmp;
    Xbar_sel_N_tmp[0] = Grant_NL_tmp;

    Xbar_sel_E_tmp[4] = Grant_EN_tmp;
    Xbar_sel_E_tmp[3] = Grant_EE_tmp;
    Xbar_sel_E_tmp[2] = Grant_EW_tmp;
    Xbar_sel_E_tmp[1] = Grant_ES_tmp;
    Xbar_sel_E_tmp[0] = Grant_EL_tmp;

    Xbar_sel_W_tmp[4] = Grant_WN_tmp;
    Xbar_sel_W_tmp[3] = Grant_WE_tmp;
    Xbar_sel_W_tmp[2] = Grant_WW_tmp;
    Xbar_sel_W_tmp[1] = Grant_WS_tmp;
    Xbar_sel_W_tmp[0] = Grant_WL_tmp;

    Xbar_sel_S_tmp[4] = Grant_SN_tmp;
    Xbar_sel_S_tmp[3] = Grant_SE_tmp;
    Xbar_sel_S_tmp[2] = Grant_SW_tmp;
    Xbar_sel_S_tmp[1] = Grant_SS_tmp;
    Xbar_sel_S_tmp[0] = Grant_SL_tmp;

    Xbar_sel_L_tmp[4] = Grant_LN_tmp;
    Xbar_sel_L_tmp[3] = Grant_LE_tmp;
    Xbar_sel_L_tmp[2] = Grant_LW_tmp;
    Xbar_sel_L_tmp[1] = Grant_LS_tmp;
    Xbar_sel_L_tmp[0] = Grant_LL_tmp;

    Xbar_sel_N.write (Xbar_sel_N_tmp);
    Xbar_sel_E.write (Xbar_sel_E_tmp);
    Xbar_sel_W.write (Xbar_sel_W_tmp);
    Xbar_sel_S.write (Xbar_sel_S_tmp);
    Xbar_sel_L.write (Xbar_sel_L_tmp);
    
}

void router_credit_based::logic_2()
{
    sc_uint<32> FIFO_D_out_N_tmp, FIFO_D_out_E_tmp, FIFO_D_out_W_tmp, FIFO_D_out_S_tmp, FIFO_D_out_L_tmp;
    
    FIFO_D_out_N_tmp = FIFO_D_out_N.read();
    FIFO_D_out_E_tmp = FIFO_D_out_E.read();
    FIFO_D_out_W_tmp = FIFO_D_out_W.read();
    FIFO_D_out_S_tmp = FIFO_D_out_S.read();
    FIFO_D_out_L_tmp = FIFO_D_out_L.read();
    
    LBDR_cur_addr_y.write ((sc_uint<7>) (current_address / NoC_size_x));
    LBDR_cur_addr_x.write ((sc_uint<7>) (current_address % NoC_size_x));

    LBDR_N_dst_addr_y.write (FIFO_D_out_N_tmp.range(14,8));
    LBDR_N_dst_addr_x.write (FIFO_D_out_N_tmp.range(7,1));
    LBDR_E_dst_addr_y.write (FIFO_D_out_E_tmp.range(14,8));
    LBDR_E_dst_addr_x.write (FIFO_D_out_E_tmp.range(7,1));
    LBDR_W_dst_addr_y.write (FIFO_D_out_W_tmp.range(14,8));
    LBDR_W_dst_addr_x.write (FIFO_D_out_W_tmp.range(7,1));
    LBDR_S_dst_addr_y.write (FIFO_D_out_S_tmp.range(14,8));
    LBDR_S_dst_addr_x.write (FIFO_D_out_S_tmp.range(7,1));
    LBDR_L_dst_addr_y.write (FIFO_D_out_L_tmp.range(14,8));
    LBDR_L_dst_addr_x.write (FIFO_D_out_L_tmp.range(7,1));

    LBDR_N_flit_type.write (FIFO_D_out_N_tmp.range(32-1, 32-3));
    LBDR_E_flit_type.write (FIFO_D_out_E_tmp.range(32-1, 32-3));
    LBDR_W_flit_type.write (FIFO_D_out_W_tmp.range(32-1, 32-3));
    LBDR_S_flit_type.write (FIFO_D_out_S_tmp.range(32-1, 32-3));
    LBDR_L_flit_type.write (FIFO_D_out_L_tmp.range(32-1, 32-3));
    
}

SC_MODULE_EXPORT(router_credit_based);