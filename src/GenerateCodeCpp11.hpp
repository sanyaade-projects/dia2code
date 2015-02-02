/*
This file is part of dia2code. It generates code from an UML Dia Diagram.
Copyright (C) 2014-2014 Javier O'Hara - Oliver Kellogg

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


#ifndef GENERATE_CODE_CPP11_HPP
#define GENERATE_CODE_CPP11_HPP

#include "config.h"

#include "GenerateCodeCpp.hpp"

class GenerateCodeCpp11 : public GenerateCodeCpp {
    public:
        GenerateCodeCpp11 (DiaGram & diagram);

        void writeFunction (const umlOperation & ope,
                            Visibility & curr_visibility);
        void writeConst (const umlClassNode & node);
        void writeEnum (const umlClassNode & node);
        
        ~GenerateCodeCpp11 ();
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
