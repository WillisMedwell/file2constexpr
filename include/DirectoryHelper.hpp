#pragma once

#include <string>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <ranges>


class DirectoryHelper
{
private: // variables
	const std::string m_working_dir;
	std::string m_current_dir;
private: // member functions
	auto move_up_dir(const std::string& path)
		{
			return path.substr(0, path.find_last_of("\\"));
		}
	auto move_into_dir(const std::string& path, const std::string& folder)
	{
		if (!std::filesystem::exists(path + "\\" + folder)) [[unlikely]]
		{
			std::cout << "ERROR: cd() changing directory failed.\n";
			std::cout << "INFO: The directory -> " << path + "\\" + folder << " does not exist.\n";
			exit(1);
		}
		return path + "\\" + folder;
	}
	auto print_dir(const std::string& path)
		{
			const auto dir = std::filesystem::path{path};
			std::cout << path << "\n";
			for (auto& i : std::filesystem::directory_iterator(dir))
			{
				std::cout << i.path().string() << '\n';
			}
		}
	auto get_dir_files(const std::string& path) -> std::vector<std::string>
	{
		namespace fs = std::filesystem;
		std::vector<std::string> files;

		const auto dir = fs::path{ path };
		for (auto& i : fs::directory_iterator(dir))
		{
			if (i.is_regular_file()) {
				files.emplace_back(i.path().string());
			}
		}
		return files;
	}
public: //member functions
	DirectoryHelper()
		: 
		m_working_dir(std::filesystem::current_path().string()),
		m_current_dir(m_working_dir)
	{}
	/*
		Used to change directories.
		2 Types of commands:
		".." == move current directory up.
		"ABC"== move current directory into folder /ABC.
	*/
	auto cd(const std::string& cmd)
	{
		if (cmd == "..") {
			m_current_dir = move_up_dir(m_current_dir);
		}
		else {
			m_current_dir = move_into_dir(m_current_dir, cmd);
		}
	}
	auto print_current_dir()
	{
		print_dir(m_current_dir);
	}
	auto print_current_dir_files()
	{
		for (const auto& file : get_current_dir_files()) {
			std::cout << file << "\n";
		}
	}
	auto get_current_dir() const { return m_current_dir; }
	auto get_current_dir_files() -> std::vector<std::string>
	{
		return get_dir_files(m_current_dir);
	}

	auto print_working_dir()
	{
		print_dir(m_working_dir);
	}
	auto print_working_dir_files()
	{
		for (const auto& file : get_working_dir_files()) {
			std::cout << file << "\n";
		}
	}
	auto get_working_dir() const { return m_working_dir; }
	auto get_working_dir_files() -> std::vector<std::string>
	{
		return get_dir_files(m_working_dir);
	}


};