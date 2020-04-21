//https://www.stmintz.com/ccc/index.php?id=141612
#include <vector>
#include <string>
#include <atomic>
#include "position.h"

class UCI {
 public:
	static void run();
 private:
	static Position* pos;
	static bool debug;
	static void position(const std::vector<std::string>&);
	static void go(const std::vector<std::string>&);
};

int indexOf(std::vector<Move>&, const std::string&);
