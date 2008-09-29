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
 * @file OSEdTextGenerator.cc
 *
 * Definition of OSEdTextGenerator class.
 *
 * @author Jussi Nyk�nen 2004 (nykanen-no.spam-cs.tut.fi)
 * @note rating: red
 */

#include "OSEdTextGenerator.hh"

OSEdTextGenerator* OSEdTextGenerator::instance_ = NULL;

/**
 * Constructor.
 */
OSEdTextGenerator::OSEdTextGenerator() {

    addText(TXT_LABEL_OPERATION_NAME, "Name:");
    addText(TXT_LABEL_MODULE_NAME, "Name of the module:");
    addText(TXT_LABEL_HAS_BEHAVIOR, "Operation behavior module defined.");
    addText(TXT_LABEL_NO_BEHAVIOR, "Operation behavior module not defined.");
    addText(TXT_LABEL_READY, "Ready");
    addText(TXT_LABEL_UPDATE, "Update");
    addText(TXT_LABEL_EDITOR, "Source code editor:");
    addText(TXT_LABEL_FORMAT, "Format:");
    addText(TXT_LABEL_CLOCK, "Clock count:");
    addText(TXT_LABEL_PC, "Program counter:");
    addText(TXT_LABEL_RA, "Return address:");
    addText(TXT_LABEL_SYS_CALL_HANDLER, "System call handler:");
    addText(TXT_LABEL_SYS_CALL_NUMBER, "System call number:");
    addText(TXT_LABEL_MODE, "Mode:");
    addText(TXT_LABEL_END, "End point:");
    addText(TXT_LABEL_START, "Start point:");

    addText(TXT_BUTTON_MODIFY, "Modify...");
    addText(TXT_BUTTON_OPEN, "Open");
    addText(TXT_BUTTON_TRIGGER, "Trigger");
    addText(TXT_BUTTON_ADVANCE_LOCK, "Advance Clock");
    addText(TXT_BUTTON_SAVE, "Save");
    addText(TXT_BUTTON_UNDO, "Undo");
    addText(TXT_BUTTON_DELETE, "Delete");
    addText(TXT_BUTTON_NEW, "New");
    addText(TXT_BUTTON_BROWSE, "Browse");
    addText(TXT_BUTTON_RESET, "Reset");
    addText(TXT_BUTTON_CLOSE, "Close");
    addText(TXT_BUTTON_SHOW_REGISTERS, "Show registers");
    addText(TXT_BUTTON_HIDE_REGISTERS, "Hide registers");
	addText(TXT_BUTTON_UPDATE, "Update");

    addText(TXT_CHECKBOX_READS_MEMORY, "Reads memory");
    addText(TXT_CHECKBOX_WRITES_MEMORY, "Writes memory");
    addText(TXT_CHECKBOX_CAN_TRAP, "Can trap");
    addText(TXT_CHECKBOX_HAS_SIDE_EFFECTS, "Has side effects");
    addText(TXT_CHECKBOX_CLOCKED, "Clocked");
    addText(TXT_CHECKBOX_MEM_DATA, "Memory data");
    addText(TXT_CHECKBOX_MEM_ADDRESS, "Memory address");

    addText(TXT_COLUMN_OPERATION, "operation");
    addText(TXT_COLUMN_OPERAND, "operand");
    addText(TXT_COLUMN_TYPE, "type");
    addText(TXT_COLUMN_VALUE, "value");
    addText(TXT_COLUMN_SEARCH_PATHS, "search paths");
    addText(TXT_COLUMN_MODULES, "modules");
    addText(TXT_COLUMN_OPERATIONS, "operations");
    addText(TXT_COLUMN_PROPERTY, "property");
    addText(TXT_COLUMN_OPERAND_VALUE, "operand value");

    addText(TXT_PROPERTY_DIALOG_TITLE, "Operation properties");
    addText(TXT_INPUT_OPERAND_DIALOG_TITLE, "Input operand properties: id %i");
    addText(TXT_OUTPUT_OPERAND_DIALOG_TITLE, "Output operand properties: id %i");
    addText(TXT_ADD_MODULE_DIALOG_TITLE, "Add module");
    addText(TXT_SIMULATE_DIALOG_TITLE, "Simulate Operation Behavior: %s");
    addText(TXT_OPTIONS_DIALOG_TITLE, "Options");
    addText(TXT_BUILD_RESULT_DIALOG_TITLE, "Build results");
    addText(TXT_USER_MANUAL_TITLE, "User manual");
    addText(TXT_XML_RESULT_DIALOG_TITLE, "Bad modules");
    addText(TXT_ABOUT_DIALOG_TITLE, "About Operation Set Editor");
    addText(TXT_SIMULATION_INFO_DIALOG_TITLE, "Simulation information");
	addText(TXT_MEMORY_DIALOG_TITLE, "Memory");

    addText(TXT_BOX_AFFECTS, "Affects");
    addText(TXT_BOX_AFFECTED_BY, "Affected by");
    addText(TXT_BOX_INPUT_OPERANDS, "Operation inputs");
    addText(TXT_BOX_OUTPUT_OPERANDS, "Operation outputs");
    addText(TXT_BOX_CAN_SWAP, "Can swap");
    addText(TXT_BOX_INPUT_VALUES, "Input values");
    addText(TXT_BOX_OUTPUT_VALUES, "Output values");

    addText(TXT_ERROR_NO_NAME, "No name given to %s.");
    addText(TXT_ERROR_CAN_NOT_MODIFY, "Operation cannot be modified.");
    addText(TXT_ERROR_CAN_NOT_CREATE_MOD, "Module cannot be created.");
    addText(TXT_ERROR_CAN_NOT_CREATE_OP, "Operation cannot be created.");
    addText(TXT_ERROR_NO_EDITOR, "Editor not set");
    addText(TXT_ERROR_OPEN, "Can not open editor %s");
    addText(TXT_ERROR_CAN_NOT_SAVE, "Can not save options");
    addText(TXT_ERROR_NON_EXISTING_OPERATION, "Operation %s does not exist");
    addText(TXT_ERROR_TRIGGER_FAILED, "Result could not be compiled");
    addText(TXT_ERROR_CAN_NOT_REMOVE_OPERATION, 
            "Operation %s can not be removed");
    
    addText(TXT_ERROR_MODULE_EXISTS, "Module %s already exists.");
    addText(TXT_ERROR_OPERATION_EXISTS, "Operation %s already exists.");
    addText(TXT_ERROR_NO_HANDLER, "No handler found for the command event");
    addText(TXT_ERROR_MOD_NAME, "Module name %s is erronous");
  
    addText(TXT_MSG_BUILD_OK, "Build successful");

    addText(TXT_ABOUT, "Operation Set Editor");

    addText(TXT_MENU_OPTIONS, "&Options");
    addText(TXT_MENU_QUIT, "&Quit");
    addText(TXT_MENU_FILE, "&File");
    addText(TXT_MENU_ADD_OPERATION, "Add &operation");
    addText(TXT_MENU_REMOVE_OPERATION, "R&emove operation");
    addText(TXT_MENU_ADD_MODULE, "Add &module");
    addText(TXT_MENU_MODIFY_PROPERTIES, "Modify &properties");
    addText(TXT_MENU_BUILD, "&Build");
    addText(TXT_MENU_BUILD_ALL, "Build &all");
    addText(TXT_MENU_SIMULATE, "&Simulate");
    addText(TXT_MENU_TOOLS, "&Tools");
    addText(TXT_MENU_ABOUT, "&About...");
    addText(TXT_MENU_USER_MANUAL, "&User manual...");
    addText(TXT_MENU_HELP, "&Help");
    addText(TXT_MENU_REMOVE_MODULE, "&Remove module");
    addText(TXT_MENU_MODIFY_BEHAVIOR, "Modify &behavior");
    addText(TXT_MENU_MEMORY, "Memo&ry");

    addText(TXT_ROW_NAME, "name");
    addText(TXT_ROW_DESCRIPTION, "description");
    addText(TXT_ROW_INPUTS, "inputs");
    addText(TXT_ROW_OUTPUTS, "outputs");
    addText(TXT_ROW_READS_MEMORY, "reads memory");
    addText(TXT_ROW_WRITES_MEMORY, "writes memory");
    addText(TXT_ROW_TRUE, "true");
    addText(TXT_ROW_FALSE, "false");
    addText(TXT_ROW_CAN_TRAP, "can trap");
    addText(TXT_ROW_HAS_SIDE_EFFECTS, "has side effects");
    addText(TXT_ROW_CLOCKED, "clocked");
    addText(TXT_ROW_AFFECTED_BY, "affected by");
    addText(TXT_ROW_AFFECTS, "affects");
    addText(TXT_ROW_INPUT_OPERANDS, "input operands");
    addText(TXT_ROW_OUTPUT_OPERANDS, "output operands");
    addText(TXT_ROW_ID, "id: ");
    addText(TXT_ROW_YES, "yes");
    addText(TXT_ROW_NO, "no");
    addText(TXT_ROW_TYPE, "type");
    addText(TXT_ROW_MEMORY_ADDRESS, "memory address");
    addText(TXT_ROW_CAN_SWAP, "can swap");
    addText(TXT_ROW_MEMORY_DATA, "memory data");
    addText(TXT_ROW_HAS_BEHAVIOR, "has behavior");

    addText(
        TXT_QUESTION_REMOVE_MODULE, 
        "Are you sure you want to remove module %s?");

    addText(
        TXT_QUESTION_REMOVE_BEHAVIOR_FILE,
        "Are you sure you want to remove behavior file %s?");

    addText(
        TXT_QUESTION_SAVE_PROPERTIES, 
        "Operation properties modified. Save properties?");

    addText(
        TXT_QUESTION_REMOVE_OPERATION, 
        "Are you sure you want to remove operation %s?");

    addText(TXT_STATUS_PATH_SELECTED, "Path selected");
    addText(TXT_STATUS_MODULE_SELECTED, "Module selected");
    addText(TXT_STATUS_OPERATION_SELECTED, "Operation selected");
    addText(TXT_STATUS_COMPILING, "Compiling %s...");
    addText(TXT_STATUS_COMPILE_SUCCESS, "Compilation successful. It took %i ms");
    addText(TXT_STATUS_COMPILE_FAILED, "Compilation failed.");
}

/**
 * Destructor.
 */
OSEdTextGenerator::~OSEdTextGenerator() {
}

/**
 * Returns an instance of text generator.
 *
 * @return Instance of text generator.
 */
OSEdTextGenerator&
OSEdTextGenerator::instance() {
    if (instance_ == NULL) {
        instance_ = new OSEdTextGenerator();
    }
    return *instance_;
}

/**
 * Destroys the only instance of text generator.
 */
void
OSEdTextGenerator::destroy() {
    if (instance_ != NULL) {
        delete instance_;
        instance_ = NULL;
    }
}

