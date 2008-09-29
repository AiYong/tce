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
 * @file InputOperandDialog.cc
 *
 * Definition of InputOperandDialog class.
 *
 * @author Jussi Nyk�nen 2004 (nykanen-no.spam-cs.tut.fi)
 * @note rating: red.
 */

#include <wx/valgen.h>
#include <string>
#include <boost/format.hpp>
#include <vector>

#include "InputOperandDialog.hh"
#include "WxConversion.hh"
#include "Conversion.hh"
#include "WidgetTools.hh"
#include "ObjectState.hh"
#include "OSEdConstants.hh"
#include "GUITextGenerator.hh"
#include "OSEdTextGenerator.hh"
#include "DialogPosition.hh"
#include "Operand.hh"

using std::set;
using std::string;
using boost::format;
using std::vector;

BEGIN_EVENT_TABLE(InputOperandDialog, wxDialog)
    EVT_LIST_ITEM_SELECTED(ID_SWAP_LIST, InputOperandDialog::onSelection)
    EVT_LIST_ITEM_DESELECTED(ID_SWAP_LIST, InputOperandDialog::onSelection)
    
    EVT_BUTTON(ID_ADD_BUTTON, InputOperandDialog::onAddSwap)
    EVT_BUTTON(ID_DELETE_BUTTON, InputOperandDialog::onDeleteSwap)
    EVT_BUTTON(wxID_OK, InputOperandDialog::onOk)

END_EVENT_TABLE()

/**
 * Constructor.
 *
 * @param parent The parent window.
 * @param operand Operand to be added or modified.
 * @param numberOfOperands The number of input operands.
 */
InputOperandDialog::InputOperandDialog(
    wxWindow* parent,
    Operand* operand,
    int numberOfOperands,
    int operandIndex) :
    wxDialog(parent, -1, _T(""), 
             DialogPosition::getPosition(DialogPosition::DIALOG_INPUT_OPERAND)),
    operand_(operand), numberOfOperands_(numberOfOperands), 
    index_(operandIndex) {

    memAddress_ = operand_->isAddress();
    memData_ = operand_->isMemoryData();
    createContents(this, true, true);

    swapList_ = dynamic_cast<wxListCtrl*>(FindWindow(ID_SWAP_LIST));
    swapChoice_ = dynamic_cast<wxChoice*>(FindWindow(ID_OPERAND_CHOICE));

    inputTypesComboBox_ =
        dynamic_cast<wxChoice*>(FindWindow(ID_OPERATION_INPUT_TYPES));
    
    FindWindow(ID_MEM_ADDRESS)->SetValidator(wxGenericValidator(&memAddress_));
    FindWindow(ID_MEM_DATA)->SetValidator(wxGenericValidator(&memData_));

    FindWindow(wxID_OK)->SetFocus();

    canSwap_ = operand_->swap();

    inputTypes_.push_back(Operand::SINT_WORD_STRING);
    inputTypes_.push_back(Operand::UINT_WORD_STRING);
    inputTypes_.push_back(Operand::FLOAT_WORD_STRING);
    inputTypes_.push_back(Operand::DOUBLE_WORD_STRING);

    operandTypes_[0] = Operand::SINT_WORD;
    operandTypes_[1] = Operand::UINT_WORD;
    operandTypes_[2] = Operand::FLOAT_WORD;;
    operandTypes_[3] = Operand::DOUBLE_WORD;

    updateTypes();

    setTexts();
}

/**
 * Destructor.
 */
InputOperandDialog::~InputOperandDialog() {
    int x, y;
    GetPosition(&x, &y);
    wxPoint point(x, y);
    DialogPosition::setPosition(DialogPosition::DIALOG_INPUT_OPERAND, point);
}

/**
 * Set texts to widgets.
 */
void
InputOperandDialog::setTexts() {
	
    GUITextGenerator& guiText = *GUITextGenerator::instance();
    OSEdTextGenerator& osedText = OSEdTextGenerator::instance();
	
    // title
    format fmt = 
        osedText.text(OSEdTextGenerator::TXT_INPUT_OPERAND_DIALOG_TITLE);
    fmt % index_;
    SetTitle(WxConversion::toWxString(fmt.str()));

    // buttons
    WidgetTools::setLabel(&guiText, FindWindow(wxID_OK),
                          GUITextGenerator::TXT_BUTTON_OK);

    WidgetTools::setLabel(&guiText, FindWindow(wxID_CANCEL),
                          GUITextGenerator::TXT_BUTTON_CANCEL);

    WidgetTools::setLabel(&guiText, FindWindow(ID_ADD_BUTTON),
                          GUITextGenerator::TXT_BUTTON_ADD);

    WidgetTools::setLabel(&guiText, FindWindow(ID_DELETE_BUTTON),
                          GUITextGenerator::TXT_BUTTON_DELETE);

    // column names
    fmt = osedText.text(OSEdTextGenerator::TXT_COLUMN_OPERAND);
    swapList_->InsertColumn(
        0, WxConversion::toWxString(fmt.str()), wxLIST_FORMAT_LEFT,
        OSEdConstants::DEFAULT_COLUMN_WIDTH);

    // check boxes
    WidgetTools::setLabel(&osedText, FindWindow(ID_MEM_DATA),
                          OSEdTextGenerator::TXT_CHECKBOX_MEM_DATA);

    WidgetTools::setLabel(&osedText, FindWindow(ID_MEM_ADDRESS),
                          OSEdTextGenerator::TXT_CHECKBOX_MEM_ADDRESS);

    // sizer
    fmt = osedText.text(OSEdTextGenerator::TXT_BOX_CAN_SWAP);
    WidgetTools::setWidgetLabel(swapSizer_, fmt.str());
}

/**
 * Updates the type lists.
 */
void
InputOperandDialog::updateTypes() {

    inputTypesComboBox_->Clear();
    
    for (unsigned int i = 0; i < inputTypes_.size(); i++) {
        wxString oper = WxConversion::toWxString(inputTypes_.at(i));
        inputTypesComboBox_->Append(oper);
    }
	
    inputTypesComboBox_->SetSelection(0);
}

/**
 * Transfers data to window.
 *
 * @return True if transfer is successful.
 */
bool
InputOperandDialog::TransferDataToWindow() {
    updateList();
    return wxWindow::TransferDataToWindow();
}

/**
 * Updates the list of can swap operands.
 */
void
InputOperandDialog::updateList() {

    swapList_->DeleteAllItems();
    swapChoice_->Clear();

    set<int>::iterator it = canSwap_.begin();
    int i = 0;
    while (it != canSwap_.end()) {
        wxString id = WxConversion::toWxString(*it);
        swapList_->InsertItem(i, id);
        i++;
        it++;
    }
	
    for (int i = 1; i <= numberOfOperands_; i++) {
        if (i != index_ && 
            swapList_->FindItem(-1, WxConversion::toWxString(i)) == -1) {
            
            swapChoice_->Append(WxConversion::toWxString(i));
        }
    }
    swapChoice_->SetSelection(0);
    if (swapChoice_->GetCount() == 0) {
        FindWindow(ID_ADD_BUTTON)->Disable();
    } else {
        FindWindow(ID_ADD_BUTTON)->Enable();
    }
    wxListEvent dummy;
    onSelection(dummy);
}

/**
 * Handles the event when id is added to can swap list.
 */
void
InputOperandDialog::onAddSwap(wxCommandEvent&) {
    wxString wxId = swapChoice_->GetStringSelection();
    string id = WxConversion::toString(wxId);
    canSwap_.insert(Conversion::toInt(id));
    updateList();
}

/**
 * Handles the event when id is deleted from can swap list.
 *
 * It is also possible to delete multible ids from the list.
 */
void
InputOperandDialog::onDeleteSwap(wxCommandEvent&) {

    vector<string> toBeDeleted;
    long item = -1;
    for (;;) {
        item = swapList_->GetNextItem(
            item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    
        if (item == -1) {
            break;
        }
        
        wxListItem info;
        info.SetId(item);
        info.SetColumn(0);
        swapList_->GetItem(info);
        toBeDeleted.push_back(WxConversion::toString(info.GetText()));
    }

    for (size_t i = 0; i < toBeDeleted.size(); i++) {
        int id = Conversion::toInt(toBeDeleted[i]);
        set<int>::iterator it = canSwap_.begin();
        while (it != canSwap_.end()) {
            if (*it == id) {
                canSwap_.erase(it);
                break;
            }
            it++;
        }
    }

    updateList();
}

/**
 * Handles the event when OK button is pushed.
 */
void
InputOperandDialog::onOk(wxCommandEvent&) {
    TransferDataFromWindow();
    updateOperand();
    EndModal(wxID_OK);
}

/**
 * Loads the properties to the modified/created operand.
 */
void
InputOperandDialog::updateOperand() {
    ObjectState* root = new ObjectState("");
    root->setAttribute(Operand::OPRND_ID, numberOfOperands_ + 1);
    
    
    int selected = inputTypesComboBox_->GetSelection();
    Operand::OperandType type = operandTypes_[selected];
    

    switch(type) {
        case Operand::SINT_WORD:
            root->setAttribute(Operand::OPRND_TYPE, Operand::SINT_WORD_STRING);
            break;
        case Operand::UINT_WORD:
            root->setAttribute(Operand::OPRND_TYPE, Operand::UINT_WORD_STRING);
            break;
        case Operand::FLOAT_WORD:
            root->setAttribute(Operand::OPRND_TYPE, Operand::FLOAT_WORD_STRING);
            break;
        case Operand::DOUBLE_WORD:
            root->setAttribute(Operand::OPRND_TYPE, Operand::DOUBLE_WORD_STRING);
            break;
        default:
            root->setAttribute(Operand::OPRND_TYPE, Operand::SINT_WORD_STRING);
            break;
    }
    
    root->setAttribute(Operand::OPRND_MEM_ADDRESS, memAddress_);
    root->setAttribute(Operand::OPRND_MEM_DATA, memData_);
    
    if (canSwap_.size() > 0) {
        ObjectState* swap = new ObjectState(Operand::OPRND_CAN_SWAP);
        set<int>::iterator it = canSwap_.begin();
        while (it != canSwap_.end()) {
            ObjectState* swapChild = new ObjectState(Operand::OPRND_IN);
            swapChild->setAttribute(Operand::OPRND_ID, *it);
            swap->addChild(swapChild);
            it++;
        }
        root->addChild(swap);
    }
    
    operand_->loadState(root);
    delete root;
}

/**
 *
 */
void
InputOperandDialog::onSelection(wxListEvent&) {
    if (swapList_->GetSelectedItemCount() == 0) {
        FindWindow(ID_DELETE_BUTTON)->Disable();
    } else {
        FindWindow(ID_DELETE_BUTTON)->Enable();
    }
}

/**
 * Creates the contents of dialog.
 *
 * NOTE! This function is generated by wxDesigner, that is why it is ugly.
 *
 * @param parent The parent window.
 * @param call_fir If true, fits the contents of the dialog inside dialog.
 * @param set_sizer If true, sets the main sizer as the contents of the dialog.
 * @return The created sizer.
 */
wxSizer*
InputOperandDialog::createContents(wxWindow *parent, bool call_fit, bool set_sizer)
{
    wxBoxSizer *item0 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *item1 = new wxBoxSizer(wxHORIZONTAL);

    wxString strs9[] = {
            wxT("id: 1")
    };


    // ComboBox for input operand types
    wxChoice *itemInputTypes = new wxChoice(parent, ID_OPERATION_INPUT_TYPES, wxDefaultPosition, wxSize(100,-1), 1, strs9);
    item1->Add(itemInputTypes, 0, wxALIGN_CENTER|wxALL, 5);

    wxCheckBox *item2 = new wxCheckBox(parent, ID_MEM_ADDRESS, wxT("Memory address"), wxDefaultPosition, wxDefaultSize, 0);
    item1->Add(item2, 0, wxALIGN_CENTER|wxALL, 5);

    wxCheckBox *item3 = new wxCheckBox(parent, ID_MEM_DATA, wxT("Memory data"), wxDefaultPosition, wxDefaultSize, 0);
    item1->Add(item3, 0, wxALIGN_CENTER|wxALL, 5);

    item0->Add(item1, 0, wxALIGN_CENTER|wxALL, 5);

    wxStaticBox *item5 = new wxStaticBox(parent, -1, wxT("Can swap"));
    wxStaticBoxSizer *item4 = new wxStaticBoxSizer(item5, wxVERTICAL);
    swapSizer_ = item4;

    wxListCtrl *item6 = new wxListCtrl(parent, ID_SWAP_LIST, wxDefaultPosition, wxSize(160,120), wxLC_REPORT|wxSUNKEN_BORDER);
    item4->Add(item6, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer *item7 = new wxBoxSizer(wxHORIZONTAL);
    
    wxChoice *item8 = new wxChoice(parent, ID_OPERAND_CHOICE, wxDefaultPosition, wxSize(100,-1), 1, strs9, 0);
    item7->Add(item8, 0, wxALIGN_CENTER|wxALL, 5);

    wxButton *item9 = new wxButton(parent, ID_ADD_BUTTON, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    item7->Add(item9, 0, wxALIGN_CENTER|wxALL, 5);

    wxButton *item10 = new wxButton(parent, ID_DELETE_BUTTON, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0);
    item7->Add(item10, 0, wxALIGN_CENTER|wxALL, 5);

    item4->Add(item7, 0, wxALIGN_CENTER|wxALL, 5);

    item0->Add(item4, 0, wxALIGN_CENTER|wxALL, 5);

    wxGridSizer *item11 = new wxGridSizer(2, 0, 0);

    item11->Add(20, 20, 0, wxALIGN_CENTER|wxALL, 5);

    wxBoxSizer *item12 = new wxBoxSizer(wxHORIZONTAL);

    wxButton *item13 = new wxButton(parent, wxID_OK, wxT("&OK"), wxDefaultPosition, wxDefaultSize, 0);
    item12->Add(item13, 0, wxALIGN_CENTER|wxALL, 5);

    wxButton *item14 = new wxButton(parent, wxID_CANCEL, wxT("&Cancel"), wxDefaultPosition, wxDefaultSize, 0);
    item12->Add(item14, 0, wxALIGN_CENTER|wxALL, 5);

    item11->Add(item12, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    item0->Add(item11, 0, wxALIGN_CENTER|wxALL, 5);

    if (set_sizer) {
        parent->SetSizer(item0);
        if (call_fit)
            item0->SetSizeHints(parent);
    }
    
    return item0;
}
