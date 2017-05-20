/*
 * Snippet.cpp
 *
 *  Created on: May 20, 2017
 *      Author: thepunchy
 */

#include "Snippet.h"

namespace snippets {

Snippet::Snippet(std::string snippet, TermBag bag) :
		snippet(snippet),
		TF(bag)
{
}

const std::string& Snippet::getSnippet() {
	return snippet;
}

SnippetTermFrequency& Snippet::getTF() {
	return TF;
}

Snippet::~Snippet() {
}

} /* namespace snippets */
