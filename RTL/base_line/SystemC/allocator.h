// Copyright (C) 2018 Siavoosh Payandeh Azad, Behrad Niazmand

#include "arbiter_in.h"
#include "arbiter_out.h"

SC_MODULE(allocator)
{
	sc_in <bool> reset;
	sc_in <bool> clk;
	// flow control
	sc_in <bool> credit_in_N, credit_in_E, credit_in_W, credit_in_S, credit_in_L;

	sc_in <bool> req_N_N, req_N_E, req_N_W, req_N_S, req_N_L;
	sc_in <bool> req_E_N, req_E_E, req_E_W, req_E_S, req_E_L;
	sc_in <bool> req_W_N, req_W_E, req_W_W, req_W_S, req_W_L;
	sc_in <bool> req_S_N, req_S_E, req_S_W, req_S_S, req_S_L;
	sc_in <bool> req_L_N, req_L_E, req_L_W, req_L_S, req_L_L;

	sc_in <bool> empty_N, empty_E, empty_W, empty_S, empty_L; 
	// grant_X_Y means the grant for X output port towards Y input port
	// this means for any X in [N, E, W, S, L] ) set grant_X_Y is one hot!
	sc_out <bool> valid_N, valid_E, valid_W, valid_S, valid_L;

	sc_out <bool> grant_N_N, grant_N_E, grant_N_W, grant_N_S, grant_N_L;
	sc_out <bool> grant_E_N, grant_E_E, grant_E_W, grant_E_S, grant_E_L;
	sc_out <bool> grant_W_N, grant_W_E, grant_W_W, grant_W_S, grant_W_L;
	sc_out <bool> grant_S_N, grant_S_E, grant_S_W, grant_S_S, grant_S_L;
	sc_out <bool> grant_L_N, grant_L_E, grant_L_W, grant_L_S, grant_L_L;

	// Signal definitions
	// So the idea is that we should have counters that keep track of credit!
	sc_signal <sc_uint<2> > credit_counter_N_in, credit_counter_N_out;
	sc_signal <sc_uint<2> > credit_counter_E_in, credit_counter_E_out;
	sc_signal <sc_uint<2> > credit_counter_W_in, credit_counter_W_out;
	sc_signal <sc_uint<2> > credit_counter_S_in, credit_counter_S_out;
	sc_signal <sc_uint<2> > credit_counter_L_in, credit_counter_L_out;

	sc_signal <bool> grant_N, grant_E, grant_W, grant_S, grant_L;

	sc_signal <bool> X_N_N, X_N_E, X_N_W, X_N_S, X_N_L;
	sc_signal <bool> X_E_N, X_E_E, X_E_W, X_E_S, X_E_L;
	sc_signal <bool> X_W_N, X_W_E, X_W_W, X_W_S, X_W_L;
	sc_signal <bool> X_S_N, X_S_E, X_S_W, X_S_S, X_S_L;
	sc_signal <bool> X_L_N, X_L_E, X_L_W, X_L_S, X_L_L;

	sc_signal <bool> grant_N_N_sig, grant_N_E_sig, grant_N_W_sig, grant_N_S_sig, grant_N_L_sig;
	sc_signal <bool> grant_E_N_sig, grant_E_E_sig, grant_E_W_sig, grant_E_S_sig, grant_E_L_sig;
	sc_signal <bool> grant_W_N_sig, grant_W_E_sig, grant_W_W_sig, grant_W_S_sig, grant_W_L_sig;
	sc_signal <bool> grant_S_N_sig, grant_S_E_sig, grant_S_W_sig, grant_S_S_sig, grant_S_L_sig;
	sc_signal <bool> grant_L_N_sig, grant_L_E_sig, grant_L_W_sig, grant_L_S_sig, grant_L_L_sig;

    arbiter_in  *arb_N_X, *arb_E_X, *arb_W_X, *arb_S_X, *arb_L_X;
    arbiter_out *arb_X_N, *arb_X_E, *arb_X_W, *arb_X_S, *arb_X_L;

	void allocator_sequential_proc();
	void logic_1();
	void logic_2();
	void logic_3();

    SC_HAS_PROCESS(allocator);
    
    allocator (sc_module_name name_) :
    sc_module(name_)
    {
		// Instantiation of Arbiter_in modules (5 modules, 1 per each input port)
        arb_N_X = new arbiter_in ("arb_N_X");
		(*arb_N_X) (reset, clk, req_N_N, req_N_E, req_N_W, req_N_S, req_N_L, X_N_N, X_N_E, X_N_W, X_N_S, X_N_L);

        arb_E_X = new arbiter_in ("arb_E_X");
        (*arb_E_X) (reset, clk, req_E_N, req_E_E, req_E_W, req_E_S, req_E_L, X_E_N, X_E_E, X_E_W, X_E_S, X_E_L);
        
        arb_W_X = new arbiter_in ("arb_W_X");
		(*arb_W_X) (reset, clk, req_W_N, req_W_E, req_W_W, req_W_S, req_W_L, X_W_N, X_W_E, X_W_W, X_W_S, X_W_L);
        
        arb_S_X = new arbiter_in ("arb_S_X");
		(*arb_S_X) (reset, clk, req_S_N, req_S_E, req_S_W, req_S_S, req_S_L, X_S_N, X_S_E, X_S_W, X_S_S, X_S_L);
        
        arb_L_X = new arbiter_in ("arb_L_X");
		(*arb_L_X) (reset, clk, req_L_N, req_L_E, req_L_W, req_L_S, req_L_L, X_L_N, X_L_E, X_L_W, X_L_S, X_L_L);

        arb_X_N = new arbiter_out ("arb_X_N");
		(*arb_X_N) (reset, clk, X_N_N, X_E_N, X_W_N, X_S_N, X_L_N, credit_counter_N_out, grant_N_N_sig, grant_N_E_sig, grant_N_W_sig, grant_N_S_sig, grant_N_L_sig);
        
        arb_X_E = new arbiter_out ("arb_X_E");
		(*arb_X_E) (reset, clk, X_N_E, X_E_E, X_W_E, X_S_E, X_L_E, credit_counter_E_out, grant_E_N_sig, grant_E_E_sig, grant_E_W_sig, grant_E_S_sig, grant_E_L_sig);
        
        arb_X_W = new arbiter_out ("arb_X_W");
		(*arb_X_W) (reset, clk, X_N_W, X_E_W, X_W_W, X_S_W, X_L_W, credit_counter_W_out, grant_W_N_sig, grant_W_E_sig, grant_W_W_sig, grant_W_S_sig, grant_W_L_sig);
        
        arb_X_S = new arbiter_out ("arb_X_S");
		(*arb_X_S) (reset, clk, X_N_S, X_E_S, X_W_S, X_S_S, X_L_S, credit_counter_S_out, grant_S_N_sig, grant_S_E_sig, grant_S_W_sig, grant_S_S_sig, grant_S_L_sig);
        
        arb_X_L = new arbiter_out ("arb_X_L");
		(*arb_X_L) (reset, clk, X_N_L, X_E_L, X_W_L, X_S_L, X_L_L, credit_counter_L_out, grant_L_N_sig, grant_L_E_sig, grant_L_W_sig, grant_L_S_sig, grant_L_L_sig);

		SC_METHOD(allocator_sequential_proc);
        sensitive << clk << reset;

		SC_METHOD(logic_1);
		sensitive << grant_N_N_sig << grant_N_E_sig << grant_N_W_sig << grant_N_S_sig << grant_N_L_sig << grant_E_N_sig << grant_E_E_sig << grant_E_W_sig << grant_E_S_sig << grant_E_L_sig << grant_W_N_sig << grant_W_E_sig << grant_W_W_sig << grant_W_S_sig << grant_W_L_sig << grant_S_N_sig << grant_S_E_sig << grant_S_W_sig << grant_S_S_sig << grant_S_L_sig << grant_L_N_sig << grant_L_E_sig << grant_L_W_sig << grant_L_S_sig << grant_L_L_sig << empty_N << empty_E << empty_W << empty_S << empty_L;

		SC_METHOD(logic_2);
		sensitive << credit_in_N << credit_in_E << credit_in_W << credit_in_S << credit_in_L << grant_N << grant_E << grant_W << grant_S << grant_L << credit_counter_N_out << credit_counter_E_out << credit_counter_W_out << credit_counter_S_out << credit_counter_L_out;

		SC_METHOD(logic_3);
		sensitive << grant_N << grant_E << grant_W << grant_S << grant_L;
	}
};

