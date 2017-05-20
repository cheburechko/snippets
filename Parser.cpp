/*
 * Parser.cpp
 *
 *  Created on: May 20, 2017
 *      Author: thepunchy
 */

#include "Parser.h"

namespace snippets {

Parser::sentenceEnds = {
		'.','!','?'
};

Parser::delimiters = {
		'\"', '#', '$', '%', '&', '\'', '(', ')', '*', '+',
		',', '/', ':', ';', '<', '>', '=', '@', '[', ']',
		'^', '\`', '{', '}', '|', '~', ' ', '\t', '\r', '\n'
};

Parser::Parser() :
	textPos(0),
	snippetPos(0),
	snippet(""),
	term(""),
	finishedSnippet(false),
	finishedText(false),
	text(nullptr)
{
}


void Parser::initSnippet(const std::string& snippet) {
	this -> snippet = snippet;
	finishedSnippet = false;
	for (snippetPos = 0; snippetPos <= snippet.size(); snippetPos++) {
		if (delimiters.find(snippet[snippetPos]) == delimiters.end()) {
			break;
		}
	}
}


void Parser::nextSnippet() {
	int nextPos = textPos;
	bool lookingForSnippetEnd = false;
	for (; nextPos < text->size(); nextPos++) {
		// Look for [.?!], then take into account '...|?!'
		if (!lookingForSnippetEnd &&
			sentenceEnds.find((*text)[nextPos]) != sentenceEnds.end()) {
			lookingForSnippetEnd = true;
		} else if (
			lookingForSnippetEnd &&
			sentenceEnds.find((*text)[nextPos]) != sentenceEnds.end()
		) {
			lookingForSnippetEnd = false;
			break;
		}
	}
	finishedText = nextPos == text->size();
	initSnippet(text->substr(textPos, nextPos-textPos));
	textPos = nextPos;
}


void Parser::nextTerm() {
	int nextPos = snippetPos;
	int termLength = 0;
	bool lookingForDelimeterEnd = false;
	for (; nextPos < snippet.size(); nextPos++) {
		if (!lookingForDelimeterEnd &&
			delimiters.find(snippet[nextPos]) != delimiters.end()) {
			lookingForDelimeterEnd = true;
			termLength = nextPos-snippetPos;
		} else if (
			lookingForDelimeterEnd &&
			delimiters.find(snippet[nextPos]) == delimiters.end()
		) {
			lookingForDelimeterEnd = false;
			break;
		}
	}
	if (lookingForDelimeterEnd) {
		termLength = nextPos-snippetPos;
	}
	finishedSnippet = nextPos >= snippet.size();
	term = snippet.substr(snippetPos, termLength);
	snippetPos = nextPos;
}


TermBag Parser::getTermBag() {
	TermBag result;
	while (!finishedSnippet) {
		nextTerm();
		if (term != "") {
			result.push_back(term);
		}
	}
	return result;
}


TermBag Parser::getTermBag(std::string snippet) {
	initSnippet(snippet);
	return getTermBag();
}

TermSet Parser::getTermSet(std::string snippet) {
	TermSet result;
	initSnippet(snippet);
	while (!finishedSnippet) {
		nextTerm();
		if (term != "") {
			result.emplace(term);
		}
	}
	return result;
}

void Parser::parse(const std::string& text, SnippetStorage& snippets,
		TermDatabase& terms) {
	this->text = &text;
	textPos = 0;
	finishedText = false;
	while (!finishedText) {
		nextSnippet();
		TermBag bag = getTermBag();
		if (bag.size() == 0) {
			continue;
		}

		Snippet snipObj = Snippet(snippet, bag);
		snippets.push_back(snipObj);

		TermSet set(bag);
		const SnippetTermFrequency& TF = snipObj.getTF();
		for (Term term : set) {
			auto termData = terms.find(term);
			if (termData == terms.end()) {
				termData = terms.emplace(term, TermData(term));
			}
			termData->second.addSnippet(snippets.size()-1, TF.getTF(term));
		}
	}

	for (auto snipObj : snippets) {
		snipObj.getTF().applyIDF(terms);
	}
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

} /* namespace snippets */
