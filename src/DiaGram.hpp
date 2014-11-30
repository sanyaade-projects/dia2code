/*
Copyright (C) 2014-2014 Vincent Le Garrec <legarrec.vincent@gmail.com>

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

#ifndef DIA_GRAM_HPP
#define DIA_GRAM_HPP

#include <string>
#include <list>

#include "dia2code.hpp"
#include "decls.hpp"

class DiaGram {
    private:
        // Diagram under uml format.
        std::list <umlclassnode> uml;
        // Selection of classes to generate code for.
        std::list <std::string> genClasses;
        // Flag that inverts the above selection.
        bool        invertsel : 1;
        // Set by push() if CORBA stereotypes in use.
        bool        usecorba : 1;
        
        std::list <std::string> tmp_classes;
        std::list <std::string> includes;
        std::list <declaration> decl;
        
        void scan_tree_classes (std::list <std::string> &res);
        void list_classes (umlclassnode & current_class, std::list <umlclassnode> & res);

        /**
         * open_outfile() returns NULL if the file exists and is not rewritten
         * due to a clobber prohibition. Does an exit(1) if serious problems happen.
        */
        int have_include (const char *name);
        void add_include (const char *name);
        void push_include (umlclassnode & node);
    public:
        DiaGram ();
//        DiaGram (DiaGram & diagram) = delete;

        std::list <umlclassnode> & getUml ();

        void addGenClasses (std::list <std::string> classes);
        std::list <std::string> getGenClasses ();

        bool getInvertSel ();
        void setInvertSel (bool invert);

        bool getUseCorba ();
        void setUseCorba (bool corba);

        void push (umlclassnode &node);
        std::list <std::string> getIncludes ();
        void cleanIncludes ();
        void determine_includes (declaration &d);
        
        std::list <declaration>::iterator getDeclBegin ();
        std::list <declaration>::iterator getDeclEnd ();
        ~DiaGram ();
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
