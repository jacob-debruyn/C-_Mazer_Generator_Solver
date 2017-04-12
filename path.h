#include <vector>
#include "cell.h"

	class Path {
		std::list<Cell*> pathWay;

		public:
			Path(){};
			void addPath(Cell * cell){
				pathWay.insert(pathWay.end(), cell);
			};
	};

#endif