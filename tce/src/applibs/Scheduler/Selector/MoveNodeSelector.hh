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
 * @file MoveNodeSelector.hh
 *
 * Declaration of MoveNodeSelector interface.
 *
 * @author Pekka Jääskeläinen 2007 (pekka.jaaskelainen-no.spam-tut.fi)
 * @note rating: red
 */

#ifndef TTA_MOVE_NODE_SELECTOR_HH
#define TTA_MOVE_NODE_SELECTOR_HH

#include "HelperSchedulerModule.hh"
#include "MoveNodeGroup.hh"

/**
 * Move node selector is an abstraction to ready operation list in a 
 * list scheduler.
 *
 * MoveNodeSelectors are responsible in maintaining the ready list and updating
 * it according to scheduling progress.
 */
class MoveNodeSelector : public HelperSchedulerModule {
public:
    MoveNodeSelector();
    virtual ~MoveNodeSelector();
    
    virtual MoveNodeGroup candidates() = 0;
    virtual void notifyScheduled(MoveNode& node) = 0;
    virtual void mightBeReady(MoveNode& node) = 0;
};

#endif
