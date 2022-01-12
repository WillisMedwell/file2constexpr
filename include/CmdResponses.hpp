#include <string>
#include <iostream>
#include <algorithm>


namespace CmdResponses
{
	const std::string default_name = {"output.h"};
	const std::string default_outDir = { "include" };
	const std::string default_inDir = { "src\\constexpr" };

	constexpr char help[] = {
			"PURPOSE:\n"
			"\tAs there is no way to read files at compile time, this program converts input files to constexpr arrays.\n"
			"EXPECTED PROJECT STRUCTURE:\n"
			"\t\\build\n"
			"\t\\include\n"
			"\t\\src\\constexpr\n"
			"HOW TO USE:\n"
			"\tCall \"file2constexpr ..\" within build folder.\n"
			"\tNOTE:: Files are read from the \"constexpr\" folder, and a header file (\"output.h\") is generated within the \"\\include\" folder.\n"
			"COMMANDS:\n"
			"\t--name()\t\"--name()\" changes the output file name\n"
			"\t--inDir()\t\"--inDir()\" changes the input directory\n"
			"\t--outDir()\t\"--outDir()\" changes the output directory\n"
			"\t.. \t\t\"..\" calls the program in the directory above the current one\n"
		};
	constexpr char name_info[] = {
			"--name()\n"
			"\tThe default header file name is \"output.h\"\n"
			"\tIf i want the name of the output file to be \"example.hpp\",\n"
			"\tUse the cmd \"--name(example.hpp)\"\n"
		};
	constexpr char outdir_info[] = {
			"--outDir()\n"
			"\tThe default directory is \"\\include\"\n"
			"\tExample project below:\n"
			"\t\t\\headers\\more_headers\n"
			"\t\t\\include\n"
			"\t\t\\src\\constexpr\n"
			"\tIf my project looked like this and i wanted to save my output to the \"\\headers\\more_headers\" folder,\n"
			"\tUse the cmd \"--outDIr(headers\\more_headers)\n"
		};
	constexpr char indir_info[] = {
			"--inDir()\n"
			"\tThe default directory is \"\\src\\constexpr\"\n"
			"\tExample project below:\n"
			"\t\t\\input\\more_input\n"
			"\t\t\\include\n"
			"\t\t\\src\\constexpr\n"
			"\tIf my project looked like this and i wanted the files from \"\\input\\more_input\" folder,\n"
			"\tUse the cmd \"--inDIr(input\\more_input)\n"
		};

	struct CmdRequirements
	{
		std::string name{ default_name };
		std::string inDir{ default_inDir };
		std::string	outDir{ default_outDir };
		bool goUpDir{ false };
	};
	auto InterpretArguments(int argc, char* argv[]) -> CmdRequirements
	{
		CmdRequirements cmdR{};
		//No cmds, therefore defaults can be returned.
		if (argc == 1) {
			return cmdR;
		}
		for (size_t i = 1; i < argc; i++)
		{
			std::string arg { argv[i] };
			if ( arg == "--help") {
				std::cout << help;
			}
			else if(arg == "--name()") {
				std::cout << std::string(name_info);
			}
			else if (arg == "--inDir()") {
				std::cout << std::string(indir_info);
			}
			else if (arg == "--outDir()") {
				std::cout << std::string(outdir_info);
			}
			else if (arg.substr(0, 3) == "--n")
			{
				cmdR.name = arg.substr(arg.find('\(')+1, arg.size());
				cmdR.name = cmdR.name.substr(0, cmdR.name.find_first_of('\)'));
			}
			else if (arg.substr(0, 3) == "--i")
			{
				cmdR.inDir = arg.substr(arg.find('\(')+1, arg.size());
				cmdR.inDir = cmdR.inDir.substr(0, cmdR.inDir.find_first_of('\)'));
			}
			else if (arg.substr(0, 3) == "--o")
			{
				cmdR.outDir = arg.substr(arg.find('\(')+1, arg.size());
				cmdR.outDir = cmdR.outDir.substr(0, cmdR.outDir.find_first_of('\)'));
			}
			else if (arg == "..")
			{
				cmdR.goUpDir = true;
			}
			else
			{
				std::cout << "ERROR: invalid argument\n";
				std::cout << "INFO: the argument:" << arg <<" is not allowed here... Try cmd --help";
			}
		}
		return cmdR;
	}
}