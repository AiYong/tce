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
 * @file FUExternalPort.hh
 *
 * Declaration of FUExternalPort class.
 *
 * @author Lasse Laasonen 2005 (lasse.laasonen-no.spam-tut.fi)
 * @note rating: red
 */

#ifndef TTA_FU_EXTERNAL_PORT_HH
#define TTA_FU_EXTERNAL_PORT_HH

#include <string>
#include <vector>

#include "HDBTypes.hh"
#include "Exception.hh"

namespace HDB {

class FUImplementation;

/**
 * Represents a non-architectural port of an FU implementation in HDB.
 */
class FUExternalPort {
public:
    FUExternalPort(
        const std::string& name,
        Direction direction,
        const std::string& widthFormula,
        const std::string& description,
        FUImplementation& parent);
    virtual ~FUExternalPort();

    void setName(const std::string& name);
    std::string name() const;
    void setDirection(Direction direction);
    Direction direction() const;
    void setWidthFormula(const std::string& widthFormula);
    std::string widthFormula() const;
    void setDescription(const std::string& description);
    std::string description() const;
    
    bool setParameterDependency(const std::string& parameter);
    bool unsetParameterDependency(const std::string& parameter);
    int parameterDependencyCount() const;
    std::string parameterDependency(int index) const
        throw (OutOfRange);

private:
    /// Typedef for string vector.
    typedef std::vector<std::string> ParameterTable;

    /// Name of the port.
    std::string name_;
    /// Direction of the port.
    Direction direction_;
    /// The formula for the width of the port.
    std::string widthFormula_;
    /// Description of the port.
    std::string description_;
    ParameterTable parameterDeps_;
};
}

#endif
