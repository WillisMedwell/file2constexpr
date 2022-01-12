#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <ranges>
#include <chrono>

class WriteHeader
{
private:
	std::ofstream m_file;
	const std::string m_filename;
	const std::string m_guardname;
	const std::string m_varname;
	const std::chrono::steady_clock::time_point m_start;
public:
	WriteHeader(std::string filename)
		: m_file(filename),
		m_filename(filename),
		m_guardname(GetHeaderGaurdName(filename)),
		m_start(std::chrono::high_resolution_clock::now())
	{	
		std::cout << "Creating File... \n\t" << m_filename << "\n";
		WriteGaurdStart(m_file);
		WriteIncludes(m_file);
	}
	~WriteHeader()
	{
		WriteGuardEnd(m_file);
		m_file.close();
		std::cout << "Finished File: \n\t"<< m_filename<<"\n";
		
		const auto total = std::chrono::high_resolution_clock::now() - m_start;
		std::cout << "time-taken: " << total.count() / 1000.0f / 1000.0f << "ms\n";
	}
	auto write_array(const std::string& dataType, const std::vector<std::string>& data, std::string varName)
	{
		varName = Capitalise(StripFormat(varName));
		//TODO :: Update when constexpr std::string is possible.
		auto type = (dataType == "std::string") ? "const" : "constexpr";
		m_file << type;
		m_file << " std::array<";
		m_file << dataType << ", " << data.size();
		m_file << "> " << varName <<" = {\n";

		auto StringNotLast = [&](auto& element) {
			m_file << "\t\"" << element << "\",\n";
		};
		auto StringLast = [&](auto& element) {
			m_file << "\t\"" << element << "\"\n";
		};
		auto NotLast = [&](auto& element) {
			m_file << "\t" << element << ",\n";
		};
		auto Last = [&](auto& element) {
			m_file << "\t" << element << "\n";
		};

		if (dataType == "std::string") [[unlikely]]
		{
			for (size_t i = 0; i < data.size()-1; i++) {
				StringNotLast(data[i]);
			}
			StringLast(data[data.size() - 1]);
		}
		else [[likely]]
		{
			for (size_t i = 0; i < data.size() - 1; i++) {
				NotLast(data[i]);
			}
			Last(data[data.size() - 1]);
		}
		m_file << "};\n";
	}

private:
	// "..\Include\Header.h" -> "Header"
	auto StripFormat(const std::string& filename) -> std::string
	{
		auto stripped = filename.substr(
			filename.find_last_of('\\') + 1, 
			filename.size()
		);
		return stripped.substr(0, stripped.find_last_of('.'));
	}
	// "Header"   -> "HEADER"
	auto Capitalise(std::string filename) -> std::string
	{
		constexpr auto CAP_DIFF = 'A' - 'a';

		for (auto& character : filename)
		{
			if (character >= 'a' && character <= 'z') {
				character += CAP_DIFF;
			}
		}
		return filename;
	}
	// "..\Include\Header.h" -> "HEADER_H"
	auto GetHeaderGaurdName(std::string filename) -> std::string
	{
		filename = StripFormat(filename);
		filename = Capitalise(filename);
		filename += "_H";
		return filename;
	}

	auto WriteGaurdStart(std::ostream& file) -> void
	{
		file << "#ifndef " << m_guardname << "\n";
		file << "#define " << m_guardname << "\n\n";
	}
	auto WriteGuardEnd(std::ofstream& file) -> void
	{
		file << "\n#endif\n";
	}
	auto WriteIncludes(std::ofstream& file) -> void
	{
		file << "#include <array>\n";
		file << "#include <string>\n\n";
	}

};


