#pragma once

std::vector<char> generatPossibleCharVectorNEW();
std::string* CrackNEW2(int cycle, int& indexJ, int& indexN, const std::vector<char>& chars, std::string* bunch_pass_candidates, std::vector<std::string>& all_tried_pass_m, int& indexI, bool& big_loop_end, int& indexT, bool& start_first);
std::vector<char>  generatPossibleCharVectorForDebug();
