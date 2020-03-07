/*
Copyright (c) 2015, Advanced Micro Devices, Inc. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef REEDSOLOMON_REPAIR_CUBE_HH_
#define REEDSOLOMON_REPAIR_CUBE_HH_

#include "RepairScheme.hh"

class ReedSolomonRepair_cube : public RepairScheme
{
public:
	// need to know how wide the devices are to determine which bits fall into one codeword
	// across all the chips
	// ReedSolomon repair module is also configurable by symbol size as 4 bit, 8 bit, 16 bit, and 32 bit, 32 bit is only available for block size of 512 bits
	ReedSolomonRepair_cube( string name, int n_correctable,int n_detectable, uint64_t data_block_bits, uint8_t symbol_size_bits );
	uint64_t fill_repl ( FaultDomain *fd );
	void repair( FaultDomain *fd, uint64_t &n_undetectable, uint64_t &n_uncorrectable);

	void printStats( void );
	void resetStats( void );
	void clear_counters ( void );

private:
	uint64_t m_n_correctable, m_n_detectable, m_bitwidth, m_log_block_bits, m_log_symbol_bits;
	uint64_t counter_prev, counter_now;
};


#endif /* REEDSOLOMONREPAIR_CUBE_HH_ */
