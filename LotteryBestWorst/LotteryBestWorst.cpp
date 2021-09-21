// URL: https://programmers.co.kr/learn/courses/30/lessons/77484

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using vecint = std::vector<int>;

vecint solution(vecint lottos, vecint win_nums){
	// Use sets for convenient element searches.
	std::multiset<int> ls(lottos.begin(), lottos.end());
	std::set<int> wns(win_nums.begin(), win_nums.end());

	// Remove all matching numbers.
	for(auto it = ls.begin(); it != ls.end();){
		*it && wns.count(*it) ? it = ls.erase(it) : ++it;
	}

	// The worst rank is the number of unmatched numbers plus 1, and the best rank is the worst rank minus the number of zeros.
	return vecint{std::min(6, static_cast<int>(1 + ls.size() - ls.count(0))), std::min(6, static_cast<int>(1 + ls.size()))};
}

// Note: Everything below this line is for testing without using the site.
int main(){
	std::vector<std::vector<vecint>> problems{{{44, 1, 0, 0, 31, 25}, {31, 10, 45, 1, 6, 19}},
		{{0, 0, 0, 0, 0, 0}, {38, 19, 20, 40, 15, 25}},
		{{45, 4, 35, 20, 3, 9}, {20, 9, 3, 45, 4, 35}}};
	for(auto const &problem : problems){
		auto const &answer = solution(problem[0], problem[1]);
		std::cout << answer[0] << ' ' << answer[1] << '\n';
	}

	return 0;
}
