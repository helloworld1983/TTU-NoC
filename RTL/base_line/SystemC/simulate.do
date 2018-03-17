vlib work

sccom -reportprogress -work work FIFO_one_hot_credit_based.cpp
sccom -reportprogress -work work LBDR.cpp
sccom -reportprogress -work work arbiter_in.cpp
sccom -reportprogress -work work arbiter_out.cpp
sccom -reportprogress -work work allocator.cpp
sccom -reportprogress -work work xbar.cpp
sccom -reportprogress -work work Router_32_bit_credit_based.cpp
sccom -reportprogress -work work network_2x2_credit_based.cpp
vcom  -reportprogress 300 -work work ../../../Packages/TB_Package_32_bit_credit_based.vhd

vcom -reportprogress 300 -work work network_2x2_Rand_credit_based_tb.vhd
sccom -link -work work -lib work

vsim work.tb_network_2x2

do ../../../tmp/simul_temp/wave_2x2.do
run 12 us
