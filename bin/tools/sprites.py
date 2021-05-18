#!/usr/bin/env python3
# vim:fileencoding=ISO-8859-1

# Initialize the program and modules

try:
    import argparse
    from PIL import Image
    import math
    from os import path
    import json
except ImportError as err:
    print("Could not load {} module.".format(err))
    raise SystemExit

from utilities import Utilities

class Sprite:

    def __init__(self, data):
        self.name = data['name']
        self.frames = data['frames']

    def readFrames(self):
        if not isinstance(self.frames, list) or len(self.frames) <= 0:
            return False

        valid = True
        for i in range(0, len(self.frames)):
            self.frames[i] = self.readFrame(self.frames[i])
            if self.frames[i]['valid'] == False:
                valid = False

        return valid

    def readFrame(self, frame):
        # Read Image
        frame['image'] = Utilities.loadImage(frame['file'])

        # Check Image Dimensions
        if frame['image'].width < frame['x'] + frame['w'] or frame['image'].height < frame['y'] + frame['w']:
            frame['valid'] = False
            return frame

        # Get Image Data from Region
        frame['imageCrop'] = frame['image'].crop((frame['x'], frame['y'], frame['x'] + frame['w'], frame['y'] + frame['h']))
        frame['buffer'] = Utilities.getImageBufferRaw(frame['imageCrop'])

        frame['valid'] = True
        return frame

    def printInfo(self):
        print("Name: {}".format(self.name))
        print("Number of Frames: {:d}\n".format(len(self.frames)))
        for i in range(0, len(self.frames)):
            print("Frame {:d} Image Info:".format(i))
            print("Image File: {}".format(self.frames[i]['file']))
            Utilities.printImageInfo(self.frames[i]['image'])
            print("Image Crop: {}".format((self.frames[i]['x'], self.frames[i]['y'], self.frames[i]['w'], self.frames[i]['h'])))
            if self.frames[i]['valid']:
                print("Valid Frame")
            else:
                print("Invalid Frame")
            print("")

    def frameDataLength(self, i):
        if self.frames[i]['valid'] == False:
            return 0
        return self.frames[i]['w'] * self.frames[i]['h']

    def totalFrameDataLength(self):
        sum = 0
        for i in range(0, len(self.frames)):
            sum += self.frameDataLength(i)
        return sum

    def totalFrames(self):
        return len(self.frames)

    def getName(self):
        return self.name

    def getFrame(self, i):
        if i >= len(self.frames) or i < 0:
            return False
        return self.frames[i]

class Sprites:

    def __init__(self):
        self.sprites = []

    def addSprite(self, data):
        if not isinstance(data, dict):
            return False

        sprite = Sprite(data)
        if not sprite.readFrames():
            return False

        self.sprites.append(sprite)
        return True

    def getSprites(self):
        return self.sprites

    def getSprite(self, i):
        if i >= len(self.sprites) or i < 0:
            return False
        return self.sprites[i]

    def getTotalPixels(self):
        sum = 0
        for i in range(0, len(self.sprites)):
            sum += self.sprites[i].totalFrameDataLength()
        return sum

    def getTotalFrames(self):
        sum = 0
        for i in range(0, len(self.sprites)):
            sum += self.sprites[i].totalFrames()
        return sum

    def composeHeader(self, file):
        # Process output file name
        file = path.splitext(file)[0] # Remove extension
        filename = path.basename(file) # Get name

        if not isinstance(self.sprites, list) or len(self.sprites) <= 0:
            return False

        # Header define and includes
        h_output = "#ifndef PY_{}_H_\n".format(filename.upper())
        h_output += "#define PY_{}_H_\n\n".format(filename.upper())
        h_output += "#include \"usvc_kernel/usvc_kernel.h\"\n\n"

        # General Data Info
        h_output += "#define SPRITEDATA_NUMPIXELS {:d}\n".format(self.getTotalPixels())
        h_output += "#define FRAMEDATA_NUMFRAMES {:d}\n".format(self.getTotalFrames())
        h_output += "#define ANIMDATA_NUMANIM {:d}\n".format(len(self.sprites))
        h_output += "#define ENTITYDATA_NUMENTITIES {:d}\n\n".format(len(self.sprites))

        # Sprite entities and animations (indexes)
        for i in range(0, len(self.sprites)):
            h_output += "#define {} {:d}\n\n".format(self.sprites[i].getName().upper(), i)
            #for j in range(0, len(self.sprites[i].animations)):
            #    h_output += "#define {}_{} {:d}"

        # Sprite Frame indexes & length
        index = 0
        for i in range(0, len(self.sprites)):
            h_output += "#define {}_FRAMEINDEX 0x{:04X}\n".format(self.sprites[i].getName().upper(), index)
            h_output += "#define {}_NUMFRAMES 0x{:04X}\n\n".format(self.sprites[i].getName().upper(), self.sprites[i].totalFrames())
            index += self.sprites[i].totalFrames()

        # Sprite animations frames & length
        #for i in range(0, len(self.sprites)):
        #    for j in range(0, len(self.sprites[i].animations)):
        #        h_output += "{}_{}_FRAMEINDEX 0x{:04X}\n".format(self.sprites[i].getName().upper(), self.sprites[i].animations[j].getName().upper())

        # Animation typedef
        h_output += "typedef struct {\n"
        h_output += " " * Utilities.outputTabLength + "uint16_t frameIndex;\n"
        h_output += " " * Utilities.outputTabLength + "uint8_t numFrames;\n"
        h_output += "} anim_t;\n\n"

        # Data externs
        h_output += "extern const uint8_t spriteData[SPRITEDATA_NUMPIXELS];\n"
        h_output += "extern const frame_t frameData[FRAMEDATA_NUMFRAMES];\n"
        h_output += "extern const anim_t animData[ANIMDATA_NUMANIM];\n"
        h_output += "extern const anim_t* entityData[ENTITYDATA_NUMENTITIES];\n"
        h_output += "extern const uint16_t entityAnimStartIndex[ENTITYDATA_NUMENTITIES];\n\n"

        # End of file
        h_output += "#endif\n"

        # Save Header File
        headerFile = open("{}.h".format(file), "w")
        headerFile.write(h_output)
        headerFile.close()

        return True

    def composeCode(self, file):
        # Process output file name
        file = path.splitext(file)[0] # Remove extension
        filename = path.basename(file) # Get name

        if not isinstance(self.sprites, list) or len(self.sprites) <= 0:
            return False

        # Compose C File Output
        c_output = "#include \"{}.h\"\n\n".format(filename)

        # Sprites pixel data
        c_output += "const uint8_t spriteData[SPRITEDATA_NUMPIXELS] = {\n\n"
        for i in range(0, len(self.sprites)):
            c_output += " " * Utilities.outputTabLength + "// {}\n".format(self.sprites[i].getName())
            for j in range(0, self.sprites[i].totalFrames()):
                frame = self.sprites[i].getFrame(j)
                c_output += "\n" + " " * Utilities.outputTabLength + "/// Frame {}\n".format(j)
                for y in range(0, frame['h']):
                    c_output += " " * Utilities.outputTabLength
                    for x in range(0, frame['w']):
                        c_output += "0x{:02X}".format(frame['buffer'][y][x])
                        if x < frame['w'] - 1:
                            c_output += ", "
                    if y < frame['h'] - 1:
                        c_output += ",\n"
                if j < self.sprites[i].totalFrames() - 1:
                    c_output += ",\n"
            if i < len(self.sprites) - 1:
                c_output += ","
            c_output += "\n\n"
        c_output += "};\n\n"

        # Frame Properties
        c_output += "const frame_t frameData[FRAMEDATA_NUMFRAMES] = {\n"
        index = 0
        for i in range(0, len(self.sprites)):
            for j in range(0, self.sprites[i].totalFrames()):
                frame = self.sprites[i].getFrame(j)
                c_output += " " * Utilities.outputTabLength + "{{ .w = 0x{:02X}, .h = 0x{:02X}, .ox = 0x{:02X}, .oy = 0x{:02X}, .pData = &spriteData[0x{:05X}] }}".format(frame['w'], frame['h'], frame['x'], frame['y'], index)
                if j < self.sprites[i].totalFrames() - 1:
                    c_output += ",\n"
                index += self.sprites[i].frameDataLength(j)
            if i < len(self.sprites) - 1:
                c_output += ","
            c_output += "\n"
        c_output += "};\n\n"

        # Animation Properties (just using each sprite for now)
        c_output += "const anim_t animData[ANIMDATA_NUMANIM] = {\n"
        index = 0
        for i in range(0, len(self.sprites)):
            c_output += " " * Utilities.outputTabLength + "{{ .frameIndex = 0x{:04X}, .numFrames = 0x{:02X} }}".format(index, self.sprites[i].totalFrames())
            index += self.sprites[i].totalFrames()
            if i < len(self.sprites) - 1:
                c_output += ","
            c_output += "\n"
        c_output += "};\n\n"

        # Entity Properties
        c_output += "const anim_t* entityData[ENTITYDATA_NUMENTITIES] = {\n"
        for i in range(0, len(self.sprites)):
            c_output += " " * Utilities.outputTabLength + "&animData[0x{:02X}]".format(i)
            if i < len(self.sprites) - 1:
                c_output += ","
            c_output += "\n"
        c_output += "};\n\n"

        # Entity Animation Start Index
        c_output += "const uint16_t entityAnimStartIndex[ENTITYDATA_NUMENTITIES] = {\n"
        for i in range(0, len(self.sprites)):
            c_output += " " * Utilities.outputTabLength + "0x{:02X}".format(i)
            if i < len(self.sprites) - 1:
                c_output += ","
            c_output += "\n"
        c_output += "};\n"

        # Save C File
        codeFile = open("{}.c".format(file), "w")
        codeFile.write(c_output)
        codeFile.close()

class SpritesCLI:

    def __init__(self):
        # Parse command line arguments
        parser = argparse.ArgumentParser()
        parser.add_argument("-v", "--verbose", help="display more verbose information", action="store_true")
        parser.add_argument("-c", "--config", help="JSON file with sprite configuration")
        parser.add_argument("-o", "--outfile", help="name and location of .c and .h file (don't include file extension)", default="sprites")

        self.args = parser.parse_args()
        if self.args.config == None:
            print("No config specified.")
            raise SystemExit

        if self.args.verbose:
            print("uSVC Sprite Utility - Version 0.10")

        # Read JSON Config
        data = None
        try:
            with open(self.args.config) as file:
                data = json.load(file)
        except json.decoder.JSONDecodeError as err:
            print("JSON decoding error encountered: {}".format(err))

        if not isinstance(data, list) or len(data) <= 0:
            print("Invalid config file provided.")
            raise SystemExit


        self.sprites = Sprites()

        for i in range(0, len(data)):
            if not self.sprites.addSprite(data[i]):
                print("Failed to process sprite at index #{:d}".format(i))
            elif self.args.verbose:
                self.sprites.getSprite(i).printInfo()

        self.sprites.composeHeader(self.args.outfile)
        self.sprites.composeCode(self.args.outfile)

        if self.args.verbose:
            print("Successfully converted sprite config and image data to C. {:d} sprites converted.".format(len(self.sprites.getSprites())))

        raise SystemExit

if __name__ == "__main__":
    SpritesCLI();
