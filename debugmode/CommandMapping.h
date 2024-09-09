/*
 WIP still, 8.28
 Maybe this will be done in the winter vacation.
 Obseleted because I wanna change to C++
*/
#ifndef H_COMMANDMAPPING
#define H_COMMANDMAPPING
#include <stdlib.h>
struct cm_CommandMapping {
	char *command;
	int id;
};
struct cm_MapsIndex {
	int count;
	int nextIndex;
};
static int _cm_firstAvailable = 0;
static int _cm_index = 0;
static struct cm_MapsIndex **_cm_mapsIndexs;
static struct cm_CommandMapping **_cm_mapsArrays;

/* Explanation
 To allocate memory dynamically, I use a point point.
 Because a point nearly equals a array in fact.
 Points always occupy 8 bytes so I just need a index,
 And every point the point point points points to an unfixed length's heap
 memory.
 */
void cm_allocate(int count) {  // NOLINT
	_cm_mapsIndexs[_cm_index] = (struct cm_MapsIndex*) malloc(
			sizeof(struct cm_MapsIndex));
	_cm_mapsIndexs[_cm_index]->count = count;
	if (!_cm_index)
		_cm_mapsIndexs[_cm_index - 1]->nextIndex = _cm_index;
	_cm_mapsIndexs[_cm_index]->nextIndex = -1;
	_cm_mapsArrays[_cm_index] = (struct cm_CommandMapping*) malloc(
			sizeof(struct cm_CommandMapping) * count);
	++_cm_index;
}
// For debug usage
void cm_heapDelete(int index) {  // NOLINT
	if (index < _cm_firstAvailable)
		return;
	if (index == _cm_firstAvailable)
		_cm_firstAvailable = _cm_mapsIndexs[_cm_firstAvailable]->nextIndex;
	else
		_cm_mapsIndexs[index - 1]->nextIndex = index + 1;
	free(_cm_mapsArrays[index]);
	free(_cm_mapsIndexs[index]);
}
// countIndex means which one instead of mapsIndex
struct cm_CommandMapping cm_get(int countIndex) {  // NOLINT
	int currentIndex = _cm_firstAvailable, total = 0, lastTotal = 0;
	while (currentIndex != -1) {
		total += _cm_mapsIndexs[currentIndex]->count;
		if (countIndex < total)
			return *(_cm_mapsArrays[total - lastTotal]);
		lastTotal = total;
		currentIndex = _cm_mapsIndexs[currentIndex]->nextIndex;
	}
	struct cm_CommandMapping tmp;
	tmp.id = -1;
}
// GC for debug
void _cm_autoclean() {
	
}

#endif
