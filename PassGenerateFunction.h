#pragma once

std::vector<char> generatPossibleCharVectorNEW();

std::string* generatePasswordVariant(int cycle, int& indexJ, int& indexN, const std::vector<char>& chars, std::string* bunch_pass_candidates, int& indexI, bool& big_loop_end, int& indexT, bool& start_first);

