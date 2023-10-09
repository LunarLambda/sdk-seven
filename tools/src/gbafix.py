#!/usr/bin/env python3

import argparse
import struct
from math import ceil, log2

NINTENDO_LOGO = (
    0x24, 0xFF, 0xAE, 0x51, 0x69, 0x9A, 0xA2, 0x21,
    0x3D, 0x84, 0x82, 0x0A, 0x84, 0xE4, 0x09, 0xAD,
    0x11, 0x24, 0x8B, 0x98, 0xC0, 0x81, 0x7F, 0x21,
    0xA3, 0x52, 0xBE, 0x19, 0x93, 0x09, 0xCE, 0x20,
    0x10, 0x46, 0x4A, 0x4A, 0xF8, 0x27, 0x31, 0xEC,
    0x58, 0xC7, 0xE8, 0x33, 0x82, 0xE3, 0xCE, 0xBF,
    0x85, 0xF4, 0xDF, 0x94, 0xCE, 0x4B, 0x09, 0xC1,
    0x94, 0x56, 0x8A, 0xC0, 0x13, 0x72, 0xA7, 0xFC,
    0x9F, 0x84, 0x4D, 0x73, 0xA3, 0xCA, 0x9A, 0x61,
    0x58, 0x97, 0xA3, 0x27, 0xFC, 0x03, 0x98, 0x76,
    0x23, 0x1D, 0xC7, 0x61, 0x03, 0x04, 0xAE, 0x56,
    0xBF, 0x38, 0x84, 0x00, 0x40, 0xA7, 0x0E, 0xFD,
    0xFF, 0x52, 0xFE, 0x03, 0x6F, 0x95, 0x30, 0xF1,
    0x97, 0xFB, 0xC0, 0x85, 0x60, 0xD6, 0x80, 0x25,
    0xA9, 0x63, 0xBE, 0x03, 0x01, 0x4E, 0x38, 0xE2,
    0xF9, 0xA2, 0x34, 0xFF, 0xBB, 0x3E, 0x03, 0x44,
    0x78, 0x00, 0x90, 0xCB, 0x88, 0x11, 0x3A, 0x94,
    0x65, 0xC0, 0x7C, 0x63, 0x87, 0xF0, 0x3C, 0xAF,
    0xD6, 0x25, 0xE4, 0x8B, 0x38, 0x0A, 0xAC, 0x72,
    0x21, 0xD4, 0xF8, 0x07,
)

class GBAHeader:
    def __init__(self):
        self.entry = 0,
        self.title = ""
        self.game_code = ""
        self.maker_code = ""
        self.version = 0

    def checksum(self):
        check = struct.pack(
                "<12s4s2sB9xB",
                self.title,
                self.game_code,
                self.maker_code,
                0x96,
                self.version)

        checksum = -0x19

        for byte in check:
            checksum -= byte

        return checksum & 0xFF

    def from_bytes(buf):
        # 0: entry
        # 1: title
        # 2: game code
        # 3: maker code
        # 4: version
        stuff = struct.unpack("<I156x12s4s2s10xB3x", buf)
        h = GBAHeader()
        h.entry = stuff[0]
        h.title = stuff[1]
        h.game_code = stuff[2]
        h.maker_code = stuff[3]
        h.version = stuff[4]
        return h

    def to_bytes(self):
        return struct.pack(
                "<I156B12s4s2sB9xBB2x",
                self.entry,
                *NINTENDO_LOGO,
                self.title,
                self.game_code,
                self.maker_code,
                0x96,
                self.version,
                self.checksum())

def limited_string(name, n):
    def inner(s):
        if len(s) > n:
            raise ValueError("{} is longer than {} characters".format(name, n))
        try:
            return s.encode('ascii')
        except UnicodeError:
            raise ValueError("{} must contain only ASCII characters".format(name))

    return inner

def byte(s):
    x = int(s)

    if x < 0 or x > 255:
        raise ValueError("version must be between 0 and 255")

    return x

def default_title(fp):
    import os.path
    return os.path.basename(fp.name).encode('ascii')[:12]

def main():
    p = argparse.ArgumentParser()

    p.add_argument(
        "file",
        type=argparse.FileType("r+b"),
        help="ROM file to fix")
    p.add_argument(
        "-t", "--title",
        nargs="?",
        const="", 
        type=limited_string("title", 12), 
        help="ROM title, 12 characters")
    p.add_argument(
        "-c", "--code",
        type=limited_string("game code", 4),
        help="Game code, 4 characters",
        dest="game_code")
    p.add_argument(
        "-m", "--maker",
        type=limited_string("maker code", 2),
        help="Maker code, 2 characters",
        dest="maker_code")
    p.add_argument(
        "-r", "--revision",
        type=byte, 
        help="ROM version",
        dest="version")
    p.add_argument(
        "-p", "--pad",
        action="store_true",
        help="Pad ROM to next power of two",
        dest="pad")
    p.add_argument(
        "-d", "--debug",
        nargs="?",
        const=0,
        type=int,
        choices=(0,1),
        help="Enable BIOS debug handler (0 = 0x09FFC000, 1 = 0x09FE2000)")

    opts = p.parse_args()

    h = opts.file.read(192)

    if len(h) < 192:
        print("file is too small")
        return 1

    header = GBAHeader.from_bytes(h)

    if opts.title == b'':
        header.title = default_title(opts.file)
    elif opts.title:
        header.title = opts.title

    if opts.game_code:
        header.game_code = opts.game_code

    if opts.maker_code:
        header.maker_code = opts.maker_code

    if opts.version:
        header.version = opts.version

    binh = header.to_bytes()

    if opts.debug != None:
        binh = bytearray(binh)
        binh[0x9C] = 0xA5
        binh[0xB4] = 0x80 if opts.debug == 1 else 0x00

    fp = opts.file
    fp.seek(0)
    fp.write(binh)

    if opts.pad:
        fp.seek(0, 2)
        pos = fp.tell()
        end = pow(2, ceil(log2(pos)))

        pad = b"\xFF" * 4096

        while (end - pos) > 0:
            n = min(end - pos, 4096)
            fp.write(pad[:n])
            pos += n

    fp.close()

    return 0

if __name__ == "__main__":
    exit(main())
