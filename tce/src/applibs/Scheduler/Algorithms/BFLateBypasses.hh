/*
    Copyright (c) 2002-2014 Tampere University.

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
 * @file BFLateBypasses.hh
 *
 * Declaration of BFLateBypasses class
 *
 * Before scheduling a result move, searches for moves which might be a
 * bypass destinations for this result and then tries to call BFLateBypass
 * class to bypass these.
 *
 * @author Heikki Kultala 2014-2020(heikki.kultala-no.spam-tuni.fi)
 * @note rating: red
 */

#include "BFOptimization.hh"

class MoveNode;
class DataDependenceGraph;
class ResourceManager;

class BFLateBypasses : public BFOptimization {
public:
    BFLateBypasses(BF2Scheduler& sched, MoveNode& src, int lc);

    virtual bool operator()();
    bool removedSource() { return removedSource_;}
private:
    MoveNode& src_;
    int lc_;
    bool removedSource_;
    int bypassDistance_;
};
