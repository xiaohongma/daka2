/*
Copyright (c) 2013, Fatih Calakli and Daniel Moreno
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
      
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
      
    * Neither the name of the Brown University nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR 
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include <fstream>

#include "dgp/PointXYZRGB.hpp"

namespace PlyWriter
{
    template <typename PointType> void write_point(PointType const& p, std::ofstream & outfile, bool flagBinary)
    {
        float x = static_cast<float>(p.x), y = static_cast<float>(p.y), z = static_cast<float>(p.z);
        if (flagBinary)
        {
            outfile.write(reinterpret_cast<const char *>(&x), sizeof(float));
            outfile.write(reinterpret_cast<const char *>(&y), sizeof(float));
            outfile.write(reinterpret_cast<const char *>(&z), sizeof(float));
        }
        else
        {
            outfile << x << " " << y << " "  << z;
            outfile << std::endl;
        }
    }

    template <> void write_point<PointXYZRGB>(PointXYZRGB const& p, std::ofstream & outfile, bool flagBinary)
    {
        float x = static_cast<float>(p.x), y = static_cast<float>(p.y), z = static_cast<float>(p.z);
        uint8_t b = static_cast<uint8_t>(p.b*255.f + 0.5f), g = static_cast<uint8_t>(p.g*255.f + 0.5f), r = static_cast<uint8_t>(p.r*255.f + 0.5f), a = static_cast<uint8_t>(p.a*255.f + 0.5f);
        if (flagBinary)
        {
            outfile.write(reinterpret_cast<const char *>(&x), sizeof(float));
            outfile.write(reinterpret_cast<const char *>(&y), sizeof(float));
            outfile.write(reinterpret_cast<const char *>(&z), sizeof(float));

            outfile.write(reinterpret_cast<const char *>(&r), sizeof(uint8_t));
            outfile.write(reinterpret_cast<const char *>(&g), sizeof(uint8_t));
            outfile.write(reinterpret_cast<const char *>(&b), sizeof(uint8_t));
            outfile.write(reinterpret_cast<const char *>(&a), sizeof(uint8_t));
        }
        else
        {
            outfile << x << " " << y << " "  << z
                    << " " << static_cast<int>(r) << " " << static_cast<int>(g) << " " << static_cast<int>(b) << " " << static_cast<int>(a)
                    << std::endl;
        }
    }
};

template <typename PointType>
bool PlyWriter::write(const std::string & filename, std::vector<PointType> const& vertices, std::vector<std::vector<size_t> > const& faces, unsigned flags)
{
    const bool flagBinary  = (flags&PlyBinary )>0;
    const bool flagFaces   = (flags&PlyFaces  )>0;
    const bool flagNormals = (flags&PlyNormals)>0;
    const bool flagColors  = (flags&PlyColors )>0;

    std::ofstream outfile;
    std::ios::openmode mode = std::ios::out|std::ios::trunc|(flagBinary?std::ios::binary:static_cast<std::ios::openmode>(0));
    outfile.open(filename.c_str(), mode);
    if (!outfile.is_open())
    {
        return false;
    }

    const char * format_header = (flagBinary? "binary_little_endian 1.0" : "ascii 1.0");
    outfile << "ply" << std::endl 
            << "format " << format_header << std::endl 
            << "comment ssd generated" << std::endl 
            << "element vertex " << vertices.size() << std::endl 
            << "property float x" << std::endl 
            << "property float y" << std::endl 
            << "property float z" << std::endl;
    if (flagNormals)
    {
        outfile << "property float nx" << std::endl 
                << "property float ny" << std::endl 
                << "property float nz" << std::endl;
    }
    if (flagColors)
    {
        outfile << "property uchar red" << std::endl 
                << "property uchar green" << std::endl 
                << "property uchar blue" << std::endl 
                << "property uchar alpha" << std::endl;
    }
    outfile << "element face " << (flagFaces ? faces.size() : 0) << std::endl 
            << "property list uchar int vertex_indices" << std::endl 
            << "end_header" << std::endl ;

    for (typename std::vector<PointType>::const_iterator iter=vertices.begin(); iter!=vertices.end(); ++iter)
    {
        write_point(*iter, outfile, flagBinary);
    }

    if (flagFaces)
    {
        for (std::vector<std::vector<size_t> >::const_iterator iter1=faces.begin(); iter1!=faces.end(); ++iter1)
        {
            std::vector<size_t> const& face = (*iter1);
            if (flagBinary)
            {
                unsigned char size = static_cast<unsigned char>(iter1->size()&0xff);
                outfile.write(reinterpret_cast<const char *>(&size), sizeof(unsigned char));
            }
            else
            {
                outfile << iter1->size();
            }

            for (std::vector<size_t>::const_iterator iter2=face.begin(); iter2!=face.end(); ++iter2)
            {
                if (flagBinary)
                {
                    int index = static_cast<int>(*iter2);
                    outfile.write(reinterpret_cast<const char *>(&index), sizeof(int));
                }
                else
                {
                    outfile << " " << (*iter2);
                }
            }
            if (!flagBinary)
            {
                outfile << std::endl;
            }
        }
    }

    outfile.close();
    return true;
}
