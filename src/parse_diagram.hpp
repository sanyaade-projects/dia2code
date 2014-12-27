/*
This file is part of dia2code. It generates code from an UML Dia Diagram.
Copyright (C) 2000-2014 Javier O'Hara

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef PARSE_DIAGRAM_HPP
#define PARSE_DIAGRAM_HPP

#include "config.h"

#include <list>
#include <string>

#include "umlAttribute.hpp"

void parseDiaNode (xmlNodePtr stringnode, std::string &buffer);
bool parseBoolean (xmlNodePtr booleannode);
void parseAttributes (xmlNodePtr node, std::list <umlAttribute> &retour);
void parseDiaString (const char * stringnode, std::string &buffer);
void recursiveSearch (xmlNodePtr node, xmlNodePtr * object);
xmlNodePtr getNextObject (xmlNodePtr from);
void parseTemplates (xmlNodePtr node,
                      std::list <std::pair <std::string, std::string> > &res);

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
