/*
    Copyright 2002-2008 Tampere University of Technology.  All Rights
    Reserved.

    This file is part of TTA-Based Codesign Environment (TCE).

    TCE is free software; you can redistribute it and/or modify it under the
    terms of the GNU General Public License version 2 as published by the Free
    Software Foundation.

    TCE is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
    details.

    You should have received a copy of the GNU General Public License along
    with TCE; if not, write to the Free Software Foundation, Inc., 51 Franklin
    St, Fifth Floor, Boston, MA  02110-1301  USA

    As a special exception, you may use this file as part of a free software
    library without restriction.  Specifically, if other files instantiate
    templates or use macros or inline functions from this file, or you compile
    this file and link it with other files to produce an executable, this
    file does not by itself cause the resulting executable to be covered by
    the GNU General Public License.  This exception does not however
    invalidate any other reasons why the executable file might be covered by
    the GNU General Public License.
*/
/**
 * @file RegisterQuantityCheck.hh
 * 
 * Declaration of RegisterQuantityCheck class.
 * 
 * Tests that given machine has enough registers.
 *
 * @author Heikki Kultala (hkultala-no.spam-cs.tut.fi)
 * @note rating: red
 */

#ifndef TTA_REGISTER_QUANTITY_CHECK_HH
#define TTA_REGISTER_QUANTITY_CHECK_HH

#include "MachineCheck.hh"

#include <set>
#include <string>

#include "RegisterFile.hh"

class RegisterQuantityCheck : public MachineCheck {
public:
    RegisterQuantityCheck();
    virtual ~RegisterQuantityCheck();

    virtual bool check(
        const TTAMachine::Machine& mach) const;
    virtual bool check(
        const TTAMachine::Machine& mach, 
        MachineCheckResults& results) const;
    bool checkWithIgnore(
        const TTAMachine::Machine& mach, 
        const std::set<std::string>& ignoreRFs) const;
    bool checkWithIgnore(
        const TTAMachine::Machine& mach, 
        MachineCheckResults& results, 
        const std::set<std::string>& ignoreRFs) const;
private:
    typedef std::pair<TTAMachine::RegisterFile*, int> Register;
    void findGuardRegisters(
        const TTAMachine::Machine& mach, 
        std::set<Register>& registers,
        const std::set<std::string>& ignoreRFs) const;
    unsigned int countIntRegisters(
        const TTAMachine::Machine& mach, 
        const std::set<Register>& registers,
        const std::set<std::string>& ignoreRFs) const;
    bool checkPredRegs(
        const unsigned int& regCount,
        MachineCheckResults* results) const;
    bool checkIntRegs(
        const unsigned int& regCount,
        MachineCheckResults* results) const;
};

#endif
