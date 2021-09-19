// URL: https://programmers.co.kr/learn/courses/30/lessons/77484

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

std::vector<int> solution(std::vector<int> lottos, std::vector<int> win_nums){
	std::multiset<int> ls(lottos.begin(), lottos.end());
	std::set<int> wns(win_nums.begin(), win_nums.end());
	for(auto it = ls.begin(); it != ls.end();){
		*it && wns.count(*it) ? it = ls.erase(it) : ++it;
	}

	return std::vector<int>{std::min(6, static_cast<int>(1 + ls.size() - ls.count(0))), std::min(6, static_cast<int>(1 + ls.size()))};
}

int main(){
	std::vector<std::vector<std::vector<int>>> problems{{{44, 1, 0, 0, 31, 25}, {31, 10, 45, 1, 6, 19}},
		{{0, 0, 0, 0, 0, 0}, {38, 19, 20, 40, 15, 25}},
		{{45, 4, 35, 20, 3, 9}, {20, 9, 3, 45, 4, 35}}};
	for(auto const &problem : problems){
		auto const &answer = solution(problem[0], problem[1]);
		std::cout << answer[0] << ' ' << answer[1] << '\n';
	}

	return 0;
}
