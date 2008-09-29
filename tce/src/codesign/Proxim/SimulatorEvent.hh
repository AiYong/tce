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
 * @file SimulatorEvent.hh
 *
 * Declaration of SimulatorEvent class.
 *
 * @author Veli-Pekka Jääskeläinen 2005 (vjaaskel-no.spam-cs.tut.fi)
 * @note rating: red
 */

#ifndef TTA_SIMULATOR_EVENT_HH
#define TTA_SIMULATOR_EVENT_HH

#include <string>
#include <wx/wx.h>

/**
 * A custom wxEvent class for passing simulator events to Proxim windows.
 */
class SimulatorEvent : public wxEvent {
public:
    SimulatorEvent(WXTYPE eventType, std::string data = "");
    virtual ~SimulatorEvent();
    virtual wxEvent* Clone(void) const { return new SimulatorEvent(*this); }
    std::string data() const;


    // Simulator event type IDs:
    // -------------------------
    /// Command received from the GUI.
    static const wxEventType EVT_SIMULATOR_COMMAND;
    /// Command execution completed.
    static const wxEventType EVT_SIMULATOR_COMMAND_DONE;
    /// Simulator thread terminated.
    static const wxEventType EVT_SIMULATOR_TERMINATED;

    /// Textual output event from simulator interpreter.
    static const wxEventType EVT_SIMULATOR_OUTPUT;
    /// Simulator error event.
    static const wxEventType EVT_SIMULATOR_ERROR;
    /// Runtime error event.
    static const wxEventType EVT_SIMULATOR_RUNTIME_ERROR;
    /// Runtime warning event.
    static const wxEventType EVT_SIMULATOR_RUNTIME_WARNING;

    /// Simulation started.
    static const wxEventType EVT_SIMULATOR_START;
    /// Simulation stopped.
    static const wxEventType EVT_SIMULATOR_STOP;
    /// Simulation ran/resumed.
    static const wxEventType EVT_SIMULATOR_RUN;


    /// Machine loading started.
    static const wxEventType EVT_SIMULATOR_LOADING_MACHINE;
    /// Machine loaded event.
    static const wxEventType EVT_SIMULATOR_MACHINE_LOADED;
    /// Program loading started.
    static const wxEventType EVT_SIMULATOR_LOADING_PROGRAM;
    /// Program loaded event.
    static const wxEventType EVT_SIMULATOR_PROGRAM_LOADED;
    /// Sent before program,machine or memory model is destroyed.
    static const wxEventType EVT_SIMULATOR_RESET;
    // -------------------------

private:
    std::string data_;
};


// Macro for setting up event handler for simulation thread termination.
#define EVT_SIMULATOR_TERMINATED(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(SimulatorEvent::EVT_SIMULATOR_TERMINATED, id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

// Macro for setting up event handler for simulation start.
#define EVT_SIMULATOR_START(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(SimulatorEvent::EVT_SIMULATOR_START, id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

// Macro for setting up event handler simulation stop.
#define EVT_SIMULATOR_STOP(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(SimulatorEvent::EVT_SIMULATOR_STOP, id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

// Macro for setting up event handler for textual output from the
// simulator interpreter.
#define EVT_SIMULATOR_OUTPUT(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(SimulatorEvent::EVT_SIMULATOR_OUTPUT, id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

// Macro for setting up event handler for executed command event
// from the simulator interpreter.
#define EVT_SIMULATOR_COMMAND(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(SimulatorEvent::EVT_SIMULATOR_COMMAND, id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

// Macro for setting up event handler for completed command execution event
// from the simulator interpreter.
#define EVT_SIMULATOR_COMMAND_DONE(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(SimulatorEvent::EVT_SIMULATOR_COMMAND_DONE, \
    id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

// Macro for setting up event handler for simulator error event.
#define EVT_SIMULATOR_ERROR(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(SimulatorEvent::EVT_SIMULATOR_ERROR, id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

#define EVT_SIMULATOR_MACHINE_LOADED(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(SimulatorEvent::EVT_SIMULATOR_MACHINE_LOADED, \
    id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

#define EVT_SIMULATOR_LOADING_PROGRAM(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(SimulatorEvent::EVT_SIMULATOR_LOADING_PROGRAM, \
    id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

#define EVT_SIMULATOR_PROGRAM_LOADED(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(SimulatorEvent::EVT_SIMULATOR_PROGRAM_LOADED, \
    id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

#define EVT_SIMULATOR_LOADING_MACHINE(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(SimulatorEvent::EVT_SIMULATOR_LOADING_MACHINE, \
    id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

#define EVT_SIMULATOR_MACHINE_LOADED(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(SimulatorEvent::EVT_SIMULATOR_MACHINE_LOADED, \
    id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

#define EVT_SIMULATOR_RUNTIME_ERROR(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(\
    SimulatorEvent::EVT_SIMULATOR_RUNTIME_ERROR,	\
    id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

#define EVT_SIMULATOR_RUNTIME_WARNING(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(\
    SimulatorEvent::EVT_SIMULATOR_RUNTIME_WARNING,	\
    id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

#define EVT_SIMULATOR_RUN(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(\
    SimulatorEvent::EVT_SIMULATOR_RUN,	\
    id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

#define EVT_SIMULATOR_RESET(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(\
    SimulatorEvent::EVT_SIMULATOR_RESET,	\
    id, -1, \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
    (wxObject*)NULL ),

#endif
