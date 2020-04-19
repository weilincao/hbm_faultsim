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
#include <iostream>

extern struct Settings settings;

ReedSolomonRepair_cube::ReedSolomonRepair_cube(string name, int n_correctable, int n_detectable, uint64_t data_block_bits, uint8_t symbol_size_bits) : RepairScheme(name) 
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
	list<FaultDomain*>::iterator it0, it1;

	//clear out touched values for each faultrange on each chip
	for(it1 =pChips->begin(); it1 !=pChips->end(); it1++)
	{
		DRAMDomain *pDRAM1 = dynamic_cast<DRAMDomain*>((*it1));
		list<FaultRange*> *pRange3 = pDRAM1->getRanges();
		list<FaultRange*>::iterator itRange3;
		for(itRange3 = pRange3->begin(); itRange3 !=pRange3->end(); itRange3++)
		{
			FaultRange *fr1 =(*itRange3);
			fr1->touched=0;
		}
	}

	// Take each chip in turn.  For every fault range in a chip, see which neighbors intersect it's ECC block(s).
	// Count the failed symbols in each ECC block.
	for( it0 = pChips->begin(); it0 != pChips->end(); it0++ )
	{
		DRAMDomain *pDRAM0 = dynamic_cast<DRAMDomain*>((*it0));
		list<FaultRange*> *pRange0 = pDRAM0->getRanges();

		list<FaultRange*>::iterator itRange0;
		for( itRange0 = pRange0->begin(); itRange0 != pRange0->end(); itRange0++ )
		{
			FaultRange *frOrg = (*itRange0); 						//The pointer to the fault location
			FaultRange frTemp = *(*itRange0); 						//This is a fault location of a chip

			uint32_t n_intersections = 0;
			
			if(frTemp.touched < frTemp.max_faults)
			{
				if( settings.debug ) {
					cout << m_name << ": outer " << frTemp.toString() << "\n";
				}

				bit_shift=m_log_block_bits;						//ECC every 64 byte i.e 512 bit granularity
				frTemp.fAddr = frTemp.fAddr >> bit_shift;                               //clear that block's address range
				frTemp.fAddr = frTemp.fAddr << bit_shift;
				frTemp.fWildMask = frTemp.fWildMask >> bit_shift;                       //clear that mask range as well
				frTemp.fWildMask = frTemp.fWildMask << bit_shift;
				frTemp.fWildMask = frTemp.fWildMask |= ((1 << m_log_symbol_bits) - 1);  //set mask to cover one symbols worth of bits
				loopcount_locations = 1 << (bit_shift - m_log_symbol_bits); 		//This gives me the number of loops for the addresses near the fault range to iterate

				for(ii=0;ii<loopcount_locations;ii++)
				{
					DRAMDomain *pDRAM1 = dynamic_cast<DRAMDomain*>((*it0));
					list<FaultRange*> *pRange1 = pDRAM1->getRanges();
					list<FaultRange*>::iterator itRange1;
					for( itRange1 = pRange1->begin(); itRange1 != pRange1->end(); itRange1++ )
					{
						FaultRange *fr1 = (*itRange1);

						if( settings.debug ) {
							cout << m_name << ": inner " << fr1->toString() << " bit " << ii << "\n";
						}

						if( fr1->touched < fr1->max_faults)
						{
							if(frTemp.intersects(fr1)) {
								if( settings.debug ) cout << m_name << ": INTERSECT " << n_intersections << "\n";

								n_intersections++;

								// There was a failed bit in at least one row of the FaultRange of interest.
								// We now only care about further intersections that are in the overlapping
								// rows of the two ranges.  Narrow down the search to only those rows in common
								// to both FaultRanges.  This is achieved by;
								// 1) Set upper mask bits to zero if they are not wild in range under test
								// 2) For those wild bits that we cleared, use the specific address bit value
								uint64_t fr1_fAddr_upper = (fr1->fAddr >> bit_shift) << bit_shift;
								uint64_t frTemp_fAddr_lower = (frTemp.fAddr & ((0x1 << bit_shift)-1) );

								uint64_t old_wild_mask = frTemp.fWildMask;
								frTemp.fWildMask &= fr1->fWildMask;
								uint64_t changed_wild_bits = old_wild_mask ^ frTemp.fWildMask;
								frTemp.fAddr = (fr1_fAddr_upper & changed_wild_bits) | (frTemp.fAddr & (~changed_wild_bits)) | frTemp_fAddr_lower;

								// immediately move on to the next location
								break;
							} else {
								if( settings.debug ) cout << m_name << ": NONE " << n_intersections << "\n";
							}
						}
					}
					frTemp.fAddr = frTemp.fAddr + m_symbol_size_bits;               //go to the next symbol 
				}

				// For this algorithm, one intersection with the symbol being tested actually means one
				// faulty symbol in the range due to the use of each fault range as a reference
				if(n_intersections <= m_n_correctable)
				{
					// correctable
				}
				if(n_intersections > m_n_correctable)
				{
					n_uncorrectable += (n_intersections - m_n_correctable);
					frOrg->transient_remove = false;
					if( !settings.continue_running ) return;
				}
				if(n_intersections >= m_n_detectable)
				{
					n_undetectable += (n_intersections - m_n_detectable);
				}
			}
		}
	}

}

uint64_t ReedSolomonRepair_cube::fill_repl(FaultDomain *fd)
{
	return 0;
}
void ReedSolomonRepair_cube::printStats( void )
{
	RepairScheme::printStats();
}

void ReedSolomonRepair_cube::clear_counters(void)
{
	counter_prev=0;
	counter_now=0;
}

void ReedSolomonRepair_cube::resetStats( void )
{
	RepairScheme::resetStats();
}
