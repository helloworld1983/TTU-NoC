// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include "LBDR.h"

// The sequential part


void LBDR::LBDR_sequential_proc()
{
    if (reset.read() == 0) // Synchronous reset ?!
    {
        Req_N_FF.write (0);
        Req_E_FF.write (0);
        Req_W_FF.write (0);
        Req_S_FF.write (0);
        Req_L_FF.write (0);
    }
    
    else if (clk.event() && clk.read() == 1) // At the rising edge of clock do the following
    {
        Req_N_FF.write (Req_N_in.read());
        Req_E_FF.write (Req_E_in.read());
        Req_W_FF.write (Req_W_in.read());
        Req_S_FF.write (Req_S_in.read());
        Req_L_FF.write (Req_L_in.read());
    }
}


// The combionational part


void LBDR::logic_1()
{
    grants.write (grant_N.read() | grant_E.read() | grant_W.read() | grant_S.read() | grant_L.read());
}


void LBDR::logic_2()
{
//    cout << "cur("<< cur_addr_x << "," <<cur_addr_y <<"), dst( "<< dst_addr_x << "," << dst_addr_y << ") \n";
    N1.write (dst_addr_y.read() < cur_addr_y.read());
    E1.write (cur_addr_x.read() < dst_addr_x.read());
    W1.write (dst_addr_x.read() < cur_addr_x.read());
    S1.write (cur_addr_y.read() < dst_addr_y.read());
//    cout << "Prime Signals are (NEWS) : " << N1 << E1 << W1 << S1 << " \n";
}


void LBDR::logic_3()
{

    sc_uint<4> Cx_tmp = Cx.read();
    sc_uint<8> Rxy_tmp = Rxy.read();

//    cout << Cx_tmp << " " << Rxy_tmp << " \n";

    if (flit_type.read() == HEAD && empty.read()==0)
    {
        Req_N_in.write (((N1.read() && !E1.read() && !W1.read()) || (N1.read() && E1.read() && Rxy_tmp[0]) || (N1.read() && W1.read() && Rxy_tmp[1])) && Cx_tmp[0]);
        Req_E_in.write (((E1.read() && !N1.read() && !S1.read()) || (E1.read() && N1.read() && Rxy_tmp[2]) || (E1.read() && S1.read() && Rxy_tmp[3])) && Cx_tmp[1]);
        Req_W_in.write (((W1.read() && !N1.read() && !S1.read()) || (W1.read() && N1.read() && Rxy_tmp[4]) || (W1.read() && S1.read() && Rxy_tmp[5])) && Cx_tmp[2]);
        Req_S_in.write (((S1.read() && !E1.read() && !W1.read()) || (S1.read() && E1.read() && Rxy_tmp[6]) || (S1.read() && W1.read() && Rxy_tmp[7])) && Cx_tmp[3]);
        Req_L_in.write (!N1.read() && !E1.read() && !W1.read() && !S1.read());
        
//        cout << "Requests are (NEWSL) : " << Req_N_in << Req_E_in << Req_W_in << Req_S_in << Req_L_in << " \n";
    }
    
    else if (flit_type.read() == TAIL && empty.read() == 0 && grants.read() == 1)
    {
        Req_N_in.write (0);
        Req_E_in.write (0);
        Req_W_in.write (0);
        Req_S_in.write (0);
        Req_L_in.write (0);
    }
    
    else // BODY flit_type or Invalid flit_type
    {
        Req_N_in.write (Req_N_FF.read());
        Req_E_in.write (Req_E_FF.read());
        Req_W_in.write (Req_W_FF.read());
        Req_S_in.write (Req_S_FF.read());
        Req_L_in.write (Req_L_FF.read());
    }
}


void LBDR::logic_4()
{
    Req_N.write (Req_N_FF.read());
    Req_E.write (Req_E_FF.read());
    Req_W.write (Req_W_FF.read());
    Req_S.write (Req_S_FF.read());
    Req_L.write (Req_L_FF.read());
}

SC_MODULE_EXPORT(LBDR);
