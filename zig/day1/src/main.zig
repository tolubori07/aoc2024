const std = @import("std");

fn readFile2Arr() !void {
    const cwd = std.fs.cwd();

    var input = try cwd.openFile("input.txt", .{});
    defer input.close();

    var buffer: [16398]u8 = undefined;
    const slice = buffer[0..];

    const bytes_read = try std.fs.File.read(input, slice);
    std.debug.print("{s}\n", .{
        slice[0..bytes_read],
    });
    //var left: [8196]u8 = undefined;
    //var right: [8196]u8 = undefined;
}

pub fn main() !void {
    try readFile2Arr();
}
