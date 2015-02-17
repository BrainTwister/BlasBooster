#include "BlasBooster/Core/BlockSizeGenerator.h"

namespace BlasBooster {

std::vector<size_t> generateBlockSizeList(size_t nbElements, size_t blockSize, BehaviorOfRemainingElements behaviorOfRemainingElements)
{
	size_t nbBlocks = nbElements / blockSize;
	size_t nbRemainingElements = nbElements % blockSize;

	std::vector<size_t> blockSizeList(nbBlocks);

	if (nbRemainingElements) {
		if (behaviorOfRemainingElements == SymmetricDistribution) {
			size_t nbElementsPerBlock = blockSize + nbRemainingElements / nbBlocks;
			size_t nbRemainingElements2 = nbRemainingElements % nbBlocks;
			fill_n(blockSizeList.begin(),nbRemainingElements2,nbElementsPerBlock + 1);
			fill(blockSizeList.begin() + nbRemainingElements2,blockSizeList.end(),nbElementsPerBlock);
	    } else if (behaviorOfRemainingElements == ExtraBlockAtTheEnd) {
	    	fill(blockSizeList.begin(),blockSizeList.end(),blockSize);
	    	blockSizeList.push_back(nbRemainingElements);
	    }
	} else {
		fill(blockSizeList.begin(),blockSizeList.end(),blockSize);
	}

	return blockSizeList;
}

} // namespace BlasBooster
