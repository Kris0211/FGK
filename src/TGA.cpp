#include "../include/TGA.hpp"

#include <fstream>
#include <ios>


void TGA::Save(const std::string& path, const std::vector<unsigned int>& data, const unsigned short width, const unsigned short height)
{
	const std::vector<unsigned short> header = { 0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000, width, height, 0x0820 };

	std::fstream file(path, std::ios::out | std::ios::binary);

	file.write(reinterpret_cast<const char*>(header.data()), header.size() * sizeof(unsigned short));
	file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(unsigned int));
	file.close();
}
