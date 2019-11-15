#pragma once

#include <stdlib.h>
#include <queue>


class SequenceKeeper
{
public:
	SequenceKeeper();	// rand range 3 - 10, initializes the sequence
	SequenceKeeper(int range);	// range 3 - 10, also initializes the sequence
	~SequenceKeeper();
	int GetSequence(int index);	// return m_Sequence
	void SetSequenceAt(int index, int data);	// set m_Sequence[index] = data, used with GenerateSequence() in Monster
	int GetRange();
private:
	int m_Range;	// m_Sequence size
	std::vector<int> m_Sequence;
};