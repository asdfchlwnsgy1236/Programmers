// URL: https://programmers.co.kr/learn/courses/30/lessons/12974

#include <map>
#include <set>
#include <utility>
#include <vector>
// Note: The headers below are for testing without using the site.
#include <iomanip>
#include <iostream>
#include <random>

// TODO: Score of 69.7% (23/23 correctness tests, 0/5 efficiency tests); not sure how to improve the efficiency.

using vecint = std::vector<int>;

struct CompareX{
	bool operator()(vecint const *a, vecint const *b) const{
		return (*a)[0] == (*b)[0] ? (*a)[2] == (*b)[2] ? (*a)[1] == (*b)[1] ?
			(*a)[3] < (*b)[3] : (*a)[1] < (*b)[1] : (*a)[2] < (*b)[2] : (*a)[0] < (*b)[0];
	}
};

struct CompareY{
	bool operator()(vecint const *a, vecint const *b) const{
		return (*a)[1] == (*b)[1] ? (*a)[3] == (*b)[3] ? (*a)[0] == (*b)[0] ?
			(*a)[2] < (*b)[2] : (*a)[0] < (*b)[0] : (*a)[3] < (*b)[3] : (*a)[1] < (*b)[1];
	}
};

long long solution(std::vector<vecint> rectangles){
	// Gather all points to visit on the x axis.
	std::map<int, std::set<vecint const *, CompareX>> xs;
	for(auto const &rect : rectangles){
		xs[rect[0]].insert(&rect);
		xs[rect[2]].insert(&rect);
	}

	// Visit each point on the x axis gathered above.
	std::set<vecint const *, CompareY> ys;
	int oldx = -1;
	long long answer = 0;
	for(auto xit = xs.begin(); xit != xs.end(); ++xit){
		// Calculate the total height of all rectangles containing within the current x interval, and add the area from it.
		if(int width = xit->first - oldx; width && !ys.empty()){
			int height = 0, y1 = -1, y2 = -1;
			for(auto yit = ys.begin(); yit != ys.end(); ++yit){
				int const ty1 = (**yit)[1], ty2 = (**yit)[3];
				if(ty1 <= y2){
					y2 = std::max(y2, ty2);
				}
				else{
					height += y2 - y1;
					y1 = ty1;
					y2 = ty2;
				}
			}
			height += y2 - y1;
			answer += static_cast<long long>(width) * height;
		}

		// Add the rectangles that begin at the current point, and then remove the rectangles that end at the current point.
		ys.insert(xit->second.begin(), xit->second.end());
		oldx = xit->first;
		for(auto yit = ys.begin(); yit != ys.end();){
			(**yit)[2] == oldx ? yit = ys.erase(yit) : ++yit;
		}
	}

	return answer;
}

// Note: Everything below this line is for testing without using the site.
long long bruteforce(std::vector<vecint> rectangles){
	int matrix[16][16]{};
	for(auto const &a : rectangles){
		for(int b = a[1]; b < a[3]; ++b){
			for(int c = a[0]; c < a[2]; ++c){
				matrix[b][c] = 1;
			}
		}
	}
	long long answer = 0;
	for(auto const &a : matrix){
		for(auto const &b : a){
			answer += b;
		}
	}

	return answer;
}

int main(){
	//std::vector<std::vector<vecint>> problems{{{0, 1, 4, 4}, {3, 1, 5, 3}},
	//	{{1, 1, 6, 5}, {2, 0, 4, 2}, {2, 4, 5, 7}, {4, 3, 8, 6}, {7, 5, 9, 7}}};
	//for(auto const &problem : problems){
	//	std::cout << solution(problem) << '\t' << bruteforce(problem) << '\n';
	//}

	std::vector<std::vector<vecint>> rproblems;
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> udn(2, 10), udc(0, 16);
	for(int a = 0; a < 256; ++a){
		std::vector<vecint> t0;
		for(int b = 0, n = udn(rng); b < n; ++b){
			vecint t1;
			for(int c = 0; c < 4; ++c){
				t1.push_back(udc(rng));
			}
			if(t1[0] > t1[2]){
				std::swap(t1[0], t1[2]);
			}
			else if(t1[0] == t1[2]){
				t1[0] == 16 ? --t1[0] : ++t1[2];
			}
			if(t1[1] > t1[3]){
				std::swap(t1[1], t1[3]);
			}
			else if(t1[1] == t1[3]){
				t1[1] == 16 ? --t1[1] : ++t1[3];
			}
			t0.push_back(std::move(t1));
		}
		rproblems.push_back(std::move(t0));
	}
	for(auto const &a : rproblems){
		long long mine = solution(a), correct = bruteforce(a);
		std::cout << "rectangles: " << a.size() << " / my solution: " << solution(a) << " / brute-force solution: " << bruteforce(a) << '\n';
		if(mine != correct){
			for(auto const &b : a){
				for(auto const &c : b){
					std::cout << std::left << std::setw(4) << c;
				}
				std::cout << '\n';
			}
		}
	}

	//std::vector<vecint> problem{{13, 5, 15, 10}, {2, 14, 10, 15}, {2, 2, 10, 6}, {1, 3, 14, 4}, {5, 2, 15, 3}};
	//std::cout << "my solution: " << solution(problem) << " / brute-force solution: " << bruteforce(problem) << '\n';

	return 0;
}
