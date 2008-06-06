/**
 * @file CompiledSimulation.hh
 *
 * Declaration of CompiledSimulation abstract class.
 *
 * @author Viljami Korhonen 2007 (viljami.korhonen@tut.fi)
 * @note This file is used in compiled simulation. Keep dependencies *clean*
 * @note rating: red
 */

#ifndef COMPILED_SIMULATION_HH
#define COMPILED_SIMULATION_HH

#include "SimulatorConstants.hh"
#include "SimValue.hh"
#include "OperationPool.hh"

namespace TTAMachine {
    class Machine;
    class FunctionUnit;
}

namespace TTAProgram {
    class Program;
}

class SimulatorFrontend;
class DirectAccessMemory;
class MemorySystem;
class SimulatorFrontend;
class CompiledSimulationEngine;
class CompiledSimulationPimpl;
class CompiledSimulation;
struct ProcedureBBRelations;


/// Type for the simulateXXXXX basic block functions
typedef void (*SimulateFunction)(CompiledSimulationEngine& engine);

// Used to set export symbols visible
#define EXPORT __attribute__((visibility("default")))


/**
 * A struct that describes a single FU result type
 */
struct FUResultElementType {
    /// time when this result is ready
    ClockCycleCount cycles;
    
    /// FU Result value
    SimValue value;
    
    /// Is this result element used in the array or not
    bool used;
    
    FUResultElementType() : cycles(0), used(false) {}
};

/**
 * A struct for dynamic array containing the FU results
 */
struct FUResultType {
    /// size of the array
    const int size;
    /// array of result elements
    FUResultElementType* data;
    /// Number of active elements in the buffer
    int numberOfElements;
    
    /// A constructor that resets the variables
    FUResultType(int maxLatency) 
        : size(maxLatency), 
          data(new FUResultElementType[size]),
          numberOfElements(0) {}
    /// The destructor. Frees all memory
    ~FUResultType() { delete[] data; data = 0; }
};


/**
 * An abstract class that is used as a base for all the compiled simulations
 * 
 * The derived classes are generated by CompiledSimCodeGenerator and then
 * get loaded as plugins by the CompiledSimController.
 * 
 */
class CompiledSimulation {
public:    
    CompiledSimulation(
        const TTAMachine::Machine& machine,
        InstructionAddress entryAddress,
        InstructionAddress lastInstruction,
        SimulatorFrontend& frontend,
        MemorySystem& memorySystem,
        bool dynamicCompilation,
        ProcedureBBRelations& procedureBBRelations);
    virtual ~CompiledSimulation();
    
    virtual void simulateCycle() = 0;
    virtual void cycleEnd();
    
    virtual void step(double count);
    virtual void next(int count);
    virtual void run();
    virtual void runUntil(UIntWord address);
            
    virtual InstructionAddress programCounter() const;
    virtual InstructionAddress lastExecutedInstruction() const;
    
    virtual ClockCycleCount cycleCount() const;
    
    virtual SimValue registerFileValue(
        const char* rfName, 
        int registerIndex);
    
    virtual SimValue immediateUnitRegisterValue(
        const char* iuName, int index);
    
    virtual SimValue FUPortValue(
        const char* fuName,
        const char* portName);
    
    virtual void requestToStop();
    virtual bool stopRequested() const;
    virtual bool isFinished() const;
    
    
    // Variables are defined public because of external C functions...
    /// Number of cycles simulated so far
    ClockCycleCount cycleCount_;
    /// Number of basic blocks gone through
    int basicBlockCount_;
    /// The jump target. Allows jumping to different addresses in the code
    InstructionAddress jumpTarget_;
    /// The program counter. i.e. which address the simulation is currently at
    InstructionAddress programCounter_;
    /// Last executed instruction
    InstructionAddress lastExecutedInstruction_;    
    /// Number of cycles left to simulate until the execution returns
    ClockCycleCount cyclesToSimulate_;
    /// Should the simulation stop or not?
    bool stopRequested_;  
    /// Is the simulation finished?
    bool isFinished_;
    
    /// The operation pool
    OperationPool operationPool_;
    /// Next jump target as a function pointer" << endl
    SimulateFunction jumpTargetFunc_;

    /// A flag for FU conflict detection
    bool conflictDetected_;
    
    static void inline clearFUResults(
        FUResultType& results);
    
    static void inline addFUResult(
        FUResultType& results,
        ClockCycleCount cycleCount,
        const SimValue& value,
        int latency);
    
    static void inline addFUResult(
        FUResultType& results,
        ClockCycleCount cycleCount,
        const UIntWord& value,
        int latency);
    
    static void inline FUResult(
        SimValue& target,
        FUResultType& results,
        ClockCycleCount cycles);
        
protected:
    TTAMachine::FunctionUnit& functionUnit(const char* name) const;
    
    DirectAccessMemory& FUMemory(const char* FUName) const;
    MemorySystem* memorySystem() const;
    SimulatorFrontend& frontend() const;
    void msg(const char* message) const;
    void haltSimulation(
        const char* file,
        int line,
        const char* procedure,
        const char* message) const;    
    
    void resizeJumpTable(int newSize);
    SimulateFunction getSimulateFunction(InstructionAddress address);
    void setJumpTargetFunction(InstructionAddress address, SimulateFunction fp);
    void compileAndLoadFunction(InstructionAddress address);
    
    SimValue* getSymbolValue(const char* symbolName);
    void addSymbol(const char* symbolName, SimValue& value);

    /// Is this a dynamic compiled simulation?
    bool dynamicCompilation_;
    
    /// A struct for finding out procedure begins from procedure's basic blocks
    ProcedureBBRelations& procedureBBRelations_;

    /// The simulated machine
    const TTAMachine::Machine& machine_;
    
    /// Entry address of the program
    const InstructionAddress entryAddress_;
    /// Last instruction of the program
    const InstructionAddress lastInstruction_;

private:
    /// Copying not allowed.
    CompiledSimulation(const CompiledSimulation&);
    /// Assignment not allowed.
    CompiledSimulation& operator=(const CompiledSimulation&);
    
    /// Private implementation in a separate source file
    CompiledSimulationPimpl* pimpl_;
};


#include "CompiledSimulation.icc"

#endif
