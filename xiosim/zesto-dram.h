#ifndef ZESTO_DRAM_INCLUDED
#define ZESTO_DRAM_INCLUDED

/* zesto-dram.h - Zesto main memory/DRAM class
 * 
 * Copyright � 2009 by Gabriel H. Loh and the Georgia Tech Research Corporation
 * Atlanta, GA  30332-0415
 * All Rights Reserved.
 * 
 * THIS IS A LEGAL DOCUMENT BY DOWNLOADING ZESTO, YOU ARE AGREEING TO THESE
 * TERMS AND CONDITIONS.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the Georgia Tech Research Corporation nor the names of
 * its contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * 4. Zesto is distributed freely for commercial and non-commercial use.
 * 
 * 5. No nonprofit user may place any restrictions on the use of this software,
 * including as modified by the user, by any other authorized user.
 * 
 * 6. Noncommercial and nonprofit users may distribute copies of Zesto in
 * compiled or executable form as set forth in Section 2, provided that either:
 * (A) it is accompanied by the corresponding machine-readable source code, or
 * (B) it is accompanied by a written offer, with no time limit, to give anyone
 * a machine-readable copy of the corresponding source code in return for
 * reimbursement of the cost of distribution. This written offer must permit
 * verbatim duplication by anyone, or (C) it is distributed by someone who
 * received only the executable form, and is accompanied by a copy of the
 * written offer of source code.
 * 
 * 7. Zesto was developed by Gabriel H. Loh, Ph.D.  US Mail: 266 Ferst Drive,
 * Georgia Institute of Technology, Atlanta, GA 30332-0765
 */

#include <assert.h>
#include "zesto-cache.h"

extern class dram_t * dram;

void dram_create(void);

class dram_t
{
  protected:
  counter_t total_accesses;
  counter_t total_latency;
  int       best_latency;
  int       worst_latency;
  counter_t total_burst;

  void init(void);

  public:
  dram_t(void);
  virtual ~dram_t(void);
  virtual unsigned int access(const enum cache_command cmd, const md_paddr_t baddr, const int bsize) = 0;
  virtual void refresh(void);
  virtual void reg_stats(xiosim::stats::StatsDatabase* sdb);
};

#ifdef DEBUG
#define dram_fatal(msg, retval) fatal(msg)
#else
#define dram_fatal(msg, retval) { \
  fprintf(stderr,"fatal (%s,%d:DRAM): ",__FILE__,__LINE__); \
  fprintf(stderr,"%s\n",msg); \
  return (retval); \
}
#endif

#ifndef dram_assert
#ifdef DEBUG
#define dram_assert(cond, retval) assert(cond)
#else
#define dram_assert(cond, retval) { \
  if(!(cond)) { \
    fprintf(stderr,"fatal (%s,%d:DRAM): ",__FILE__,__LINE__); \
    fprintf(stderr,"%s\n",#cond); \
    return (retval); \
  } \
}
#endif
#endif

#endif /* ZESTO_DRAM_INCLUDED */
