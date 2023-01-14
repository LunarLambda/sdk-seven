#!/usr/bin/env python3

import argparse
import os.path
import struct
import sys

class GBAHeader:
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
                *self.NINTENDO_LOGO,
                self.title,
                self.game_code,
                self.maker_code,
                0x96,
                self.version,
                self.checksum())

def main():
    p = argparse.ArgumentParser()

    p.add_argument("file", help="ROM file to fix", type=argparse.FileType("r+b"))
    p.add_argument("-t", "--title", type=str, nargs="?", const="", dest="title")
    p.add_argument("-c", "--code", type=str, nargs=1, dest="game_code")
    p.add_argument("-m", "--maker", type=str, nargs=1, dest="maker_code")
    p.add_argument("-r", "--revision", type=int, nargs=1, dest="version")
    p.add_argument("-p", "--pad", type=int, nargs="?", dest="pad")
    p.add_argument("-d", "--debug", type=int, nargs="?", help="ignored")

    opts = p.parse_args()

    h = opts.file.read(192)

    if len(h) < 192:
        raise Exception("specified file is too small (min. 192 bytes)")

    header = GBAHeader.from_bytes(h)

    opts.title = path.basename(opts.file.name) if opts.title == "" else opts.title

    header.title        = opts.title or header.title
    header.game_code    = opts.game_code or header.game_code
    header.maker_code   = opts.maker_code or header.maker_code
    header.version      = opts.version or header.version

    binh = header.to_bytes()

    opts.file.seek(0)
    opts.file.write(binh)
    opts.file.close()

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(e, file=sys.stderr)
        exit(1)
