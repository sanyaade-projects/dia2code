/*
Copyright (C) 2014-2014

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef GENERATE_CODE_CPP_HPP
#define GENERATE_CODE_CPP_HPP

#include "DiaGram.hpp"

class GenerateCodeCpp {
    private:
        // Diagram to generate into code.
        DiaGram & dia;
        uint8_t indent : 3;
        uint8_t indentlevel : 3;
        int pass_by_reference (umlclass *cl);
        void gen_class (umlclassnode *node);
        void gen_decl (declaration *d);
        char * cppname (char *name);
        void check_visibility (int *curr_vis, int new_vis);
        void print (char *msg, ...);
        void pbody (char *msg, ...);
        void pboth (char *msg, ...);
        char * spc();
    public:
        GenerateCodeCpp (DiaGram & diagram);

        void generate_code_cpp ();
        
        uint32_t getIndent ();
        void     setIndent (uint32_t spaces);
        
        ~GenerateCodeCpp ();
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
