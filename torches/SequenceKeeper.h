#pragma once

#include <vector>

template<class T>
class SequenceKeeper
{
public:
	SequenceKeeper();	// rand range 3 - 10, initializes the sequence
	SequenceKeeper(int range);	// range 3 - 10, also initializes the sequence
	~SequenceKeeper();
	std::vector<T>& GetSequence() const;	// return m_Sequence
	void GenerateSequence();	// randomize a new set of sequence
private:
	int range;	// m_Sequence size
	std::vector<T> m_Sequence;
};

// DO include <stdlib.h> in SequenceKeeper.cpp
// DO NOT include <time.h> in SequenceKeeper.cpp