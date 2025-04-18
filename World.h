#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Org.h"

class OrgWorld : public emp::World<Organism> {

    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;

    public:

    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    ~OrgWorld() {
    }

  void Update() {
    double pointsPerUpdate = 100;

    emp::World<Organism>::Update();

    emp::vector<size_t> schedule1 = emp::GetPermutation(random, GetSize());
    emp::vector<size_t> schedule2 = emp::GetPermutation(random, GetSize());

    for (int i :schedule1){
        if(IsOccupied(i)){
            pop[i]->Process(pointsPerUpdate);
        }
    }

    for (int i : schedule2){
        if(IsOccupied(i)){
            emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
            if (offspring){
                DoBirth(*offspring, i);
            }
        }
    }
}

    emp::Ptr<Organism> ExtractOrganism(int orgPos){
        emp::Ptr<Organism> extracted_org = pop[orgPos];
        pop[orgPos] = nullptr;

        emp::WorldPosition newPosition = GetRandomNeighborPos(orgPos);
        AddOrgAt(extracted_org, newPosition);
    }

};
#endif