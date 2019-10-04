#include <iostream>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "PIF.h"

// constructor for a pif neuron
PIF::PIF(double a, double b)
{
  mu = a;
  D = b;
};

// pif constructor from .json file
PIF::PIF(std::string input_file)
{
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read simulation data into simulation variables
  mu = root.get<double>("Neuron.mu");
  D = root.get<double>("Neuron.D");
};

// drift of a PIF neuron
double PIF::drift(double v, double t) const
{
  return mu;
};

// analytic function of the firing rate
double PIF::rate_analytic() const
{
  return mu;
};

// print neuron parameters
void PIF::print_parameters()
{
  std::cout << "Neuron (PIF) parameters: \n"
  << "mu = "     << mu << "\n"
  << "D = "      << D << "\n"
  << std::endl;
};