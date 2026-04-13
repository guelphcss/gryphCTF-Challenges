from enum import IntEnum
from colorama import init, Fore

class Opcode(IntEnum):
    Add = 0
    Sub = 1
    Div = 2
    Mul = 3
    Or = 4
    And = 5
    Xor = 6
    Nand = 7
    Not = 8
    Test = 9
    Ldr = 10
    Push = 11
    Pop = 12
    PopA = 13
    Print = 14
    PrintS = 15
    Input = 16
    HaltNE = 17
    Halt = 18

class Regs(IntEnum):
    X1 = 0
    X2 = 1
    X3 = 2
    X4 = 3
    X5 = 4
    X6 = 5
    X7 = 6
    X8 = 7
    X9 = 8
    X10 = 9
    TEST = 10

def disas(bytecode: list[int]) -> None:
    """
    Disassemble stream of integers representing VM bytecode. Exits if an unknown bytecode is found; will dump remaining bytecode.
    """
    print(Fore.GREEN + "[INFO]" + Fore.RESET + " Starting disassembly") 
    while (len(bytecode) > 0):
        op: int = bytecode[0]
        match (op):
            case Opcode.Add | Opcode.Sub | Opcode.Div | Opcode.Mul | Opcode.Or | Opcode.And | Opcode.Xor | Opcode.Nand:
                print(f"{Fore.BLUE}{Opcode(op).name}{Fore.RESET}, {bytecode[1]}, {bytecode[2]}")
                del bytecode[0:3]
            case Opcode.Not | Opcode.Push:
                print(f"{Fore.CYAN}{Opcode(op).name}{Fore.RESET}, {bytecode[1]}")
                del bytecode[0:2]
            case Opcode.Ldr:
                print(f"{Fore.YELLOW}{Opcode(op).name}{Fore.RESET}, {Regs(bytecode[1]).name}, {Regs.__call__(bytecode[2]).name}")
                del bytecode[0:3]
            case Opcode.Pop | Opcode.Print:
                print(f"{Fore.MAGENTA}{Opcode(op).name}{Fore.RESET}, {Regs(bytecode[1]).name}")
                del bytecode[0:2]
            case Opcode.Push | Opcode.PrintS:
                print(f"{Fore.MAGENTA}{Opcode(op).name}{Fore.RESET}, {bytecode[1]}")
                del bytecode[0:2]
            case Opcode.PopA | Opcode.Input | Opcode.HaltNE | Opcode.Halt:
                print(f"{Fore.RED}{Opcode(op).name}{Fore.RESET}")
                del bytecode[0]
            case _:
                print(f"{Fore.RED}[ERROR]{Fore.RESET} Unknown opcode: {op}. Dumping remaining bytecode:\n{bytecode}")
                break

def main() -> None:
    """
    Get stream of integers representing VM bytecode, then pass to disassembler.
    """
    init()
    print(f"{Fore.GREEN}BBD. The BabyVM Disassembler.{Fore.RESET}")
    bytecode: list[int] = [int(op) for op in input("Enter BabyVM bytcode (space-seperated integers): ").split()]
    try:
        disas(bytecode)
    except IndexError:
        print(f"{Fore.RED}[ERROR]{Fore.RESET} Invalid bytecode was supplied and could not be disassembled. Dumping remaining bytecode:\n{bytecode}")

main()
