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
 * @file ProximCDCmd.cc
 *
 * Implementation of ProximCDCmd class.
 *
 * @author Veli-Pekka Jääskeläinen 2005 (vjaaskel-no.spam-cs.tut.fi)
 * @note rating: red
 */

#include "ProximCDCmd.hh"
#include "WxConversion.hh"
#include "ProximConstants.hh"
#include "Proxim.hh"
#include "FileSystem.hh"
#include "ProximSimulationThread.hh"

/**
 * The Constructor.
 */
ProximCDCmd::ProximCDCmd():
    GUICommand("Change Directory", NULL) {

    }

/**
 * The Destructor.
 */
ProximCDCmd::~ProximCDCmd() {
}


/**
 * Executes the command.
 */
bool
ProximCDCmd::Do() {

    assert(parentWindow() != NULL);
    wxDirDialog dialog(parentWindow(), _T("Choose a directory"), wxGetCwd());

    if (dialog.ShowModal() == wxID_CANCEL) {
	return false;
    }

    std::string command = 
        "cd \"" + WxConversion::toString(dialog.GetPath()) + "\"";

    wxGetApp().simulation()->lineReader().input(command);
    return true;
}


/**
 * Returns full path to the command icon file.
 *
 * @return Full path to the command icon file.
 */
std::string
ProximCDCmd::icon() const {
    return "cd.png";
}


/**
 * Returns ID of this command.
 */
int
ProximCDCmd::id() const {
    return ProximConstants::COMMAND_CD;
}


/**
 * Creates and returns a new isntance of this command.
 *
 * @return Newly created instance of this command.
 */
ProximCDCmd*
ProximCDCmd::create() const {
    return new ProximCDCmd();
}


/**
 * Returns true if the command is enabled, false otherwise.
 *
 * @return Always true.
 */
bool
ProximCDCmd::isEnabled() {
    return true;
}
