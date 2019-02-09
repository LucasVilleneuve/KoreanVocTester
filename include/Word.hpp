//
// Created by Lucas on 30-Jan-19.
//

#ifndef KOREANVOCTESTER_WORD_HPP
#define KOREANVOCTESTER_WORD_HPP

#include <string>
#include <utility>

enum WordType
{
	UNKNOWN = 0,
	VERB,
	MISC
};

struct Word
{
	std::string	word;
	std::string	translation;
	WordType	type = UNKNOWN;

	Word() = default;
	Word(std::string w, std::string trans, WordType t)
	 : word(std::move(w)), translation(std::move(trans)), type(t)
	{
	}
};

#endif //KOREANVOCTESTER_WORD_HPP
