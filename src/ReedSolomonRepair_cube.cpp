/*
Copyright (c) 2015, Advanced Micro Devices, Inc. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "ReedSolomonRepair_cube.hh"
#include "DRAMDomain.hh"
#include "Settings.hh"

extern struct Settings settings;

ReedSolomonRepair_cube::ReedSolomonRepair_cube(string name, int n_correctable, int n_detectable, uint64_t data_block_bits,uint8_t symbol_size_bits) : RepairScheme(name) 
, m_n_correctable(n_correctable)
, m_n_detectable(n_detectable)
, m_bitwidth(data_block_bits)
, m_symbol_size_bits(symbol_size_bits)
{
	counter_prev=0;
	counter_now=0;
	m_log_block_bits = log2( data_block_bits );
	m_log_symbol_bits = log2( symbol_size_bits );
}

void ReedSolomonRepair_cube::repair( FaultDomain *fd, uint64_t &n_undetectable, uint64_t &n_uncorrectable )
{

	n_undetectable = n_uncorrectable = 0;
	uint bit_shift=0;
	uint loopcount_locations=0;
	uint ii=0;
	list<FaultDomain*> *pChips = fd->getChildren();

}
