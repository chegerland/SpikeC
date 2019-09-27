#include <iostream>

#include "filetools.h"
#include "options.h"

// program options
#include <boost/program_options.hpp>
namespace po = boost::program_options;

// get options from command line
void get_options(int argc, char * argv[], Options *options)
{
  try
  {
		// List all options and their description
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help,h", "Help screen")
    ("mode", po::value<int>(&(options->mode)), "Mode \n 0 = Simulation, 1 = Evaluation, 2 = Curves")
    ("file", po::value<std::string>(&(options->parameters)), "Input File")
    ("rate", po::value<double>(&(options->dt)), "Calculates firing rate")
    ("isi", po::bool_switch(&(options->isi)), "Calculates interspike intervals");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

		// if the help option is given, show the flag description
    if (vm.count("help"))
    {
      std::cout << desc << std::endl;
      exit(0);
    };

    // set rate to true if dt is given
    if (vm.count("rate"))
    {
      options->rate = true;
    };
  }
  catch(std::exception& e)
  {
    std::cerr << "error: " << e.what() << std::endl;
  }
};

// check the command line options
void check_options(Options *options)
{
		// get command line options from struct
		int mode = options->mode;
		std::string parameters = options->parameters;

		// check if file extension is right
    if ( mode == 0 )
    {
			// input file should be .json
      if ( getFileExtension(parameters) != ".json" )
      {
        std::cerr << "Input file must have extension .json!" << std::endl;
        exit(0);
      }

			// check if output file already exists
			std::string output_file = parameters.substr(0,parameters.find_last_of('.'))+".out";
			if ( exists(output_file) )
			{
				char input;
				std::cout << "Output file \"" << output_file << "\" already exists!\n"
									<< "Overwrite file? [y/n]" << std::endl;
				std::cin >> input;

				if ( input == 'n' )
				{
					exit(0);
				};
			};

    }
    else if ( mode == 1 )
    {
      std::cout << "Evaluation mode.\n" << std::endl;
			// Evaluation mode needs .out
      if ( getFileExtension(parameters) != ".json" )
      {
        std::cerr << "Input file must have extension .json!" << std::endl;
        exit(0);
      };

			// check if output file exists
			std::string output_file = parameters.substr(0,parameters.find_last_of('.'))+".out";
			if ( !exists(output_file) )
			{
				std::cout << "Spike times file \"" << output_file << "\" does not exist!\n";
				exit(0);
			};
    }
    else if ( mode == 2 )
    {
      std::cout << "Pretty curves mode.\n" << std::endl;
			// curves mode needs .out
      if ( getFileExtension(parameters) != ".json" )
      {
        std::cerr << "Input file must have extension .json!" << std::endl;
        exit(0);
      };
    }
    else
    {
			// if mode != 0 or 1, show error
      std::cerr << "Unknown mode. Please choose 0 (simulation) or 1 (evaluation)." << std::endl;
      exit(0);
    };
};
