#include <map>
#include <string>

class Enemy {
	std::string path;	
	std::map<int, int> y_src;
	std::map<int, int> heights;
	std::map<int, std::map<int, int>> widths;
	
	

public:
	Enemy(int enemy);
	
	std::string getPath();
	
	int getYsrc(int mov_type);

	std::map<int, int>::iterator widthSrc(int mov_type, int num_mov);

	int	heightSrc(int mov_type);
	
};
