#pragma once

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <variant>
#include <vector>

class ReadInput
{
private:
	enum class DataType { BOOL, INT, FLOAT, STRING };
	DataType m_fileType;
	uint64_t m_lineCount;
	const std::string m_filename;
public:
	ReadInput(const std::string& filename)
		: m_filename(filename),
		m_lineCount(0),
		m_fileType(DataType::BOOL)
	{
		std::ifstream file{ m_filename };
		
		if (file.is_open()) [[likely]]
		{
			std::string line;
			while (file.good())
			{
				getline(file, line);
				m_lineCount++;
				m_fileType = GetLineType(line, m_fileType);
			}
			std::cout << "\t" << m_filename << "\n";
		}
		else [[unlikely]]
		{
			std::cout << "ERROR: ReadInput() failed\n";
			std::cout << "INFO: Unable to access -> " << m_filename << "\n";
			exit(1);
		}
		file.close();
	}
	auto line_count() const { return m_lineCount; }
	auto file_name() const { return m_filename; }
	auto file_type() const {
		switch (m_fileType)
		{
		case DataType::BOOL:
			return std::string{ "bool" };
		break; case DataType::INT:
			return std::string{ "int" };
		break; case DataType::FLOAT:
			return std::string{ "float" };
		break; case DataType::STRING:
			return std::string{ "std::string" };
		break; default:
			return std::string{ "undefined" };
		break;
		}
	}
	auto get_data()
	{
		std::vector<std::string> data;
		data.reserve(m_lineCount);

		std::ifstream file{ m_filename };
		if (file.is_open()) [[likely]]
		{
			std::string line;
			while (file.good())
			{
				getline(file, line);
				data.emplace_back(line);
			}
			file.clear();
			file.seekg(0);
		}
		else [[unlikely]]
		{
			std::cout << "ERROR: Invalid file name\n";
			exit(1);
		}
		file.close();
		return data;
	}

private:
	auto GetLineType(const std::string &input, const DataType fileType) -> DataType
	{
		auto current_type = fileType;
		for (const auto& character : input)
		{
			switch (current_type)
			{
			case DataType::BOOL:
				if (character == '0' || character == '1') {
					//NOTHING
				}
				else if(character >= '0' && character <= '9') {
					current_type = DataType::INT;
				}
				else if(character == '.') {
					current_type = DataType::FLOAT;
				}
				else {
					current_type = DataType::STRING;
				}
			break; case DataType::INT:
				if (character >= '0' && character <= '9') {
					//NOTHING
				}
				else if (character == '.') {
					current_type = DataType::FLOAT;
				}
				else {
					current_type = DataType::STRING;
				}
			break; case DataType::FLOAT:
				if (character >= '0' && character <= '9') {
					//NOTHING
				}
				else if (character == '.') {
					//NOTHING
				}
				else {
					current_type = DataType::STRING;
				}
			break; case DataType::STRING:
				//NOTHING
			break;
			}
		}

		return current_type;
	}
};


