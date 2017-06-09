/*
 * Copyright 2017 Hao Sun <sun.me.0207@gmail.com>
 * Copyright 2017 Zongyu Yin <alexyin1012@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include <ABELogger.h>
#include <cstring>
#include <malloc.h>
#include <GL/glew.h>
#include "ABETexture.h"

#define DDS_FILE_MAGIC "DDS "
#define DDS_FOUR_CAPS_DXT1 0x31545844 // "DXT1" in ASCII.
#define DDS_FOUR_CAPS_DXT3 0x33545844 // "DXT3" in ASCII.
#define DDS_FOUR_CAPS_DXT5 0x35545844 // "DXT5" in ASCII.

using abege::ABETexture;

void ABETexture::loadBMP(const char * imagepath) {

    LOGI(TAG, "Reading image", imagepath);

    // Data read from the header of the BMP file
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    unsigned int width, height;
    // Actual RGB data
    unsigned char * data;

    // Open the file
    FILE *file = fopen(imagepath, "rb");
    if (!file) {
        LOGE(TAG, "Failed to open", imagepath);
        return;
    }

    // Read the header, i.e. the 54 first bytes

    // If less than 54 bytes are read, problem
    if (fread(header, 1, 54, file) != 54) {
        LOGE(TAG, "Not a correct BMP file");
        return;
    }
    // A BMP files always begins with "BM"
    if (header[0] != 'B' || header[1] != 'M') {
        LOGE(TAG, "Not a correct BMP file");
        return;
    }
    // Make sure this is a 24bpp file
    if (*(int*)&(header[0x1E]) != 0) {
        LOGE(TAG, "Not a correct BMP file");
        return;
    }
    if (*(int*)&(header[0x1C]) != 24) {
        LOGE("Not a correct BMP file\n");
        return;
    }

    // Read the information about the image
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0) {
        imageSize = width*height * 3;
    } // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0) {
        dataPos = 54;
    } // The BMP header is done that way

    // Create a buffer
    data = new unsigned char[imageSize];

    // Read the actual data from the file into the buffer
    fread(data, 1, imageSize, file);

    // Everything is in memory now, the file wan be closed
    fclose(file);

    // Create one OpenGL texture
    glGenTextures(1, &ID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, ID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    // OpenGL has now copied the data. Free our own version
    delete[] data;

    // Poor filtering, or ...
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

    // ... nice trilinear filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}


void ABETexture::loadDDS(const char *imagePath) {
    unsigned char header[124];

    FILE *fp;

    fp = fopen(imagePath, "rb");
    if (fp == NULL){
        LOGE(TAG, "Failed to open image.");
        return;
    }

    // Verify the type of the file.
    char magic[4];
    fread(magic, 1, 4, fp);
    if (strncmp(magic, DDS_FILE_MAGIC, 4) != 0) {
        fclose(fp);
        return;
    }

    // Get file header.
    fread(&header, 124, 1, fp);

    unsigned int height = *(unsigned int*)&(header[8]);
    unsigned int width = *(unsigned int*)&(header[12]);
    unsigned int linearSize = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCaps = *(unsigned int*)&(header[80]);


    unsigned char *buffer;
    unsigned int bufferSize;

    bufferSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufferSize * sizeof(unsigned char));
    fread(buffer, 1, bufferSize, fp);

    fclose(fp);

    unsigned int format;
    switch(fourCaps) {
        case DDS_FOUR_CAPS_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case DDS_FOUR_CAPS_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case DDS_FOUR_CAPS_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            free(buffer);
            return;
    }

    // Create one OpenGL texture.
    glGenTextures(1, &ID);

    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    // Load the mipmaps.
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) {
        unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                               0, size, buffer + offset);

        offset += size;
        width  /= 2;
        height /= 2;

        if (width < 1) {
            width = 1;
        }
        if (height < 1) {
            height = 1;
        }
    }

    free(buffer);
}
