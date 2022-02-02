#include <string>
#include <vector>
#include <filesystem>

#include "ReadInput.hpp"
#include "WriteHeader.hpp"
#include "DirectoryHelper.hpp"
#include "CmdResponses.hpp"

auto GetInfileNames(const CmdResponses::CmdRequirements&) -> std::vector<std::string>;
auto GetOutfilePath(const CmdResponses::CmdRequirements&) -> std::string;
auto GenerateHeaderFile(const std::vector<std::string>&, const std::string&, const std::string&) -> void;

int main(int argc, char* argv[])
{
	const auto cmdOptions  = CmdResponses::InterpretArguments(argc, argv);
	const auto infileNames = GetInfileNames(cmdOptions);
	const auto outfilePath = GetOutfilePath(cmdOptions);
	const auto outfileName = cmdOptions.name;

	GenerateHeaderFile(infileNames, outfilePath, outfileName);

	return 0;
}

auto GetInfileNames(const CmdResponses::CmdRequirements& requirements) -> std::vector<std::string>
{
	DirectoryHelper dir;
	if (requirements.goUpDir) {
		dir.cd("..");
	}
	dir.cd(requirements.inDir);
	return dir.get_current_dir_files();
}

auto GetOutfilePath(const CmdResponses::CmdRequirements& requirements) -> std::string
{
	DirectoryHelper dir;
	if (requirements.goUpDir) {
		dir.cd("..");
	}
	dir.cd(requirements.outDir);
	return dir.get_current_dir();
}

auto GenerateHeaderFile(
	const std::vector<std::string>& infileNames,
	const std::string& outfilePath,
	const std::string& outfileName) -> void
{
	WriteHeader fileOut{ outfilePath + '\\' + outfileName };
	std::cout << "Reading Files...\n";
	for (const auto& infileName : infileNames)
	{
		ReadInput infile{ infileName };
		fileOut.write_array(infile.file_type(), infile.get_data(), infile.file_name());
	}
}
