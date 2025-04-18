#include <iostream>

#include "Org.h"
#include "emp/base/vector.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "World.h"

// This is the main function for the NATIVE version of this project.

int main(int argc, char* argv[])
{

  emp::Random random(2);
  OrgWorld world{random};

  emp::Random random_gen_2(5);
  OrgWorld world_2{random_gen_2};

  Organism* new_org = new Organism(&random);
  world.Inject(*new_org);

  world.Resize(10, 10);

  std::cout << world.GetNumOrgs() << std::endl;

  // Calls Update to make sure it's working
  for (int i = 0; i < 10; i++){
    world.Update();
  }

  std::cout << world.size() << std::endl;
  std::cout << world.GetNumOrgs() << std::endl;

}
