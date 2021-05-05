#include "Manager.h"


void Manager::Setup(std::shared_ptr <Queue> &tasq, std::shared_ptr <Queue> &resq) {}

void Manager::WorkCycle() {}

void Manager::SetBuilder(std::unique_ptr<GABuilder> &builder) {}

const Result * Manager::work(std::string, std::string, std::string, std::string) {}