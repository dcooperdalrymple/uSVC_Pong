#!/usr/bin/env python3
# vim:fileencoding=ISO-8859-1

# Initialize the program and modules

try:
    import argparse
    from PIL import Image
    import math
    from os import path
except ImportError as err:
    print("Could not load {} module.".format(err))
    raise SystemExit

from utilities import Utilities

# Parse command line arguments

parser = argparse.ArgumentParser()

parser.add_argument("-v", "--verbose", help="display more verbose information", action="store_true")
parser.add_argument("-l", "--label", help="variable label to use in your code", default="tileData")
parser.add_argument("-i", "--infile", help="location to read image file (jpg/png/bmp)")
parser.add_argument("-o", "--outfile", help="name and location of .c and .h file (don't include file extension)", default="tileset")

args = parser.parse_args()
if args.infile == None:
    print("No image specified.")
    raise SystemExit

if args.verbose:
    print("uSVC Tileset Converter - Version 0.10")

# Read Image
image = Utilities.loadImage(args.infile)
if args.verbose:
    print("Image successfully loaded.")
    Utilities.printImageInfo(image)

# Extract Tileset
tileData = Utilities.readImageTiles(image)
tileset = Utilities.extractTileSet(tileData)

# Process output file name
args.outfile = path.splitext(args.outfile)[0] # Remove extension
outfileName = path.basename(args.outfile) # Get name

# Compose Header File Output
h_output = "#ifndef {}_H_\n".format(outfileName.upper())
h_output += "#define {}_H_\n\n".format(outfileName.upper())
h_output += "#include <stdint.h>\n\n"
h_output += "#define MAXTILEINDEX {:d}\n".format(len(tileset))
h_output += "#define TILESIZEX {:d}\n".format(Utilities.tileSize)
h_output += "#define TILESIZEY {:d}\n".format(Utilities.tileSize)
h_output += "extern const uint8_t {}[MAXTILEINDEX][TILESIZEX * TILESIZEY];\n\n".format(args.label)
h_output += "#endif\n"

# Save Header File
headerFile = open("{}.h".format(args.outfile), "w")
headerFile.write(h_output)
headerFile.close()

# Compose C File Output
c_output = "#include \"{}.h\"\n\n".format(outfileName)
c_output += "const uint8_t {}[MAXTILEINDEX][TILESIZEX * TILESIZEY] = {{\n".format(args.label)

for i in range(0, len(tileset)):
    c_output += " " * Utilities.outputTabLength + "{\n"

    for y in range(0, Utilities.tileSize):
        c_output += " " * (Utilities.outputTabLength * 2)
        for x in range(0, Utilities.tileSize):
            c_output += "0x{:02X}".format(tileset[i][y][x])
            if x < Utilities.tileSize - 1:
                c_output += ", "
        if y < Utilities.tileSize - 1:
            c_output += ","
        c_output += "\n"

    c_output += " " * Utilities.outputTabLength + "}"
    if i < len(tileset) - 1:
        c_output += ","
    c_output += "\n"

c_output += "};\n"

# Save C File
codeFile = open("{}.c".format(args.outfile), "w")
codeFile.write(c_output)
codeFile.close()

if args.verbose:
    print("Successfully converted image to tileset data. {:d} tiles in tileset.".format(len(tileset)))

raise SystemExit
