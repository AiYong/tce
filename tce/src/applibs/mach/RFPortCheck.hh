/*
    Copyright (c) 2002-2009 Tampere University.

    This file is part of TTA-Based Codesign Environment (TCE).

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
 */
/**
 * @file RFPortCheck.hh
 *
 * Declaration of RFPortCheck class.
 *
 * @author Pekka Jääskeläinen 2008 (pekka.jaaskelainen-no.spam-tut.fi)
 * @note rating: red
 */

#ifndef RF_PORT_CHECK_HH
#define RF_PORT_CHECK_HH

#include "MachineCheck.hh"

/**
 * Checks that the ports of the register files are sensible.
 *
 * Currently checks only that there is at least one input port in the
 * register file.
 */
class RFPortCheck : public MachineCheck {
public:
    RFPortCheck();
    virtual ~RFPortCheck();

    virtual bool check(
        const TTAMachine::Machine& mach,
        MachineCheckResults& results) const;
};

#endif
