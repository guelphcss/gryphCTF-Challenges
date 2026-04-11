//! Medium zig chal; stack strings string obfuscation at runtime
//! The method to solving here is to statically analyze the binary to find the `obfs` function, then debug the program until the loop counter is equal to `0x18`. Because this is all comptime, the counter is known at compile time and is constant, so players may opt to set a conditional breakpoint, or simply follow execution until they notice that the `jae` instruction (which takes them out of the loop body) is ready to jump.
//! The breakpoint that can be set in this case is `b *<addr of comparison> if $<reg being compared>==0x18`
//! Tools needed: Any decompiler + Debugger; pwndbg makes this very comfortable but regular gdb should work. Debug symbols are included so this should be somewhat comfy.
const std = @import("std");
const Print = std.debug.print;
fn obfs(comptime cs: []const u8) void {
    var css: [cs.len]u8 = undefined;
    for (0.., cs) |i, *c| {
        // stupid shift
        css[i] = c.* ^ ((1 << 8) & 2 | 4);
    }
}

fn deobfs(cs: []const u8) void {
    _ = cs;
}

pub fn main() void {
    const cs = [_]u8 {99, 118, 125, 116, 108, 71, 80, 66, 127, 108, 55, 104, 104, 52, 91, 48, 118, 52, 105, 91, 126, 53, 61, 121};
    const css: []u8 = obfs(&cs);
    Print("{s}", .{obfs(&css)});
}
