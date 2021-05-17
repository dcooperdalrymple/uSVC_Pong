#!/usr/bin/env python3
# vim:fileencoding=ISO-8859-1

# Initialize the program and modules

try:
    import sys
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
parser.add_argument("-l", "--label", help="variable label to use in your code", default="tileMap")
parser.add_argument("-i", "--infile", help="location to read image file (jpg/png/bmp)")
parser.add_argument("-o", "--outfile", help="name and location of .c and .h file (don't include file extension)", default="tilemap")
parser.add_argument("-t", "--tilesetfile", help="location to read tileset data (jpg/png/bmp; if not specified, tileset will be extract from infile)")

args = parser.parse_args()
if args.infile == None:
    print("No image specified.")
    raise SystemExit

if args.verbose:
    print("uSVC Tilemap Converter - Version 0.10")

# Read Image
image = Utilities.loadImage(args.infile)
if args.verbose:
    print("Image successfully loaded")
    Utilities.printImageInfo(image)

# Get tiles from image
tileW = Utilities.getImageTileW(image)
tileH = Utilities.getImageTileH(image)
tileData = Utilities.readImageTiles(image)

# Determine tileset
tileSet = False
if args.tilesetfile != None:
    tileSet_image = Utilities.loadImage(args.tilesetfile)
    tileSet_w = Utilities.getImageTileW(tileSet_image) * Utilities.tileSize
    tileSet_h = Utilities.getImageTileH(tileSet_image) * Utilities.tileSize
    tileSet_buffer = Utilities.getImageBuffer(tileSet_image, tileSet_w, tileSet_h)
    tileSet = Utilities.readImageTiles(tileSet_buffer, tileSet_w, tileSet_h)
else:
    tileSet = Utilities.extractTileSet(tileData)

# Identify tiles in tileset to build tilemap
tileMap = Utilities.getTileMap(tileData, tileSet)

# Process output file name
args.outfile = path.splitext(args.outfile)[0] # Remove extension
outfileName = path.basename(args.outfile) # Get name

# Compose Header File Output
h_output = "#ifndef {}_H_\n".format(outfileName.upper())
h_output += "#define {}_H_\n\n".format(outfileName.upper())
h_output +=  "#include <stdint.h>\n\n"
h_output += "#define MAPSIZEX_{} {:d}\n".format(args.label.upper(), tileW)
h_output += "#define MAPSIZEY_{} {:d}\n".format(args.label.upper(), tileH)
h_output += "extern const uint16_t {}[MAPSIZEY_{} * MAPSIZEX_{}];\n\n".format(args.label, args.label.upper(), args.label.upper())
h_output += "#endif\n"

# Save Header File
headerFile = open("{}.h".format(args.outfile), "w")
headerFile.write(h_output)
headerFile.close()

# Compose C File Output
c_output = "#include \"{}.h\"\n\n".format(outfileName)
c_output += "const uint16_t {}[MAPSIZEY_{} * MAPSIZEX_{}] = {{\n".format(args.label, args.label.upper(), args.label.upper())

for y in range(0, tileH):
    c_output += " " * Utilities.outputTabLength
    for x in range(0, tileW):
        c_output += "0x{:04X}".format(tileMap[y * tileW + x])
        if x < tileW - 1:
            c_output += ", "
    if y < tileH - 1:
        c_output += ","
    c_output += "\n"
c_output += "};\n"

# Save C File
codeFile = open("{}.c".format(args.outfile), "w")
codeFile.write(c_output)
codeFile.close()

if args.verbose:
    print("Successfully converted image to tilemap data.")

raise SystemExit
