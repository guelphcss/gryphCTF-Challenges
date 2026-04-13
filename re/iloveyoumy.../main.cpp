// Very very very basic VM challenge. Just solve what the VM is trying to do (like a keygen challenge or something to get the flag. VM reference: https://github.com/idkhidden/hiddenvm) 
// To build, run `cmake -B build`, then `cmake --build build`.
// See decomp.png for how this looks like under decompilation. In particular, you can find the VM bytecode in the binary and write a disassembler to easily solve the challenge (see disas.py!)

#include <print>
#include <vector>
#include <iostream>

enum Signals {
    Continue = 1,
    Stop = 0,
    Err = 0
};

enum Registers {
    X1,
    X2,
    X3,
    X4,
    X5,
    X6,
    X7,
    X8,
    X9,
    X10,
    TEST,
    COUNT       // Fake variable, just for allocation
};

enum Opcode {
    Add,    // Add 5, 6 would push 11 to the stack
    Sub,    // Sub 3, 1 would push 2 to the stack
    Div,    // Div 5, 1 would push 5 to the stack
    Mul,    // Mul 2, 2 would push 4 to the stack
    Or,     // Or 1, 0 would push 1 to the stack
    And,    // And 1, 0 would push 0 to the stack
    Xor,    // Xor 1, 1 would push 0 to the stack
    Nand,   // Nand 0, 0 would push 1 to the stack
    Not,    // Not 0 would push 1 to the stack
    Test,   // Test equality between two register values, puts result into TEST register
    Ldr,    // Ldr X6, 10 would load 10 into X6
    Push,   // Push immediate value to stack
    Pop,    // Pop off the stack to a register
    PopA,   // Clear the stack, pops to nowhere
    Print,  // Print supplied REGISTER' VALUE to stdout
    PrintS, // Print a string by walking the stack and printing individual ASCII characters for the supplied length of characters, characters should be pushed to the stack beforehand (Big-endian-ish byte order, first thing pushed is first thing printed)
    Input,  // Get string input from the user, then push individual string characters to the stack
    HaltNE, // Halt if last Test operation did not return true/1
    Halt,   // Exit VM
};

class VM {
    public:
        std::vector<int> stack;
        std::vector<int> bytecode;
        int registers[Registers::COUNT];
        size_t pc = 0;
        VM() {
        }
        void show_stack() {
            std::print("STACK: ");
            for (int n : stack) {
                std::print("{} ", n);
            }
            std::print("\n");
        }
        void execute() {
            bool signal = Signals::Continue;
            while (signal == Signals::Continue && pc < bytecode.size()) {
                int opcode = bytecode[pc++];
                //std::println("Instruction: {}", opcode);
                //show_stack();
                switch (opcode) {
                    case Opcode::Add: {
                        int a = bytecode[pc++];
                        int b = bytecode[pc++];
                        stack.push_back(a+b);
                        break;
                    }
                    case Opcode::Sub: {
                        int a = bytecode[pc++];
                        int b = bytecode[pc++];
                        stack.push_back(a-b);
                        break;
                    }
                    case Opcode::Div: {
                        int a = bytecode[pc++];
                        int b = bytecode[pc++];
                        if (b != 0) {
                            stack.push_back(a/b);
                        } else {
                            std::println("attempted division by zero");
                            signal = Signals::Err;
                        }
                        break;
                    }
                    case Opcode::Mul: {
                        int a = bytecode[pc++];
                        int b = bytecode[pc++];
                        stack.push_back(a*b);
                        break;
                    }
                    case Opcode::Or: {
                        int a = bytecode[pc++];
                        int b = bytecode[pc++];
                        stack.push_back(a | b);
                        break;
                    }
                    case Opcode::And: {
                        int a = bytecode[pc++];
                        int b = bytecode[pc++];
                        stack.push_back(a & b);
                        break;
                    }
                    case Opcode::Xor: {
                        int a = bytecode[pc++];
                        int b = bytecode[pc++];
                        stack.push_back(a ^ b);
                        break;
                    }
                    case Opcode::Nand: {
                        int a = bytecode[pc++];
                        int b = bytecode[pc++];
                        stack.push_back(~(a & b));
                        break;
                    }
                    case Opcode::Not: {
                        int a = bytecode[pc++];
                        stack.push_back(~a);
                        break;
                    }
                    case Opcode::Test: {
                        int a = bytecode[pc++];
                        int b = bytecode[pc++];
                        //std::println("a: {}, b: {}, res: {}", registers[a], registers[b], registers[a] == registers[b]);
                        registers[Registers::TEST] = (registers[a] == registers[b]);
                        break;
                    }
                    case Opcode::Ldr: {
                        int dst = bytecode[pc++];
                        int src = bytecode[pc++];
                        registers[dst] = src;
                        break;
                    }
                    case Opcode::Push: {
                        int a = bytecode[pc++];
                        stack.push_back(a);
                        break;
                    }
                    case Opcode::Pop: {
                        int dst = bytecode[pc++];
                        registers[dst] = stack.back();
                        stack.pop_back();
                        break;
                    }
                    case Opcode::PopA: {
                        for (int n : stack) {
                            stack.pop_back();
                        }
                        break;
                    }
                    case Opcode::Print: {
                        int src = bytecode[pc++];
                        std::println("babyvm: {}", registers[src]);
                        break;
                    }
                    case Opcode::PrintS: {
                        int len = bytecode[pc++];
                        for (int c : stack) {
                            if (len > 0 && !stack.empty()) {
                                std::print("{}", static_cast<char>(c));
                                stack.pop_back();
                                len--;
                            }
                        }
                        std::print("\n");
                        break;
                    }
                    case Opcode::Input: {
                        std::print("babyvm input: ");
                        std::string input;
                        std::getline(std::cin, input);
                        for (char c : input) {
                            stack.push_back(static_cast<int>(c));
                        }
                        break;
                    }
                    case Opcode::HaltNE: {
                        if (registers[Registers::TEST] != 1) {
                            signal = Signals::Stop;
                        }
                        break;
                    }
                    case Opcode::Halt: {
                        signal = Signals::Stop;
                        break;
                    }
                    default: {
                        std::println("an error occurred, killing babyvm");
                        signal = Signals::Err;
                        break;
                    }
                }
            }
        }
};

int main(void) {
    VM *vm = new VM();
    // Make some logical ops to compare against the flag contents, ask AI imo
    // gryphCTF{w3lc0m3_to_8a8y_VM!!}
    vm->bytecode = {
        Input,
        // '}' = 125
        Mul, 25, 5,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // '!' = 33
        Add, 17, 16,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // '!' = 33
        Sub, 50, 17,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'M' = 77
        Div, 154, 2,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'V' = 86
        Add, 40, 46,
        Pop, X3,
        Xor, 86, 0,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // '_' = 95 
        Or, 64, 31,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'y' = 121
        Sub, 200, 79,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // '8' = 56
        And, 63, 56,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'a' = 97
        Xor, 113, 16,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // '8' = 56  (use Mul/Div combo)
        Mul, 7, 8,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // '_' = 95
        Nand, 0, 0,
        Pop, X3,
        Not, 0,
        Pop, X4,
        Add, 50, 45,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'o' = 111
        Add, 100, 11,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 't' = 116 (use Sub)
        Sub, 232, 116,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // '_' = 95 (use Or)
        Or, 64, 31,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // expect '3' = 51
        Add, 25, 26,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'm' = 109
        Mul, 11, 10,
        Pop, X5,
        Sub, 110, 1,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // '0' = 48
        Div, 96, 2,
        Pop, X3,
        Pop, X1,
        Test, X1, X3,
        HaltNE,
        // 'c' = 99
        Add, 50, 49,
        Pop, X9,
        Pop, X1,
        Test, X1, X9,
        HaltNE,
        // 'l' = 108
        Add, 60, 48,
        Pop, X2,
        Pop, X8,
        Test, X8, X2,
        HaltNE,
        // '3' = 51
        Sub, 102, 51,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'w' = 119
        Or, 118, 1,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // '{' = 123
        Add, 100, 23,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'F' = 70
        Sub, 140, 70,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'T' = 84
        Div, 168, 2,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'C' = 67
        Add, 40, 27,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'h' = 104
        Mul, 13, 8,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'p' = 112
        Sub, 224, 112,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'y' = 121
        Add, 60, 61,
        Pop, X4,
        Pop, X10,
        Test, X4, X10,
        HaltNE,
        // 'r' = 114
        Div, 228, 2,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // 'g' = 103
        Add, 50, 53,
        Pop, X2,
        Pop, X1,
        Test, X1, X2,
        HaltNE,
        // nice!
        PopA,
        Push, 83,
        Push, 117,
        Push, 99,
        Push, 99,
        Push, 101,
        Push, 115,
        Push, 115,
        Push, 33,
        PrintS, 8,
        Halt
    };
    vm->execute();
}
