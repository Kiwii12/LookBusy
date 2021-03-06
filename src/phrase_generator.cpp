#include "phrase_generator.h"

#include "flat_list_parser.h"

#include <cstdlib>
#include <ctime>
#include <fstream>

phrase_generator::phrase_generator()
  : actions(), adjectives(), nouns(), jokes()
{
  std::srand(std::time(0));
}

phrase_generator::~phrase_generator()
{
  // Nothing else to do
}

phrase_generator& phrase_generator::load_action_strings(std::string filename)
{
  load_strings(filename, actions);
  return *this;
}

phrase_generator& phrase_generator::load_adjective_strings(std::string filename)
{
  load_strings(filename, adjectives);
  return *this;
}

phrase_generator& phrase_generator::load_noun_strings(std::string filename)
{
  load_strings(filename, nouns);
  return *this;
}

phrase_generator& phrase_generator::load_joke_strings(std::string filename)
{
  load_strings(filename, jokes);
  return *this;
}

std::string phrase_generator::generate_phrase()
{
  int r = std::rand();
  std::string s = "";
  
  if (r % 20 == 0)
  {
    // 1:20 chance to use an easter egg
    s = jokes.next();
  }
  else
  {
    // 19:20 chance to use random arrangement of words
    s = actions.next();
    
    if (std::rand() % 3 == 0)
    {
      // 1:3 chance to add an adjective
      s += " " + adjectives.next();
    }
    
    s += " " + nouns.next();
  }
  
  return s;
}

bool phrase_generator::load_strings(std::string filename, list_randomizer& randomizer)
{
  // Open new file using filename
  std::ifstream in;
  in.open(filename);
  
  // Verify file opened successfully
  if (!in.good()) return false;
  
  std::vector<std::string> strings;
  std::string s;
  flat_list_parser parser(in);
  
  while (parser.next(s))
  {
    strings.push_back(s);
  }
  
  randomizer.set_list_contents(strings);
  randomizer.shuffle();
  
  in.close();
  return true;
}
